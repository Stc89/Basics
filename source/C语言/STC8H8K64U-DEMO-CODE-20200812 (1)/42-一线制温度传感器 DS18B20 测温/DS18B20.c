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

通过一个IO口获取一线制温度传感器 DS18B20 温度值.

使用Timer0的16位自动重装来产生1ms节拍,程序运行于这个节拍下, 用户修改MCU主时钟频率时,自动定时于1ms.

用STC的MCU的IO方式驱动8位数码管，通过数码管显示测量的温度值.

下载时, 选择时钟 24MHZ (用户可自行修改频率).

******************************************/

#include    "reg51.h"
#include    "intrins.h"

#define     MAIN_Fosc       24000000L   //定义主时钟

typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;

sfr AUXR = 0x8E;
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

/***********************************************************/

sbit DQ = P3^3;                   //DS18B20的数据口

#define DIS_DOT     0x20
#define DIS_BLACK   0x10
#define DIS_        0x11

#define Timer0_Reload   (65536UL -(MAIN_Fosc / 1000))       //Timer 0 中断频率, 1000次/秒

#if (MAIN_Fosc >= 40000000L)
    #define		NOP()    _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_()
#elif (MAIN_Fosc >= 36000000L)
    #define		NOP()    _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_()
#elif (MAIN_Fosc >= 30000000L)
    #define		NOP()    _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_()
#elif (MAIN_Fosc >= 24000000L)
    #define		NOP()    _nop_();_nop_();_nop_();_nop_();_nop_();_nop_()
#elif (MAIN_Fosc >= 20000000L)
    #define		NOP()    _nop_();_nop_();_nop_();_nop_();_nop_()
#elif (MAIN_Fosc >= 18000000L)
    #define		NOP()    _nop_();_nop_();_nop_();_nop_()
#elif (MAIN_Fosc >= 12000000L)
    #define		NOP()    _nop_();_nop_();_nop_()
#elif (MAIN_Fosc >= 6000000L)
    #define		NOP()    _nop_();_nop_()
#else
    #define		NOP()    _nop_()
#endif

/*************  本地常量声明    **************/
u8 code t_display[]={                       //标准字库
//   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,
//black  -     H    J    K    L    N    o   P    U     t    G    Q    r   M    y
    0x00,0x40,0x76,0x1E,0x70,0x38,0x37,0x5C,0x73,0x3E,0x78,0x3d,0x67,0x50,0x37,0x6e,
    0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x46};    //0. 1. 2. 3. 4. 5. 6. 7. 8. 9. -1

u8 code T_COM[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};      //位码

/***************  本地变量声明  ****************/

u8  LED8[8];        //显示缓冲
u8  display_index;  //显示位索引
bit B_1ms;          //1ms标志
u16 msecond;
u8 MinusFlag;       //负数标志，0：正数，1：负数

/**********************************************/
void DS18B20_Reset();
void DS18B20_WriteByte(u8 dat);
u8 DS18B20_ReadByte();

void delay_us(u8 us);
u16 ReadTemperature();
void DisplayTemperature(u16 temp);
/**********************************************/
void main()
{
    u8  i;
    u16 Temp;

    P0M1 = 0;   P0M0 = 0;   //设置为准双向口
    P1M1 = 0;   P1M0 = 0;   //设置为准双向口
    P2M1 = 0;   P2M0 = 0;   //设置为准双向口
    P3M1 = 0;   P3M0 = 0;   //设置为准双向口
    P4M1 = 0;   P4M0 = 0;   //设置为准双向口
    P5M1 = 0;   P5M0 = 0;   //设置为准双向口
    P6M1 = 0;   P6M0 = 0;   //设置为准双向口
    P7M1 = 0;   P7M0 = 0;   //设置为准双向口
	
    display_index = 0;
    AUXR = 0x80;    //Timer0 set as 1T, 16 bits timer auto-reload, 
    TH0 = (u8)(Timer0_Reload / 256);
    TL0 = (u8)(Timer0_Reload % 256);
    ET0 = 1;    //Timer0 interrupt enable
    TR0 = 1;    //Tiner0 run
    EA = 1;     //打开总中断
    
    for(i=0; i<8; i++)  LED8[i] = 0x10; //上电消隐

    while (1)
    {
        if(B_1ms)   //1ms到
        {
            B_1ms = 0;
            if(++msecond >= 300)    //300ms到
            {
                msecond = 0;
                Temp = ReadTemperature();
                DisplayTemperature(Temp);
            }
        }
    }
}

