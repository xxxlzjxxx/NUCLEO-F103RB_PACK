
#include "bmp180.h"
#include "stdio.h"
#include "usart.h"
#include "stm32f10x_gpio.h"
short ac1;
short ac2; 
short ac3; 
unsigned short ac4;
unsigned short ac5;
unsigned short ac6;
short b1; 
short b2;
short mb;
short mc;
short md;
/* Private function prototypes -----------------------------------------------*/
void  Delay(u32 nCount);
s32  bmp180_presure=0,bmp180_temp=0;
void GPIO_Configuration(void);
extern void I2C_delay(uint32_t cnt);
u8 presure_data[];
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
 ////Read calibration data from the E2PROM of the BMP180
 ////read out E2PROM registers, 16 bit, MSB first
void temp_calibration(void)
{
  uint8_t buf[2];
  I2C_Read(Open_I2C,ADDR_24LC02,0xaa,buf, 2);
  ac1 = buf[0] << 8 |buf[1];
  I2C_Read(Open_I2C,ADDR_24LC02,0xac,buf, 2);
  ac2 = buf[0] << 8 |buf[1];
  I2C_Read(Open_I2C,ADDR_24LC02,0xae,buf, 2);
  ac3 = buf[0] << 8 |buf[1];
  I2C_Read(Open_I2C,ADDR_24LC02,0xb0,buf, 2);
  ac4 = buf[0] << 8 |buf[1];
  I2C_Read(Open_I2C,ADDR_24LC02,0xb2,buf, 2);
  ac5 = buf[0] << 8 |buf[1];
  I2C_Read(Open_I2C,ADDR_24LC02,0xb4,buf, 2);
  ac6 = buf[0] << 8 |buf[1]; 
  I2C_Read(Open_I2C,ADDR_24LC02,0xb6,buf, 2);
  b1 = buf[0] << 8 |buf[1];
  I2C_Read(Open_I2C,ADDR_24LC02,0xb8,buf, 2);
  b2 = buf[0] << 8 |buf[1];
  I2C_Read(Open_I2C,ADDR_24LC02,0xba,buf, 2);
  mb = buf[0] << 8 |buf[1];
  I2C_Read(Open_I2C,ADDR_24LC02,0xbc,buf, 2);
  mc = buf[0] << 8 |buf[1];
  I2C_Read(Open_I2C,ADDR_24LC02,0xbe,buf, 2);
  md = buf[0] << 8 |buf[1];
  //printf("ac1=%d,ac2=%d,ac3=%d,ac4=%d,ac5=%d,ac6=%d,b1=%d,b2=%d,mb=%d,mc=%d,md=%d\r\n",ac1,ac2,ac3,ac4,ac5,ac6,b1,b2,mb,mc,md);
}

