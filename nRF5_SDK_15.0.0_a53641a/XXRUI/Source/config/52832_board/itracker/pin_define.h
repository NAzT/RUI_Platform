
#ifndef __PIN_DEFINE_ITRACKER_52832_H__
#define __PIN_DEFINE_ITRACKER_52832_H__

/**
 * Pin definitions
 */
#define RADIO_DIO_0		P7
#define RADIO_DIO_1		P8
#define RADIO_DIO_2		P9
#define RADIO_DIO_3		P10

#define RADIO_NSS		P14
#define RADIO_MOSI		P13
#define RADIO_MISO		P12
#define RADIO_SCK		P11

#define RADIO_RESET		P6
#define RADIO_TCXO		P5
#define RADIO_RF_CTX	        P23
#define RADIO_RF_CPS	        P22

#define ASSERT_ERROR	0xA55EA55E

#define USE_FULL_ASSERT
#ifdef  USE_FULL_ASSERT
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
	#define assert_param(expr)	((expr) ? (void)0U : app_error_handler(ASSERT_ERROR, __LINE__, (const uint8_t *)__FILE__))
#else
	#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

	
	//#define BC95
//#define M35

/*
		UART PIN Assignment
		P028_UART1_RX
		P029_UART1_TX

*/
#define             LOG_RXD_PIN                        28
#define             LOG_TXD_PIN                        29

/*
		GSM PIN Assignment
		GSM_PWR_ON		--	P0.06
		GSM_TXD			--	P0.12
		GSM_RESET		--	P0.14
		GSM_PWRKEY		--	P0.15
		GSM_RXD			--	P0.20

*/
	


#define             GSM_PWR_ON_PIN                        6
#define             GSM_RESET_PIN                        14
#define             GSM_PWRKEY_PIN                        15

#if defined(BG96_TEST)
#define             GSM_TXD_PIN                        9
#define             GSM_RXD_PIN                        7
#endif
#if defined(M35_TEST)
#define             GSM_TXD_PIN                        12
#define             GSM_RXD_PIN                        20
#endif
#if defined(BC95G_TEST)
#define             GSM_TXD_PIN                        20
#define             GSM_RXD_PIN                        12
#endif


#define             GSM_PWR_ON                     nrf_gpio_pin_write ( GSM_PWR_ON_PIN, 1 )
#define             GSM_PWR_OFF                      nrf_gpio_pin_write ( GSM_PWR_ON_PIN, 0 )

#define             GSM_PWRKEY_HIGH                           nrf_gpio_pin_write ( GSM_PWRKEY_PIN, 0 )
#define             GSM_PWRKEY_LOW                            nrf_gpio_pin_write ( GSM_PWRKEY_PIN, 1 )

#define             GSM_RESET_HIGH                           nrf_gpio_pin_write ( GSM_RESET_PIN, 0 )
#define             GSM_RESET_LOW                            nrf_gpio_pin_write ( GSM_RESET_PIN, 1 )

#define 			POWER_ON       GSM_PWR_OFF;\
    delay_ms(200);\
    GSM_PWR_ON;\
    GSM_RESET_HIGH;\
    delay_ms(60);		\
    GSM_PWRKEY_LOW;\
    delay_ms(500); \
    GSM_PWRKEY_HIGH;\
    delay_ms(500)
/*
		GPS PIN Assignment
		GPS_STANDBY		--	P0.07
		GPS_TXD			--	P0.08
		GPS_RXD		--	P0.09(nfc default)
		GPS_PWR_ON		--	P0.10
		GPS_RESET		--	P0.31

*/
#define             GPS_STANDBY_PIN                        7
#define             GPS_TXD_PIN                        9
#define             GPS_RXD_PIN                        8
#define 		  GPS_PWR_ON_PIN											10
#define             GPS_RESET_PIN                        31

#define             GPS_PWR_ON                     nrf_gpio_pin_write ( GPS_PWR_ON_PIN, 1 )
#define             GPS_PWR_OFF                      nrf_gpio_pin_write ( GPS_PWR_ON_PIN, 0 )

#define             GPS_RESET_HIGH                           nrf_gpio_pin_write ( GPS_RESET_PIN, 1 )
#define             GPS_RESET_LOW                            nrf_gpio_pin_write ( GPS_RESET_PIN, 0 )


/*
		lis3dh PIN Assignment
		LIS3DH_SCL		--	P0.18
		LIS3DH_SDA		--	P0.19
		LIS3DH_INT1		--	P0.25
		LIS3DH_RES		--	P0.26
		LIS3DH_INT2		--	P0.27
		
*/
#define             LIS3DH_TWI_SCL_PIN                        18
#define             LIS3DH_TWI_SDA_PIN                        19
#define             LIS3DH_INT1_PIN                        25
#define 						LIS3DH_RES_PIN											26
#define             LIS3DH_INT2_PIN                        27
#define             LIS3DH_INT1_THRESHOLD          5
/*
		lis2mdl PIN Assignment
		LIS2MDL_SCL		--	P0.11
		LIS2MDL_SDA		--	P0.13
		LIS2MDL_INT		--	P0.16
		
*/
#define             LIS2MDL_TWI_SCL_PIN                        11
#define             LIS2MDL_TWI_SDA_PIN                        13
#define             LIS2MDL_INT_PIN                        16


#endif  // __PIN_DEFINE_ITRACKER_H__