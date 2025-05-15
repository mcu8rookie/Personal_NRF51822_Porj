#ifndef __USRLED_H__
#define __USRLED_H__

#include "stdint.h"


#define LED_0 21
#define LED_1 22
#define LED_2 23
#define LED_3 24

#define DEF_DBGIO1	4
#define DEF_DBGIO2	12


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

#endif




