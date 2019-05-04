#include <stdbool.h>
#include "nrf_assert.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "board_basic.h"
#include <stddef.h>
#include <string.h>
#include "app_error.h"
#include "nrf_soc.h"
#include "itracker.h"
#include "gps.h"
#include "bme280.h"
#ifdef BG96_TEST
#include "bg96.h"
#endif
#ifdef BC95G_TEST
#include "bc95-g.h"
#endif
#ifdef M35_TEST
#include "m35.h"
#endif
#include "hal_uart.h"

double gps_lat = 0;
double gps_lon = 0;   
#ifdef LORA_TEST
uint32_t lora_send(uint8_t *cmd);
#endif

itracker_function_stru itracker_function;
extern GSM_RECEIVE_TYPE g_type;


#ifdef LIS3DH_TEST
uint32_t get_lis3dh_data_bus(int *x, int *y, int *z)
{
    uint32_t ret = 0;
    if(x == NULL || y == NULL || z == NULL)
    {
        return 1;
    }
    ret = lis3dh_twi_init();
    if(ret != NRF_SUCCESS)
    {
        NRF_LOG_INFO( "lis3dh_twi_init fail %d\r\n", ret);
    }
    get_lis3dh_data(x,y,z);
	*x =*x * 4000/65536;
	*y =*y * 4000/65536;
	*z =*z * 4000/65536;	
    return ret;
}
#endif
#ifdef BG96_TEST
uint32_t gps_data_get_bus(uint8_t *data, uint32_t len)
{
    
    uint32_t ret = 0;
    if(data == NULL || len < 0)
    {
        return 1;
    }
    gps_data_get(data,len);
	memcpy(data,&data[14],len-14);
    if (GpsParseGpsData(data, len))
    {
        GpsGetLatestGpsPositionDouble(&gps_lat, &gps_lon);
    }
    return ret;
}
extern char GSM_RSP[1600];
void Gsm_wait_response(uint8_t *rsp, uint32_t len, uint32_t timeout,GSM_RECEIVE_TYPE type)
{
    if(rsp == NULL || len < 0)
    {
        return;
    }
    g_type = type;
    memset(GSM_RSP, 0, 1600);
    Gsm_WaitRspOK(GSM_RSP, timeout, true);
    NRF_LOG_INFO("%s\r\n",GSM_RSP);
}
#endif
#ifdef L70R_TEST
uint32_t gps_data_get_bus(uint8_t *data, uint32_t len)
{
    uint32_t ret = 0;
    if(data == NULL || len < 0)
    {
        return 1;
    }
    rak_uart_init(GPS_USE_UART,GPS_RXD_PIN,GPS_TXD_PIN,UART_BAUDRATE_BAUDRATE_Baud9600);
    delay_ms(2000);
    gps_data_get(data,len);
    delay_ms(800);
#ifdef M35_TEST
    rak_uart_init(GSM_USE_UART,GSM_RXD_PIN,GSM_TXD_PIN,UART_BAUDRATE_BAUDRATE_Baud115200);
#endif
#ifdef BC95G_TEST
    rak_uart_init(GSM_USE_UART,GSM_RXD_PIN,GSM_TXD_PIN,UART_BAUDRATE_BAUDRATE_Baud9600);
#endif
    return ret;
}
#endif
#if defined(BC95G_TEST) || defined(M35_TEST)
void Gsm_wait_response(uint8_t *rsp, uint32_t len, uint32_t timeout,GSM_RECEIVE_TYPE type)
{
    if(rsp == NULL || len < 0)
    {
        return;
    }
    g_type = type;
    Gsm_WaitRspOK(rsp, timeout, true);
}
#endif


void itracker_function_init()
{
    memset(&itracker_function,0,sizeof(itracker_function));
#ifdef LIS3DH_TEST
    itracker_function.acceleration_get = get_lis3dh_data_bus;
#endif

#if defined(L70R_TEST) ||  defined(BG96_TEST) ||  defined(MAX7_TEST)
    itracker_function.gps_get = gps_data_get_bus;
#endif

#if defined(BC95G_TEST) || defined(M35_TEST) || defined(BG96_TEST)
    itracker_function.communicate_send = Gsm_print;
    itracker_function.communicate_response = Gsm_wait_response;
#endif

#ifdef LORA_TEST
    itracker_function.communicate_send = lora_send;
#endif
}