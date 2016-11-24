/**
  ******************************************************************************
  * @file    bmp180.h
  * @author  
  * @version 
  * @date   
  * @brief   
 */

#ifndef __BMP180_H__
#define __BMP180_H__


#include "stm32f10x.h"
#include "bmpi2c.h"
extern s32   bmp180_temp,bmp180_presure; //bmp180
extern void test_pressure_main(void);
extern void GPIO_Configuration(void);
#endif
