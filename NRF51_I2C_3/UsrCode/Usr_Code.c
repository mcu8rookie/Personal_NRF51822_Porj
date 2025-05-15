
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


uint8_t YearMonthDateSN[12] = 
{
    DEF_YMDSN_YEAR1,
    DEF_YMDSN_YEAR2,
    DEF_YMDSN_CRC1,
    
    DEF_YMDSN_MONTH,
    DEF_YMDSN_DATE,
    DEF_YMDSN_CRC2,
    
    DEF_YMDSN_SN1,
    DEF_YMDSN_SN2,
    DEF_YMDSN_CRC3,
    
    DEF_YMDSN_SN3,
    DEF_YMDSN_SN4,
    DEF_YMDSN_CRC4,
    
};

uint32_t Reset_Source = 0;
uint32_t MainLoop_Cnt = 0;
uint32_t TimeStamp_Cnt = 0;


void Usr_InitSetup(void)
{
    LED_Init();
    
    Usr_UartInit();
    
    Usr_Timer_InitSetup();
    
    Usr_Key_Init();
    
    Usr_I2C_InitSetup();
    
    
}

uint16_t a,b;
uint16_t c = 124;
int16_t d;

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
        Usr_Key_MainLoop();
        
        if(TimeStamp_Cnt>=1000)
        {   
            TimeStamp_Cnt = 0;
            
            MainLoop_Cnt ++;
            printf("\nML_Cnt,%d,",MainLoop_Cnt);
            
            a = 12;
            b = MainLoop_Cnt;
            
            d = a - b;
            //printf("\nd = %d,",d);
            
            #if 0
            LED1_Toggle();
            LED2_Toggle();
            LED3_Toggle();
            LED4_Toggle();
            //nrf_delay_ms(500);
            #endif
            
        }
        
        //while(app_uart_get(&cr) != NRF_SUCCESS);
        //while(app_uart_put(cr) != NRF_SUCCESS);
        if(app_uart_get(&cr) == NRF_SUCCESS)
        {
            //while(app_uart_put(cr) != NRF_SUCCESS);
            app_uart_put(cr);
            
            Usr_I2C_MainLoop(cr);
        }
    }
}

#endif

