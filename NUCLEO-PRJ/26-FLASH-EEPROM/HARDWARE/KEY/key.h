#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK miniSTM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PBin(0)   	
//#define KEY1 PAin(10)	 
//#define WK_UP  PAin(0)	 
 

#define KEY0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//读取按键
#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)//读取按键
#define USER  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)//读取按键
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键
 

#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define USER_PRES	4		//USER
#define WKUP_PRES	3		//WK_UP  

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数					    
#endif
