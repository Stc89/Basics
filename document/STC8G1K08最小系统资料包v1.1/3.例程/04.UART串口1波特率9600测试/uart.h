/******************************************************************
	���ߣ����زر���
	���̣�ILoveMCU.taobao.com
	���ս���Ȩ��ԭ�������У������������̲��Ͷ���ĳ�Ϯ��Ϊ��
******************************************************************/
#ifndef __UART_H__
#define __UART_H__

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BRT (65536 - MAIN_Fosc / 9600 / 4)


//�������߱�������
extern void Uart_Init();
extern void UartPrintf(unsigned char *p);
extern void UartPrintASCII(unsigned char c);
extern void clrStruct();


extern unsigned char RX_Count;



#endif