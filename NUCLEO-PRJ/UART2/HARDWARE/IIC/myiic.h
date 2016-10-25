#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//IIC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/6/10 
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  

/*********************����ΪEEPROMʹ��******************************/
//SCL	PA9
//SDA	PA8
//WP	PB10
	   		   
//IO��������
#define SDA_IN()  {GPIOA->CRH &= 0XFFFFFFF0; GPIOA->CRH |= 8 << 0;}
#define SDA_OUT() {GPIOA->CRH &= 0XFFFFFFF0; GPIOA->CRH |= 3 << 0;}
//IO��������	 
#define IIC_SCL    PAout(9) //SCL
#define IIC_SDA    PAout(8) //SDA	 
#define READ_SDA   PAin(8)  //����SDA
/*****************************************************************/
/*********************����ΪBMP180ʹ��*****************************/
//SCL -> PC9
//SDA -> PC8
//IO��������
//#define SDA_IN()  {GPIOC->CRH &= 0XFFFFFFF0; GPIOC->CRH |= 8 << 0;}
//#define SDA_OUT() {GPIOC->CRH &= 0XFFFFFFF0; GPIOC->CRH |= 3 << 0;}
//IO��������	 
//#define IIC_SCL    PCout(9) //SCL
//#define IIC_SDA    PCout(8) //SDA	 
//#define READ_SDA   PCin(8)  //����SDA
/*****************************************************************/

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















