
#ifndef __USR_LED_C__
#define __USR_LED_C__


#include"Usr_Code.h"
#include"nrf_gpio.h"
#include"Usr_Led.h"

void LED_Init(void)
{
	nrf_gpio_cfg_output(LED_0);
	nrf_gpio_cfg_output(LED_1);
	nrf_gpio_cfg_output(LED_2);
	nrf_gpio_cfg_output(LED_3);
	
	nrf_gpio_cfg_output(DEF_DBGIO1);
	nrf_gpio_cfg_output(DEF_DBGIO2);
	
	LED1_Open();
	LED2_Close();
	LED3_Open();
	LED4_Close();
}
void LED1_Open(void)
{
	nrf_gpio_pin_clear(LED_0);
}
void LED1_Close(void)
{
	nrf_gpio_pin_set(LED_0);
}
void LED1_Toggle(void)
{
	nrf_gpio_pin_toggle(LED_0);
}
void LED2_Open(void)
{
	nrf_gpio_pin_clear(LED_1);
}
void LED2_Close(void)
{
	nrf_gpio_pin_set(LED_1);
}
void LED2_Toggle(void)
{
	nrf_gpio_pin_toggle(LED_1);
}
void LED3_Open(void)
{
	nrf_gpio_pin_clear(LED_2);
}
void LED3_Close(void)
{
	nrf_gpio_pin_set(LED_2);
}
void LED3_Toggle(void)
{
	nrf_gpio_pin_toggle(LED_2);
}
void LED4_Open(void)
{
	nrf_gpio_pin_clear(LED_3);
}
void LED4_Close(void)
{
	nrf_gpio_pin_set(LED_3);
}
void LED4_Toggle(void)
{
	nrf_gpio_pin_toggle(LED_3);
}


void Usr_Dbg_IO(uint8_t nbr,uint8_t state)
{
	switch(nbr)
	{
		case 1:
		{
			if(state == 0)
			{
				nrf_gpio_pin_clear(DEF_DBGIO1);
			}
			else if(state == 1)
			{
				nrf_gpio_pin_set(DEF_DBGIO1);
			}
			else
			{
				nrf_gpio_pin_toggle(DEF_DBGIO1);
			}
		}
		break;
		
		case 2:
		{
			if(state == 0)
			{
				nrf_gpio_pin_clear(DEF_DBGIO2);
			}
			else if(state == 1)
			{
				nrf_gpio_pin_set(DEF_DBGIO2);
			}
			else
			{
				nrf_gpio_pin_toggle(DEF_DBGIO2);
			}
		}
		break;
		
		default:
			
		break;
	}
}


#endif

