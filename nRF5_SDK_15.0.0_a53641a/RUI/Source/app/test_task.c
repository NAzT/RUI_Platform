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

#ifndef ACCESS_NET_TEST
void test_task(void * pvParameter)
{
    uint8_t gps_rsp[128] = {0};
    uint8_t lora_data[128] = {0};
    uint8_t lora_len_acc = 0;
    uint8_t lora_len_t_h = 0;
    uint8_t lora_len_gps = 0;
    double temp = 0;
    double humidity = 0;
    double pressure = 0;
    int x = 0;
    int y = 0;
    int z = 0;
    float magnetic_x = 0;
    float magnetic_y = 0;
    float magnetic_z = 0;
    float light = 0;
    double lat = 0;
    double lon = 0;
    while(1)
    {
        NRF_LOG_INFO("++++++++++++++++test begin++++++++++++++++\r\n");
        power_save_close();

#ifdef LIS3DH_TEST
        itracker_function.acceleration_get(&x,&y,&z);
        NRF_LOG_INFO("acceleration x,y,z = %d mg,%d mg,%d mg",x,y,z);

#endif
#ifdef LIS2MDL_TEST
        itracker_function.magnetic_get(&magnetic_x,&magnetic_y,&magnetic_z);
        NRF_LOG_INFO("magnetic x,y,z = %d,%d,%d\r\n",magnetic_x,magnetic_y,magnetic_z);
#endif

#if defined(L70R_TEST) ||  defined(BG96_TEST) || defined(MAX7_TEST)

        memset(gps_rsp,0,128);
        itracker_function.gps_get(gps_rsp,128);
        vTaskDelay(2000);
        NRF_LOG_INFO("iiigps info :%lf,%lf;",gps_lat,gps_lon);

#endif 

#if defined(SLEEP_MODE) && !defined(LORA_TEST)
        power_save_open();
#endif
        NRF_LOG_INFO("++++++++++++++++test end++++++++++++++++\r\n");
        vTaskDelay(5000);
    }
}

#else 
#endif