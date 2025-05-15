#ifndef __USR_I2C_H__
#define __USR_I2C_H__



#include <stdint.h>

void Usr_I2C_InitSetup(void);

void Usr_I2C_MainLoop(unsigned char dat);

extern uint8_t sensirion_common_generate(const uint8_t *data,uint16_t count);
extern uint8_t compute_crc8(uint8_t *data, uint16_t size);


#endif



