
#ifndef __USR_LED_C__
#define __USR_LED_C__


#include"Usr_Code.h"
#include"nrf_gpio.h"
#include"Usr_Led.h"

#include "multi_button.h"


void LED_Init(void)
{
    nrf_gpio_cfg_output(DEF_LED1);
    nrf_gpio_cfg_output(DEF_LED2);
    nrf_gpio_cfg_output(DEF_LED3);
    nrf_gpio_cfg_output(DEF_LED4);
    
    nrf_gpio_cfg_output(DEF_DBGIO1);
    nrf_gpio_cfg_output(DEF_DBGIO2);
    
    LED1_Open();
    LED2_Close();
    LED3_Open();
    LED4_Close();
}
void LED1_Open(void)
{
    nrf_gpio_pin_clear(DEF_LED1);
}
void LED1_Close(void)
{
    nrf_gpio_pin_set(DEF_LED1);
}
void LED1_Toggle(void)
{
    nrf_gpio_pin_toggle(DEF_LED1);
}
void LED2_Open(void)
{
    nrf_gpio_pin_clear(DEF_LED2);
}
void LED2_Close(void)
{
    nrf_gpio_pin_set(DEF_LED2);
}
void LED2_Toggle(void)
{
    nrf_gpio_pin_toggle(DEF_LED2);
}
void LED3_Open(void)
{
    nrf_gpio_pin_clear(DEF_LED3);
}
void LED3_Close(void)
{
    nrf_gpio_pin_set(DEF_LED3);
}
void LED3_Toggle(void)
{
    nrf_gpio_pin_toggle(DEF_LED3);
}
void LED4_Open(void)
{
    nrf_gpio_pin_clear(DEF_LED4);
}
void LED4_Close(void)
{
    nrf_gpio_pin_set(DEF_LED4);
}
void LED4_Toggle(void)
{
    nrf_gpio_pin_toggle(DEF_LED4);
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



#define DEF_KEY_ACTIVE_LEVEL    (0)
#define DEF_TOUCH_ACTIVE_LEVEL  (1)

uint8_t Key_TimeCnt;

struct Button Key1;
struct Button Key2;
struct Button Key3;
struct Button Key4;

struct Button Touch1;

uint8_t Usr_Read_Key1_State(uint8_t nbr)
{
    nbr = nbr;
    return nrf_gpio_pin_read(DEF_KEY1);
}

uint8_t Usr_Read_Key2_State(uint8_t nbr)
{
    return nrf_gpio_pin_read(DEF_KEY2);
}

uint8_t Usr_Read_Key3_State(uint8_t nbr)
{
    return nrf_gpio_pin_read(DEF_KEY3);
}

uint8_t Usr_Read_Key4_State(uint8_t nbr)
{
    return nrf_gpio_pin_read(DEF_KEY4);
}

uint8_t Usr_Read_Touch1_State(uint8_t nbr)
{
    return nrf_gpio_pin_read(DEF_TOUCH1);
}

void Usr_Key1_Up_Func(void* ptr)
{
    printf("\nKey1 up event.");
}

void Usr_Key2_Up_Func(void* ptr)
{
    printf("\nKey2 up event.");
}

void Usr_Key3_Up_Func(void* ptr)
{
    printf("\nKey3 up event.");
}

void Usr_Key4_Up_Func(void* ptr)
{
    printf("\nKey4 up event.");
}

void Usr_Touch1_Up_Func(void)
{
    printf("\nTouch1 up event.");
}




void Usr_Key_Init(void)
{
    //printf("\nInit keys function.");
    
    nrf_gpio_cfg_input(DEF_KEY1,NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(DEF_KEY2,NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(DEF_KEY3,NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(DEF_KEY4,NRF_GPIO_PIN_PULLUP);
    
    nrf_gpio_cfg_input(DEF_TOUCH1,NRF_GPIO_PIN_PULLUP);
    
    #if 1
    button_init(&Key1,Usr_Read_Key1_State,DEF_KEY_ACTIVE_LEVEL,1);
    button_init(&Key2,Usr_Read_Key2_State,DEF_KEY_ACTIVE_LEVEL,2);
    button_init(&Key3,Usr_Read_Key3_State,DEF_KEY_ACTIVE_LEVEL,3);
    button_init(&Key4,Usr_Read_Key4_State,DEF_KEY_ACTIVE_LEVEL,4);
    
    button_init(&Touch1,Usr_Read_Touch1_State,DEF_TOUCH_ACTIVE_LEVEL,5);
    #endif
    
    #if 1
    button_attach(&Key1,PRESS_UP,Usr_Key1_Up_Func);
    button_attach(&Key2,PRESS_UP,Usr_Key2_Up_Func);
    button_attach(&Key3,PRESS_UP,Usr_Key3_Up_Func);
    button_attach(&Key4,PRESS_UP,Usr_Key4_Up_Func);
    
    button_attach(&Touch1,PRESS_UP,Usr_Touch1_Up_Func);
    #endif
    
    #if 1
    button_start(&Key1);
    button_start(&Key2);
    button_start(&Key3);
    button_start(&Key4);
    
    button_start(&Touch1);
    #endif
    
}


void Usr_Key_MainLoop(void)
{   
    static uint8_t nbr = 0;
    
    if(Key_TimeCnt>=5)
    {
        Key_TimeCnt = 0;
        
        // printf("\nkf %d,",nbr++);
        
        button_ticks();
        
        
        #if 0
        LED1_Toggle();
        LED2_Toggle();
        LED3_Toggle();
        LED4_Toggle();
        //nrf_delay_ms(500);
        #endif
        
        #if 0
        if(nrf_gpio_pin_read(DEF_KEY1) == 0)
        {
            while(nrf_gpio_pin_read(DEF_KEY1) == 0);
            LED1_Toggle();
        }
        if(nrf_gpio_pin_read(DEF_KEY2) == 0)
        {
            while(nrf_gpio_pin_read(DEF_KEY2) == 0);
            LED2_Toggle();
        }
        if(nrf_gpio_pin_read(DEF_KEY3) == 0)
        {
            while(nrf_gpio_pin_read(DEF_KEY3) == 0);
            LED3_Toggle();
        }
        if(nrf_gpio_pin_read(DEF_KEY4) == 0)
        {
            while(nrf_gpio_pin_read(DEF_KEY4) == 0);
            LED4_Toggle();
        }
        //nrf_delay_ms(500);
        #endif
    }
}

#endif

