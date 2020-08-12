/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����            */
/*---------------------------------------------------------------------*/


/*************  ����˵��    **************

�߼�PWM��ʱ�� PWM5,PWM6,PWM7,PWM8 ÿ��ͨ�����ɶ���ʵ��PWM���.

4��ͨ��PWM������Ҫ���ö�Ӧ����ڣ���ͨ��ʾ�����۲�������ź�.

PWM���ں�ռ�ձȿ����Զ������ã���߿ɴ�65535.

����ʱ, ѡ��ʱ�� 24MHZ (�û��������޸�Ƶ��).

******************************************/

#include    "reg51.h"
#include    "intrins.h"

#define     MAIN_Fosc       24000000L   //������ʱ��

typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;

sfr TH2  = 0xD6;
sfr TL2  = 0xD7;
sfr IE2  = 0xAF;
sfr AUXR = 0x8E;
sfr INT_CLKO = 0x8F;
sfr P_SW1 = 0xA2;
sfr P_SW2 = 0xBA;

sfr P4   = 0xC0;
sfr P5   = 0xC8;
sfr P6   = 0xE8;
sfr P7   = 0xF8;
sfr P1M1 = 0x91;    //PxM1.n,PxM0.n     =00--->Standard,    01--->push-pull
sfr P1M0 = 0x92;    //                  =10--->pure input,  11--->open drain
sfr P0M1 = 0x93;
sfr P0M0 = 0x94;
sfr P2M1 = 0x95;
sfr P2M0 = 0x96;
sfr P3M1 = 0xB1;
sfr P3M0 = 0xB2;
sfr P4M1 = 0xB3;
sfr P4M0 = 0xB4;
sfr P5M1 = 0xC9;
sfr P5M0 = 0xCA;
sfr P6M1 = 0xCB;
sfr P6M0 = 0xCC;
sfr P7M1 = 0xE1;
sfr P7M0 = 0xE2;

sbit P00 = P0^0;
sbit P01 = P0^1;
sbit P02 = P0^2;
sbit P03 = P0^3;
sbit P04 = P0^4;
sbit P05 = P0^5;
sbit P06 = P0^6;
sbit P07 = P0^7;
sbit P10 = P1^0;
sbit P11 = P1^1;
sbit P12 = P1^2;
sbit P13 = P1^3;
sbit P14 = P1^4;
sbit P15 = P1^5;
sbit P16 = P1^6;
sbit P17 = P1^7;
sbit P20 = P2^0;
sbit P21 = P2^1;
sbit P22 = P2^2;
sbit P23 = P2^3;
sbit P24 = P2^4;
sbit P25 = P2^5;
sbit P26 = P2^6;
sbit P27 = P2^7;
sbit P30 = P3^0;
sbit P31 = P3^1;
sbit P32 = P3^2;
sbit P33 = P3^3;
sbit P34 = P3^4;
sbit P35 = P3^5;
sbit P36 = P3^6;
sbit P37 = P3^7;
sbit P40 = P4^0;
sbit P41 = P4^1;
sbit P42 = P4^2;
sbit P43 = P4^3;
sbit P44 = P4^4;
sbit P45 = P4^5;
sbit P46 = P4^6;
sbit P47 = P4^7;
sbit P50 = P5^0;
sbit P51 = P5^1;
sbit P52 = P5^2;
sbit P53 = P5^3;
sbit P54 = P5^4;
sbit P55 = P5^5;
sbit P56 = P5^6;
sbit P57 = P5^7;

/****************************** �û������ ***********************************/

#define Timer0_Reload   (65536UL -(MAIN_Fosc / 1000))       //Timer 0 �ж�Ƶ��, 1000��/��

#define PWM2_ETRPS   (*(unsigned char  volatile xdata *)  0xFEB4)
#define PWM2_ENO     (*(unsigned char  volatile xdata *)  0xFEB5)
#define PWM2_PS      (*(unsigned char  volatile xdata *)  0xFEB6)
#define PWM2_IOAUX   (*(unsigned char  volatile xdata *)  0xFEB7)

