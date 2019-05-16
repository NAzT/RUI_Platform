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

#if defined(LORA_81x_TEST) || defined(LORA_4600_TEST)
extern uint8_t JOIN_FLAG;
extern lora_cfg_t g_lora_cfg_t;
int lora_send_ok = 0;
#endif

#if defined(BC95G_TEST) || defined(M35_TEST) || defined(BG96_TEST)
extern uint8_t cmd[128];
extern xSemaphoreHandle xBinarySemaphore_iot;
#endif

extern double gps_lat;
extern double gps_lon;  

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
#if defined(LORA_81x_TEST) || defined(LORA_4600_TEST)
    if(g_lora_cfg_t.sof == LORA_CONFIG_MAGIC)
    {
       region_init();
    }

#endif
    NRF_LOG_INFO("START...........");
    NRF_LOG_INFO("START...........");
    NRF_LOG_INFO("START...........");
    NRF_LOG_INFO("START...........");
    NRF_LOG_INFO("START...........");
    while(1)
    {
        NRF_LOG_INFO("++++++++++++++++test begin++++++++++++++++\r\n");
        power_save_close();
#if defined(SLEEP_MODE) && !defined(LORA_81x_TEST) && !defined(LORA_4600_TEST)
        power_save_open();
#endif
        NRF_LOG_INFO("++++++++++++++++test end++++++++++++++++\r\n");
        vTaskDelay(60000);
    }
}
