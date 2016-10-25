#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"  
#include "24cxx.h" 
#include "myiic.h"
#include "BMP180.h"
//ALIENTEK Mini STM32开发板范例代码3
//串口实验   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

//要写入到24c02的字符串数组
const u8 TEXT_Buffer[]={"xxxlzjxxx IIC TEST"};
#define SIZE sizeof(TEXT_Buffer)	

u8 BMP180_ID=0;          //BMP180的ID

void AT24CXX_Test(void);
void BMP180_Test(void);

int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口	
	KEY_Init();				//按键初始化		 	
//	BMP180_PortInit();			//IIC初始化 
	AT24CXX_Init();
	while(1)
	{
		AT24CXX_Test();
	}	 
}
/*AT24CXX测试程序*/
/*测试未通过*/
void AT24CXX_Test(void)
{
	u8 key;
	u16 i = 0, j = 0;
	u8 datatemp[SIZE];	
	
	while(AT24CXX_Check())//检测不到24c02
	{
		printf("24C02 Check Failed!  Please Check!      \r\n");
		delay_ms(5000);
		LED0=!LED0;//DS0闪烁
	}
	printf("24C02 Ready!\r\n");	
	key = KEY_Scan(0);
	if(key == WKUP_PRES)//WK_UP 按下,写入24C02
	{  
 		printf("Start Write 24C02....\r\n");
		AT24CXX_Write(0,(u8*)TEXT_Buffer,SIZE);
		printf("24C02 Write Finished!\r\n");//提示传送完成
	}
	if(key == KEY0_PRES)//KEY0 按下,读取字符串并显示
	{
 		printf("Start Read 24C02.... \r\n");
		AT24CXX_Read(0,datatemp,SIZE);
		printf("The Data Readed Is:  ");//提示传送完成
		for(j = SIZE; j > 0; j--)
		{
			printf(" %c ", datatemp[i]);//显示读到的字符串
		}
		printf("\r\n");
	}
	i++;
	delay_ms(10);
	if(i==20)
	{
		LED0=!LED0;//提示系统正在运行	
		i=0;
	}	
}
/*BMP180测试程序*/
/*测试未通过*/
void BMP180_Test(void)
{
	u8 key;
	u16 i = 0;

	key = KEY_Scan(0);
	if(key == KEY0_PRES)//KEY0 按下,读取字符串并显示
	{
		long UT,UP;
		Read_CalibrationData();         //读取BMP180的校准系数
		BMP180_ID = BMP180_ReadOneByte(0xd0);      //读取ID地址
		printf("BMP180_ID:0x%x \r\n", BMP180_ID);
		UT = Get_BMP180UT();           
		UP = Get_BMP180UP();                                
		Convert_UncompensatedToTrue(UT,UP); 
	}
	i++;
	delay_ms(10);
	if(i==20)
	{
		LED0=!LED0;//提示系统正在运行	
		i=0;
	}	
}

