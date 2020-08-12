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

比较器的正极可以是 P3.7 端口或者 ADC 的模拟输入通道，

而负极可以是 P3.6 端口或者是内部 BandGap 经过 OP 后的 REFV 电压（1.19V内部固定比较电压）。

通过中断或者查询方式读取比较器比较结果，CMP+的电平低于CMP-的电平P47口输出低电平(LED10亮)，反之输出高电平(LED10灭)。

******************************************/

#include "reg51.h"
#include "intrins.h"

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

sfr P_SW2 = 0xBA;
sfr CMPCR1 = 0xE6;
sfr CMPCR2 = 0xE7;

void CMP_Isr() interrupt 21
{
    CMPCR1 &= ~0x40;                         //清中断标志
    P47 = CMPCR1 & 0x01;                     //中断方式读取比较器比较结果
}

void main()
{
    P0M1 = 0;   P0M0 = 0;   //设置为准双向口
    P1M1 = 0;   P1M0 = 0;   //设置为准双向口
    P2M1 = 0;   P2M0 = 0;   //设置为准双向口
    P3M1 = 0;   P3M0 = 0;   //设置为准双向口
    P4M1 = 0;   P4M0 = 0;   //设置为准双向口
    P5M1 = 0;   P5M0 = 0;   //设置为准双向口
    P6M1 = 0;   P6M0 = 0;   //设置为准双向口
    P7M1 = 0;   P7M0 = 0;   //设置为准双向口
	
    CMPCR2 = 0x00;
    CMPCR2 &= ~0x80;                            //比较器正向输出
//  CMPCR2 |= 0x80;                             //比较器反向输出
    CMPCR2 &= ~0x40;                            //禁止0.1us滤波
//  CMPCR2 |= 0x40;                             //使能0.1us滤波
//  CMPCR2 &= ~0x3f;                            //比较器结果直接输出
    CMPCR2 |= 0x10;                             //比较器结果经过16个去抖时钟后输出
    CMPCR1 = 0x00;
    CMPCR1 |= 0x30;                             //使能比较器边沿中断
//  CMPCR1 &= ~0x20;                            //禁止比较器上升沿中断
//  CMPCR1 |= 0x20;                             //使能比较器上升沿中断
//  CMPCR1 &= ~0x10;                            //禁止比较器下降沿中断
//  CMPCR1 |= 0x10;                             //使能比较器下降沿中断

    CMPCR1 &= ~0x08;                            //P3.7为CMP+输入脚
//  CMPCR1 |= 0x08;                             //ADC输入脚为CMP+输入教

    CMPCR1 &= ~0x04;                            //内部参考电压为CMP-输入脚
//  CMPCR1 |= 0x04;                             //P3.6为CMP-输入脚

//  CMPCR1 &= ~0x02;                            //禁止比较器输出
    CMPCR1 |= 0x02;                             //使能比较器输出
    P_SW2 &= ~0x08;                             //选择P3.4作为比较器输出脚
//  P_SW2 |= 0x08;                              //选择P4.1作为比较器输出脚
    CMPCR1 |= 0x80;                             //使能比较器模块

    EA = 1;

    while (1)
		{
//      P50 = CMPCR1 & 0x01;  //查询方式读取比较器比较结果
		}
}

