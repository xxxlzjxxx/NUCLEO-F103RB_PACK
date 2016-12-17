#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "spi.h"
#include "flash.h"

//ALIENTEK Mini STM32�����巶������20
//SPIʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
   	
//Ҫд�뵽W25Q64���ַ�������
const u8 TEXT_Buffer[]={"MiniSTM32 SPI TEST"};
#define SIZE sizeof(TEXT_Buffer)	 
 int main(void)
 { 
	u8 key;
	u16 i=0, j = 0;
	u8 datatemp[SIZE];
	u32 FLASH_SIZE;
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	LCD_Init();
	KEY_Init();				//������ʼ��		 	
	SPI_Flash_Init();  		//SPI FLASH ��ʼ�� 	 
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	printf("Mini STM32");	
	printf("SPI TEST");	
	printf("ATOM@ALIENTEK");
	printf("2014/3/9");	
	printf("WK_UP:Write  KEY0:Read");	//��ʾ��ʾ��Ϣ		
	while(SPI_Flash_ReadID()!=W25Q64)							//��ⲻ��W25Q64
	{
		printf("25Q64 Check Failed!");
		delay_ms(500);
		printf("Please Check!      ");
		delay_ms(1000);
		LED0=!LED0;//DS0��˸
	}
	printf("25Q64 Ready!");

	FLASH_SIZE=8*1024*1024;	//FLASH ��СΪ8M�ֽ�
  	POINT_COLOR=BLUE;		//��������Ϊ��ɫ	  
	while(1)
	{
		key=KEY_Scan(0);
		if(key==WKUP_PRES)	//WK_UP ����,д��W25Q64
		{
//			LCD_Fill(0,170,239,319,WHITE);//�������    
 			printf("Start Write W25Q64....");
			SPI_Flash_Write((u8*)TEXT_Buffer,FLASH_SIZE-100,SIZE);		//�ӵ�����100����ַ����ʼ,д��SIZE���ȵ�����
			printf("W25Q64 Write Finished!");	//��ʾ�������
		}
		if(key==KEY0_PRES)	//KEY0 ����,��ȡ�ַ�������ʾ
		{
 			printf("Start Read W25Q64.... ");
			SPI_Flash_Read(datatemp,FLASH_SIZE-100,SIZE);				//�ӵ�����100����ַ����ʼ,����SIZE���ֽ�
			printf("The Data Readed Is: ");	//��ʾ�������
			for(j = 0; j < SIZE; j--)
            {
                printf(" %c ", datatemp[j]);					//��ʾ�������ַ���
            }
        }
		i++;
		delay_ms(10);
		if(i==20)
		{
			LED0=!LED0;//��ʾϵͳ��������	
			i=0;
		}		   
	}
}

