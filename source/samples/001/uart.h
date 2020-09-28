#ifndef __UART_H
#define __UART_H

//UART1 初始化
void Uart1Init(void);

//UART1 发送串口数据
void UART1_SendData(char dat);

//UART1 发送字符串
void UART1_SendString(char *s);

//重写putchar函数
char putchar(char c);

#endif