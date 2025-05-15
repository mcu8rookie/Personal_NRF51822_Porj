#ifndef __USRLED_H__
#define __USRLED_H__

#include "stdint.h"


#define DEF_LED1    (21)
#define DEF_LED2    (22)
#define DEF_LED3    (23)
#define DEF_LED4    (24)

#define DEF_DBGIO1  (4)
#define DEF_DBGIO2  (12)

#define DEF_KEY1    (17)
#define DEF_KEY2    (18)
#define DEF_KEY3    (19)
#define DEF_KEY4    (20)

#define DEF_TOUCH1  (30)


void LED_Init(void);
void LED1_Open(void);
void LED1_Close(void);
void LED1_Toggle(void);
void LED2_Open(void);
void LED2_Close(void);
void LED2_Toggle(void);
void LED3_Open(void);
void LED3_Close(void);
void LED3_Toggle(void);
void LED4_Open(void);
void LED4_Close(void);
void LED4_Toggle(void);


void Usr_Dbg_IO(uint8_t nbr,uint8_t state);


extern uint8_t Key_TimeCnt;

void Usr_Key_Init(void);

void Usr_Key_MainLoop(void);



#endif




