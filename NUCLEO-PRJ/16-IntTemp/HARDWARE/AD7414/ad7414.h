/*******************************************************************************
* File Name  ：ad7414.h
* Function   ：Function declaration
* Author     ：
* Version    ：
* Description：
* Chang Log  ：
*******************************************************************************/
#ifndef __AD7414_H
#define __AD7414_H

/*****************************************************************************
* 管脚定义
*****************************************************************************/
//#define   SDA_AD7414_SEL_GPIO                  (P3SEL &=~BIT1)  //设置为GPIO口
#define SDA_AD7414_DIR_INPUT()  {GPIOB->CRL&=0XFFF0FFFF;GPIOB->CRL|=3<<16;}
#define SDA_AD7414_DIR_OUTPUT() {GPIOB->CRL&=0XFFF0FFFF;GPIOB->CRL|=3<<16;}
#define   SDA_AD7414_OUT_HIGH                  (GPIO_SetBits(GPIOB, GPIO_Pin_4))  //输出高
#define   SDA_AD7414_OUT_LOW                   (GPIO_ResetBits(GPIOB, GPIO_Pin_4))  //输出低

//#define   SDA_AD7414_DIR_INPUT                 (P3DIR &=~BIT1)  //输入
#define   SDA_AD7414_READ                      PBin(4)      //读管脚电平状态

//#define   SCL_AD7414_SEL_GPIO                  (P3SEL &=~BIT2)  //设置为GPIO口
//#define   SCL_AD7414_DIR_OUTPUT                (P3DIR |= BIT2)  //方向输出
//#define   SCL_AD7414_DIR_INPUT                 (P3DIR &=~BIT2)  //方向输入
#define   SCL_AD7414_OUT_HIGH                  (GPIO_SetBits(GPIOB, GPIO_Pin_3))  //输出高
#define   SCL_AD7414_OUT_LOW                   (GPIO_ResetBits(GPIOB, GPIO_Pin_3))  //输出低

//#define   AD7414_ALT_SEL_GPIO                  (P3SEL &=~BIT0)  //设置为GPIO口
//#define   AD7414_ALT_DIR_INPUT                 (P3DIR &=~BIT0)  //方向输入

#define AD7414IICAddress	0x48	//	1001 000
//#if 1
#define AD7414_WriteDeviceAddress       0x90          //AD7414-0's Write Address 1001 000 0
#define AD7414_ReadDeviceAddress        0x91          //AD7414-0's Read  Address 1001 000 1
//#endif

//#if 0
//#define AD7414_WriteDeviceAddress       0x9A          /*AD7414-1's Write Address*/
//#define AD7414_ReadDeviceAddress        0x9B          /*AD7414-1's Read  Address*/
//#endif

/*******************************************************************************
* 函数声明
*******************************************************************************/
void AD7414_Init(void);
void AD7414_I2c_Start(void);
void AD7414_I2c_Stop(void);
void AD7414_I2cAck_Slaver(void);
void AD7414_I2cNoAck_Mcu(void);
void AD7414_I2cWriteByte(unsigned char wbyte);
unsigned char AD7414_I2cReadByte(void);
float AD7414_Read_Temp(void);
void delay_usad7414(unsigned int delaytimes);

#endif


