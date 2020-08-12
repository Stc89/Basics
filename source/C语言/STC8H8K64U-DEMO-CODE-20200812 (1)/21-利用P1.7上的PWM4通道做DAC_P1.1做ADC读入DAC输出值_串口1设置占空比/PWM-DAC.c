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

从P1.7(PWM4N)输出16位的PWM, 输出的PWM经过RC滤波成直流电压送P1.1做ADC并用数码管显示出来.

串口1配置为115200bps, 8,n, 1, 切换到P3.0 P3.1, 下载后就可以直接测试. 通过串口1设置占空比.

串口命令使用ASCII码的数字，比如： 10，就是设置占空比为10/256， 100： 就是设置占空比为100/256。

可以设置的值为0~256, 0为连续低电平, 256为连续高电平.

左边4位数码管显示PWM的占空比值，右边4位数码管显示ADC值。

下载时, 选择时钟 22.1184MHz (用户可自行修改频率).

******************************************/

#include    "reg51.h"
#include    "intrins.h"

#define     MAIN_Fosc       22118400L   //定义主时钟（精确计算115200波特率）

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

sfr ADC_CONTR = 0xBC;   //带AD系列
sfr ADC_RES   = 0xBD;   //带AD系列
sfr ADC_RESL  = 0xBE;   //带AD系列
sfr ADCCFG = 0xDE;

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
#define ADCTIM (*(unsigned char volatile xdata *)0xfea8)

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

#define DIS_DOT     0x20
#define DIS_BLACK   0x10
#define DIS_        0x11

/*************  本地常量声明    **************/
u8 code t_display[]={                       //标准字库
//   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,
//black  -     H    J    K    L    N    o   P    U     t    G    Q    r   M    y
    0x00,0x40,0x76,0x1E,0x70,0x38,0x37,0x5C,0x73,0x3E,0x78,0x3d,0x67,0x50,0x37,0x6e,
    0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x46};    //0. 1. 2. 3. 4. 5. 6. 7. 8. 9. -1

u8 code T_COM[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};      //位码

/*************  本地变量声明    **************/

u8  LED8[8];        //显示缓冲
u8  display_index;  //显示位索引
bit B_1ms;          //1ms标志
u8  cnt200ms;

#define     Baudrate1           115200L
#define     UART1_BUF_LENGTH    128     //串口缓冲长度

u8  RX1_TimeOut;
u8  TX1_Cnt;    //发送计数
u8  RX1_Cnt;    //接收计数
bit B_TX1_Busy; //发送忙标志
u16 adc;

u8  xdata   RX1_Buffer[UART1_BUF_LENGTH];   //接收缓冲

void    UART1_config(u8 brt);   // 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer1做波特率.
void    PrintString1(u8 *puts);
void    UART1_TxByte(u8 dat);
void    UpdatePwm(u16 pwm_value);
u16     Get_ADC12bitResult(u8 channel); //channel = 0~15

