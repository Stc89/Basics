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

内部集成I2C串行总线控制器做从机模式，SCL->P3.2, SDA->P3.3;
IO口模拟I2C做主机模式，SCL->P0.0, SDA->P0.1;
通过外部飞线连接 P0.0->P3.2, P0.1->P3.3，实现I2C自发自收功能。

用STC的MCU的IO方式驱动8位数码管。
使用Timer0的16位自动重装来产生1ms节拍,程序运行于这个节拍下,用户修改MCU主时钟频率时,自动定时于1ms.
计数器每秒钟加1, 计数范围为0~9999.

显示效果为: 上电后主机每秒钟发送一次计数数据，并在左边4个数码管上显示发送内容；从机接收到数据后在右边4个数码管显示。

下载时, 选择时钟 24MHZ (用户可自行修改频率).

******************************************/


#include "reg51.h"
#include "intrins.h"

#define MAIN_Fosc       24000000L   //定义主时钟

typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;

sfr P_SW2 = 0xba;
sfr AUXR = 0x8E;

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
sfr P6   = 0xE8;
sfr P7   = 0xF8;

#define I2CCFG          (*(unsigned char volatile xdata *)0xfe80)
#define I2CMSCR         (*(unsigned char volatile xdata *)0xfe81)
#define I2CMSST         (*(unsigned char volatile xdata *)0xfe82)
#define I2CSLCR         (*(unsigned char volatile xdata *)0xfe83)
#define I2CSLST         (*(unsigned char volatile xdata *)0xfe84)
#define I2CSLADR        (*(unsigned char volatile xdata *)0xfe85)
#define I2CTXD          (*(unsigned char volatile xdata *)0xfe86)
#define I2CRXD          (*(unsigned char volatile xdata *)0xfe87)
#define I2CMSAUX        (*(unsigned char volatile xdata *)0xfe88)

#define Timer0_Reload   (65536UL -(MAIN_Fosc / 1000))       //Timer 0 中断频率, 1000次/秒

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

bit isda;                                       //设备地址标志
bit isma;                                       //存储地址标志
bit B_1ms;          //1ms标志
bit DisplayFlag;
u8 addr;
u8 pdata buffer[256];
u16 msecond;
u16 Test_cnt;   //测试用的秒计数变量
u8  tmp[4];     //通用数组

void Timer0_config(void);
void WriteNbyte(u8 addr, u8 *p, u8 number);
void ReadNbyte(u8 addr, u8 *p, u8 number);

void I2C_Isr() interrupt 24
{
    char store;
    
    store = P_SW2;
    P_SW2 |= 0x80;

    if (I2CSLST & 0x40)
    {
        I2CSLST &= ~0x40;                       //处理START事件
    }
    else if (I2CSLST & 0x20)
    {
        I2CSLST &= ~0x20;                       //处理RECV事件，SLACKO设置为0
        if (isda)
        {
            isda = 0;                           //处理RECV事件（RECV DEVICE ADDR）
        }
        else if (isma)
        {
            isma = 0;                           //处理RECV事件（RECV MEMORY ADDR）
            addr = I2CRXD;
            I2CTXD = buffer[addr];
        }
        else
        {
            buffer[addr++] = I2CRXD;            //处理RECV事件（RECV DATA）
        }
    }
    else if (I2CSLST & 0x10)
    {
        I2CSLST &= ~0x10;                       //处理SEND事件
        if (I2CSLST & 0x02)
        {
            I2CTXD = 0xff;
        }
        else
        {
            I2CTXD = buffer[++addr];
        }
    }
    else if (I2CSLST & 0x08)
    {
        I2CSLST &= ~0x08;                       //处理STOP事件
        isda = 1;
        isma = 1;
        DisplayFlag = 1;
    }

    P_SW2 = store;
}

void main()
{
    u8  i;

    P0M1 = 0;   P0M0 = 0;   //设置为准双向口
    P6M1 = 0;   P6M0 = 0;   //设置为准双向口
    P7M1 = 0;   P7M0 = 0;   //设置为准双向口
    P3M1 = 0x04;   P3M0 = 0x00;   //SCL设置为输入口，SDA设置为准双向口

    P_SW2 = 0x80;
    P_SW2 |= 0x30;   //I2C功能脚选择，00:P1.5,P1.4; 01:P2.5,P2.4; 11:P3.2,P3.3

    I2CCFG = 0x80;                              //使能I2C从机模式
    I2CSLADR = 0x5a;                            //设置从机设备地址为5A
    I2CSLST = 0x00;
    I2CSLCR = 0x78;                             //使能从机模式中断

    Timer0_config();
    display_index = 0;
    DisplayFlag = 0;
    EA = 1;

    isda = 1;                                   //用户变量初始化
    isma = 1;
    addr = 0;
    I2CTXD = buffer[addr];

    for(i=0; i<8; i++)  LED8[i] = DIS_; //上电全部显示-
    
    while (1)
		{
			if(DisplayFlag)
			{
				DisplayFlag = 0;
				LED8[4] = buffer[0];
				LED8[5] = buffer[1];
				LED8[6] = buffer[2];
				LED8[7] = buffer[3];
			}
			
			if(B_1ms)
			{
				B_1ms = 0;
				
				if(++msecond >= 1000)   //1秒到
				{
						msecond = 0;        //清1000ms计数
						Test_cnt++;         //秒计数+1
						if(Test_cnt >= 10000)    Test_cnt = 0;   //秒计数范围为0~9999

						tmp[0] = Test_cnt / 1000;
						tmp[1] = (Test_cnt % 1000) / 100;
						tmp[2] = (Test_cnt % 100) / 10;
						tmp[3] = Test_cnt % 10;
						LED8[0] = tmp[0];
						LED8[1] = tmp[1];
						LED8[2] = tmp[2];
						LED8[3] = tmp[3];

						WriteNbyte(0, tmp, 4);
				 }
			}
		}
}

