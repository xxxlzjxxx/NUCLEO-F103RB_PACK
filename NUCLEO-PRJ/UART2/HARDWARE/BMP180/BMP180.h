#ifndef __BMP180_H
#define __BMP180_H
#include "myiic.h"   
//NUCLEO_F103RF-PACK开发板
//BMP180驱动函数
//xxxlzjxxx
//2016/10/25
//V1.0

//SCL -> PC9
//SDA -> PC8
// #define SCL_H()  GPIO_SetBits(GPIOC, GPIO_Pin_9)
// #define SCL_L()  GPIO_ResetBits(GPIOC, GPIO_Pin_9)
// #define SDA_H()  GPIO_SetBits(GPIOC, GPIO_Pin_8)
// #define SDA_L()  GPIO_ResetBits(GPIOC, GPIO_Pin_8)
// #define SDA  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)
 
#define BMP180_SlaveAddr 0xee   //BMP180的器件地址

void BMP180_PortInit(void);
u8 BMP180_ReadOneByte(u8 ReadAddr);
short BMP180_ReadTwoByte(u8 ReadAddr);
void Write_OneByteToBMP180(u8 RegAdd, u8 Data);
void Read_CalibrationData(void);
long Get_BMP180UT(void);
long Get_BMP180UP(void);
void Convert_UncompensatedToTrue(long UT,long UP);


#endif



















