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


/*************  本程序功能说明  **************

用户可以在宏定义中改变MCU主时钟频率. 范围 8MHZ ~ 33MHZ.

红外接收程序。模拟市场上用量最大的NEC的编码。

用户可以在宏定义中指定用户码.

使用PWM4产生38KHZ载波, 1/3占空比, 每个38KHZ周期发射管发射9us,关闭16.3us.

使用开发板上的16个IO扫描按键, MCU不睡眠, 连续扫描按键.

当键按下, 第一帧为数据, 后面的帧为重复帧,不带数据, 具体定义请自行参考NEC的编码资料.

键释放后, 停止发送.

******************************************/


#include    "reg51.h"
#include    "intrins.h"

#define     MAIN_Fosc       24000000UL  //定义主时钟

typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;

sfr TH2  = 0xD6;
sfr TL2  = 0xD7;
sfr IE2   = 0xAF;
sfr INT_CLKO = 0x8F;
sfr AUXR = 0x8E;
sfr AUXR1 = 0xA2;
sfr P_SW1 = 0xA2;
sfr P_SW2 = 0xBA;
sfr S2CON = 0x9A;
sfr S2BUF = 0x9B;

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

/*************  红外发送相关变量    **************/
#define User_code   0xFF00      //定义红外用户码

sbit    P_IR_TX   = P1^6;   //定义红外发送端口
#define IR_TX_ON    0
#define IR_TX_OFF   1

u16     tx_cnt;     //发送或空闲的脉冲计数(等于38KHZ的脉冲数，对应时间), 红外频率为38KHZ, 周期26.3us
u8      TxTime;     //发送时间

/*************  IO键盘变量声明  **************/

u8  IO_KeyState, IO_KeyState1, IO_KeyHoldCnt;   //行列键盘变量
u8  KeyHoldCnt; //键按下计时
u8  KeyCode;    //给用户使用的键码, 1~16有效

/*************  本地函数声明    **************/
void    delay_ms(u8 ms);
void    IO_KeyScan(void);
void    PWM_config(void);
void    IR_TxPulse(u16 pulse);
void    IR_TxSpace(u16 pulse);
void    IR_TxByte(u8 dat);

/********************** 主函数 ************************/
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
    
    PWM_config();
    P_IR_TX = IR_TX_OFF;
    
    EA = 1;                     //打开总中断
    
    while(1)
    {
        delay_ms(30);       //30ms
        IO_KeyScan();

        if(KeyCode != 0)        //检测到键码
        {
            TxTime = 0;
                                //一帧数据最小长度 = 9 + 4.5 + 0.5625 + 24 * 1.125 + 8 * 2.25 = 59.0625 ms
                                //一帧数据最大长度 = 9 + 4.5 + 0.5625 + 8 * 1.125 + 24 * 2.25 = 77.0625 ms
            IR_TxPulse(342);    //对应9ms，同步头       9ms
            IR_TxSpace(171);    //对应4.5ms，同步头间隔 4.5ms
            IR_TxPulse(21);     //开始发送数据          0.5625ms

            IR_TxByte(User_code%256);   //发用户码低字节
            IR_TxByte(User_code/256);   //发用户码高字节
            IR_TxByte(KeyCode);         //发数据
            IR_TxByte(~KeyCode);        //发数据反码
            
            if(TxTime < 56)     //一帧按最大77ms发送, 不够的话,补偿时间     108ms
            {
                TxTime = 56 - TxTime;
                TxTime = TxTime + TxTime / 8;
                delay_ms(TxTime);
            }
            delay_ms(31);

            while(IO_KeyState != 0) //键未释放
            {
                IR_TxPulse(342);    //对应9ms，   同步头        9ms
                IR_TxSpace(86);     //对应2.25ms，同步头间隔    2.25ms
                IR_TxPulse(21);     //开始发送数据              0.5625ms
                delay_ms(96);
                IO_KeyScan();
            }
            KeyCode = 0;
        }
    }
} 
/**********************************************/