//========================================================================
// 函数: void Timer0_config(void)
// 描述: Timer0初始化函数。
// 参数: 无.
// 返回: 无.
// 版本: V1.0, 2020-6-10
//========================================================================
void Timer0_config(void)
{
    AUXR = 0x80;    //Timer0 set as 1T, 16 bits timer auto-reload, 
    TH0 = (u8)(Timer0_Reload / 256);
    TL0 = (u8)(Timer0_Reload % 256);
    ET0 = 1;    //Timer0 interrupt enable
    TR0 = 1;    //Tiner0 run
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


#define SLAW    0x5A
#define SLAR    0x5B

sbit    SDA = P0^1; //定义SDA
sbit    SCL = P0^0; //定义SCL

/****************************/
void    I2C_Delay(void) //for normal MCS51, delay (2 * dly + 4) T, for STC12Cxxxx delay (4 * dly + 10) T
{
    u8  dly;
    dly = MAIN_Fosc / 2000000UL;        //按2us计算
    while(--dly)    ;
}

/****************************/
void I2C_Start(void)               //start the I2C, SDA High-to-low when SCL is high
{
    SDA = 1;
    I2C_Delay();
    SCL = 1;
    I2C_Delay();
    SDA = 0;
    I2C_Delay();
    SCL = 0;
    I2C_Delay();
}       


void I2C_Stop(void)                 //STOP the I2C, SDA Low-to-high when SCL is high
{
    SDA = 0;
    I2C_Delay();
    SCL = 1;
    I2C_Delay();
    SDA = 1;
    I2C_Delay();
}

void S_ACK(void)              //Send ACK (LOW)
{
    SDA = 0;
    I2C_Delay();
    SCL = 1;
    I2C_Delay();
    SCL = 0;
    I2C_Delay();
}

void S_NoACK(void)           //Send No ACK (High)
{
    SDA = 1;
    I2C_Delay();
    SCL = 1;
    I2C_Delay();
    SCL = 0;
    I2C_Delay();
}
        
void I2C_Check_ACK(void)         //Check ACK, If F0=0, then right, if F0=1, then error
{
    SDA = 1;
    I2C_Delay();
    SCL = 1;
    I2C_Delay();
    F0  = SDA;
    SCL = 0;
    I2C_Delay();
}

/****************************/
void I2C_WriteAbyte(u8 dat)     //write a byte to I2C
{
    u8 i;
    i = 8;
    do
    {
        if(dat & 0x80)  SDA = 1;
        else            SDA = 0;
        dat <<= 1;
        I2C_Delay();
        SCL = 1;
        I2C_Delay();
        SCL = 0;
        I2C_Delay();
    }
    while(--i);
}

/****************************/
u8 I2C_ReadAbyte(void)          //read A byte from I2C
{
    u8 i,dat;
    i = 8;
    SDA = 1;
    do
    {
        SCL = 1;
        I2C_Delay();
        dat <<= 1;
        if(SDA)     dat++;
        SCL  = 0;
        I2C_Delay();
    }
    while(--i);
    return(dat);
}

/****************************/
void WriteNbyte(u8 addr, u8 *p, u8 number)          /*  WordAddress,First Data Address,Byte lenth   */
                                                            //F0=0,right, F0=1,error
{
    I2C_Start();
    I2C_WriteAbyte(SLAW);
    I2C_Check_ACK();
    if(!F0)
    {
        I2C_WriteAbyte(addr);
        I2C_Check_ACK();
        if(!F0)
        {
            do
            {
                I2C_WriteAbyte(*p);     p++;
                I2C_Check_ACK();
                if(F0)  break;
            }
            while(--number);
        }
    }
    I2C_Stop();
}


/****************************/
void ReadNbyte(u8 addr, u8 *p, u8 number)       /*  WordAddress,First Data Address,Byte lenth   */
{
    I2C_Start();
    I2C_WriteAbyte(SLAW);
    I2C_Check_ACK();
    if(!F0)
    {
        I2C_WriteAbyte(addr);
        I2C_Check_ACK();
        if(!F0)
        {
            I2C_Start();
            I2C_WriteAbyte(SLAR);
            I2C_Check_ACK();
            if(!F0)
            {
                do
                {
                    *p = I2C_ReadAbyte();   p++;
                    if(number != 1)     S_ACK();    //send ACK
                }
                while(--number);
                S_NoACK();          //send no ACK
            }
        }
    }
    I2C_Stop();
}

