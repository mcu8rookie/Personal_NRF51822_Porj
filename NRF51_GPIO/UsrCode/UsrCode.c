
#if 0
Armcc V5.05;
CMSIS_Core 			
OK:	4.1.0;	4.3.0;	5.6.0;
NG:	
Device_Startup,	
OK:	8.5.0; 	8.11.0;	8.17.0;
NG: 8.35.0;	8.44.1;	8.59.0;
#endif

#ifndef __USRCODE_C__
#define __USRCODE_C__

#include"UsrCode.h"
#include"nrf_gpio.h"
#include "nrf_delay.h"
#include"UsrLed.h"

int main()
{
    LED_Init();
    
    while(1)
    {
				#if 0
        LED1_Toggle();
        LED2_Toggle();
        LED3_Toggle();
        LED4_Toggle();
        nrf_delay_ms(DEF_LED_DELAYTIME);
				#endif
				
				#if 1
				nrf_gpio_pin_clear(LED_0);
				nrf_gpio_pin_set(LED_1);
				nrf_gpio_pin_set(LED_2);
				nrf_gpio_pin_set(LED_3);
				nrf_delay_ms(DEF_LED_DELAYTIME);
			
				nrf_gpio_pin_set(LED_0);
				nrf_gpio_pin_clear(LED_1);
				nrf_gpio_pin_set(LED_2);
				nrf_gpio_pin_set(LED_3);
				nrf_delay_ms(DEF_LED_DELAYTIME);
			
				nrf_gpio_pin_set(LED_0);
				nrf_gpio_pin_set(LED_1);
				nrf_gpio_pin_clear(LED_2);
				nrf_gpio_pin_set(LED_3);
				nrf_delay_ms(DEF_LED_DELAYTIME);
				
				nrf_gpio_pin_set(LED_0);
				nrf_gpio_pin_set(LED_1);
				nrf_gpio_pin_set(LED_2);
				nrf_gpio_pin_clear(LED_3);
				nrf_delay_ms(DEF_LED_DELAYTIME);
				
				#endif
    }
}

#endif

