
#ifndef __USR_CODE_C__
#define __USR_CODE_C__

#include "stdio.h"
#include "stdint.h"
#include "Usr_Code.h"
#include "nrf_delay.h"
#include "Usr_Led.h"
#include "app_uart.h"
#include "Usr_Uart.h"
#include "nrf_power.h"

#include "Usr_Timer.h"
#include "Usr_I2C.h"

uint32_t Reset_Source = 0;
uint32_t MainLoop_Cnt = 0;
uint32_t TimeStamp_Cnt = 0;


void Usr_InitSetup(void)
{
    LED_Init();
    
    Usr_UartInit();
    
    Usr_Timer_InitSetup();
    
    Usr_I2C_InitSetup();
}

int main()
{
    uint8_t cr;
    
    Reset_Source = nrf_power_resetreas_get();
    
    Usr_InitSetup(); 
    
    printf("\n\nMCU Start running-------->\n");
    printf("\nReset_Source = 0x%08X",Reset_Source);
    printf("\nHad initialized.\n");
    
    while(1)
    {   
        
        if(TimeStamp_Cnt>=1000)
        {   
            TimeStamp_Cnt = 0;
            
            MainLoop_Cnt ++;
            printf("\nML_Cnt,%d,",MainLoop_Cnt);
            //printf("\n%d\t\t",MainLoop_Cnt);
            
            LED1_Toggle();
            LED2_Toggle();
            LED3_Toggle();
            LED4_Toggle();
            //nrf_delay_ms(500);
            
            
            Usr_I2C_MainLoop();
        }
        
        //while(app_uart_get(&cr) != NRF_SUCCESS);
        //while(app_uart_put(cr) != NRF_SUCCESS);
        if(app_uart_get(&cr) == NRF_SUCCESS)
        {
            //while(app_uart_put(cr) != NRF_SUCCESS);
            app_uart_put(cr);
        }
        
        
    }
}

#endif

