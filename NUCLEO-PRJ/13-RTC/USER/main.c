#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "usmart.h"
#include "rtc.h"
//ALIENTEK Mini STM32�����巶������13
//RTCʵʱʱ��ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
 	
 int main(void)
 { 
	u8 t;	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();				//��ʼ����LED���ӵ�Ӳ���ӿ�
// 	LCD_Init();				//��ʼ��LCD
	usmart_dev.init(72);	//��ʼ��USMART				 	
//	POINT_COLOR=RED;//��������Ϊ��ɫ 
//	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
//	LCD_ShowString(60,70,200,16,16,"RTC TEST");	
//	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
//	LCD_ShowString(60,110,200,16,16,"2014/3/8");	
	while(RTC_Init())		//RTC��ʼ��	��һ��Ҫ��ʼ���ɹ�
	{ 
//		LCD_ShowString(60,130,200,16,16,"RTC ERROR!   ");
		printf("RTC ERROR!   ");
		delay_ms(800);
//		LCD_ShowString(60,130,200,16,16,"RTC Trying...");	
	}		    						
	//��ʾʱ��
//	POINT_COLOR=BLUE;//��������Ϊ��ɫ					 
//	LCD_ShowString(60,130,200,16,16,"    -  -     ");	   
//	LCD_ShowString(60,162,200,16,16,"  :  :  ");	 		    
	while(1)
	{								    
		if(t!=calendar.sec)
		{
			t=calendar.sec;
//			LCD_ShowNum(60,130,calendar.w_year,4,16);									  
//			LCD_ShowNum(100,130,calendar.w_month,2,16);									  
//			LCD_ShowNum(124,130,calendar.w_date,2,16);
			printf("Date: %d-%d-%d \r\n", calendar.w_year, calendar.w_month, calendar.w_date);
			printf("Week: ");
			switch(calendar.week)
			{
				case 0:
//					LCD_ShowString(60,148,200,16,16,"Sunday   ");
					printf("Sunday\r\n");
					break;
				case 1:
//					LCD_ShowString(60,148,200,16,16,"Monday   ");
					printf("Monday\r\n");
					break;
				case 2:
//					LCD_ShowString(60,148,200,16,16,"Tuesday  ");
					printf("Tuesday\r\n");
					break;
				case 3:
//					LCD_ShowString(60,148,200,16,16,"Wednesday");
					printf("Wednesday\r\n");
					break;
				case 4:
//					LCD_ShowString(60,148,200,16,16,"Thursday ");
					printf("Thursday\r\n");
					break;
				case 5:
//					LCD_ShowString(60,148,200,16,16,"Friday   ");
					printf("Friday\r\n");
					break;
				case 6:
//					LCD_ShowString(60,148,200,16,16,"Saturday ");
					printf("Saturday\r\n");
					break;  
			}
//			LCD_ShowNum(60,162,calendar.hour,2,16);									  
//			LCD_ShowNum(84,162,calendar.min,2,16);									  
//			LCD_ShowNum(108,162,calendar.sec,2,16);
			printf("Time: %d:%d:%d \r\n", calendar.hour, calendar.min, calendar.sec);
			LED0=!LED0;
		}	
		delay_ms(10);								  
	};  											    
}	



