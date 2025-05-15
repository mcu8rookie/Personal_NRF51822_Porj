#ifndef __USR_I2C_C__
#define __USR_I2C_C__

#include <stdio.h>
#include <stdint.h>
#include "twi_master.h"
#include "Usr_I2C.h"
#include <stdint.h>
#include "Usr_Code.h"

//#define DEF_I2C_ADDR_7B     (0x12)
//#define DEF_I2C_ADDR_7B     (0x50)
//#define DEF_I2C_ADDR_7B     (0x98>>1)
#define DEF_I2C_ADDR_7B     (0x13)


#define DEF_I2C_ADDR_WT     ((DEF_I2C_ADDR_7B<<1)+0)
#define DEF_I2C_ADDR_RD     ((DEF_I2C_ADDR_7B<<1)+1)

#define DEF_I2C_BUFF_MUM    (64)

uint8_t i2c_wt_len;
uint8_t i2c_rd_len;

uint8_t i2cBuff[DEF_I2C_BUFF_MUM];

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



void Usr_I2C_MainLoop(unsigned char dat)
{
    uint8_t i;
    
    static uint32_t ml_cnt = 0;
    
    uint8_t rtn;
    
    uint8_t cal_crc1;
    uint8_t cal_crc2;
    
    if(dat == 'w')
    {
        ml_cnt ++;
        
        i2cBuff[0] = 0xD0;
        i2cBuff[1] = ml_cnt;
        i2cBuff[2] = ml_cnt>>8;
        i2cBuff[3] = 0x03;
        i2cBuff[4] = ml_cnt>>8;
        i2cBuff[5] = ml_cnt;
        i2c_wt_len = 6;
        
        rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,6,TWI_ISSUE_STOP);
        
        if(true == rtn)
        {
            printf("\nWrite HEX  0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X,",i2cBuff[0],i2cBuff[1],i2cBuff[2],i2cBuff[3],i2cBuff[4],i2cBuff[5]);
            printf("\t\tData1,\t%d,\tData2,\t%d,",(i2cBuff[1]<<8)+i2cBuff[2],(i2cBuff[4]<<8)+i2cBuff[5]);
        }
        else
        {
            printf("\nI2C: Erroe, twi_master_transfer(); return %d,",rtn);
        }
    }
    else if(dat == 'r')
    {   
        #if 0
        //ml_cnt ++;
        
        //i2cBuff[0] = 0xD0;
        
        i2cBuff[0] = 0xE2;
        
        i2c_wt_len = 1;
        
        
        rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,1,TWI_DONT_ISSUE_STOP);
        //rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,1,TWI_ISSUE_STOP);
        
        rtn |= twi_master_transfer(DEF_I2C_ADDR_RD,i2cBuff,6,TWI_ISSUE_STOP);
        
        if(true == rtn)
        {
            printf("\nRead0 HEX  0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X,",i2cBuff[0],i2cBuff[1],i2cBuff[2],i2cBuff[3],i2cBuff[4],i2cBuff[5]);
            printf("\t\tData1,\t%d,\tData2,\t%d,",(i2cBuff[1]<<8)+i2cBuff[2],(i2cBuff[4]<<8)+i2cBuff[5]);
        }
        else
        {
            printf("\nI2C: Erroe, twi_master_transfer(); return %d,",rtn);
        }
        #endif
    
        
        #if 1
        //ml_cnt ++;
        
        //i2cBuff[0] = 0xD0;
        
        i2cBuff[0] = 0xEC;
        i2cBuff[1] = 0x05;
        
        //rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,1,TWI_DONT_ISSUE_STOP);
        rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,2,TWI_ISSUE_STOP);
        
        rtn |= twi_master_transfer(DEF_I2C_ADDR_RD,i2cBuff,18,TWI_ISSUE_STOP);
        
        
        if(true == rtn)
        {
            printf("\nRead1 HEX, ");
            
            for(i=0;i<18;i++)
            {
                printf("\t0x%02X,",i2cBuff[i]);
            }
        }
        else
        {
            printf("\nI2C: Erroe, twi_master_transfer(); return %d,",rtn);
        }
        #endif
    }
    else if(dat == 'R')
    {
        #if 0
        //ml_cnt ++;
        
        //i2cBuff[0] = 0xD0;
        
        i2cBuff[0] = 0xE2;
        
        i2c_wt_len = 1;
        
        
        //rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,1,TWI_DONT_ISSUE_STOP);
        rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,1,TWI_ISSUE_STOP);
        
        rtn |= twi_master_transfer(DEF_I2C_ADDR_RD,i2cBuff,6,TWI_ISSUE_STOP);
        
        if(true == rtn)
        {
            printf("\nRead1 HEX  0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X,",i2cBuff[0],i2cBuff[1],i2cBuff[2],i2cBuff[3],i2cBuff[4],i2cBuff[5]);
            printf("\t\tData1,\t%d,\tData2,\t%d,",(i2cBuff[1]<<8)+i2cBuff[2],(i2cBuff[4]<<8)+i2cBuff[5]);
        }
        else
        {
            printf("\nI2C: Erroe, twi_master_transfer(); return %d,",rtn);
        }
        #endif
        
        #if 1
        //ml_cnt ++;
        
        //i2cBuff[0] = 0xD0;
        
        i2cBuff[0] = 0x36;
        i2cBuff[1] = 0x15;
        
        
        //rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,1,TWI_DONT_ISSUE_STOP);
        rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,2,TWI_ISSUE_STOP);
        
        i2cBuff[0] = 0xEC;
        i2cBuff[1] = 0x05;
        
        //rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,1,TWI_DONT_ISSUE_STOP);
        rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,2,TWI_ISSUE_STOP);
        
        rtn |= twi_master_transfer(DEF_I2C_ADDR_RD,i2cBuff,18,TWI_ISSUE_STOP);
        
        
        if(true == rtn)
        {
            printf("\nRead1 HEX, ");
            
            for(i=0;i<18;i++)
            {
                printf("\t0x%02X,",i2cBuff[i]);
            }
        }
        else
        {
            printf("\nI2C: Erroe, twi_master_transfer(); return %d,",rtn);
        }
        #endif
    }
    else if(dat == '1')
    {
        
        #if 1
        
        i2cBuff[0] = 0x36;
        i2cBuff[1] = 0x15;
        
        i2c_wt_len = 2;
        
        //rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,1,TWI_DONT_ISSUE_STOP);
        rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,i2c_wt_len,TWI_ISSUE_STOP);
        
        i2cBuff[0] = 0xEC;
        i2cBuff[1] = 0x05;
        
        i2c_wt_len = 2;
        
        //rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,1,TWI_DONT_ISSUE_STOP);
        rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,i2c_wt_len,TWI_ISSUE_STOP);
        
        i2c_rd_len = 18;
        
        rtn |= twi_master_transfer(DEF_I2C_ADDR_RD,i2cBuff,i2c_rd_len,TWI_ISSUE_STOP);
        
        
        if(true == rtn)
        {
            printf("\nRead1 HEX, ");
            
            for(i=0;i<i2c_rd_len;i++)
            {
                printf("\t0x%02X,",i2cBuff[i]);
            }
        }
        else
        {
            printf("\nI2C: Erroe, twi_master_transfer(); return %d,",rtn);
        }
        #endif
    }
    else if(dat == '2')
    {   
        
        #if 1
        
        i2cBuff[0] = 0xEC;
        i2cBuff[1] = 0x05;
        
        i2c_wt_len = 2;
        
        //rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,1,TWI_DONT_ISSUE_STOP);
        rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,i2c_wt_len,TWI_ISSUE_STOP);
        
        i2c_rd_len = 18;
        
        rtn |= twi_master_transfer(DEF_I2C_ADDR_RD,i2cBuff,i2c_rd_len,TWI_ISSUE_STOP);
        
        
        if(true == rtn)
        {
            printf("\nRead2 HEX, ");
            
            for(i=0;i<i2c_rd_len;i++)
            {
                printf("\t0x%02X,",i2cBuff[i]);
            }
        }
        else
        {
            printf("\nI2C: Erroe, twi_master_transfer(); return %d,",rtn);
        }
        #endif
    }
    else if(dat == '3')
    {   // Write;
        
        #if 1
        
        i2cBuff[0] = 0x36;
        i2cBuff[1] = 0x08;
        i2cBuff[2] = 0x00;
        i2cBuff[3] = 0x19;
        //i2cBuff[4] = 0x5A;
        
        {
            uint8_t cal_crc1;
            uint8_t cal_crc2;
            cal_crc1 = sensirion_common_generate(i2cBuff+2,2);
            cal_crc2 = compute_crc8(i2cBuff+2,2);
            //printf("\ncrc1 = 0x%02X,\tcrc2 = 0x%02X, ",cal_crc1,cal_crc2);
            
            i2cBuff[4] = cal_crc1;
        }
        
        i2c_wt_len = 5;
        
        rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,i2c_wt_len,TWI_ISSUE_STOP);
        
        if(true == rtn)
        {
            printf("\nWrite3 HEX, ");
            
            for(i=0;i<i2c_wt_len;i++)
            {
                printf("\t0x%02X,",i2cBuff[i]);
            }
        }
        else
        {
            printf("\nI2C: Erroe, twi_master_transfer(); return %d,",rtn);
        }
        #endif
    }
    else if(dat == '4')
    {   // Write;
        
        #if 1
        
        i2cBuff[0] = 0x36;
        i2cBuff[1] = 0x03;
        
        i2c_wt_len = 2;
        
        rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,i2c_wt_len,TWI_ISSUE_STOP);
        
        if(true == rtn)
        {
            printf("\nWrite4 HEX, ");
            
            for(i=0;i<i2c_wt_len;i++)
            {
                printf("\t0x%02X,",i2cBuff[i]);
            }
        }
        else
        {
            printf("\nI2C: Erroe, twi_master_transfer(); return %d,",rtn);
        }
        #endif
    }
    
    else if(dat == '5')
    {   // Read;
        
        #if 1
        
        i2cBuff[0] = 0x36;
        i2cBuff[1] = 0x15;
        
        i2c_wt_len = 2;
        
        rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,i2c_wt_len,TWI_DONT_ISSUE_STOP);
        //rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,i2c_wt_len,TWI_ISSUE_STOP);
        
        i2cBuff[0] = 0xEC;
        i2cBuff[1] = 0x05;
        
        i2c_wt_len = 2;
        
        rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,i2c_wt_len,TWI_DONT_ISSUE_STOP);
        //rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,i2c_wt_len,TWI_ISSUE_STOP);
        
        i2c_rd_len = 18;
        
        rtn |= twi_master_transfer(DEF_I2C_ADDR_RD,i2cBuff,i2c_rd_len,TWI_ISSUE_STOP);
        
        
        if(true == rtn)
        {
            printf("\nRead5 HEX, ");
            
            for(i=0;i<i2c_rd_len;i++)
            {
                printf("\t0x%02X,",i2cBuff[i]);
            }
        }
        else
        {
            printf("\nI2C: Erroe, twi_master_transfer(); return %d,",rtn);
        }
        #endif
    }
    else if(dat == '6')
    {   // Read;
        
        #if 1
        
        i2cBuff[0] = 0xEC;
        i2cBuff[1] = 0x05;
        
        i2c_wt_len = 2;
        
        rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,i2c_wt_len,TWI_DONT_ISSUE_STOP);
        //rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,i2c_wt_len,TWI_ISSUE_STOP);
        
        i2c_rd_len = 18;
        
        rtn |= twi_master_transfer(DEF_I2C_ADDR_RD,i2cBuff,i2c_rd_len,TWI_ISSUE_STOP);
        
        
        if(true == rtn)
        {
            printf("\nRead6 HEX, ");
            
            for(i=0;i<i2c_rd_len;i++)
            {
                printf("\t0x%02X,",i2cBuff[i]);
            }
        }
        else
        {
            printf("\nI2C: Erroe, twi_master_transfer(); return %d,",rtn);
        }
        #endif
    }
    #if 1
    else if(dat == 'a')
    {   // Write;
        
        #if 1
        
        i2cBuff[0] = 0x11;
        i2cBuff[1] = 0x88;
        
        for(i2c_wt_len=2;i2c_wt_len<14;i2c_wt_len++)
        {
            i2cBuff[i2c_wt_len] = YearMonthDateSN[i2c_wt_len-2];
        }
        
        cal_crc1 = compute_crc8(i2cBuff+2,2);
        *(i2cBuff+2+2) = cal_crc1;
        
        cal_crc1 = compute_crc8(i2cBuff+2+3,2);
        *(i2cBuff+2+2+3) = cal_crc1;
        
        cal_crc1 = compute_crc8(i2cBuff+2+3+3,2);
        *(i2cBuff+2+2+3+3) = cal_crc1;
        
        cal_crc1 = compute_crc8(i2cBuff+2+3+3+3,2);
        *(i2cBuff+2+2+3+3+3) = cal_crc1;
        
        rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,i2c_wt_len,TWI_ISSUE_STOP);
        
        if(true == rtn)
        {
            printf("\nWrite a HEX, ");
            
            for(i=0;i<i2c_wt_len;i++)
            {
                printf("\t0x%02X,",i2cBuff[i]);
            }
        }
        else
        {
            printf("\nI2C: Erroe, twi_master_transfer(); return %d,",rtn);
        }
        #endif
    }
    else if(dat == 'b')
    {   // Read;
        
        #if 1
        
        i2cBuff[0] = 0x11;
        i2cBuff[1] = 0x08;
        
        i2c_wt_len = 2;
        
        //rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,i2c_wt_len,TWI_DONT_ISSUE_STOP);
        rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,i2c_wt_len,TWI_ISSUE_STOP);
        
        i2c_rd_len = 12;
        
        rtn |= twi_master_transfer(DEF_I2C_ADDR_RD,i2cBuff,i2c_rd_len,TWI_ISSUE_STOP);
        
        
        if(true == rtn)
        {
            printf("\nRead b HEX, ");
            
            for(i=0;i<i2c_rd_len;i++)
            {
                printf("\t0x%02X,",i2cBuff[i]);
            }
        }
        else
        {
            printf("\nI2C: Erroe, twi_master_transfer(); return %d,",rtn);
        }
        #endif
    }
    else if(dat == 'c')
    {   // Read;
        
        #if 1
        
        i2cBuff[0] = 0x10;
        i2cBuff[1] = 0x01;
        
        i2c_wt_len = 2;
        
        //rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,i2c_wt_len,TWI_DONT_ISSUE_STOP);
        rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,i2c_wt_len,TWI_ISSUE_STOP);
        
        i2c_rd_len = 9;
        
        rtn |= twi_master_transfer(DEF_I2C_ADDR_RD,i2cBuff,i2c_rd_len,TWI_ISSUE_STOP);
        
        
        if(true == rtn)
        {
            printf("\nRead c HEX, ");
            
            for(i=0;i<i2c_rd_len;i++)
            {
                printf("\t0x%02X,",i2cBuff[i]);
            }
        }
        else
        {
            printf("\nI2C: Erroe, twi_master_transfer(); return %d,",rtn);
        }
        #endif
    }
    else if(dat == 'd')
    {   // Read TmprCmpPara;
        
        #if 1
        
        i2cBuff[0] = 0x11;
        i2cBuff[1] = 0x09;
        
        i2c_wt_len = 2;
        
        //rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,i2c_wt_len,TWI_DONT_ISSUE_STOP);
        rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,i2c_wt_len,TWI_ISSUE_STOP);
        
        i2c_rd_len = 24;
        
        rtn |= twi_master_transfer(DEF_I2C_ADDR_RD,i2cBuff,i2c_rd_len,TWI_ISSUE_STOP);
        
        
        if(true == rtn)
        {
            printf("\nRead d HEX, ");
            
            for(i=0;i<i2c_rd_len;i++)
            {
                printf("\t0x%02X,",i2cBuff[i]);
            }
        }
        else
        {
            printf("\nI2C: Erroe, twi_master_transfer(); return %d,",rtn);
        }
        #endif
    }
    else if(dat == 'e')
    {   // Write TmprCompPara;
        
        uint32_t Tmp_k;
        #if 1
        
        i2cBuff[0] = 0x11;
        i2cBuff[1] = 0x89;
        
        // P0
        Tmp_k = 0x11111111;
        
        i2cBuff[2] = Tmp_k>>24;
        i2cBuff[3] = Tmp_k>>16;
        cal_crc1 = compute_crc8(i2cBuff+2+3*0,2);
        *(i2cBuff+2+2+3*0) = cal_crc1;
        
        i2cBuff[5] = Tmp_k>>8;
        i2cBuff[6] = Tmp_k>>0;
        cal_crc1 = compute_crc8(i2cBuff+2+3*1,2);
        *(i2cBuff+2+2+3*1) = cal_crc1;
        
        // P1
        Tmp_k = 0x22222222;
        
        i2cBuff[8] = Tmp_k>>24;
        i2cBuff[9] = Tmp_k>>16;
        cal_crc1 = compute_crc8(i2cBuff+2+3*2,2);
        *(i2cBuff+2+2+3*2) = cal_crc1;
        
        i2cBuff[11] = Tmp_k>>8;
        i2cBuff[12] = Tmp_k>>0;
        cal_crc1 = compute_crc8(i2cBuff+2+3*3,2);
        *(i2cBuff+2+2+3*3) = cal_crc1;
        
        // P2
        Tmp_k = 0x33333333;
        
        i2cBuff[14] = Tmp_k>>24;
        i2cBuff[15] = Tmp_k>>16;
        cal_crc1 = compute_crc8(i2cBuff+2+3*4,2);
        *(i2cBuff+2+2+3*4) = cal_crc1;
        
        i2cBuff[17] = Tmp_k>>8;
        i2cBuff[18] = Tmp_k>>0;
        cal_crc1 = compute_crc8(i2cBuff+2+3*5,2);
        *(i2cBuff+2+2+3*5) = cal_crc1;
        
        // P3
        Tmp_k = 0x44444444;
        
        i2cBuff[20] = Tmp_k>>24;
        i2cBuff[21] = Tmp_k>>16;
        cal_crc1 = compute_crc8(i2cBuff+2+3*6,2);
        *(i2cBuff+2+2+3*6) = cal_crc1;
        
        i2cBuff[23] = Tmp_k>>8;
        i2cBuff[24] = Tmp_k>>0;
        cal_crc1 = compute_crc8(i2cBuff+2+3*7,2);
        *(i2cBuff+2+2+3*7) = cal_crc1;
        
        i2c_wt_len = 26;
        
        rtn = twi_master_transfer(DEF_I2C_ADDR_WT,i2cBuff,i2c_wt_len,TWI_ISSUE_STOP);
        
        if(true == rtn)
        {
            printf("\nWrite e HEX, ");
            
            for(i=0;i<i2c_wt_len;i++)
            {
                printf("\t0x%02X,",i2cBuff[i]);
            }
        }
        else
        {
            printf("\nI2C: Erroe, twi_master_transfer(); return %d,",rtn);
        }
        #endif
    }
    #endif
}



