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

本程序演示5个定时器的使用, 本例程均使用16位自动重装.

下载时, 选择时钟 24MHZ (用户可自行修改频率).

定时器0做16位自动重装, 中断频率为1000HZ，中断函数从P6.7取反输出500HZ方波信号.

定时器1做16位自动重装, 中断频率为2000HZ，中断函数从P6.6取反输出1000HZ方波信号.

定时器2做16位自动重装, 中断频率为3000HZ，中断函数从P6.5取反输出1500HZ方波信号.

定时器3做16位自动重装, 中断频率为4000HZ，中断函数从P6.4取反输出2000HZ方波信号.

定时器4做16位自动重装, 中断频率为5000HZ，中断函数从P6.3取反输出2500HZ方波信号.

******************************************/

#include "reg51.h"

#define     MAIN_Fosc       24000000UL  //定义主时钟


typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;

sfr INT_CLKO = 0x8F;
sfr AUXR = 0x8E;
sfr IE2   = 0xAF;   //STC8H8K64U系列
sfr T2H  = 0xD6;
sfr T2L  = 0xD7;

sfr T4T3M  = 0xD1;
sfr T4H = 0xD2;
sfr T4L = 0xD3;
sfr T3H = 0xD4;
sfr T3L = 0xD5;

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
sbit P60 = P6^0;
sbit P61 = P6^1;
sbit P62 = P6^2;
sbit P63 = P6^3;
sbit P64 = P6^4;
sbit P65 = P6^5;
sbit P66 = P6^6;
sbit P67 = P6^7;

#define ET2 0x04
#define ET3 0x20
#define ET4 0x40

#define Timer0_Reload   (MAIN_Fosc / 1000)      //Timer 0 中断频率, 1000次/秒
#define Timer1_Reload   (MAIN_Fosc / 2000)      //Timer 1 中断频率, 2000次/秒
#define Timer2_Reload   (MAIN_Fosc / 3000)      //Timer 2 中断频率, 3000次/秒
#define Timer3_Reload   (MAIN_Fosc / 4000)      //Timer 3 中断频率, 4000次/秒
#define Timer4_Reload   (MAIN_Fosc / 5000)      //Timer 4 中断频率, 5000次/秒

void    Timer0_init(void);
void    Timer1_init(void);
void    Timer2_init(void);
void    Timer3_init(void);
void    Timer4_init(void);


//========================================================================
// 函数: void main(void)
// 描述: 主函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
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

    EA = 1;     //打开总中断
		P40 = 0;		//打开LED电源
    
    Timer0_init();
    Timer1_init();
    Timer2_init();
    Timer3_init();
    Timer4_init();

    while (1)
    {

    }
}

//========================================================================
// 函数: void   Timer0_init(void)
// 描述: timer0初始化函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void    Timer0_init(void)
{
        TR0 = 0;    //停止计数

    #if (Timer0_Reload < 64)    // 如果用户设置值不合适， 则不启动定时器
        #error "Timer0设置的中断过快!"

    #elif ((Timer0_Reload/12) < 65536UL)    // 如果用户设置值不合适， 则不启动定时器
        ET0 = 1;    //允许中断
    //  PT0 = 1;    //高优先级中断
        TMOD &= ~0x03;
        TMOD |= 0;  //工作模式, 0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装, 3: 16位自动重装, 不可屏蔽中断
    //  TMOD |=  0x04;  //对外计数或分频
        TMOD &= ~0x04;  //定时
    //  INT_CLKO |=  0x01;  //输出时钟
        INT_CLKO &= ~0x01;  //不输出时钟

        #if (Timer0_Reload < 65536UL)
            AUXR |=  0x80;  //1T mode
            TH0 = (u8)((65536UL - Timer0_Reload) / 256);
            TL0 = (u8)((65536UL - Timer0_Reload) % 256);
        #else
            AUXR &= ~0x80;  //12T mode
            TH0 = (u8)((65536UL - Timer0_Reload/12) / 256);
            TL0 = (u8)((65536UL - Timer0_Reload/12) % 256);
        #endif

        TR0 = 1;    //开始运行

    #else
        #error "Timer0设置的中断过慢!"
    #endif
}

//========================================================================
// 函数: void   Timer1_init(void)
// 描述: timer1初始化函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void    Timer1_init(void)
{
        TR1 = 0;    //停止计数

    #if (Timer1_Reload < 64)    // 如果用户设置值不合适， 则不启动定时器
        #error "Timer1设置的中断过快!"

    #elif ((Timer1_Reload/12) < 65536UL)    // 如果用户设置值不合适， 则不启动定时器
        ET1 = 1;    //允许中断
    //  PT1 = 1;    //高优先级中断
        TMOD &= ~0x30;
        TMOD |= (0 << 4);   //工作模式, 0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装
    //  TMOD |=  0x40;  //对外计数或分频
        TMOD &= ~0x40;  //定时
    //  INT_CLKO |=  0x02;  //输出时钟
        INT_CLKO &= ~0x02;  //不输出时钟

        #if (Timer1_Reload < 65536UL)
            AUXR |=  0x40;  //1T mode
            TH1 = (u8)((65536UL - Timer1_Reload) / 256);
            TL1 = (u8)((65536UL - Timer1_Reload) % 256);
        #else
            AUXR &= ~0x40;  //12T mode
            TH1 = (u8)((65536UL - Timer1_Reload/12) / 256);
            TL1 = (u8)((65536UL - Timer1_Reload/12) % 256);
        #endif

        TR1 = 1;    //开始运行

    #else
        #error "Timer1设置的中断过慢!"
    #endif
}

