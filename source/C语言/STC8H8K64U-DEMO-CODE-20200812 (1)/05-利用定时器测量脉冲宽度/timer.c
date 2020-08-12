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

定时器0做16位自动重装, 中断频率为1000HZ，作为数码管扫描显示.

定时器1做16位自动重装, 中断频率为10000HZ，作为脉冲信号宽度检测.

用STC的MCU的IO方式驱动8位数码管。

P33口产生低电平(用户可自定义修改端口跟检测电平)时进行计时，电平变化后停止计时。

数码管显示脉冲信号宽度，单位0.1ms，测量范围0.1ms~6553.5ms.

下载时, 选择时钟 24MHZ (用户可自行修改频率).

******************************************/

#include "reg51.h"

#define     MAIN_Fosc       24000000UL  //定义主时钟


typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;

sfr INT_CLKO = 0x8F;
sfr AUXR = 0x8E;
sfr IE2  = 0xAF;
sfr T2H  = 0xD6;
sfr T2L  = 0xD7;

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

/****************************** 用户定义宏 ***********************************/
#define Timer0_Reload   (MAIN_Fosc / 1000)      //Timer 0 中断频率, 1000次/秒
#define Timer1_Reload   (MAIN_Fosc / 10000)     //Timer 1 中断频率, 10000次/秒

#define DIS_DOT     0x20
#define DIS_BLACK   0x10
#define DIS_        0x11

/***************************** 本地常量声明 **********************************/
u8 code t_display[]={                       //标准字库
//   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,
//black  -     H    J    K    L    N    o   P    U     t    G    Q    r   M    y
    0x00,0x40,0x76,0x1E,0x70,0x38,0x37,0x5C,0x73,0x3E,0x78,0x3d,0x67,0x50,0x37,0x6e,
    0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x46};    //0. 1. 2. 3. 4. 5. 6. 7. 8. 9. -1

u8 code T_COM[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};      //位码

/***************************** 本地变量声明 **********************************/
u8  LED8[8];        //显示缓冲
u8  display_index;  //显示位索引
bit B_1ms;          //1ms标志
u16 msecond;
u16 Test_cnt;   //显示用的计数变量
u16 Temp_cnt;   //测量用的计数变量

/*****************************************************************************/

void Timer0_init(void);
void Timer1_init(void);
void DisplayScan(void);
void Display(void);

//========================================================================
// 函数: void main(void)
// 描述: 主函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void main(void)
{
    u8  i;
    
    P0M1 = 0;   P0M0 = 0;   //设置为准双向口
    P1M1 = 0;   P1M0 = 0;   //设置为准双向口
    P2M1 = 0;   P2M0 = 0;   //设置为准双向口
    P3M1 = 0;   P3M0 = 0;   //设置为准双向口
    P4M1 = 0;   P4M0 = 0;   //设置为准双向口
    P5M1 = 0;   P5M0 = 0;   //设置为准双向口
    P6M1 = 0;   P6M0 = 0;   //设置为准双向口
    P7M1 = 0;   P7M0 = 0;   //设置为准双向口

    Test_cnt = 0;
    Temp_cnt = 0;
    for(i=0; i<8; i++)  LED8[i] = DIS_BLACK;    //上电消隐
    
    Timer0_init();
    Timer1_init();
    EA = 1;     //打开总中断

    while (1)
    {
        if(B_1ms)   //1ms到
        {
            B_1ms = 0;
            if(++msecond >= 1000)   //1秒到
            {
                msecond = 0;        //清1000ms计数
                Display();          //显示秒计数
            }
        }
    }
}

//========================================================================
// 函数: void Timer0_init(void)
// 描述: timer0初始化函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void Timer0_init(void)
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
// 函数: void Timer1_init(void)
// 描述: timer1初始化函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void Timer1_init(void)
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
// 函数: void timer0_int (void) interrupt TIMER0_VECTOR
// 描述:  timer0中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void timer0_int (void) interrupt 1
{
    DisplayScan();  //1ms扫描显示一位
    B_1ms = 1;      //1ms标志
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
   if(!P33)
   {
      Temp_cnt++;
   }
   else
   {
      if(Temp_cnt>0)
      {
         Test_cnt = Temp_cnt;
         Temp_cnt = 0;
      }
   }
}

/********************** 显示扫描函数 ************************/
void DisplayScan(void)
{   
   P7 = ~T_COM[7-display_index];
   P6 = ~t_display[LED8[display_index]];
   if(++display_index >= 8)   display_index = 0;  //8位结束回0
}

/********************** 显示计数函数 ************************/
void Display(void)
{
    u8  i;
    
    LED8[3] = Test_cnt / 10000;
    LED8[4] = (Test_cnt % 10000) / 1000;
    LED8[5] = (Test_cnt % 1000) / 100;
    LED8[6] = (Test_cnt % 100) / 10;
    LED8[7] = Test_cnt % 10;
    
    for(i=3; i<7; i++)  //消无效0
    {
        if(LED8[i] > 0) break;
        LED8[i] = DIS_BLACK;
    }
}
