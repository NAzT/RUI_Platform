#include "board_basic.h"
#include "boards.h"
#include "nrf_delay.h"
#include "nrf_drv_rtc.h"
#include "nrf_rtc.h"
#include "FreeRTOS.h"
#include "task.h"
#include <string.h>
#include "sensor.h"
#include "itracker.h"
#include "nrf_log.h"


#if defined(BC95G_TEST) || defined(M35_TEST) || defined(BG96_TEST)
extern uint8_t cmd[128];

extern xSemaphoreHandle xBinarySemaphore_iot;
#endif

extern double gps_lat;
extern double gps_lon;  

void test_task(void * pvParameter)
{

    uint8_t gps_rsp[128] = {0};
    double temp = 0;
    double humidity = 0;
    double pressure = 0;
    int x = 0;
    int y = 0;
    int z = 0;
    float light = 0;
    double lat = 0;
    double lon = 0;
    NRF_LOG_INFO("x test begin++++++++++++++++\r\n");
    while(1)
    {
        NRF_LOG_INFO("++++++++++++++++test begin++++++++++++++++\r\n");
        power_save_close();

        // itracker_function.acceleration_get(&x,&y,&z);
        // NRF_LOG_INFO("acceleration x,y,z = %d mg,%d mg,%d mg",x,y,z); 

        NRF_LOG_INFO("Z");
        memset(gps_rsp,0,128);
        itracker_function.gps_get(gps_rsp,128);
        vTaskDelay(2000);
        NRF_LOG_INFO("Y");
        // NRF_LOG_INFO("iiigps info :%lf,%lf;",gps_lat,gps_lon); 
        uint8_t msg_chunk;
        
//        __SEV();
//        __WFE();
//        __WFE();
        // Handle data that come from UART.
        while (app_uart_get(&msg_chunk) == NRF_SUCCESS)
        {
//            if (app_fifo_put(&m_nfc_tx_fifo, msg_chunk) != NRF_SUCCESS)
//            {
//                NRF_LOG_WARNING("NFC TX FIFO buffer overflow");
//            }
            NRF_LOG_INFO("%c", msg_chunk);
        }
#if defined(SLEEP_MODE) && !defined(LORA_TEST)
        power_save_open();
#endif
        NRF_LOG_INFO("++++++++++++++++test end++++++++++++++++\r\n");
        vTaskDelay(5000);
    }
}