void test_pressure_main(void)
{
	
  long x1,x2,x3,b3,b5,b6,b7,press_reg,pressure,temp_reg,temp;
	//long x1,x2,x3,b3,b5,b6,b7,press_reg,pressure,temp_reg;
  unsigned long b4;
  int i;	//ret,

  uint8_t ReadBuffer[10];
	//unsigned short ;
  //unsigned int ;
  char oss = 0;  //这个值在读气压时可以置进寄存器
	//GPIO_Configuration();
	//USART_Configuration();
  I2C_Configuration();
	 
	while (1)
	{	
	//printf("\r\n Read start \r\n");
 
  temp_calibration();
  //read uncompensated temperature
  I2C_WriteOneByte(Open_I2C,ADDR_24LC02,0xf4,0x2e);
  I2C_delay(200000);//delay 4.5ms
  //ret = I2C_Read(Open_I2C,ADDR_24LC02,0xf6,ReadBuffer,2);
  I2C_Read(Open_I2C,ADDR_24LC02,0xf6,ReadBuffer,2);
  temp_reg = ReadBuffer[0] << 8 | ReadBuffer[1];
  ////printf("temp_reg %d \r\n",temp_reg);
  
  //calculate true temperature
  x1 = ((temp_reg - ac6) * ac5) >> 15;
  x2 = ((long) mc << 11) / (x1 + md);
  b5 = x1 + x2;
  temp = (b5 + 8) >> 4;
  bmp180_temp=temp;
  //printf("x1:%d, x2:%d, b5:%d, temp(*0.1):%d \r\n",x1,x2,b5,temp);
  
  //read uncompensated pressure
  
  //////write 0x34+(oss<<6) into reg 0xF4, wait 4.5ms
  I2C_WriteOneByte(Open_I2C,ADDR_24LC02,0xf4,(0x34 +(oss<<6)));
  
  //I2C_WriteOneByte(Open_I2C,ADDR_24LC02,0xf4,(0x3e + oss<<6));
  //I2C_WriteOneByte(Open_I2C,ADDR_24LC02,0xf4,0x3e);
  I2C_delay(200000);//delay 4.5ms
  
  //read reg 0xF6 (MSB), 0xF7 (LSB), 0xF8 (XLSB)
  I2C_Read(Open_I2C,ADDR_24LC02,0xf6,ReadBuffer,3);
  
  //I2C_Read(Open_I2C,ADDR_24LC02,0xf6,ReadBuffer,2);

  //////UP = (MSB<<16 + LSB<<8 + XLSB) >> (8-oss)
  press_reg = ((ReadBuffer[0] << 16)+(ReadBuffer[1] << 8)+ReadBuffer[2]) >> (8 - oss);

  //press_reg = ((ReadBuffer[0] << 16) | (ReadBuffer[1] << 8) | ReadBuffer[2]) >> (8 - oss);
  //press_reg = ReadBuffer[0] << 8 | ReadBuffer[1];
  //press_reg &= 0x00FFFF;
  //printf("press_reg %d \r\n",press_reg);
  
  b6 = b5 - 4000;
  
  //X1 = (B2 * (B6 * B6 / 2^12)) / 2^11
  x1 = (b2 * ((b6 * b6) >> 12)) >> 11;
  
  //X2 = AC2 * B6 / 2^11
  x2 = (ac2 * b6) >> 11;
  
  x3 = x1 + x2;
  
  //B3 = ((AC1*4+X3) << oss + 2) / 4
  b3 = ((((long)ac1 * 4 + x3) << oss) + 2) / 4;
  //b3 = (((long)ac1 * 4 + x3) + 2) / 4;
  
  //X1 = AC3 * B6 / 2^13
  x1 = (ac3 * b6) >> 13;

  //X2 = (B1 * (B6 * B6 / 2^12 )) / 2^16
  x2 = (b1 * ((b6 * b6)>> 12)) >> 16;

  //X3 = ((X1 + X2) + 2) / 2^2
  x3 = ((x1 + x2 )+ 2) >> 2;

  //B4 = AC4 * (unsigend long)(X3 + 32768) / 2^15
  b4 = (ac4 * (unsigned long)(x3 + 32768)) >> 15;

  //B7 = ((unsigned long)UP - B3) * (50000 >> oss)
  b7 = ((unsigned long)press_reg - b3) * (50000 >> oss);
  //b7 = ((unsigned long)press_reg - b3) * (50000);
  
  if(b7 < 0x80000000)
  {
    pressure = (b7 * 2) / b4;
  }
  else
  {
    pressure = (b7 / b4) * 2;
  }

  //X1 = (p / 2^8 ) * (p / 2^8 )
  x1 = (pressure >> 8) * (pressure >> 8);

  //X1 = (X1 * 3038) / 2^16
  x1 = (x1 * 3038) >> 16;

  //X2 = (-7357 * p) / 2^16
  x2 = (-7357 * pressure) >> 16;

  //p = p + (X1 + X2 + 3791) / 2^4
  pressure = pressure + ((x1 + x2 + 3791) >> 4);

  bmp180_presure  = pressure;
  bmp180_presure  /= 10;
  presure_data[0]=bmp180_presure+'0';
  //presure_data[1]=bmp180_presure+'0';
  printf("气压值:%d\n",bmp180_presure);
  for(i=0; i<200*3; i++)
  I2C_delay(20000);
	}
}

/*******************************************************************************
* Function Name  : Delay
* Description    : Delay Time
* Input          : - nCount: Delay Time
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void  Delay(uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure I2C1 pins: SCL and SDA ----------------------------------------*/
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure I2C2 pins: SCL and SDA ----------------------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}





  
