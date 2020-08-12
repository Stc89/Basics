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

串口3全双工中断方式收发通讯程序。

通过PC向MCU发送数据, MCU收到后通过串口3把收到的数据原样返回.

下载时, 选择时钟 22.1184MHz (用户可自行修改频率).

******************************************/

#include    "reg51.h"

#define MAIN_Fosc       22118400L   //定义主时钟（精确计算115200波特率）

typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;

sfr T2H  = 0xD6;
sfr T2L  = 0xD7;
sfr T3H  = 0xD4;
sfr T3L  = 0xD5;
sfr T4T3M = 0xD1;
sfr IE2   = 0xAF;
sfr INT_CLKO = 0x8F;
sfr AUXR = 0x8E;
sfr P_SW1 = 0xA2;
sfr P_SW2 = 0xBA;
sfr S3CON = 0xAC;
sfr S3BUF = 0xAD;

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


#define Baudrate3   115200L
#define UART3_BUF_LENGTH    64


u8  TX3_Cnt;    //发送计数
u8  RX3_Cnt;    //接收计数
bit B_TX3_Busy; //发送忙标志

u8  idata RX3_Buffer[UART3_BUF_LENGTH]; //接收缓冲


void    UART3_config(u8 brt);   // 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer3做波特率.
void    PrintString3(u8 *puts);


//========================================================================
// 函数: void main(void)
// 描述: 主函数。
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2014-11-28
// 备注: 
//========================================================================
void main(void)
{
    P0M1 = 0;   P0M0 = 0;   //设置为准双向口
    P1M1 = 0;   P1M0 = 0;   //设置为准双向口
    P2M1 = 0;   P2M0 = 0;   //设置为准双向口
    P3M1 = 0;   P3M0 = 0;   //设置为准双向口
    P4M1 = 0xC0;   P4M0 = 0;//P4.6,P4.7设置为输入口(防止实验箱串口2数据口干扰)
    P5M1 = 0;   P5M0 = 0;   //设置为准双向口
    P6M1 = 0;   P6M0 = 0;   //设置为准双向口
    P7M1 = 0;   P7M0 = 0;   //设置为准双向口

    UART3_config(0);    // 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer3做波特率.
    EA = 1; //允许全局中断
    
    PrintString3("STC8H8K64U UART3 Test Programme!\r\n");  //UART3发送一个字符串

    while (1)
    {
        if((TX3_Cnt != RX3_Cnt) && (!B_TX3_Busy))   //收到数据, 发送空闲
        {
            S3BUF = RX3_Buffer[TX3_Cnt];
            B_TX3_Busy = 1;
            if(++TX3_Cnt >= UART3_BUF_LENGTH)   TX3_Cnt = 0;
        }
    }
}


//========================================================================
// 函数: void PrintString3(u8 *puts)
// 描述: 串口3发送字符串函数。
// 参数: puts:  字符串指针.
// 返回: none.
// 版本: VER1.0
// 日期: 2014-11-28
// 备注: 
//========================================================================
void PrintString3(u8 *puts)
{
    for (; *puts != 0;  puts++)     //遇到停止符0结束
    {
        S3BUF = *puts;
        B_TX3_Busy = 1;
        while(B_TX3_Busy);
    }
}

//========================================================================
// 函数: SetTimer2Baudraye(u16 dat)
// 描述: 设置Timer2做波特率发生器。
// 参数: dat: Timer2的重装值.
// 返回: none.
// 版本: VER1.0
// 日期: 2014-11-28
// 备注: 
//========================================================================
void SetTimer2Baudraye(u16 dat)  // 使用Timer2做波特率.
{
    AUXR &= ~(1<<4);    //Timer stop
    AUXR &= ~(1<<3);    //Timer2 set As Timer
    AUXR |=  (1<<2);    //Timer2 set as 1T mode
    T2H = dat / 256;
    T2L = dat % 256;
    IE2  &= ~(1<<2);    //禁止T2中断
    AUXR |=  (1<<4);    //Timer run enable
}

//========================================================================
// 函数: void UART3_config(u8 brt)
// 描述: UART3初始化函数。
// 参数: brt: 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer3做波特率.
// 返回: none.
// 版本: VER1.0
// 日期: 2014-11-28
// 备注: 
//========================================================================
void UART3_config(u8 brt)    // 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer3做波特率.
{
    if(brt == 2)
    {
        SetTimer2Baudraye(65536UL - (MAIN_Fosc / 4) / Baudrate3);
        S3CON = 0x10;       //8位数据, 使用Timer2做波特率发生器, 允许接收
    }
		else
		{
        S3CON = 0x50;       //8位数据, 使用Timer3做波特率发生器, 允许接收
        T3H = (65536UL - (MAIN_Fosc / 4) / Baudrate3) / 256;
        T3L = (65536UL - (MAIN_Fosc / 4) / Baudrate3) % 256;
        T4T3M = 0x0a;
		}
    IE2 |= 0x08;          //允许UART3中断
    P_SW2 &= ~0x02; 
    //P_SW2 |= 0x02;      //UART3 switch bit1 to: 0: P0.0 P0.1,  1: P5.0 P5.1

    B_TX3_Busy = 0;
    TX3_Cnt = 0;
    RX3_Cnt = 0;
}


//========================================================================
// 函数: void UART3_int (void) interrupt UART3_VECTOR
// 描述: UART3中断函数。
// 参数: nine.
// 返回: none.
// 版本: VER1.0
// 日期: 2014-11-28
// 备注: 
//========================================================================
void UART3_int (void) interrupt 17
{
    if((S3CON & 0x01) != 0)
    {
        S3CON &= ~0x01;    //Clear Rx flag
        RX3_Buffer[RX3_Cnt] = S3BUF;
        if(++RX3_Cnt >= UART3_BUF_LENGTH)   RX3_Cnt = 0;
    }

    if((S3CON & 0x02) != 0)
    {
        S3CON &= ~0x02;    //Clear Tx flag
        B_TX3_Busy = 0;
    }
}

