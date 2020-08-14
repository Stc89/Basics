/******************************************************************
	作者：神秘藏宝室
	店铺：ILoveMCU.taobao.com
	最终解释权归原作者所有，鄙视其他店铺不劳而获的抄袭行为！
******************************************************************/
#ifndef __UART_H__
#define __UART_H__

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BRT (65536 - MAIN_Fosc / 9600 / 4)


//函数或者变量声明
extern void Uart_Init();
extern void UartPrintf(unsigned char *p);
extern void UartPrintASCII(unsigned char c);
extern void clrStruct();


extern unsigned char RX_Count;



#endif