#ifndef __UART_H
#define __UART_H

//UART1 ��ʼ��
void Uart1Init(void);

//UART1 ���ʹ�������
void UART1_SendData(char dat);

//UART1 �����ַ���
void UART1_SendString(char *s);

//��дputchar����
char putchar(char c);

#endif