//========================================================================
// 函数: void  delay_ms(unsigned char ms)
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
          while(--i)    ;   //13T per loop
     }while(--ms);
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

void    IO_KeyScan(void)    //50ms call
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


/************* 发送脉冲函数 **************/
void    IR_TxPulse(u16 pulse)
{
    tx_cnt = pulse;
    PWM1_CCER2 = 0x00; //写 CCMRx 前必须先清零 CCxE 关闭通道
    PWM1_CCMR4 = 0x60; //设置 PWM4 模式1 输出
    PWM1_CCER2 = 0xB0; //使能 CC4E 通道, 低电平有效
    PWM1_IER = 0x10;   //使能捕获/比较 4 中断
    while(tx_cnt);
}

/************* 发送空闲函数 **************/
void    IR_TxSpace(u16 pulse)
{
    tx_cnt = pulse;
    PWM1_CCER2 = 0x00; //写 CCMRx 前必须先清零 CCxE 关闭通道
    PWM1_CCMR4 = 0x40; //设置 PWM4 强制为无效电平
    PWM1_CCER2 = 0xB0; //使能 CC4E 通道, 低电平有效
    PWM1_IER = 0x10;   //使能捕获/比较 4 中断
    while(tx_cnt);
}


/************* 发送一个字节函数 **************/
void    IR_TxByte(u8 dat)
{
    u8 i;
    for(i=0; i<8; i++)
    {
        if(dat & 1)     IR_TxSpace(63), TxTime += 2;    //数据1对应 1.6875 + 0.5625 ms 
        else            IR_TxSpace(21), TxTime++;       //数据0对应 0.5625 + 0.5625 ms
        IR_TxPulse(21);         //脉冲都是0.5625ms
        dat >>= 1;              //下一个位
    }
}

//========================================================================
// 函数: void   PWM_config(void)
// 描述: PCA配置函数.
// 参数: None
// 返回: none.
// 版本: V1.0, 2012-11-22
//========================================================================
void    PWM_config(void)
{
		P_SW2 |= 0x80;
		
    PWM1_CCER2 = 0x00; //写 CCMRx 前必须先清零 CCxE 关闭通道
    PWM1_CCMR4 = 0x60; //设置 PWM4 模式1 输出
    //PWM1_CCER2 = 0xB0; //使能 CC4E 通道, 低电平有效

    PWM1_ARRH = 0x02; //设置周期时间
    PWM1_ARRL = 0x77;
    PWM1_CCR4H = 0;
    PWM1_CCR4L = 210; //设置占空比时间

//  PWM1_ENO = 0x80; //使能 PWM4N 输出
    PWM1_ENO = 0x40; //使能 PWM4P 输出
//  PWM1_PS = 0x00;  //高级 PWM 通道 4N 输出脚选择位, 0x00:P1.7, 0x40:P2.7, 0x80:P6.7, 0xC0:P3.3
    PWM1_PS = 0x00;  //高级 PWM 通道 4P 输出脚选择位, 0x00:P1.6, 0x40:P2.6, 0x80:P6.6, 0xC0:P3.4
    PWM1_BKR = 0x80; //使能主输出
//    PWM1_IER = 0x10; // 使能中断
    PWM1_CR1 |= 0x01; //开始计时
//		P_SW2 &= 0x7f;
}

/******************* PWM中断函数 ********************/
void PWM1_ISR() interrupt 26
{
    if(PWM1_SR1 & 0X10)
    {
        //PWM1_SR1 &=~0X10;
        PWM1_SR1 = 0;
			
        if(--tx_cnt == 0)
        {
            PWM1_CCER2 = 0x00; //写 CCMRx 前必须先清零 CCxE 关闭通道
            PWM1_CCMR4 = 0x40; //设置 PWM4 强制为无效电平
            PWM1_CCER2 = 0xB0; //使能 CC4E 通道, 低电平有效
            PWM1_IER = 0x00;   // 关闭中断
        }
		}
}

