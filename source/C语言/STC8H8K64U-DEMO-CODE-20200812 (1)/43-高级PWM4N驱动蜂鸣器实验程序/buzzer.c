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

通过P2.7口输出PWM驱动蜂鸣器.

行列扫描按键每个按键按下后蜂鸣器响一下.

下载时, 选择时钟 24MHZ (用户可自行修改频率).

******************************************/

#include    "reg51.h"
#include    "intrins.h"

#define     MAIN_Fosc       24000000L   //定义主时钟

typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;

sfr TH2  = 0xD6;
sfr TL2  = 0xD7;
sfr IE2   = 0xAF;
sfr INT_CLKO = 0x8F;
sfr AUXR = 0x8E;
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

/****************************** 用户定义宏 ***********************************/

#define Timer0_Reload   (65536UL -(MAIN_Fosc / 1000))       //Timer 0 中断频率, 1000次/秒

#define PWM1_ENO     (*(unsigned char  volatile xdata *)  0xFEB1)
#define PWM1_PS      (*(unsigned char  volatile xdata *)  0xFEB2)
#define PWM2_ENO     (*(unsigned char  volatile xdata *)  0xFEB5)
#define PWM2_PS      (*(unsigned char  volatile xdata *)  0xFEB6)                               

#define PWM1_CR1     (*(unsigned char  volatile xdata *)  0xFEC0)
#define PWM1_CR2     (*(unsigned char  volatile xdata *)  0xFEC1)
#define PWM1_SMCR    (*(unsigned char  volatile xdata *)  0xFEC2) 
#define PWM1_ETR     (*(unsigned char  volatile xdata *)  0xFEC3) 
#define PWM1_IER     (*(unsigned char  volatile xdata *)  0xFEC4) 
#define PWM1_SR1     (*(unsigned char  volatile xdata *)  0xFEC5) 
#define PWM1_SR2     (*(unsigned char  volatile xdata *)  0xFEC6) 
#define PWM1_EGR     (*(unsigned char  volatile xdata *)  0xFEC7) 
#define PWM1_CCMR1   (*(unsigned char  volatile xdata *)  0xFEC8) 
#define PWM1_CCMR2   (*(unsigned char  volatile xdata *)  0xFEC9)
#define PWM1_CCMR3   (*(unsigned char  volatile xdata *)  0xFECA)
#define PWM1_CCMR4   (*(unsigned char  volatile xdata *)  0xFECB)
#define PWM1_CCER1   (*(unsigned char  volatile xdata *)  0xFECC)
#define PWM1_CCER2   (*(unsigned char  volatile xdata *)  0xFECD)
#define PWM1_CNTRH   (*(unsigned char  volatile xdata *)  0xFECE)
#define PWM1_CNTRL   (*(unsigned char  volatile xdata *)  0xFECF)
#define PWM1_PSCRH   (*(unsigned char  volatile xdata *)  0xFED0)
#define PWM1_PSCRL   (*(unsigned char  volatile xdata *)  0xFED1)
#define PWM1_ARRH    (*(unsigned char  volatile xdata *)  0xFED2)
#define PWM1_ARRL    (*(unsigned char  volatile xdata *)  0xFED3)
#define PWM1_RCR     (*(unsigned char  volatile xdata *)  0xFED4)
#define PWM1_CCR1H   (*(unsigned char  volatile xdata *)  0xFED5)
#define PWM1_CCR1L   (*(unsigned char  volatile xdata *)  0xFED6)
#define PWM1_CCR2H   (*(unsigned char  volatile xdata *)  0xFED7)
#define PWM1_CCR2L   (*(unsigned char  volatile xdata *)  0xFED8)
#define PWM1_CCR3H   (*(unsigned char  volatile xdata *)  0xFED9)
#define PWM1_CCR3L   (*(unsigned char  volatile xdata *)  0xFEDA)
#define PWM1_CCR4H   (*(unsigned char  volatile xdata *)  0xFEDB)
#define PWM1_CCR4L   (*(unsigned char  volatile xdata *)  0xFEDC)
#define PWM1_BKR     (*(unsigned char  volatile xdata *)  0xFEDD)
#define PWM1_DTR     (*(unsigned char  volatile xdata *)  0xFEDE)
#define PWM1_OISR    (*(unsigned char  volatile xdata *)  0xFEDF)

/*****************************************************************************/

#define PWM1_0      0x00	//P:P1.0  N:P1.1
#define PWM1_1      0x01	//P:P2.0  N:P2.1
#define PWM1_2      0x02	//P:P6.0  N:P6.1

#define PWM2_0      0x00	//P:P1.2/P5.4  N:P1.3
#define PWM2_1      0x04	//P:P2.2  N:P2.3
#define PWM2_2      0x08	//P:P6.2  N:P6.3

#define PWM3_0      0x00	//P:P1.4  N:P1.5
#define PWM3_1      0x10	//P:P2.4  N:P2.5
#define PWM3_2      0x20	//P:P6.4  N:P6.5