/******************** 主函数 **************************/
void main(void)
{
    u8  i;
    u16 j;
    
    P0M1 = 0;   P0M0 = 0;   //设置为准双向口
    P2M1 = 0;   P2M0 = 0;   //设置为准双向口
    P3M1 = 0;   P3M0 = 0;   //设置为准双向口
    P4M1 = 0;   P4M0 = 0;   //设置为准双向口
    P5M1 = 0;   P5M0 = 0;   //设置为准双向口
    P6M1 = 0;   P6M0 = 0;   //设置为准双向口
    P7M1 = 0;   P7M0 = 0;   //设置为准双向口
    P1M1 = 0x02;   P1M0 = 0x00;   //设置 P1.1 为 ADC 口

    display_index = 0;

    //  Timer0初始化
    AUXR = 0x80;    //Timer0 set as 1T, 16 bits timer auto-reload, 
    TH0 = (u8)(Timer0_Reload / 256);
    TL0 = (u8)(Timer0_Reload % 256);
    ET0 = 1;    //Timer0 interrupt enable
    TR0 = 1;    //Tiner0 run

    //  ADC初始化
		P_SW2 |= 0x80;
		ADCTIM = 0x3f;		//设置 ADC 内部时序，ADC采样时间建议设最大值
		P_SW2 &= 0x7f;
		ADCCFG = 0x2f;		//设置 ADC 转换结果右对齐,时钟为系统时钟/2/16
		ADC_CONTR = 0x81; //使能 ADC 模块

		P_SW2 |= 0x80;
		
    PWM1_CCER2 = 0x00; //写 CCMRx 前必须先清零 CCxE 关闭通道
    PWM1_CCMR4 = 0x60; //设置 PWM4 模式1 输出
    PWM1_CCER2 = 0x50; //使能 CC4E 通道

    PWM1_ARRH = 2; //设置周期时间
    PWM1_ARRL = 0;
    PWM1_CCR4H = 0;
    PWM1_CCR4L = 128; //设置占空比时间

    PWM1_ENO = 0x80; //使能 PWM4N 输出
//  PWM1_ENO = 0x40; //使能 PWM4P 输出
		PWM1_PS = 0x00;  //高级 PWM 通道 4N 输出脚选择位, 0x00:P1.7, 0x40:P2.7, 0x80:P6.7, 0xC0:P3.3
//  PWM1_PS = 0x00;  //高级 PWM 通道 4P 输出脚选择位, 0x00:P1.6, 0x40:P2.6, 0x80:P6.6, 0xC0:P3.4
    PWM1_BKR = 0x80; //使能主输出
    PWM1_CR1 |= 0x01; //开始计时
		P_SW2 &= 0x7f;

    UpdatePwm(128);

    UART1_config(1);    // 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer1做波特率.
    EA = 1;     //打开总中断

    for(i=0; i<8; i++)  LED8[i] = DIS_; //上电全部显示-
    
    LED8[0] = 1;    //显示PWM默认值
    LED8[1] = 2;
    LED8[2] = 8;
    LED8[3] = DIS_BLACK;    //这位不显示

    PrintString1("PWM和ADC测试程序, 输入占空比为 0~256!\r\n");  //SUART1发送一个字符串
    
    while (1)
    {
        if(B_1ms)   //1ms到
        {
            B_1ms = 0;
            if(++cnt200ms >= 200)   //200ms读一次ADC
            {
                cnt200ms = 0;
                j = Get_ADC12bitResult(1);  //参数0~15,查询方式做一次ADC, 返回值就是结果, == 4096 为错误
                if(j >= 1000)   LED8[4] = j / 1000;     //显示ADC值
                else            LED8[4] = DIS_BLACK;
                LED8[5] = (j % 1000) / 100;
                LED8[6] = (j % 100) / 10;
                LED8[7] = j % 10;
            }

            if(RX1_TimeOut > 0)     //超时计数
            {
                if(--RX1_TimeOut == 0)
                {
                    if((RX1_Cnt > 0) && (RX1_Cnt <= 3)) //限制为3位数字
                    {
                        F0 = 0; //错误标志
                        j = 0;
                        for(i=0; i<RX1_Cnt; i++)
                        {
                            if((RX1_Buffer[i] >= '0') && (RX1_Buffer[i] <= '9'))    //限定为数字
                            {
                                j = j * 10 + RX1_Buffer[i] - '0';
                            }
                            else
                            {
                                F0 = 1; //接收到非数字字符, 错误
                                PrintString1("错误! 接收到非数字字符! 占空比为0~256!\r\n");
                                break;
                            }
                        }
                        if(!F0)
                        {
                            if(j > 256) PrintString1("错误! 输入占空比过大, 请不要大于256!\r\n");
                            else
                            {
                                UpdatePwm(j);
                                if(j >= 100)    LED8[0] = j / 100,  j %= 100;   //显示PWM默认值
                                else            LED8[0] = DIS_BLACK;
                                LED8[1] = j % 100 / 10;
                                LED8[2] = j % 10;
                                PrintString1("已更新占空比!\r\n");
                            }
                        }
                    }
                    else  PrintString1("错误! 输入字符过多! 输入占空比为0~256!\r\n");
                    RX1_Cnt = 0;
                }
            }
        }
    }
}

//========================================================================
// 函数: void UART1_TxByte(u8 dat)
// 描述: 发送一个字节.
// 参数: 无.
// 返回: 无.
// 版本: V1.0, 2014-6-30
//========================================================================
void UART1_TxByte(u8 dat)
{
    SBUF = dat;
    B_TX1_Busy = 1;
    while(B_TX1_Busy);
}

//========================================================================
// 函数: void PrintString1(u8 *puts)
// 描述: 串口1发送字符串函数。
// 参数: puts:  字符串指针.
// 返回: none.
// 版本: VER1.0
// 日期: 2014-11-28
// 备注: 
//========================================================================
void PrintString1(u8 *puts) //发送一个字符串
{
    for (; *puts != 0;  puts++)   UART1_TxByte(*puts);  //遇到停止符0结束
}

//========================================================================
// 函数: void SetTimer2Baudraye(u16 dat)
// 描述: 设置Timer2做波特率发生器。
// 参数: dat: Timer2的重装值.
// 返回: none.
// 版本: VER1.0
// 日期: 2014-11-28
// 备注: 
//========================================================================
void SetTimer2Baudraye(u16 dat)  // 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer1做波特率.
{
    AUXR &= ~(1<<4);    //Timer stop
    AUXR &= ~(1<<3);    //Timer2 set As Timer
    AUXR |=  (1<<2);    //Timer2 set as 1T mode
    TH2 = dat / 256;
    TL2 = dat % 256;
    IE2  &= ~(1<<2);    //禁止中断
    AUXR |=  (1<<4);    //Timer run enable
}

