#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "nordic_common.h"
#include "nrf.h"
#include "nrf_sdh.h"
#include "app_timer.h"
#include "fds.h"
#include "app_uart.h"
#include "app_util_platform.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "board_basic.h"
#include "nrf_power.h"
#include "hal_uart.h"



void Gps_Gpio_Init()
{
    nrf_gpio_cfg_output(GPS_PWR_ON_PIN);
    nrf_gpio_cfg_output(GPS_RESET_PIN);
    nrf_gpio_cfg_input(GPS_STANDBY_PIN,NRF_GPIO_PIN_PULLUP);    
}

void Gps_power_up( void )
{
    GPS_PWR_OFF;
    delay_ms(1000);
    GPS_PWR_ON;

    GPS_RESET_LOW;
    delay_ms(2000);
    GPS_RESET_HIGH;
}

void Gps_Init(void)
{
    Gps_Gpio_Init();
    Gps_power_up();
}

void Gps_standby(void)
{
     nrf_gpio_cfg_output(GPS_STANDBY_PIN);
     nrf_gpio_pin_write (GPS_STANDBY_PIN, 0);
}

void sensors_init()
{
    int ret;
    // init gsm
    // Gsm_Init();
    Gps_Init();
}
