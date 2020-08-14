/******************************************************************
	���ߣ����زر���
	���̣�ILoveMCU.taobao.com
	���ս���Ȩ��ԭ�������У������������̲��Ͷ���ĳ�Ϯ��Ϊ��
******************************************************************/
#include "uart.h"

unsigned char RX_Count = 0;


bit busy;
char wptr;
char rptr;
char buffer[16];

void Uart_Init()					  			   
{
//	SCON = 0X50;  //UART��ʽ1��8λUART
//	REN  = 1;     //�����пڽ�������
//	PCON = 0x00;  //SMOD=0;�����ʲ��ӱ�
//	TMOD = 0x20;  //T1��ʽ2�����ڲ���������
//	TH1  = 0xFD;  //װ��ֵ
//	TL1  = 0xFD;
//	TR1  = 1;     //������ʱ��1
//	EA   = 1;     //��ȫ���жϿ���
//	ES   = 1;     //�򿪴��п��ж�

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

void UartPrintf(unsigned char *p)				//�����ַ���
{	
 	while (*p)
	{
		UartPrintASCII(*p++);
	}  
}

void UartPrintASCII(unsigned char dat)				//����һ���ַ�
{ 
    while (busy);
	busy = 1;
	SBUF = dat;   
}


//��дputchar����
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























