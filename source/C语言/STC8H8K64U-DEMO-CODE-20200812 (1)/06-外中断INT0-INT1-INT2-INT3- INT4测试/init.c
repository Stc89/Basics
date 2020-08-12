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

用STC的MCU的IO方式驱动8位数码管。

下载时, 选择时钟 24MHZ (用户可自行修改频率).

显示效果为: 左边为INT0(SW17)中断计数, 右边为INT1(SW18)中断计数, 计数范围为0~255.

由于按键是机械按键, 按下有抖动, 而本例程没有去抖动处理, 所以按一次有多个计数也是正常的.

INT2, INT3, INT4 实验板上没有引出测试按键，供需要时参考使用.

******************************************/

#include    "reg51.h"

#define MAIN_Fosc       24000000L   //定义主时钟

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

sfr INTCLKO = 0x8F;
#define EX2 0x10
#define EX3 0x20
#define EX4 0x40

#define DIS_DOT     0x20
#define DIS_BLACK   0x10
#define DIS_        0x11

/****************************** 用户定义宏 ***********************************/

#define     Timer0_Reload   (65536UL -(MAIN_Fosc / 1000))       //Timer 0 中断频率, 1000次/秒

/*****************************************************************************/


/*************  本地常量声明    **************/
u8 code t_display[]={                       //标准字库
//   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,
//black  -     H    J    K    L    N    o   P    U     t    G    Q    r   M    y
    0x00,0x40,0x76,0x1E,0x70,0x38,0x37,0x5C,0x73,0x3E,0x78,0x3d,0x67,0x50,0x37,0x6e,
    0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x46};    //0. 1. 2. 3. 4. 5. 6. 7. 8. 9. -1

u8 code T_COM[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};      //位码


/*************  IO口定义    **************/

/*************  本地变量声明    **************/

u8  LED8[8];        //显示缓冲
u8  display_index;  //显示位索引

u8  INT0_cnt, INT1_cnt; //测试用的计数变量
u8  INT2_cnt, INT3_cnt, INT4_cnt; //测试用的计数变量

void    delay_ms(u8 ms);
void    DisplayScan(void);

/********************** 主函数 ************************/
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

    display_index = 0;
    for(i=0; i<8; i++)  LED8[i] = DIS_BLACK;    //全部消隐
    
    
    INT0_cnt = 0;
    INT1_cnt = 0;

    IE1  = 0;   //外中断1标志位
    IE0  = 0;   //外中断0标志位
    EX1 = 1;    //INT1 Enable
    EX0 = 1;    //INT0 Enable

    IT0 = 1;        //INT0 下降沿中断       
//  IT0 = 0;        //INT0 上升,下降沿中断  
    IT1 = 1;        //INT1 下降沿中断       
//  IT1 = 0;        //INT1 上升,下降沿中断  

    //INT2, INT3, INT4 实验板上没有引出测试按键，供需要时参考使用
//    INTCLKO = EX2;  //使能 INT2 下降沿中断
//    INTCLKO |= EX3; //使能 INT3 下降沿中断
//    INTCLKO |= EX4; //使能 INT4 下降沿中断

    EA = 1;     //允许总中断

    while(1)
    {
        delay_ms(1);    //延时1ms
        DisplayScan();
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
          while(--i)    ;   //14T per loop
     }while(--ms);
}


/********************* INT0中断函数 *************************/
void INT0_int (void) interrupt 0      //进中断时已经清除标志
{
    INT0_cnt++; //中断+1
}

/********************* INT1中断函数 *************************/
void INT1_int (void) interrupt 2      //进中断时已经清除标志
{
    INT1_cnt++; //中断+1
}

/********************* INT2中断函数 *************************/
void INT2_int (void) interrupt 10     //进中断时已经清除标志
{
    INT2_cnt++; //中断+1
}

/********************* INT3中断函数 *************************/
void INT3_int (void) interrupt 11     //进中断时已经清除标志
{
    INT3_cnt++; //中断+1
}

/********************* INT4中断函数 *************************/
void INT4_int (void) interrupt 16     //进中断时已经清除标志
{
    INT4_cnt++; //中断+1
}

/********************** 显示扫描函数 ************************/
void DisplayScan(void)
{   
		P7 = ~T_COM[7-display_index];
		P6 = ~t_display[LED8[display_index]];
    if(++display_index >= 8)
    {
        display_index = 0;  //8位结束回0
        LED8[0] = INT0_cnt / 100;
        LED8[1] = (INT0_cnt % 100)/10;
        LED8[2] = INT0_cnt % 10;
        LED8[3] = DIS_BLACK;
        LED8[4] = DIS_BLACK;
        LED8[5] = INT1_cnt / 100;
        LED8[6] = (INT1_cnt % 100)/10;
        LED8[7] = INT1_cnt % 10;
    }
}

