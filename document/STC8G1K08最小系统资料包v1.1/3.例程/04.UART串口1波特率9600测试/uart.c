/******************************************************************
	作者：神秘藏宝室
	店铺：ILoveMCU.taobao.com
	最终解释权归原作者所有，鄙视其他店铺不劳而获的抄袭行为！
******************************************************************/
#include "uart.h"

unsigned char RX_Count = 0;


bit busy;
char wptr;
char rptr;
char buffer[16];

void Uart_Init()					  			   
{
//	SCON = 0X50;  //UART方式1；8位UART
//	REN  = 1;     //允许串行口接收数据
//	PCON = 0x00;  //SMOD=0;波特率不加倍
//	TMOD = 0x20;  //T1方式2，用于产生波特率
//	TH1  = 0xFD;  //装初值
//	TL1  = 0xFD;
//	TR1  = 1;     //启动定时器1
//	EA   = 1;     //打开全局中断控制
//	ES   = 1;     //打开串行口中断

	SCON = 0x50;
	T2L = BRT;
	T2H = BRT >> 8;
	
	AUXR = 0x15;
	wptr = 0x00;
	rptr = 0x00;
	busy = 0;
	
	ES = 1;
	EA = 1;
	
}

void UartPrintf(unsigned char *p)				//发送字符串
{	
 	while (*p)
	{
		UartPrintASCII(*p++);
	}  
}

void UartPrintASCII(unsigned char dat)				//发送一个字符
{ 
    while (busy);
	busy = 1;
	SBUF = dat;   
}


//重写putchar函数
char putchar(char c)
{
    UartPrintASCII(c);
    return c;
}


//void RECEIVE_DATA(void) interrupt 4 using 3	  		
//{ 
//	unsigned char temp = 0;
//	char i = 0;
//	ES=0;
//	temp = SBUF;
//	RI = 0;
//	
//	ES=1; 
//}

void UartIsr() interrupt 4
{
	if (TI)
	{
		TI = 0;
		busy = 0;
	}
	if (RI)
	{
		RI = 0;
		buffer[wptr++] = SBUF;
		wptr &= 0x0f;
	}
}