#define PWM4_0      0x00	//P:P1.6  N:P1.7
#define PWM4_1      0x40	//P:P2.6  N:P2.7
#define PWM4_2      0x80	//P:P6.6  N:P6.7
#define PWM4_3      0xC0	//P:P3.4  N:P3.3

#define ENO1P       0x01
#define ENO1N       0x02
#define ENO2P       0x04
#define ENO2N       0x08
#define ENO3P       0x10
#define ENO3N       0x20
#define ENO4P       0x40
#define ENO4N       0x80

/*************  本地变量声明    **************/
bit B_1ms;          //1ms标志

u8 cnt50ms;
u8  KeyCode;    //给用户使用的键码, 1~16有效
u8 IO_KeyState, IO_KeyState1, IO_KeyHoldCnt;    //行列键盘变量

void IO_KeyScan(void);   //50ms call
void  delay_ms(u8 ms);
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

    //  Timer0初始化
    AUXR = 0x80;    //Timer0 set as 1T, 16 bits timer auto-reload, 
    TH0 = (u8)(Timer0_Reload / 256);
    TL0 = (u8)(Timer0_Reload % 256);
    ET0 = 1;    //Timer0 interrupt enable
    TR0 = 1;    //Tiner0 run

		P_SW2 |= 0x80;
		
    PWM1_CCER2 = 0x00;
    PWM1_CCMR4 = 0x30;
    PWM1_CCER2 = 0x50;

    PWM1_ARRH = 0x07; //设置周期时间
    PWM1_ARRL = 0xff;

    PWM1_ENO = 0x00;
    PWM1_ENO |= ENO4N; //使能输出

		PWM1_PS = 0x00;  //高级 PWM 通道输出脚选择位
    PWM1_PS |= PWM4_1; //选择 PWM4_2 通道

    PWM1_BKR = 0x80; //使能主输出
    PWM1_CR1 |= 0x01; //开始计时

    delay_ms(250);
    delay_ms(250);
    PWM1_ENO = 0x00;
		
    P_SW2 &= 0x7f;
    EA = 1;     //打开总中断

    while (1)
    {
        if(B_1ms)   //1ms到
        {
            B_1ms = 0;
            if(++cnt50ms >= 50)     //50ms扫描一次行列键盘
            {
                cnt50ms = 0;
                IO_KeyScan();
            }
            
            if(KeyCode > 0)     //有键按下
            {
                P_SW2 |= 0x80;
                PWM1_ENO |= ENO4N; //使能输出
                delay_ms(250);
                PWM1_ENO = 0x00;
                P_SW2 &= 0x7f;
                KeyCode = 0;
            }
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


/********************** Timer0 1ms中断函数 ************************/
void timer0(void) interrupt 1
{
    B_1ms = 1;      //1ms标志
}


/*****************************************************
    行列键扫描程序
    使用XY查找4x4键的方法，只能单键，速度快

   Y     P04      P05      P06      P07
          |        |        |        |
X         |        |        |        |
P00 ---- K00 ---- K01 ---- K02 ---- K03 ----
          |        |        |        |
P01 ---- K04 ---- K05 ---- K06 ---- K07 ----
          |        |        |        |
P02 ---- K08 ---- K09 ---- K10 ---- K11 ----
          |        |        |        |
P03 ---- K12 ---- K13 ---- K14 ---- K15 ----
          |        |        |        |
******************************************************/


u8 code T_KeyTable[16] = {0,1,2,0,3,0,0,0,4,0,0,0,0,0,0,0};

void IO_KeyDelay(void)
{
    u8 i;
    i = 60;
    while(--i)  ;
}

void IO_KeyScan(void)    //50ms call
{
    u8  j;

    j = IO_KeyState1;   //保存上一次状态

    P0 = 0xf0;  //X低，读Y
    IO_KeyDelay();
    IO_KeyState1 = P0 & 0xf0;

    P0 = 0x0f;  //Y低，读X
    IO_KeyDelay();
    IO_KeyState1 |= (P0 & 0x0f);
    IO_KeyState1 ^= 0xff;   //取反
    
    if(j == IO_KeyState1)   //连续两次读相等
    {
        j = IO_KeyState;
        IO_KeyState = IO_KeyState1;
        if(IO_KeyState != 0)    //有键按下
        {
            F0 = 0;
            if(j == 0)  F0 = 1; //第一次按下
            else if(j == IO_KeyState)
            {
                if(++IO_KeyHoldCnt >= 20)   //1秒后重键
                {
                    IO_KeyHoldCnt = 18;
                    F0 = 1;
                }
            }
            if(F0)
            {
                j = T_KeyTable[IO_KeyState >> 4];
                if((j != 0) && (T_KeyTable[IO_KeyState& 0x0f] != 0)) 
                    KeyCode = (j - 1) * 4 + T_KeyTable[IO_KeyState & 0x0f] + 16;    //计算键码，17~32
            }
        }
        else    IO_KeyHoldCnt = 0;
    }
    P0 = 0xff;
}