//========================================================================
// 函数: u16 ReadTemperature()
// 描述: 读取温度函数。
// 参数: none.
// 返回: 温度值.
// 版本: VER1.0
// 日期: 2020-7-30
// 备注: 
//========================================================================
u16 ReadTemperature()
{
    u16 TempH, TempL, Temperature;
	
    DS18B20_Reset();                //设备复位
    DS18B20_WriteByte(0xCC);        //跳过ROM命令
    DS18B20_WriteByte(0x44);        //开始转换命令
    while (!DQ);                    //等待转换完成

    DS18B20_Reset();                //设备复位
    DS18B20_WriteByte(0xCC);        //跳过ROM命令
    DS18B20_WriteByte(0xBE);        //读暂存存储器命令
    TempL = DS18B20_ReadByte();     //读温度低字节
    TempH = DS18B20_ReadByte();     //读温度高字节
	
    if(TempH & 0xf8)    //判断是否位负数
    {
        MinusFlag = 1;  //设置负数标志
        Temperature = (TempH<<8) | TempL;
        Temperature = ~Temperature + 1;
        Temperature *= 0.625;       //0.0625 * 10，保留1位小数点
    }
    else
    {
        MinusFlag = 0;  //清除负数标志
        Temperature = (((TempH<<8) | TempL) * 0.625); //0.0625 * 10，保留1位小数点
    }

    return Temperature;
}

//========================================================================
// 函数: void DisplayTemperature(u16 temp)
// 描述: 显示温度函数。
// 参数: none.
// 返回: 温度值.
// 版本: VER1.0
// 日期: 2020-7-30
// 备注: 
//========================================================================
void DisplayTemperature(u16 temp)
{
    if(MinusFlag)
    {
        if(temp > 999)
        {
            LED8[3] = DIS_;
            LED8[4] = temp / 1000;
        }
        else
        {
            LED8[3] = DIS_BLACK;
            LED8[4] = DIS_;
        }
    }
    else
    {
        LED8[3] = DIS_BLACK;
        if(temp > 999)
        {
            LED8[4] = temp / 1000;
        }
        else
        {
            LED8[4] = DIS_BLACK;
        }
    }
    LED8[5] = (temp % 1000) / 100;
    LED8[6] = ((temp % 100) / 10) + DIS_DOT;
    LED8[7] = temp % 10;
}

//========================================================================
// 函数: void  delay_us(u8 us)
// 描述: 延时函数。
// 参数: us,要延时的us数, 这里只支持1~255us. 
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void delay_us(u8 us)
{
    do{
        NOP();
        NOP();
    }while(--us);
}

/**************************************
复位DS18B20,并检测设备是否存在
**************************************/
void DS18B20_Reset()
{
    CY = 1;
    while (CY)
    {
        DQ = 0;                     //送出低电平复位信号
        delay_us(240);              //延时至少480us
        delay_us(240);
        DQ = 1;                     //释放数据线
        delay_us(60);               //等待60us
        CY = DQ;                    //检测存在脉冲
        delay_us(240);              //等待设备释放数据线
        delay_us(180);
    }
}

/**************************************
从DS18B20读1字节数据
**************************************/
u8 DS18B20_ReadByte()
{
    u8 i;
    u8 dat = 0;

    for (i=0; i<8; i++)             //8位计数器
    {
        dat >>= 1;
        DQ = 0;                     //开始时间片
        delay_us(1);                //延时等待
        DQ = 1;                     //准备接收
        delay_us(1);                //接收延时
        if (DQ) dat |= 0x80;        //读取数据
        delay_us(60);               //等待时间片结束
    }

    return dat;
}

/**************************************
向DS18B20写1字节数据
**************************************/
void DS18B20_WriteByte(u8 dat)
{
    char i;

    for (i=0; i<8; i++)             //8位计数器
    {
        DQ = 0;                     //开始时间片
        delay_us(1);                //延时等待
        dat >>= 1;                  //送出数据
        DQ = CY;
        delay_us(60);               //等待时间片结束
        DQ = 1;                     //恢复数据线
        delay_us(1);                //恢复延时
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
void timer0 (void) interrupt 1
{
    DisplayScan();  //1ms扫描显示一位
    B_1ms = 1;      //1ms标志
}

