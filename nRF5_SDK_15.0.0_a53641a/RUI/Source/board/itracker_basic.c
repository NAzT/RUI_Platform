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
#include "bg96.h"
#include "hal_uart.h"

double gps_lat = 0;
double gps_lon = 0;   

itracker_function_stru itracker_function;
extern GSM_RECEIVE_TYPE g_type;

uint32_t gps_data_get_bus(uint8_t *data, uint32_t len)
{
    uint32_t ret = 0;
    uint8_t i = 0;
    if(data == NULL || len < 0)
    {
        return 1;
    }
    gps_data_get(data,len);
	memcpy(data,&data[14],len-14);
    for (i = 0; data[i] !=0; i++)
    {
        
        if (data[i] == '\r' || data[i] == '\n')
        {

            break;
        }
    }
    memset(&data[i],0,127-i);
    //gps_parse(data);

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

void itracker_function_init()
{
    memset(&itracker_function,0,sizeof(itracker_function));
    itracker_function.communicate_send = Gsm_print;
    itracker_function.communicate_response = Gsm_wait_response; 
}