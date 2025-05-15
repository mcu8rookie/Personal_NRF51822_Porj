#ifndef __USR_I2C_C__
#define __USR_I2C_C__

#include <stdio.h>
#include "twi_master.h"
#include "Usr_I2C.h"

//#define DEF_I2C_ADDR_7B     (0x12)
#define DEF_I2C_ADDR_7B     (0x50)

#define DEF_I2C_ADDR_WT     ((DEF_I2C_ADDR_7B<<1)+0)
#define DEF_I2C_ADDR_RD     ((DEF_I2C_ADDR_7B<<1)+1)

uint8_t i2c_wt_len;
uint8_t i2c_rd_len;

uint8_t i2cBuff[32];

void Usr_I2C_InitSetup(void)
{
    twi_master_init();
}


#if 1
bool twi_master_transfer(uint8_t   address,
                         uint8_t * data,
                         uint8_t   data_length,
                         bool      issue_stop_condition);
#endif

void Usr_I2C_MainLoop(void)
{
    static uint32_t I2C_LoopCnt = 0;
    
    uint8_t rtn;
    uint16_t Read_Data1,Read_Data2;
    
    i2cBuff[0] = 0xD0;
    i2cBuff[1] = 22;
    i2c_wt_len = 1;
    
    I2C_LoopCnt++;
    
    //printf("\nI2C: LoopCnt,\t%d,",I2C_LoopCnt);
    
    rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,1,TWI_DONT_ISSUE_STOP);
    
    if(true == rtn)
    {
        
    }
    else
    {
        printf("\nI2C: Error1, twi_master_transfer(); return %d,",rtn);
    }
    
    rtn = twi_master_transfer(DEF_I2C_ADDR_RD,i2cBuff,6,TWI_ISSUE_STOP);
    
    if(true == rtn)
    {
        Read_Data1 = i2cBuff[1];
        Read_Data1 <<= 8;
        Read_Data1 += i2cBuff[2];
        
        Read_Data2 = i2cBuff[4];
        Read_Data2 <<= 8;
        Read_Data2 += i2cBuff[5];
        
        //printf("\tRead,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,,",i2cBuff[0],i2cBuff[1],i2cBuff[2],i2cBuff[3],i2cBuff[4],i2cBuff[5]);
        
        printf("\tData1,\t%d,\tData2,\t%d,",Read_Data1,Read_Data2);
    }
    else
    {
        printf("\nI2C: Error2, twi_master_transfer(); return %d,",rtn);
    }
}

#endif



