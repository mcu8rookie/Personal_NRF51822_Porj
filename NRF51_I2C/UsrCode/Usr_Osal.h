#ifndef __USR_OSAL_H__
#define __USR_OSAL_H__

#include "Usr_Config.h"

#include "stdint.h"

#include "type.h"

#if(defined(DEF_OSAL_EN)&&(DEF_OSAL_EN==1))


#define DEF_OSAL_TICK_MS    (1)

extern uint32_t Usr_Osal_Timestamp_Real;
extern uint32_t Usr_Osal_Timestamp_Old;
extern uint32_t Usr_Osal_Timestamp_Now;

extern uint8 timerActive;

void Usr_osal_Init(void);


#if 1

#define DEF_EVT_PRINT   0x0001

extern uint8_t Task_Print_Id;

void Task_Print_Init(uint8_t task_id);

uint16_t Task_Print_Event_Process(uint8_t task_id,uint16_t task_event);

#endif

#if 1

#define DEF_EVT_KEY   0x0002

extern uint8_t Task_Key_Id;

void Task_Key_Init(uint8_t task_id);

uint16_t Task_Key_Event_Process(uint8_t task_id,uint16_t task_event);

#endif




#endif

#endif