//========================================================================
// 函数: void UART1_config(u8 brt)
// 描述: UART1初始化函数。
// 参数: brt: 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer1做波特率.
// 返回: none.
// 版本: VER1.0
// 日期: 2014-11-28
// 备注: 
//========================================================================
void UART1_config(u8 brt)    // 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer1做波特率.
{
    /*********** 波特率使用定时器2 *****************/
    if(brt == 2)
    {
        AUXR |= 0x01;       //S1 BRT Use Timer2;
        SetTimer2Baudraye(65536UL - (MAIN_Fosc / 4) / Baudrate1);
    }

    /*********** 波特率使用定时器1 *****************/
    else
    {
        TR1 = 0;
        AUXR &= ~0x01;      //S1 BRT Use Timer1;
        AUXR |=  (1<<6);    //Timer1 set as 1T mode
        TMOD &= ~(1<<6);    //Timer1 set As Timer
        TMOD &= ~0x30;      //Timer1_16bitAutoReload;
        TH1 = (u8)((65536UL - (MAIN_Fosc / 4) / Baudrate1) / 256);
        TL1 = (u8)((65536UL - (MAIN_Fosc / 4) / Baudrate1) % 256);
        ET1 = 0;    //禁止中断
        INT_CLKO &= ~0x02;  //不输出时钟
        TR1  = 1;
    }
    /*************************************************/

    SCON = (SCON & 0x3f) | 0x40;    //UART1模式, 0x00: 同步移位输出, 0x40: 8位数据,可变波特率, 0x80: 9位数据,固定波特率, 0xc0: 9位数据,可变波特率
//  PS  = 1;    //高优先级中断
    ES  = 1;    //允许中断
    REN = 1;    //允许接收
    P_SW1 &= 0x3f;
//    P_SW1 |= 0x00;      //UART1 switch to, 0x00: P3.0 P3.1, 0x40: P3.6 P3.7, 0x80: P1.6 P1.7 (必须使用内部时钟)
//  PCON2 |=  (1<<4);   //内部短路RXD与TXD, 做中继, ENABLE,DISABLE

    B_TX1_Busy = 0;
    TX1_Cnt = 0;
    RX1_Cnt = 0;
}


//========================================================================
// 函数: void UART1_int (void) interrupt UART1_VECTOR
// 描述: UART1中断函数。
// 参数: nine.
// 返回: none.
// 版本: VER1.0
// 日期: 2014-11-28
// 备注: 
//========================================================================
void UART1_int (void) interrupt 4
{
    if(RI)
    {
        RI = 0;
        if(RX1_Cnt >= UART1_BUF_LENGTH) RX1_Cnt = 0;
        RX1_Buffer[RX1_Cnt] = SBUF;
        RX1_Cnt++;
        RX1_TimeOut = 5;
    }

    if(TI)
    {
        TI = 0;
        B_TX1_Busy = 0;
    }
}

/********************** 显示扫描函数 ************************/
void DisplayScan(void)
{   
    P7 = ~T_COM[7-display_index];
    P6 = ~t_display[LED8[display_index]];
    if(++display_index >= 8)    display_index = 0;  //8位结束回0
}


/********************** Timer0 1ms中断函数 ************************/
void timer0(void) interrupt 1
{
    DisplayScan();  //1ms扫描显示一位
    B_1ms = 1;      //1ms标志
}


//========================================================================
// 函数: u16 Get_ADC12bitResult(u8 channel)
// 描述: 查询法读一次ADC结果.
// 参数: channel: 选择要转换的ADC.
// 返回: 12位ADC结果.
// 版本: V1.0, 2012-10-22
//========================================================================
u16 Get_ADC12bitResult(u8 channel)  //channel = 0~15
{
    ADC_RES = 0;
    ADC_RESL = 0;

    ADC_CONTR = (ADC_CONTR & 0xF0) | 0x40 | channel;    //启动 AD 转换
    _nop_();
    _nop_();
    _nop_();
    _nop_();

    while((ADC_CONTR & 0x20) == 0)  ;   //wait for ADC finish
    ADC_CONTR &= ~0x20;     //清除ADC结束标志
    return  (((u16)ADC_RES << 8) | ADC_RESL);
}

//========================================================================
// 函数: UpdatePwm(u16 pwm_value)
// 描述: 更新PWM值. 
// 参数: pwm_value: pwm值, 这个值是输出高电平的时间.
// 返回: none.
// 版本: V1.0, 2012-11-22
//========================================================================
void UpdatePwm(u16 pwm_value)
{
		P_SW2 |= 0x80;
	  PWM1_CCR4H = (u8)(pwm_value >> 8); //设置占空比时间
    PWM1_CCR4L = (u8)(pwm_value);
		P_SW2 &= 0x7f;
}

