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
#include "hal_uart.h"

double gps_lat = 0;
double gps_lon = 0;   

itracker_function_stru itracker_function;
extern GSM_RECEIVE_TYPE g_type;

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

// uint32_t gps_data_get_bus(uint8_t *data, uint32_t len)
// {
//     NRF_LOG_INFO("NAT gps_data_get_bus");

//     uint32_t ret = 0;
//     if(data == NULL || len < 0)
//     {
//         return 1;
//     }
//     NRF_LOG_INFO("[2] NAT gps_data_get_bus");
//     rak_uart_init(GPS_USE_UART,GPS_RXD_PIN,GPS_TXD_PIN,UART_BAUDRATE_BAUDRATE_Baud9600);
//     delay_ms(500);
//     gps_data_get(data,len);
//     NRF_LOG_INFO("[2] NAT gps_data_get_bus");
// 	memcpy(data,&data[14],len-14);
//     NRF_LOG_INFO(">%s", data);
//     // if (GpsParseGpsData(data, len))
//     // {
//     //     GpsGetLatestGpsPositionDouble(&gps_lat, &gps_lon);
//     // }
//     NRF_LOG_INFO("[4] NAT gps_data_get_bus");
//     return ret;
// }
// #if defined(BC95G_TEST) || defined(M35_TEST)
// void Gsm_wait_response(uint8_t *rsp, uint32_t len, uint32_t timeout,GSM_RECEIVE_TYPE type)
// {
//     if(rsp == NULL || len < 0)
//     {
//         return;
//     }
//     g_type = type;
//     Gsm_WaitRspOK(rsp, timeout, true);
// }
// #endif
uint32_t gps_data_get_bus(uint8_t *data, uint32_t len)
{
    NRF_LOG_INFO("gps_data_get_bus len=%lu\r\n", len);
    uint32_t ret = 0; 
    if(data == NULL || len < 0)
    {
        return 1;
    }
    NRF_LOG_INFO("GET DATA len=%lu\r\n", len);
    NRF_LOG_INFO("GET DATA %s\r\n", data);
    for(int i =0 ; i < len; i++) {
        NRF_LOG_INFO("%c", data[i]); 
    }

    // gps_data_get(data,len);

    return ret;
}


void itracker_function_init()
{
    NRF_LOG_INFO("itracker_function_init");
    memset(&itracker_function,0,sizeof(itracker_function));
    rak_uart_init(GPS_USE_UART, GPS_RXD_PIN, GPS_TXD_PIN, UART_BAUDRATE_BAUDRATE_Baud9600);
    // rak_uart_init(GPS_USE_UART,GPS_RXD_PIN,GPS_TXD_PIN,UART_BAUDRATE_BAUDRATE_Baud9600);
    itracker_function.gps_get = gps_data_get_bus;
    NRF_LOG_INFO("/itracker_function_init");

    // itracker_function.communicate_send = Gsm_print;
    // itracker_function.communicate_response = Gsm_wait_response;
}