#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "tsensor.h"
#include "ad7414.h"
#include "bmp180.h"
#include "bmpi2c.h"
 
//ALIENTEK Mini STM32�����巶������16
//�ڲ��¶ȴ�����ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
 int main(void)
 { 
	u16 adcx;
	float temp;
	float temperate;	 
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
// 	LCD_Init();
 	T_Adc_Init();		  		//ADC��ʼ��	
	AD7414_Init();	 			//AD7414��ʼ��
//	POINT_COLOR=RED;//��������Ϊ��ɫ 
//	LCD_ShowString(60,50,200,16,16,"Mini STM32");
	printf("Temperature TEST \r\n");
//	LCD_ShowString(60,70,200,16,16,"Temperature TEST");	
//	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
//	LCD_ShowString(60,110,200,16,16,"2014/3/9");	
	//��ʾ��ʾ��Ϣ											      
//	POINT_COLOR=BLUE;//��������Ϊ��ɫ
//	LCD_ShowString(60,130,200,16,16,"TEMP_VAL:");	      
//	LCD_ShowString(60,150,200,16,16,"TEMP_VOL:0.000V");	      
//	LCD_ShowString(60,170,200,16,16,"TEMPERATE:00.00C");	  
	while(1)
	{
		adcx=T_Get_Adc_Average(ADC_CH_TEMP,10);
		printf("TEMP_VAL: %d    ", adcx);
//		LCD_ShowxNum(132,130,adcx,4,16,0);//��ʾADC��ֵ
		temp=(float)adcx*(3.3/4096);
		temperate=temp;//�����¶ȴ������ĵ�ѹֵ
		adcx=temp;
		printf("TEMP_VOL: %.4f   ", temp);
		temperate = ((1.43 - temp) / 4.3) + 25;
		printf("TEMP: %.4f   ", temperate);
		
		temperate = AD7414_Read_Temp();
		printf("AD7414 TEMP: %.4f  \r\n", temperate);
//		LCD_ShowxNum(132,150,adcx,1,16,0);     		//��ʾ��ѹֵ��������
//		temp-=(u8)temp;				    			//������������		  
//		LCD_ShowxNum(148,150,temp*1000,3,16,0X80);	//��ʾ��ѹС������
// 		temperate=(1.43-temperate)/0.0043+25;		//�������ǰ�¶�ֵ	 
//		LCD_ShowxNum(140,170,(u8)temperate,2,16,0); //��ʾ�¶���������
//		temperate-=(u8)temperate;	  
//		LCD_ShowxNum(164,170,temperate*100,2,16,0X80);//��ʾ�¶�С������
		LED0=!LED0;
		delay_ms(500);
	}										    
}	
