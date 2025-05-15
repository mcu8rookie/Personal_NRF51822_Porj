
#ifndef __USRCODE_C__
#define __USRCODE_C__

#include"stdio.h"
#include"stdint.h"
#include"UsrCode.h"
#include "nrf_delay.h"
#include"UsrLed.h"
#include "app_uart.h"
#include"UsrUart.h"
#include"nrf_power.h"

uint32_t Reset_Source = 0;
uint32_t MainLoop_Cnt = 0;
uint32_t TimeStamp_Cnt = 0;


void Usr_InitSetup(void)
{
    LED_Init();
    
    LED1_Open();
    LED2_Close();
    LED3_Open();
    LED4_Close();
    
    
    
    Usr_UartInit();
}

int main()
{
    uint8_t cr;
    
    Reset_Source = nrf_power_resetreas_get();
    
    Usr_InitSetup(); 
    
    printf("\n\nMCU Start running-------->\n");
    printf("\nReset_Source = 0x%08X",Reset_Source);
    printf("\nMainLoop_Cnt = ML_Cnt = %d",MainLoop_Cnt);
    printf("\nTimeStamp_Cnt = TS_Cnt = %d\n",TimeStamp_Cnt);
    printf("\nHad initialized.\n");
    
    while(1)
    {   
        MainLoop_Cnt ++;
        
        //printf("\nML_Cnt = %d\t\t",MainLoop_Cnt);
        //printf("\n%d\t\t",MainLoop_Cnt);
        
        LED1_Toggle();
        LED2_Toggle();
        LED3_Toggle();
        LED4_Toggle();
        //nrf_delay_ms(500);
        
        
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