#if 1   // CRC algorithm from Midea little board project;
#define CRC8_POLYNOMIAL 0x31
#define CRC8_INIT       0xFF

uint8_t sensirion_common_generate(const uint8_t *data,uint16_t count)
{
    uint16_t current_byte;
    uint8_t crc = CRC8_INIT;
    uint8_t crc_bit;
    /* calculates 8-Bit checksum with given polynomial */
    for(current_byte=0; current_byte<count; ++current_byte)
    {
        crc ^= (data[current_byte]);
        for(crc_bit=8; crc_bit>0; --crc_bit)
        {
            if(crc&0x80)
            {
                crc = (crc<<1)^CRC8_POLYNOMIAL;
            }
            else
            {
                crc = (crc<<1);
            }
        }
    }
    return crc;
}

#endif

#if 1   // CRC algorithm from HuangShiliang for Midea little board project;
#if 0   // 
2.CRC校验
本协议采用CRC8校验，校验参数如下：
宽度 WIDTH	8 bits
多项式 POLY	0x31 (X8 + X5 + X4 + 1)
初始值 INIT	0xFF
结果异或值 XOROUT	0x00
输入数据反转 REFIN	FALSE
输出数据反转 REFOUT	FALSE
查表法例程：
// 按照多项式 X^8 + X^5 + X^4 + 1 生成。
#endif
static const uint8_t crc8_table[256] =
{
  0x00, 0x31, 0x62, 0x53, 0xc4, 0xf5, 0xa6, 0x97, 0xb9, 0x88, 0xdb, 0xea, 0x7d, 0x4c, 0x1f, 0x2e, 
  0x43, 0x72, 0x21, 0x10, 0x87, 0xb6, 0xe5, 0xd4, 0xfa, 0xcb, 0x98, 0xa9, 0x3e, 0x0f, 0x5c, 0x6d, 
  0x86, 0xb7, 0xe4, 0xd5, 0x42, 0x73, 0x20, 0x11, 0x3f, 0x0e, 0x5d, 0x6c, 0xfb, 0xca, 0x99, 0xa8, 
  0xc5, 0xf4, 0xa7, 0x96, 0x01, 0x30, 0x63, 0x52, 0x7c, 0x4d, 0x1e, 0x2f, 0xb8, 0x89, 0xda, 0xeb, 
  0x3d, 0x0c, 0x5f, 0x6e, 0xf9, 0xc8, 0x9b, 0xaa, 0x84, 0xb5, 0xe6, 0xd7, 0x40, 0x71, 0x22, 0x13, 
  0x7e, 0x4f, 0x1c, 0x2d, 0xba, 0x8b, 0xd8, 0xe9, 0xc7, 0xf6, 0xa5, 0x94, 0x03, 0x32, 0x61, 0x50, 
  0xbb, 0x8a, 0xd9, 0xe8, 0x7f, 0x4e, 0x1d, 0x2c, 0x02, 0x33, 0x60, 0x51, 0xc6, 0xf7, 0xa4, 0x95, 
  0xf8, 0xc9, 0x9a, 0xab, 0x3c, 0x0d, 0x5e, 0x6f, 0x41, 0x70, 0x23, 0x12, 0x85, 0xb4, 0xe7, 0xd6, 
  0x7a, 0x4b, 0x18, 0x29, 0xbe, 0x8f, 0xdc, 0xed, 0xc3, 0xf2, 0xa1, 0x90, 0x07, 0x36, 0x65, 0x54, 
  0x39, 0x08, 0x5b, 0x6a, 0xfd, 0xcc, 0x9f, 0xae, 0x80, 0xb1, 0xe2, 0xd3, 0x44, 0x75, 0x26, 0x17, 
  0xfc, 0xcd, 0x9e, 0xaf, 0x38, 0x09, 0x5a, 0x6b, 0x45, 0x74, 0x27, 0x16, 0x81, 0xb0, 0xe3, 0xd2, 
  0xbf, 0x8e, 0xdd, 0xec, 0x7b, 0x4a, 0x19, 0x28, 0x06, 0x37, 0x64, 0x55, 0xc2, 0xf3, 0xa0, 0x91, 
  0x47, 0x76, 0x25, 0x14, 0x83, 0xb2, 0xe1, 0xd0, 0xfe, 0xcf, 0x9c, 0xad, 0x3a, 0x0b, 0x58, 0x69, 
  0x04, 0x35, 0x66, 0x57, 0xc0, 0xf1, 0xa2, 0x93, 0xbd, 0x8c, 0xdf, 0xee, 0x79, 0x48, 0x1b, 0x2a, 
  0xc1, 0xf0, 0xa3, 0x92, 0x05, 0x34, 0x67, 0x56, 0x78, 0x49, 0x1a, 0x2b, 0xbc, 0x8d, 0xde, 0xef, 
  0x82, 0xb3, 0xe0, 0xd1, 0x46, 0x77, 0x24, 0x15, 0x3b, 0x0a, 0x59, 0x68, 0xff, 0xce, 0x9d, 0xac
};



// 使用CRC8表计算数据的CRC8值
//static uint8_t compute_crc8(uint8_t *data, uint16_t size) 
uint8_t compute_crc8(uint8_t *data, uint16_t size)
{
    //uint8_t crc = 0;  // 初始值设置为0
    uint8_t crc = 0xFF;  // 初始值设置为0
    
    while(size--) 
    {
        crc = crc8_table[crc ^ (*data)];
        data++;
    }
    return crc;
}
#endif


#endif