#define PWM2_CR1     (*(unsigned char  volatile xdata *)  0xFEE0)
#define PWM2_CR2     (*(unsigned char  volatile xdata *)  0xFEE1)
#define PWM2_SMCR    (*(unsigned char  volatile xdata *)  0xFEE2)
#define PWM2_ETR     (*(unsigned char  volatile xdata *)  0xFEE3)
#define PWM2_IER     (*(unsigned char  volatile xdata *)  0xFEE4)
#define PWM2_SR1     (*(unsigned char  volatile xdata *)  0xFEE5)
#define PWM2_SR2     (*(unsigned char  volatile xdata *)  0xFEE6)
#define PWM2_EGR     (*(unsigned char  volatile xdata *)  0xFEE7)
#define PWM2_CCMR1   (*(unsigned char  volatile xdata *)  0xFEE8)
#define PWM2_CCMR2   (*(unsigned char  volatile xdata *)  0xFEE9)
#define PWM2_CCMR3   (*(unsigned char  volatile xdata *)  0xFEEA)
#define PWM2_CCMR4   (*(unsigned char  volatile xdata *)  0xFEEB)
#define PWM2_CCER1   (*(unsigned char  volatile xdata *)  0xFEEC)
#define PWM2_CCER2   (*(unsigned char  volatile xdata *)  0xFEED)
#define PWM2_CNTRH   (*(unsigned char  volatile xdata *)  0xFEEE)
#define PWM2_CNTRL   (*(unsigned char  volatile xdata *)  0xFEEF)
#define PWM2_PSCRH   (*(unsigned char  volatile xdata *)  0xFEF0)
#define PWM2_PSCRL   (*(unsigned char  volatile xdata *)  0xFEF1)
#define PWM2_ARRH    (*(unsigned char  volatile xdata *)  0xFEF2)
#define PWM2_ARRL    (*(unsigned char  volatile xdata *)  0xFEF3)
#define PWM2_RCR     (*(unsigned char  volatile xdata *)  0xFEF4)
#define PWM2_CCR1H   (*(unsigned char  volatile xdata *)  0xFEF5)
#define PWM2_CCR1L   (*(unsigned char  volatile xdata *)  0xFEF6)
#define PWM2_CCR2H   (*(unsigned char  volatile xdata *)  0xFEF7)
#define PWM2_CCR2L   (*(unsigned char  volatile xdata *)  0xFEF8)
#define PWM2_CCR3H   (*(unsigned char  volatile xdata *)  0xFEF9)
#define PWM2_CCR3L   (*(unsigned char  volatile xdata *)  0xFEFA)
#define PWM2_CCR4H   (*(unsigned char  volatile xdata *)  0xFEFB)
#define PWM2_CCR4L   (*(unsigned char  volatile xdata *)  0xFEFC)
#define PWM2_BKR     (*(unsigned char  volatile xdata *)  0xFEFD)
#define PWM2_DTR     (*(unsigned char  volatile xdata *)  0xFEFE)
#define PWM2_OISR    (*(unsigned char  volatile xdata *)  0xFEFF)

/*****************************************************************************/

#define PWM5_0      0x00	//P2.0
#define PWM5_1      0x01	//P1.7
#define PWM5_2      0x02	//P0.0
#define PWM5_3      0x03	//P7.4

#define PWM6_0      0x00	//P2.1
#define PWM6_1      0x04	//P5.4
#define PWM6_2      0x08	//P0.1
#define PWM6_3      0x0C	//P7.5

#define PWM7_0      0x00	//P2.2
#define PWM7_1      0x10	//P3.3
#define PWM7_2      0x20	//P0.2
#define PWM7_3      0x30	//P7.6

#define PWM8_0      0x00	//P2.3
#define PWM8_1      0x40	//P3.4
#define PWM8_2      0x80	//P0.3
#define PWM8_3      0xC0	//P7.7

#define ENO5P       0x01
#define ENO6P       0x04
#define ENO7P       0x10
#define ENO8P       0x40

/***************************** ���ر������� **********************************/
bit B_1ms;          //1ms��־

u16 PWM5_Duty;
u16 PWM6_Duty;
u16 PWM7_Duty;
u16 PWM8_Duty;

bit PWM5_Flag;
bit PWM6_Flag;
bit PWM7_Flag;
bit PWM8_Flag;

void UpdatePwm(void);

