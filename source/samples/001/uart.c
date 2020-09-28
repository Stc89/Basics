#include "stc8g.h"
#include <stdio.h>

//UART1 初始化
void Uart1Init(void)	//115200bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON 	= 0x50;		//8位数据，可变波特率
	AUXR |= 0x04;		//1T模式
//	BRT 	= 0xFD;		//设置独立波特率发生器重装值
	AUXR |=0X01;		//串口1选择独立发生器为波特率发生器
	AUXR |=0X10;		//启动独立波特率发生器
	ES = 1; 			//使能串口1中断
}

//UART1 发送串口数据
void UART1_SendData(char dat)
{
	ES=0;			//关串口中断
	SBUF=dat;			
	while(TI!=1);	//等待发送成功
	TI=0;			//清除发送中断标志
	ES=1;			//开串口中断
}

//UART1 发送字符串
void UART1_SendString(char *s)
{
	while(*s)//检测字符串结束符
	{
		UART1_SendData(*s++);//发送当前字符
	}
}

//重写putchar函数
char putchar(char c)
{
	UART1_SendData(c);
	return c;
}