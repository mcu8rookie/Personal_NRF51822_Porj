#ifndef __USR_CODE_H__
#define __USR_CODE_H__

#include "stdint.h"
#include "nrf51822_peripherals.h"

#define DEF_YMDSN_YEAR1             (20)
#define DEF_YMDSN_YEAR2             (25)
#define DEF_YMDSN_CRC1              (1)

#define DEF_YMDSN_MONTH             (2)
#define DEF_YMDSN_DATE              (21)
#define DEF_YMDSN_CRC2              (2)

#define DEF_YMDSN_SN1               (1)
#define DEF_YMDSN_SN2               (2)
#define DEF_YMDSN_CRC3              (3)

#define DEF_YMDSN_SN3               (3)
#define DEF_YMDSN_SN4               (4)
#define DEF_YMDSN_CRC4              (4)

extern uint8_t YearMonthDateSN[12];


extern uint32_t Reset_Source;
extern uint32_t MainLoop_Cnt;
extern uint32_t TimeStamp_Cnt;

#endif



