#include "led.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
//ALIENTEK Mini STM32�����巶������7
//��ʱ���ж�ʵ��   
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
 int main(void)
 {	
	delay_init();	    	 //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	TIM3_Int_Init(9000 - 1,7200 - 1);//10Khz�ļ���Ƶ�ʣ�������9000Ϊ900ms  
   	while(1)
	{
		LED1=!LED1;
		delay_ms(200);		   
	}
}
