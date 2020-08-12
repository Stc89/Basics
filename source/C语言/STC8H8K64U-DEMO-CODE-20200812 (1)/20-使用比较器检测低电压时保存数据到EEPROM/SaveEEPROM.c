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

比较器的正极通过 P3.7 端口连接可调电阻，与1.19V内部固定比较；

调节可调电阻，当P3.7口的输入电压低于1.19V时产生比较器中断，此时保存数据到EEPROM；

当P3.7口的输入电压高于1.19V后，或者重新上电时，读取EEPROM数据进行恢复。

用STC的MCU的IO方式驱动8位数码管。

使用Timer0的16位自动重装来产生1ms节拍,程序运行于这个节拍下,用户修改MCU主时钟频率时,自动定时于1ms.

用户可以在"用户定义宏"中修改保存数据的EEPROM地址。

显示效果为: 上电后显示秒计数, 计数范围为0~10000，显示在右边的5个数码管。

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
注意：下载时，下载界面"硬件选项"中下面的项要确认如下设置:

设置用户EEPROM大小，并确保"用户定义宏"中设定的地址在EEPROM设置的大小范围之内。

选择时钟 24MHZ (用户可自行修改频率)。
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

******************************************/

#include    "reg51.h"
#include    "intrins.h"

#define     MAIN_Fosc       24000000L   //定义主时钟

#define     Timer0_16bitAutoReload()    TMOD &= ~0x03                   //16位自动重装
#define     Timer0_16bit()              TMOD  = (TMOD & ~0x03) | 0x01   //16位
#define     Timer0_8bitAutoReload()     TMOD  = (TMOD & ~0x03) | 0x02   //8位自动重装
#define     Timer0_16bitAutoRL_NoMask() TMOD |=  0x03       //16位自动重装不可屏蔽中断
#define     Timer0_AsCounterP32()       TMOD |=  4      //时器0用做计数器
#define     Timer0_AsTimer()            TMOD &= ~4      //时器0用做定时器
#define     Timer0_ExtControlP34()      TMOD |=  4      //时器0由外部INT0高电平允许定时计数
#define     Timer0_Run()                TR0 = 1             //允许定时器0计数
#define     Timer0_Stop()               TR0 = 0             //禁止定时器0计数
#define     Timer0_InterruptEnable()    ET0 = 1             //允许Timer1中断.
#define     Timer0_InterruptDisable()   ET0 = 0             //禁止Timer1中断.
#define     Timer0_1T()                 AUXR |=  (1<<7) //Timer0 clodk = fo
#define     Timer0_12T()                AUXR &= ~(1<<7) //Timer0 clodk = fo/12  12分频, default
#define     Timer0_Load(n)      TH0 = (n) / 256,    TL0 = (n) % 256

typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;

sfr TH2  = 0xD6;
sfr TL2  = 0xD7;
sfr IE2  = 0xAF;
sfr INT_CLKO = 0x8F;
sfr AUXR = 0x8E;
sfr AUXR1 = 0xA2;
sfr P_SW1 = 0xA2;
sfr P_SW2 = 0xBA;

sfr IAP_DATA  = 0xC2;
sfr IAP_ADDRH = 0xC3;
sfr IAP_ADDRL = 0xC4;
sfr IAP_CMD   = 0xC5;
sfr IAP_TRIG  = 0xC6;
sfr IAP_CONTR = 0xC7;
sfr IAP_TPS   = 0xF5;

sfr ADCCFG = 0xDE;
sfr CMPCR1 = 0xE6;
sfr CMPCR2 = 0xE7;

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

sbit ELVD = IE^6;   //低压监测中断允许位
sbit PLVD = IP^6;

#define DIS_DOT     0x20
#define DIS_BLACK   0x10
#define DIS_        0x11

/****************************** 用户定义宏 ***********************************/

#define     EE_ADDRESS  0x0000  //保存的EEPROM起始地址

#define     Timer0_Reload   (65536UL -(MAIN_Fosc / 1000))       //Timer 0 中断频率, 1000次/秒

#define     Tip_Delay   (MAIN_Fosc / 1000000)

/*****************************************************************************/


