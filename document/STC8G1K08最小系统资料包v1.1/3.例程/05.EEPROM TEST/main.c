/******************************************
	���ߣ����زر���
	���̣�ILoveMCU.taobao.com
******************************************/


#include	"config.h"
#include	"delay.h"
#include  "uart.h"
#include  "intrins.h"

/*************	����˵��	**************

��������ʾLED��˸  


******************************************/

/*************	���س�������	**************/


/*************	���ر�������	**************/


/*************	���غ�������	**************/



/*************  �ⲿ�����ͱ������� *****************/



/******************** IO���ú��� **************************/
void	GPIO_config(void)
{
	P1M0 = 0x00; 		//����׼˫���
	P1M1 = 0x00;

	P3M0 = 0x00;
	P3M1 = 0x00;
}


void IapIdle()
{
	IAP_CONTR = 0; //�ر� IAP ����
	IAP_CMD = 0; //�������Ĵ���
	IAP_TRIG = 0; //��������Ĵ���
	IAP_ADDRH = 0x80; //����ַ���õ��� IAP ����
	IAP_ADDRL = 0;
}

char IapRead(int addr)
{
	char dat;
	IAP_CONTR = 0x80; //ʹ�� IAP
	IAP_TPS = 12; //���ò����ȴ����� 12MHz
	IAP_CMD = 1; //���� IAP ������
	IAP_ADDRL = addr; //���� IAP �͵�ַ
	IAP_ADDRH = addr >> 8; //���� IAP �ߵ�ַ
	IAP_TRIG = 0x5a; //д��������(0x5a)
	IAP_TRIG = 0xa5; //д��������(0xa5)
	_nop_();
	dat = IAP_DATA; //�� IAP ����
	IapIdle(); //�ر� IAP ����

return dat;
}

void IapProgram(int addr, char dat)
{
	IAP_CONTR = 0x80; //ʹ�� IAP
	IAP_TPS = 12; //���ò����ȴ����� 12MHz
	IAP_CMD = 2; //���� IAP д����
	IAP_ADDRL = addr; //���� IAP �͵�ַ
	IAP_ADDRH = addr >> 8; //���� IAP �ߵ�ַ
	IAP_DATA = dat; //д IAP ����
	IAP_TRIG = 0x5a; //д��������(0x5a)
	IAP_TRIG = 0xa5; //д��������(0xa5)
	_nop_();
	IapIdle(); //�ر� IAP ����
}
void IapErase(int addr)
{
	IAP_CONTR = 0x80; //ʹ�� IAP
	IAP_TPS = 12; //���ò����ȴ����� 12MHz
	IAP_CMD = 3; //���� IAP ��������
	IAP_ADDRL = addr; //���� IAP �͵�ַ
	IAP_ADDRH = addr >> 8; //���� IAP �ߵ�ַ
	IAP_TRIG = 0x5a; //д��������(0x5a)
	IAP_TRIG = 0xa5; //д��������(0xa5)
	_nop_(); //
	IapIdle(); //�ر� IAP ����
}



/******************** ������ **************************/
void main(void)
{
	char test = 0;
	P_SW1 = 0x00; //RXD/P3.0, TXD/P3.1

	GPIO_config();
	Uart_Init();

	
	
	while(1)
	{
		printf("uart test\r\n");

//		IapErase(0x0400);
//		test = IapRead(0x0400); //P0=0xff
//		printf("Erase:%x\r\n",test);
		IapProgram(0x0400, 0x22);
		test = IapRead(0x0400); //P1=0x12
		printf("Program:%x\r\n",test);

		P16 = 0;
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		P16 = 1;
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
	}
}
//
//
//
//
//
//#include "reg51.h"
//#include "intrins.h"
//sfr P0M1 = 0x93;
//sfr P0M0 = 0x94;
//sfr P1M1 = 0x91;
//sfr P1M0 = 0x92;
//sfr P2M1 = 0x95;
//sfr P2M0 = 0x96;
//sfr P3M1 = 0xb1;
//sfr P3M0 = 0xb2;
//sfr P4M1 = 0xb3;
//sfr P4M0 = 0xb4;
//sfr P5M1 = 0xc9;
//sfr P5M0 = 0xca;
//sfr IAP_DATA = 0xC2;
//sfr IAP_ADDRH = 0xC3;
//sfr IAP_ADDRL = 0xC4;
//sfr IAP_CMD = 0xC5;
//sfr IAP_TRIG = 0xC6;
//sfr IAP_CONTR = 0xC7;
//sfr IAP_TPS = 0xF5;
//void IapIdle()
//{
//IAP_CONTR = 0; //�ر� IAP ����
//IAP_CMD = 0; //�������Ĵ���
//IAP_TRIG = 0; //��������Ĵ���
//IAP_ADDRH = 0x80; //����ַ���õ��� IAP ����
//IAP_ADDRL = 0;
//}
//char IapRead(int addr)
//{
//char dat;
//IAP_CONTR = 0x80; //ʹ�� IAP
//IAP_TPS = 12; //���ò����ȴ����� 12MHz
//IAP_CMD = 1; //���� IAP ������
//IAP_ADDRL = addr; //���� IAP �͵�ַ
//IAP_ADDRH = addr >> 8; //���� IAP �ߵ�ַ
//IAP_TRIG = 0x5a; //д��������(0x5a)
//IAP_TRIG = 0xa5; //д��������(0xa5)
//_nop_();
//dat = IAP_DATA; //�� IAP ����
//IapIdle(); //�ر� IAP ����
//
//return dat;
//}
//void IapProgram(int addr, char dat)
//{
//IAP_CONTR = 0x80; //ʹ�� IAP
//IAP_TPS = 12; //���ò����ȴ����� 12MHz
//IAP_CMD = 2; //���� IAP д����
//IAP_ADDRL = addr; //���� IAP �͵�ַ
//IAP_ADDRH = addr >> 8; //���� IAP �ߵ�ַ
//IAP_DATA = dat; //д IAP ����
//IAP_TRIG = 0x5a; //д��������(0x5a)
//IAP_TRIG = 0xa5; //д��������(0xa5)
//_nop_();
//IapIdle(); //�ر� IAP ����
//}
//void IapErase(int addr)
//{
//	IAP_CONTR = 0x80; //ʹ�� IAP
//	IAP_TPS = 12; //���ò����ȴ����� 12MHz
//	IAP_CMD = 3; //���� IAP ��������
//	IAP_ADDRL = addr; //���� IAP �͵�ַ
//	IAP_ADDRH = addr >> 8; //���� IAP �ߵ�ַ
//	IAP_TRIG = 0x5a; //д��������(0x5a)
//	IAP_TRIG = 0xa5; //д��������(0xa5)
//	_nop_(); //
//	IapIdle(); //�ر� IAP ����
//}
//void main()
//{
//	P0M0 = 0x00;
//	P0M1 = 0x00;
//	P1M0 = 0x00;
//	P1M1 = 0x00;
//	P2M0 = 0x00;
//	P2M1 = 0x00;
//	P3M0 = 0x00;
//	P3M1 = 0x00;
//	P4M0 = 0x00;
//	P4M1 = 0x00;
//	P5M0 = 0x00;
//	P5M1 = 0x00;
//	IapErase(0x0400);
//	P0 = IapRead(0x0400); //P0=0xff
//	IapProgram(0x0400, 0x12);
//	P1 = IapRead(0x0400); //P1=0x12
//	while (1);
//}
