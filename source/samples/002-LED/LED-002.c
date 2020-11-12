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

#include    "reg51.h"
#include    <string.h>

#define     MAIN_Fosc       24000000L   //������ʱ��

/*************  ����˵��    **************

����ʹ��P6������ʾ����ƣ������������

����ʱ, ѡ��ʱ�� 24MHZ (�û��������޸�Ƶ��).

���û�ʹ��Ӳ�� USB �� STC8H8K64U ϵ�н��� ISP ����ʱ���ܵ����ڲ� IRC ��Ƶ�ʣ�
���û�����ѡ���ڲ�Ԥ�õ� 16 ��Ƶ��
���ֱ��� 5.5296M�� 6M�� 11.0592M�� 12M�� 18.432M�� 20M�� 22.1184M�� 
24M��27M�� 30M�� 33.1776M�� 35M�� 36.864M�� 40M�� 44.2368M �� 48M����
����ʱ�û�ֻ�ܴ�Ƶ�������б��н���ѡ������֮һ���������ֶ���������Ƶ�ʡ�
��ʹ�ô���������������� 4M��48M ֮�������Ƶ�ʣ���

******************************************/

typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;

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

u8 ledIndex;
u8 code ledNum[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

void  delay_ms(u8 ms);

#define KEY_0  P57 /*����*/
#define UP_500W P56 /*�ϲ��*/
#define DOWN_200W P55 /*�²��*/
#define FUNJI P54 /*���*/ 
#define true (1)
#define false (0)

enum STATE{

	STATE_UP_ON, /*�����ϲ��700W*/
	STATE_DOWN_ON, /*�����²��200W*/
	STATE_FUN_ON, /*�������*/
	STATE_TIME1_5MIN, /*��ʱ��1 5����*/
	STATE_TIME2_10MIN, /*��ʱ��2 10����*/
	STATE_TIME3_5MIN, /*��ʱ��3 5����*/
	
	STATE_idle,	  /*����*/
};

struct strg_data{
	int time_cout;
};

enum STATE sys_state;
struct strg_data stu_data;

void gpio_init(void)
{
	P0M1 = 0;   P0M0 = 0;   //����Ϊ׼˫���
    P1M1 = 0;   P1M0 = 0;   //����Ϊ׼˫���
    P2M1 = 0;   P2M0 = 0;   //����Ϊ׼˫���
    P3M1 = 0;   P3M0 = 0;   //����Ϊ׼˫���
    P4M1 = 0;   P4M0 = 0;   //����Ϊ׼˫���
    P5M1 = 0;   P5M0 = 0;   //����Ϊ׼˫���
    P6M1 = 0;   P6M0 = 0;   //����Ϊ׼˫���
    P7M1 = 0;   P7M0 = 0;   //����Ϊ׼˫���
}

unsigned char get_key_value(void)
{
	if(KEY_0 == 1){
		delay_ms(200);
		if(KEY_0 == 1){
			return (true);
		}
	}
	return (false);
}

/******************** ������ **************************/
void main(void)
{

	gpio_init();

	sys_state =  STATE_idle;

	memset(&stu_data,0,sizeof(stu_data));
    while(1)
    {
		if(get_key_value() && sys_state == STATE_idle){
			sys_state = STATE_UP_ON;
		}

		switch(sys_state)
		{
			case STATE_UP_ON:
			{
				 DOWN_200W = 1; /*�����²��*/
				 sys_state = STATE_TIME2_10MIN;	
			}
			break; 
			case STATE_TIME1_5MIN:
			{
				 stu_data.time_cout ++;
				 delay_ms(1000);
				 if(stu_data.time_cout >= 5*60){
				 	stu_data.time_cout = 0;
					sys_state = STATE_DOWN_ON;
				 }
			}
			break; 
			case STATE_TIME2_10MIN:
			{
				 stu_data.time_cout ++;
				 delay_ms(1000);
				 if(stu_data.time_cout >= 10*60){
				 	stu_data.time_cout = 0;
					sys_state = STATE_TIME3_5MIN;

					DOWN_200W = 0; /*�ر��²��*/
					FUNJI = 1; /*�������*/
				 }
			}
			break;
			case STATE_TIME3_5MIN:
			{
				 stu_data.time_cout ++;
				 delay_ms(1000);
				 if(stu_data.time_cout >= 5*60){
				 	stu_data.time_cout = 0;
					sys_state = STATE_idle;

					UP_500W = 0; /*�ر��ϲ��*/
					FUNJI = 0; /*�رշ��*/
				 }
			}
			break;

			default:

			break;
		}
    }
}

//========================================================================
// ����: void  delay_ms(u8 ms)
// ����: ��ʱ������
// ����: ms,Ҫ��ʱ��ms��, ����ֻ֧��1~255ms. �Զ���Ӧ��ʱ��.
// ����: none.
// �汾: VER1.0
// ����: 2013-4-1
// ��ע: 
//========================================================================
void  delay_ms(u8 ms)
{
     u16 i;
     do{
          i = MAIN_Fosc / 13000;
          while(--i)    ;   //14T per loop
     }while(--ms);
}

