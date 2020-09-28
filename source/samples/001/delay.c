#include "delay.h"
#include "core.h"
#include "task_switch.h"
#include "stc8g.h"

#define	NUS(n) (65536 - 0.9216*n)	//��ΪҪ���г�������,����ϵͳ���ٶȻ��Ϊԭ����һ��


void delay_us(unsigned int nus)
{
	unsigned char th,tl;
	unsigned int us;
	
	os_enter_critical();
	TF0 = 0;		//����жϱ�־λ
	th = TH0;
	tl = TL0;
	
	us = NUS(nus);
	TH0 = us >> 8;
	TL0 = us;
	do
	{
					//TF0��ʱ�������־
	}while(!TF0);
	TF0 = 0;
	
	TH0 = th;
	TL0 = tl;
	
	os_exit_critical();
}


void delay_ms(unsigned int nms)
{
	unsigned char ms = nms%5;
	
	
	if(nms >= 5)
	{
		os_delay(nms/5);
	}
	delay_us(ms * 1000);
}