//========================================================================
// 函数: void   Timer2_init(void)
// 描述: timer2初始化函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void    Timer2_init(void)
{
        AUXR &= ~0x1c;      //停止计数, 定时模式, 12T模式

    #if (Timer2_Reload < 64)    // 如果用户设置值不合适， 则不启动定时器
        #error "Timer2设置的中断过快!"

    #elif ((Timer2_Reload/12) < 65536UL)    // 如果用户设置值不合适， 则不启动定时器
    //  IE2  &= ~ET2;       //禁止中断
        IE2  |=  ET2;       //允许中断
    //  INT_CLKO |=  0x04;  //输出时钟
        INT_CLKO &= ~0x04;  //不输出时钟

        #if (Timer2_Reload < 65536UL)
            AUXR |=  (1<<2);    //1T mode
            T2H = (u8)((65536UL - Timer2_Reload) / 256);
            T2L = (u8)((65536UL - Timer2_Reload) % 256);
        #else
            T2H = (u8)((65536UL - Timer2_Reload/12) / 256);
            T2L = (u8)((65536UL - Timer2_Reload/12) % 256);
        #endif

            AUXR |=  (1<<4);    //开始运行

    #else
        #error "Timer2设置的中断过慢!"
    #endif
}

//========================================================================
// 函数: void   Timer3_init(void)
// 描述: timer3初始化函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void    Timer3_init(void)
{
        T4T3M &= ~0x0f;     //停止计数, 定时模式, 12T模式, 不输出时钟

    #if (Timer3_Reload < 64)    // 如果用户设置值不合适， 则不启动定时器
        #error "Timer3设置的中断过快!"

    #elif ((Timer3_Reload/12) < 65536UL)    // 如果用户设置值不合适， 则不启动定时器
    //  IE2  &= ~ET3;       //禁止中断
        IE2  |=  ET3;       //允许中断
    //  T4T3M |=  0x01;     //输出时钟
    //  T4T3M &= ~0x01;     //不输出时钟

        #if (Timer3_Reload < 65536UL)
            T4T3M |=  (1<<1);    //1T mode
            T3H = (u8)((65536UL - Timer3_Reload) / 256);
            T3L = (u8)((65536UL - Timer3_Reload) % 256);
        #else
            T3H = (u8)((65536UL - Timer3_Reload/12) / 256);
            T3L = (u8)((65536UL - Timer3_Reload/12) % 256);
        #endif

            T4T3M |=  (1<<3);    //开始运行

    #else
        #error "Timer3设置的中断过慢!"
    #endif
}

//========================================================================
// 函数: void   Timer4_init(void)
// 描述: timer4初始化函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void    Timer4_init(void)
{
        T4T3M &= ~0xf0;     //停止计数, 定时模式, 12T模式, 不输出时钟

    #if (Timer4_Reload < 64)    // 如果用户设置值不合适， 则不启动定时器
        #error "Timer4设置的中断过快!"

    #elif ((Timer4_Reload/12) < 65536UL)    // 如果用户设置值不合适， 则不启动定时器
    //  IE2  &= ~ET4;       //禁止中断
        IE2  |=  ET4;       //允许中断
    //  T4T3M |=  0x10;     //输出时钟
    //  T4T3M &= ~0x10;     //不输出时钟

        #if (Timer4_Reload < 65536UL)
            T4T3M |=  (1<<5);    //1T mode
            T4H = (u8)((65536UL - Timer4_Reload) / 256);
            T4L = (u8)((65536UL - Timer4_Reload) % 256);
        #else
            T4H = (u8)((65536UL - Timer4_Reload/12) / 256);
            T4L = (u8)((65536UL - Timer4_Reload/12) % 256);
        #endif

            T4T3M |=  (1<<7);    //开始运行

    #else
        #error "Timer4设置的中断过慢!"
    #endif
}

//========================================================================
// 函数: void timer0_int (void) interrupt TIMER0_VECTOR
// 描述:  timer0中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void timer0_int (void) interrupt 1
{
   P67 = ~P67;
}

//========================================================================
// 函数: void timer1_int (void) interrupt TIMER1_VECTOR
// 描述:  timer1中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void timer1_int (void) interrupt 3
{
   P66 = ~P66;
}

//========================================================================
// 函数: void timer2_int (void) interrupt TIMER2_VECTOR
// 描述:  timer2中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void timer2_int (void) interrupt 12
{
    P65 = ~P65;
}

//========================================================================
// 函数: void timer3_int (void) interrupt TIMER3_VECTOR
// 描述:  timer3中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void timer3_int(void) interrupt 19
{
    P64 = ~P64;
}

//========================================================================
// 函数: void timer4_int (void) interrupt TIMER4_VECTOR
// 描述:  timer4中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void timer4_int(void) interrupt 20
{
    P63 = ~P63;
}
