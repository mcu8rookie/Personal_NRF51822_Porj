#ifndef __USR_OSAL_C__
#define __USR_OSAL_C__

#include "Usr_Config.h"

#include "Usr_Debug.h"

#include "multi_button.h"


#if(defined(DEF_OSAL_EN)&&(DEF_OSAL_EN==1))

#include "type.h"
#include "osal.h"
#include "osal_timer.h"
#include "osal_event.h"
#include "osal_memory.h"
#include "osal_msg.h"
#include "Usr_Osal.h"

#include <stdio.h>

uint32_t Usr_Osal_Timestamp_Real;
uint32_t Usr_Osal_Timestamp_Old;
uint32_t Usr_Osal_Timestamp_Now;


void Usr_osal_Init(void)
{
    //系统硬件、外设等初始化
    
    //禁止中断
    ///HAL_DISABLE_INTERRUPTS();
    
    //osal操作系统初始化
    osal_init_system();
    
    //添加任务
    ///osal_add_Task(print_task_init, print_task_event_process, 1);
    ///osal_add_Task(statistics_task_init, statistics_task_event_process, 2);
    osal_add_Task(Task_Print_Init,Task_Print_Event_Process,1);
    osal_add_Task(Task_Key_Init,Task_Key_Event_Process,2);
    
    //添加的任务统一进行初始化
    osal_Task_init();
    
    osal_mem_kick();
    
    //允许中断
    ///HAL_ENABLE_INTERRUPTS();
    
    //设置初始任务事件，上电就需要自动轮询的任务事件可在此添加
    
    //启动osal系统，不会再返回
    osal_start_system();
    
    
}



#if 1

//#define DEF_EVT_PRINT   0x0001

uint8_t Task_Print_Id;

void Task_Print_Init(uint8_t task_id)
{
    Task_Print_Id = task_id;
    
    osal_start_reload_timer(Task_Print_Id,DEF_EVT_PRINT,1000);
    
    printf("\nTask_Print_Init;");
}

uint16_t Task_Print_Event_Process(uint8_t task_id,uint16_t task_event)
{
    if(task_event&SYS_EVENT_MSG)
    {
        
    
    }
    
    if(task_event&DEF_EVT_PRINT)
    {
        static uint32_t print_cnt=0;
        printf("\nTask_Print Cnt = %d;",print_cnt);
        print_cnt++;
    
        return task_event^DEF_EVT_PRINT;
    }
    
    return 0;
}

#endif

#if 1

//#define DEF_EVT_PRINT   0x0001

uint8_t Task_Key_Id;

void Task_Key_Init(uint8_t task_id)
{
    Task_Key_Id = task_id;
    
    osal_start_reload_timer(Task_Key_Id,DEF_EVT_KEY,10);
    
    printf("\nTask_Key_Init;");
}

uint16_t Task_Key_Event_Process(uint8_t task_id,uint16_t task_event)
{
    if(task_event&SYS_EVENT_MSG)
    {
        
        
    }
    
    if(task_event&DEF_EVT_KEY)
    {
        static uint32_t Key_cnt=0;
        //printf("\nTask_Key Cnt = %d;",Key_cnt);
        Key_cnt++;
        
        button_ticks();
        
        return task_event^DEF_EVT_KEY;
    }
    
    return 0;
}

#endif



#if 1


#endif


#endif



#endif



