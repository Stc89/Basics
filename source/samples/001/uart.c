#include "stc8g.h"
#include <stdio.h>

//UART1 ��ʼ��
void Uart1Init(void)	//115200bps@11.0592MHz
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON 	= 0x50;		//8λ���ݣ��ɱ䲨����
	AUXR |= 0x04;		//1Tģʽ
//	BRT 	= 0xFD;		//���ö��������ʷ�������װֵ
	AUXR |=0X01;		//����1ѡ�����������Ϊ�����ʷ�����
	AUXR |=0X10;		//�������������ʷ�����
	ES = 1; 			//ʹ�ܴ���1�ж�
}

//UART1 ���ʹ�������
void UART1_SendData(char dat)
{
	ES=0;			//�ش����ж�
	SBUF=dat;			
	while(TI!=1);	//�ȴ����ͳɹ�
	TI=0;			//��������жϱ�־
	ES=1;			//�������ж�
}

//UART1 �����ַ���
void UART1_SendString(char *s)
{
	while(*s)//����ַ���������
	{
		UART1_SendData(*s++);//���͵�ǰ�ַ�
	}
}

//��дputchar����
char putchar(char c)
{
	UART1_SendData(c);
	return c;
}