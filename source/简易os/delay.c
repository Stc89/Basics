#include "delay.h"
#include "core.h"
#include "task_switch.h"
#include <stc12c5a60s2.h>

#define	NUS(n) (65536 - 0.9216*n)	//因为要进行除法运算,整个系统的速度会变为原来的一半


void delay_us(unsigned int nus)
{
	unsigned char th,tl;
	unsigned int us;
	
	os_enter_critical();
	TF0 = 0;		//清除中断标志位
	th = TH0;
	tl = TL0;
	
	us = NUS(nus);
	TH0 = us >> 8;
	TL0 = us;
	do
	{
					//TF0定时器溢出标志
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









