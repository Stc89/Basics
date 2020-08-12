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

/*************  功能说明    **************

程序使用P6口做跑马灯，演示系统时钟源切换效果。

跑马灯每跑一轮切换一次时钟源，分别是默认IRC主频，主频48分频，内部32K IRC。

下载时, 选择时钟 24MHZ (用户可自行修改频率).

******************************************/

#include    "reg51.h"

#define     MAIN_Fosc       24000000L   //定义主时钟

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

sfr P_SW2 = 0xba;

#define CKSEL (*(unsigned char volatile xdata *)0xfe00)
#define CLKDIV (*(unsigned char volatile xdata *)0xfe01)
#define HIRCCR (*(unsigned char volatile xdata *)0xfe02)
#define XOSCCR (*(unsigned char volatile xdata *)0xfe03)
#define IRC32KCR (*(unsigned char volatile xdata *)0xfe04)

u8 ledIndex;
u8 code ledNum[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
u8 mode = 1;

void  delay_ms(u8 ms);
void  MCLK_Sel(void);

/******************** 主函数 **************************/
void main(void)
{
    P0M1 = 0;   P0M0 = 0;   //设置为准双向口
    P1M1 = 0;   P1M0 = 0;   //设置为准双向口
    P2M1 = 0;   P2M0 = 0;   //设置为准双向口
    P3M1 = 0;   P3M0 = 0;   //设置为准双向口
    P4M1 = 0;   P4M0 = 0;   //设置为准双向口
    P5M1 = 0;   P5M0 = 0;   //设置为准双向口
    P6M1 = 0;   P6M0 = 0;   //设置为准双向口
    P7M1 = 0;   P7M0 = 0;   //设置为准双向口

    P40 = 0;		//LED Power On
		ledIndex = 0;
    while(1)
    {
        P6 = ~ledNum[ledIndex];	//输出低驱动
				ledIndex++;
				if(ledIndex > 7)
				{
						ledIndex = 0;
						MCLK_Sel();
				}
        delay_ms(10);
    }
}

//========================================================================
// 函数: void  MCLK_Sel(void)
// 描述: 系统时钟设置函数。
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2020-7-29
// 备注: 
//========================================================================
void  MCLK_Sel(void)
{
    if(mode == 0)
    {
				mode++;
        P_SW2 = 0x80;
        HIRCCR = 0x80; //启动内部 IRC
        while (!(HIRCCR & 1)); //等待时钟稳定
        CLKDIV = 0;
        CKSEL = 0x00; //选择内部 IRC ( 默认 )
        P_SW2 = 0x00;
    }
    else if(mode == 1)
    {
				mode++;
        P_SW2 = 0x80;
        HIRCCR = 0x80; //启动内部 IRC
        while (!(HIRCCR & 1)); //等待时钟稳定
        CLKDIV = 48;   //MCLK/48
        CKSEL = 0x00; //选择内部 IRC ( 默认 )
        P_SW2 = 0x00;
    }
//    else if(mode == 2)
//    {
//				mode++;
//        P_SW2 = 0x80;
//				XOSCCR = 0xc0; //启动外部晶振
//				while (!(XOSCCR & 1)); //等待时钟稳定
//				CLKDIV = 0x00; //时钟不分频
//				CKSEL = 0x01; //选择外部晶振
//        P_SW2 = 0x00;
//    }
    else
    {
        mode = 0;
        P_SW2 = 0x80;
        IRC32KCR = 0x80; //启动内部 32K IRC
        while (!(IRC32KCR & 1)); //等待时钟稳定
        CLKDIV = 0x00; //时钟不分频
        CKSEL = 0x03; //选择内部 32K
        P_SW2 = 0x00;
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