/******************************** ������ ************************************/
void main(void)
{
    P0M1 = 0;   P0M0 = 0;   //����Ϊ׼˫���
    P1M1 = 0;   P1M0 = 0;   //����Ϊ׼˫���
    P2M1 = 0;   P2M0 = 0;   //����Ϊ׼˫���
    P3M1 = 0;   P3M0 = 0;   //����Ϊ׼˫���
    P4M1 = 0;   P4M0 = 0;   //����Ϊ׼˫���
    P5M1 = 0;   P5M0 = 0;   //����Ϊ׼˫���
    P6M1 = 0;   P6M0 = 0;   //����Ϊ׼˫���
    P7M1 = 0;   P7M0 = 0;   //����Ϊ׼˫���

		PWM5_Flag = 0;
		PWM6_Flag = 0;
		PWM7_Flag = 0;
		PWM8_Flag = 0;
	
		PWM5_Duty = 0;
		PWM6_Duty = 256;
		PWM7_Duty = 512;
		PWM8_Duty = 1024;

    //  Timer0��ʼ��
    AUXR = 0x80;    //Timer0 set as 1T, 16 bits timer auto-reload, 
    TH0 = (u8)(Timer0_Reload / 256);
    TL0 = (u8)(Timer0_Reload % 256);
    ET0 = 1;    //Timer0 interrupt enable
    TR0 = 1;    //Tiner0 run

		P_SW2 |= 0x80;
    PWM2_CCER1 = 0x00; //д CCMRx ǰ���������� CCxE �ر�ͨ��
    PWM2_CCER2 = 0x00;
    PWM2_CCMR1 = 0x60; //ͨ��ģʽ����
    PWM2_CCMR2 = 0x60;
    PWM2_CCMR3 = 0x60;
    PWM2_CCMR4 = 0x60;
    PWM2_CCER1 = 0x33; //����ͨ�����ʹ�ܺͼ���
    PWM2_CCER2 = 0x33;

    PWM2_ARRH = 0x03; //��������ʱ��
    PWM2_ARRL = 0xff;

    PWM2_ENO = 0x00;
    PWM2_ENO |= ENO5P; //ʹ�����
    PWM2_ENO |= ENO6P; //ʹ�����
    PWM2_ENO |= ENO7P; //ʹ�����
    PWM2_ENO |= ENO8P; //ʹ�����

		PWM2_PS = 0x00;    //�߼� PWM ͨ�������ѡ��λ
    PWM2_PS |= PWM5_0; //ѡ�� PWM5_0 ͨ��
    PWM2_PS |= PWM6_0; //ѡ�� PWM6_0 ͨ��
    PWM2_PS |= PWM7_0; //ѡ�� PWM7_0 ͨ��
    PWM2_PS |= PWM8_0; //ѡ�� PWM8_0 ͨ��

    PWM2_BKR = 0x80;   //ʹ�������
    PWM2_CR1 |= 0x01;  //��ʼ��ʱ
		P_SW2 &= 0x7f;

    EA = 1;     //�����ж�

    while (1)
    {
		}
}


/********************** Timer0 1ms�жϺ��� ************************/
void timer0(void) interrupt 1
{
		if(!PWM5_Flag)
		{
				PWM5_Duty++;
				if(PWM5_Duty >= 2047) PWM5_Flag = 1;
		}
		else
		{
				PWM5_Duty--;
				if(PWM5_Duty <= 0) PWM5_Flag = 0;
		}

		if(!PWM6_Flag)
		{
				PWM6_Duty++;
				if(PWM6_Duty >= 2047) PWM6_Flag = 1;
		}
		else
		{
				PWM6_Duty--;
				if(PWM6_Duty <= 0) PWM6_Flag = 0;
		}

		if(!PWM7_Flag)
		{
				PWM7_Duty++;
				if(PWM7_Duty >= 2047) PWM7_Flag = 1;
		}
		else
		{
				PWM7_Duty--;
				if(PWM7_Duty <= 0) PWM7_Flag = 0;
		}

		if(!PWM8_Flag)
		{
				PWM8_Duty++;
				if(PWM8_Duty >= 2047) PWM8_Flag = 1;
		}
		else
		{
				PWM8_Duty--;
				if(PWM8_Duty <= 0) PWM8_Flag = 0;
		}
		
		UpdatePwm();
}


//========================================================================
// ����: UpdatePwm(void)
// ����: ����PWMռ�ձ�. 
// ����: none.
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================
void UpdatePwm(void)
{
		P_SW2 |= 0x80;
	  PWM2_CCR1H = (u8)(PWM5_Duty >> 8); //����ռ�ձ�ʱ��
    PWM2_CCR1L = (u8)(PWM5_Duty);
	  PWM2_CCR2H = (u8)(PWM6_Duty >> 8); //����ռ�ձ�ʱ��
    PWM2_CCR2L = (u8)(PWM6_Duty);
	  PWM2_CCR3H = (u8)(PWM7_Duty >> 8); //����ռ�ձ�ʱ��
    PWM2_CCR3L = (u8)(PWM7_Duty);
	  PWM2_CCR4H = (u8)(PWM8_Duty >> 8); //����ռ�ձ�ʱ��
    PWM2_CCR4L = (u8)(PWM8_Duty);
		P_SW2 &= 0x7f;
}

