#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"  
#include "24cxx.h" 
#include "myiic.h"
#include "BMP180.h"
//ALIENTEK Mini STM32�����巶������3
//����ʵ��   
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾

//Ҫд�뵽24c02���ַ�������
const u8 TEXT_Buffer[]={"xxxlzjxxx IIC TEST"};
#define SIZE sizeof(TEXT_Buffer)	

u8 BMP180_ID=0;          //BMP180��ID

void AT24CXX_Test(void);
void BMP180_Test(void);

int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�	
	KEY_Init();				//������ʼ��		 	
//	BMP180_PortInit();			//IIC��ʼ�� 
	AT24CXX_Init();
	while(1)
	{
		AT24CXX_Test();
	}	 
}
/*AT24CXX���Գ���*/
/*����δͨ��*/
void AT24CXX_Test(void)
{
	u8 key;
	u16 i = 0, j = 0;
	u8 datatemp[SIZE];	
	
	while(AT24CXX_Check())//��ⲻ��24c02
	{
		printf("24C02 Check Failed!  Please Check!      \r\n");
		delay_ms(5000);
		LED0=!LED0;//DS0��˸
	}
	printf("24C02 Ready!\r\n");	
	key = KEY_Scan(0);
	if(key == WKUP_PRES)//WK_UP ����,д��24C02
	{  
 		printf("Start Write 24C02....\r\n");
		AT24CXX_Write(0,(u8*)TEXT_Buffer,SIZE);
		printf("24C02 Write Finished!\r\n");//��ʾ�������
	}
	if(key == KEY0_PRES)//KEY0 ����,��ȡ�ַ�������ʾ
	{
 		printf("Start Read 24C02.... \r\n");
		AT24CXX_Read(0,datatemp,SIZE);
		printf("The Data Readed Is:  ");//��ʾ�������
		for(j = SIZE; j > 0; j--)
		{
			printf(" %c ", datatemp[i]);//��ʾ�������ַ���
		}
		printf("\r\n");
	}
	i++;
	delay_ms(10);
	if(i==20)
	{
		LED0=!LED0;//��ʾϵͳ��������	
		i=0;
	}	
}
/*BMP180���Գ���*/
/*����δͨ��*/
void BMP180_Test(void)
{
	u8 key;
	u16 i = 0;

	key = KEY_Scan(0);
	if(key == KEY0_PRES)//KEY0 ����,��ȡ�ַ�������ʾ
	{
		long UT,UP;
		Read_CalibrationData();         //��ȡBMP180��У׼ϵ��
		BMP180_ID = BMP180_ReadOneByte(0xd0);      //��ȡID��ַ
		printf("BMP180_ID:0x%x \r\n", BMP180_ID);
		UT = Get_BMP180UT();           
		UP = Get_BMP180UP();                                
		Convert_UncompensatedToTrue(UT,UP); 
	}
	i++;
	delay_ms(10);
	if(i==20)
	{
		LED0=!LED0;//��ʾϵͳ��������	
		i=0;
	}	
}