/*************  本地常量声明    **************/
u8 code t_display[]={                       //标准字库
//   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,
//black  -     H    J    K    L    N    o   P    U     t    G    Q    r   M    y
    0x00,0x40,0x76,0x1E,0x70,0x38,0x37,0x5C,0x73,0x3E,0x78,0x3d,0x67,0x50,0x37,0x6e,
    0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x46};    //0. 1. 2. 3. 4. 5. 6. 7. 8. 9. -1

u8 code T_COM[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};      //位码


u8  LED8[8];        //显示缓冲
u8  display_index;  //显示位索引
bit B_1ms;          //1ms标志
u16 msecond;
bit LowVolFlag;     //低电压标志

u16 Test_cnt;   //测试用的秒计数变量
u16 Temp_cnt;   //保存用的秒计数变量
u8  tmp[2];     //通用数组

void    CMP_config(void);
void    Display(void);
void    DisableEEPROM(void);
void    EEPROM_read_n(u16 EE_address,u8 *DataAddress,u16 number);
void    EEPROM_write_n(u16 EE_address,u8 *DataAddress,u16 number);
void    EEPROM_SectorErase(u16 EE_address);

/******************* 比较器中断函数 ********************/
void CMP_Isr() interrupt 21
{
    CMPCR1 &= ~0x40;                         //清中断标志
    P50 = CMPCR1 & 0x01;                     //中断方式读取比较器比较结果
    
    if(CMPCR1 & 0x01)
    {
        if(LowVolFlag)
        {
            LowVolFlag = 0;    //清除低电压标志
            if(Test_cnt != Temp_cnt)
            {
                EEPROM_read_n(EE_ADDRESS,tmp,2);        //读出2字节
                Test_cnt = ((u16)tmp[0] << 8) + tmp[1]; //秒计数
                if(Test_cnt > 10000)    Test_cnt = 0;   //秒计数范围为0~10000
                Temp_cnt = Test_cnt;
            }
        }
    }
    else
    {
        P7 = 0xff;     //关闭显示，省电
        if(!LowVolFlag)
        {
            LowVolFlag = 1;    //设置低电压标志
            if(Test_cnt != Temp_cnt)
            {
                Temp_cnt = Test_cnt;
                EEPROM_SectorErase(EE_ADDRESS); //擦除扇区
                tmp[0] = (u8)(Temp_cnt >> 8);
                tmp[1] = (u8)Temp_cnt;
                EEPROM_write_n(EE_ADDRESS,tmp,2);
            }
        }
    }
}

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
    
    Timer0_1T();
    Timer0_AsTimer();
    Timer0_16bitAutoReload();
    Timer0_Load(Timer0_Reload);
    Timer0_InterruptEnable();
    Timer0_Run();

    CMP_config();
    EA = 1;     //打开总中断
    
    for(msecond=0; msecond < 200; ) //延时200ms
    {
        if(B_1ms)   //1ms到
        {
            B_1ms = 0;
            msecond ++;
        }
    }

    EEPROM_read_n(EE_ADDRESS,tmp,2);        //读出2字节
    Test_cnt = ((u16)tmp[0] << 8) + tmp[1]; //秒计数
    if(Test_cnt > 10000)    Test_cnt = 0;   //秒计数范围为0~10000
    
    Display();      //显示秒计数
    
    while(1)
    {
        if((B_1ms) && (LowVolFlag == 0))   //1ms到，低电压时不工作
        {
            B_1ms = 0;
            if(++msecond >= 1000)   //1秒到
            {
                msecond = 0;        //清1000ms计数
                Test_cnt++;         //秒计数+1
                if(Test_cnt > 10000)    Test_cnt = 0;   //秒计数范围为0~10000
                Display();          //显示秒计数
            }
        }
    }
}

