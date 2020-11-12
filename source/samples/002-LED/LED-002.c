/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序            */
/*---------------------------------------------------------------------*/

#include    "reg51.h"
#include    <string.h>

#define     MAIN_Fosc       24000000L   //定义主时钟

/*************  功能说明    **************

程序使用P6口来演示跑马灯，输出低驱动。

下载时, 选择时钟 24MHZ (用户可自行修改频率).

当用户使用硬件 USB 对 STC8H8K64U 系列进行 ISP 下载时不能调节内部 IRC 的频率，
但用户可用选择内部预置的 16 个频率
（分别是 5.5296M、 6M、 11.0592M、 12M、 18.432M、 20M、 22.1184M、 
24M、27M、 30M、 33.1776M、 35M、 36.864M、 40M、 44.2368M 和 48M）。
下载时用户只能从频率下拉列表中进行选择其中之一，而不能手动输入其他频率。
（使用串口下载则可用输入 4M～48M 之间的任意频率）。

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

#define KEY_0  P57 /*按键*/
#define UP_500W P56 /*上层管*/
#define DOWN_200W P55 /*下层管*/
#define FUNJI P54 /*风机*/ 
#define true (1)
#define false (0)

enum STATE{

	STATE_UP_ON, /*启动上层管700W*/
	STATE_DOWN_ON, /*启动下层管200W*/
	STATE_FUN_ON, /*启动风机*/
	STATE_TIME1_5MIN, /*定时器1 5分钟*/
	STATE_TIME2_10MIN, /*定时器2 10分钟*/
	STATE_TIME3_5MIN, /*定时器3 5分钟*/
	
	STATE_idle,	  /*空闲*/
};

struct strg_data{
	int time_cout;
};

enum STATE sys_state;
struct strg_data stu_data;

void gpio_init(void)
{
	P0M1 = 0;   P0M0 = 0;   //设置为准双向口
    P1M1 = 0;   P1M0 = 0;   //设置为准双向口
    P2M1 = 0;   P2M0 = 0;   //设置为准双向口
    P3M1 = 0;   P3M0 = 0;   //设置为准双向口
    P4M1 = 0;   P4M0 = 0;   //设置为准双向口
    P5M1 = 0;   P5M0 = 0;   //设置为准双向口
    P6M1 = 0;   P6M0 = 0;   //设置为准双向口
    P7M1 = 0;   P7M0 = 0;   //设置为准双向口
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

/******************** 主函数 **************************/
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
				 DOWN_200W = 1; /*启动下层管*/
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

					DOWN_200W = 0; /*关闭下层管*/
					FUNJI = 1; /*启动风机*/
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

					UP_500W = 0; /*关闭上层管*/
					FUNJI = 0; /*关闭风机*/
				 }
			}
			break;

			default:

			break;
		}
    }
}

//========================================================================
// 函数: void  delay_ms(u8 ms)
// 描述: 延时函数。
// 参数: ms,要延时的ms数, 这里只支持1~255ms. 自动适应主时钟.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void  delay_ms(u8 ms)
{
     u16 i;
     do{
          i = MAIN_Fosc / 13000;
          while(--i)    ;   //14T per loop
     }while(--ms);
}

