
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

#include "Usr_Osal.h"


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
    
    #if(defined(DEF_OSAL_EN)&&(DEF_OSAL_EN==1))
    
    Usr_osal_Init();
    
    #else
    
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
    #endif
    
}


#if 0
#include <stdint.h>
#include <math.h>

/* 传感器参数结构体 */
typedef struct 
{
    float baseline;      // 当前基线值
    float noise_rms;     // 噪声有效值(根据标定数据预置)
    uint32_t last_update;// 最后更新时间戳(ms)
    uint16_t sample_interval; // 采样间隔(ms)
    uint8_t freeze_counter;   // 基线冻结计数器
} ABC_Calibrator;

/* ABC算法初始化 */
void ABC_Init(ABC_Calibrator *cal, float init_baseline, float noise_level) 
{
    cal->baseline = init_baseline;
    cal->noise_rms = noise_level;
    cal->sample_interval = 100; // 默认100ms采样间隔
    cal->freeze_counter = 0;
}

/* 带温度补偿的低通滤波器 */
float low_pass_filter(float input, float prev_output, float alpha, float temp_comp) 
{
    // 温度补偿系数应用(需根据具体传感器特性调整)
    return alpha * prev_output + (1 - alpha) * input*temp_comp ;

//return prev_output + (1 - alpha)(input-prev_output);
}

/* 基线自动校准核心算法 */
float ABC_Update(ABC_Calibrator *cal, float raw_value, float temperature) 
{
    const float alpha_slow = 0.999f;   // 慢速更新系数
    const float alpha_fast = 0.950f;   // 快速响应系数
    static float filtered_value = 0;
    
    // 温度补偿计算(示例:每℃补偿0.1%)
    float temp_comp = 1.0f + (temperature - 25.0f) * 0.001f;
    
    // 一级滤波消除高频噪声
    filtered_value = low_pass_filter(raw_value, filtered_value, 0.85f, temp_comp);
    
    // 基线更新逻辑
    if(cal->freeze_counter == 0) 
    {
        float delta = fabsf(filtered_value - cal->baseline);
        
        // 噪声带检测(3σ原则)
        if(delta < 3 * cal->noise_rms) 
        {
            // 慢速基线追踪
            cal->baseline = low_pass_filter(filtered_value, cal->baseline, alpha_slow, 1.0f);
        } 
        else 
        {
            // 快速响应路径
            float emergency_shift = filtered_value - cal->baseline;
            cal->baseline += emergency_shift * (1 - alpha_fast);
            cal->freeze_counter = 10; // 冻结10个采样周期
        }
    } 
    else 
    {
        cal->freeze_counter--;
    }
    
    // 24小时强制复位机制
    static uint32_t last_reset_time = 0;
    if((HAL_GetTick() - last_reset_time) > 86400000) 
    {   // 24小时
        cal->baseline = filtered_value;
        last_reset_time = HAL_GetTick();
    }
    
    return filtered_value - cal->baseline; // 返回校准后值
}

/&zwnj;*********************** 使用示例 ************************&zwnj;/
int main(void) 
{
    ABC_Calibrator gas_sensor;
    
    // 初始化: 设初始基线500,噪声水平2.5
    ABC_Init(&gas_sensor, 500.0f, 2.5f); 
    
    while(1) 
    {
        float raw_adc = read_adc_channel(0);      // 读取ADC原始值
        float temp = read_temperature_sensor();  // 读取温度传感器
        
        // 执行基线校准
        float calibrated = ABC_Update(&gas_sensor, raw_adc, temp);
        
        // 应用层处理校准后的信号
        process_gas_concentration(calibrated);
        
        HAL_Delay(gas_sensor.sample_interval);
    }
}

#endif


#endif