//========================================================================
// 函数: void CMP_config(void)
// 描述: 比较器初始化函数。
// 参数: 无.
// 返回: 无.
// 版本: V1.0, 2020-6-10
//========================================================================
void CMP_config(void)
{
    CMPCR2 = 0x00;
    CMPCR2 &= ~0x80;                            //比较器正向输出
//  CMPCR2 |= 0x80;                             //比较器反向输出
//  CMPCR2 &= ~0x40;                            //禁止0.1us滤波
    CMPCR2 |= 0x40;                             //使能0.1us滤波
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

//========================================================================
// 函数: void   ISP_Disable(void)
// 描述: 禁止访问ISP/IAP.
// 参数: non.
// 返回: non.
// 版本: V1.0, 2012-10-22
//========================================================================
void DisableEEPROM(void)
{
		IAP_CONTR = 0;          //关闭 IAP 功能
		IAP_CMD = 0;            //清除命令寄存器
		IAP_TRIG = 0;           //清除触发寄存器
		IAP_ADDRH = 0x80;       //将地址设置到非 IAP 区域
		IAP_ADDRL = 0;
}

//========================================================================
// 函数: void EEPROM_read_n(u16 EE_address,u8 *DataAddress,u16 number)
// 描述: 从指定EEPROM首地址读出n个字节放指定的缓冲.
// 参数: EE_address:  读出EEPROM的首地址.
//       DataAddress: 读出数据放缓冲的首地址.
//       number:      读出的字节长度.
// 返回: non.
// 版本: V1.0, 2012-10-22
//========================================================================
void EEPROM_read_n(u16 EE_address,u8 *DataAddress,u16 number)
{
    EA = 0;     //禁止中断

		IAP_CONTR = 0x80; //使能 IAP
		IAP_TPS = Tip_Delay; //设置擦除等待参数 24MHz
		IAP_CMD = 1;  //设置 IAP 读命令
		do
		{
				IAP_ADDRH = EE_address / 256; //设置 IAP 地址高字节
				IAP_ADDRL = EE_address % 256; //设置 IAP 地址低字节
				IAP_TRIG = 0x5a; //写触发命令(0x5a)
				IAP_TRIG = 0xa5; //写触发命令(0xa5)
				_nop_();
				*DataAddress = IAP_DATA; //读 IAP 数据
        EE_address++;
        DataAddress++;
    }while(--number);
    DisableEEPROM();
    EA = 1;     //重新允许中断
}


/******************** 扇区擦除函数 *****************/
//========================================================================
// 函数: void EEPROM_SectorErase(u16 EE_address)
// 描述: 把指定地址的EEPROM扇区擦除.
// 参数: EE_address:  要擦除的扇区EEPROM的地址.
// 返回: non.
// 版本: V1.0, 2013-5-10
//========================================================================
void EEPROM_SectorErase(u16 EE_address)
{
    EA = 0;     //禁止中断

		IAP_CONTR = 0x80; //使能 IAP
		IAP_TPS = Tip_Delay; //设置擦除等待参数 24MHz
		IAP_CMD = 3;      //设置 IAP 擦除命令
		IAP_ADDRH = EE_address / 256; //设置 IAP 地址高字节
		IAP_ADDRL = EE_address % 256; //设置 IAP 地址低字节
		IAP_TRIG = 0x5a; //写触发命令(0x5a)
		IAP_TRIG = 0xa5; //写触发命令(0xa5)
		_nop_();
    DisableEEPROM();
    EA = 1;     //重新允许中断
}

//========================================================================
// 函数: void EEPROM_write_n(u16 EE_address,u8 *DataAddress,u16 number)
// 描述: 把缓冲的n个字节写入指定首地址的EEPROM.
// 参数: EE_address:  写入EEPROM的首地址.
//       DataAddress: 写入源数据的缓冲的首地址.
//       number:      写入的字节长度.
// 返回: non.
// 版本: V1.0, 2012-10-22
//========================================================================
void EEPROM_write_n(u16 EE_address,u8 *DataAddress,u16 number)
{
    EA = 0;     //禁止中断

		IAP_CONTR = 0x80; //使能 IAP
		IAP_TPS = Tip_Delay; //设置擦除等待参数 24MHz
		IAP_CMD = 2;  //设置 IAP 写命令
    do
    {
				IAP_ADDRH = EE_address / 256; //设置 IAP 地址高字节
				IAP_ADDRL = EE_address % 256; //设置 IAP 地址低字节
				IAP_DATA = *DataAddress; //写 IAP 数据
				IAP_TRIG = 0x5a; //写触发命令(0x5a)
				IAP_TRIG = 0xa5; //写触发命令(0xa5)
				_nop_();
        EE_address++;
        DataAddress++;
    }while(--number);

    DisableEEPROM();
    EA = 1;     //重新允许中断
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
    if(LowVolFlag == 0)
    {
        DisplayScan();  //1ms扫描显示一位
        B_1ms = 1;      //1ms标志
    }
}
