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

通过串口对STC内部自带的EEPROM(FLASH)进行读写测试。

对FLASH做扇区擦除、写入、读出的操作，命令指定地址。

默认波特率:  115200,8,N,1. 
默认主时钟:  22.1184MHz.

串口命令设置: (命令字母不区分大小写)
    W 0x0040 1234567890  --> 对0x0040地址写入字符1234567890.
    R 0x0040 10          --> 对0x0040地址读出10个字节数据. 

注意：下载时，下载界面"硬件选项"中设置用户EEPROM大小，

并确保串口命令中的地址在EEPROM设置的大小范围之内。

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


#define     Baudrate1           115200L
#define     Tmp_Length          100      //读写EEPROM缓冲长度

#define     UART1_BUF_LENGTH    (Tmp_Length+9)  //串口缓冲长度

u8  RX1_TimeOut;
u8  TX1_Cnt;    //发送计数
u8  RX1_Cnt;    //接收计数
bit B_TX1_Busy; //发送忙标志

u8  xdata   RX1_Buffer[UART1_BUF_LENGTH];   //接收缓冲
u8  xdata   tmp[Tmp_Length];        //EEPROM操作缓冲


void    UART1_config(u8 brt);   // 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer1做波特率.
void    PrintString1(u8 *puts);
void    UART1_TxByte(u8 dat);
void    delay_ms(u8 ms);
u8      CheckData(u8 dat);
u16     GetAddress(void);
u8      GetDataLength(void);
void    EEPROM_SectorErase(u16 EE_address);
void    EEPROM_read_n(u16 EE_address,u8 *DataAddress,u8 length);
u8      EEPROM_write_n(u16 EE_address,u8 *DataAddress,u8 length);


/********************* 主函数 *************************/
void main(void)
{
    u8  i,j;
    u16 addr;
    u8  status;

    P0M1 = 0;   P0M0 = 0;   //设置为准双向口
    P1M1 = 0;   P1M0 = 0;   //设置为准双向口
    P2M1 = 0;   P2M0 = 0;   //设置为准双向口
    P3M1 = 0;   P3M0 = 0;   //设置为准双向口
    P4M1 = 0;   P4M0 = 0;   //设置为准双向口
    P5M1 = 0;   P5M0 = 0;   //设置为准双向口
    P6M1 = 0;   P6M0 = 0;   //设置为准双向口
    P7M1 = 0;   P7M0 = 0;   //设置为准双向口

    UART1_config(1);    // 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer1做波特率.
    EA = 1; //允许总中断

    PrintString1("STC8H8K64U系列单片机EEPROM测试程序，串口命令设置如下:\r\n");    //SUART1发送一个字符串
    PrintString1("W 0x0040 1234567890  --> 对0x0040地址写入字符1234567890.\r\n");   //SUART1发送一个字符串
    PrintString1("R 0x0040 10          --> 对0x0040地址读出10个字节内容.\r\n"); //SUART1发送一个字符串

    while(1)
    {
        delay_ms(1);
        if(RX1_TimeOut > 0)     //超时计数
        {
            if(--RX1_TimeOut == 0)
            {
              for(i=0; i<RX1_Cnt; i++)    UART1_TxByte(RX1_Buffer[i]);    //把收到的数据原样返回,用于测试

                status = 0xff;  //状态给一个非0值
                if((RX1_Cnt >= 10) && (RX1_Buffer[1] == ' ') && (RX1_Buffer[8] == ' ')) //最短命令为10个字节
                {
                    for(i=0; i<8; i++)
                    {
                        if((RX1_Buffer[i] >= 'a') && (RX1_Buffer[i] <= 'z'))    RX1_Buffer[i] = RX1_Buffer[i] - 'a' + 'A';  //小写转大写
                    }
                    addr = GetAddress();
                    if(addr < 63488)    //限制在0~123扇区
                    {
                        if(RX1_Buffer[0] == 'W')    //写入N个字节
                        {
                            j = RX1_Cnt - 9;
                            if(j > Tmp_Length)  j = Tmp_Length; //越界检测
                            EEPROM_SectorErase(addr);           //擦除扇区
                            i = EEPROM_write_n(addr,&RX1_Buffer[9],j);      //写N个字节
                            if(i == 0)
                            {
                                PrintString1("已写入");
                                if(j >= 100)    {UART1_TxByte(j/100+'0');   j = j % 100;}
                                if(j >= 10)     {UART1_TxByte(j/10+'0');    j = j % 10;}
                                UART1_TxByte(j%10+'0');
                                PrintString1("字节！\r\n");
                            }
                            else    PrintString1("写入错误！\r\n");
                            status = 0; //命令正确
                        }

                        else if(RX1_Buffer[0] == 'R')   //PC请求返回N字节EEPROM数据
                        {
                            j = GetDataLength();
                            if(j > Tmp_Length)  j = Tmp_Length; //越界检测
                            if(j > 0)
                            {
                                PrintString1("读出");
                                UART1_TxByte(j/10+'0');
                                UART1_TxByte(j%10+'0');
                                PrintString1("个字节内容如下：\r\n");
                                EEPROM_read_n(addr,tmp,j);
                                for(i=0; i<j; i++)  UART1_TxByte(tmp[i]);
                                UART1_TxByte(0x0d);
                                UART1_TxByte(0x0a);
                                status = 0; //命令正确
                            }
                        }
                    }
                }
                if(status != 0) PrintString1("命令错误！\r\n");
                RX1_Cnt  = 0;   //清除字节数
            }
        }
    }
}
//========================================================================


//========================================================================
// 函数: void delay_ms(unsigned char ms)
// 描述: 延时函数。
// 参数: ms,要延时的ms数, 这里只支持1~255ms. 自动适应主时钟.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void delay_ms(u8 ms)
{
     unsigned int i;
     do{
          i = MAIN_Fosc / 14000;
          while(--i)    ;   //14T per loop
     }while(--ms);
}

//========================================================================
// 函数: u8 CheckData(u8 dat)
// 描述: 将字符"0~9,A~F或a~f"转成十六进制.
// 参数: dat: 要检测的字符.
// 返回: 0x00~0x0F为正确. 0xFF为错误.
// 版本: V1.0, 2012-10-22
//========================================================================
u8 CheckData(u8 dat)
{
    if((dat >= '0') && (dat <= '9'))        return (dat-'0');
    if((dat >= 'A') && (dat <= 'F'))        return (dat-'A'+10);
    return 0xff;
}

//========================================================================
// 函数: u16    GetAddress(void)
// 描述: 计算各种输入方式的地址.
// 参数: 无.
// 返回: 16位EEPROM地址.
// 版本: V1.0, 2013-6-6
//========================================================================
u16 GetAddress(void)
{
    u16 address;
    u8  i,j;
    
    address = 0;
    if((RX1_Buffer[2] == '0') && (RX1_Buffer[3] == 'X'))
    {
        for(i=4; i<8; i++)
        {
            j = CheckData(RX1_Buffer[i]);
            if(j >= 0x10)   return 65535;   //error
            address = (address << 4) + j;
        }
        return (address);
    }
    return  65535;  //error
}

/**************** 获取要读出数据的字节数 ****************************/
u8 GetDataLength(void)
{
    u8  i;
    u8  length;
    
    length = 0;
    for(i=9; i<RX1_Cnt; i++)
    {
        if(CheckData(RX1_Buffer[i]) >= 10)  break;
        length = length * 10 + CheckData(RX1_Buffer[i]);
    }
    return (length);
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
    for (; *puts != 0;  puts++) UART1_TxByte(*puts);    //遇到停止符0结束
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
    P_SW1 |= 0x00;      //UART1 switch to, 0x00: P3.0 P3.1, 0x40: P3.6 P3.7, 0x80: P1.6 P1.7 (必须使用内部时钟)
//  PCON2 |=  (1<<4);   //内部短路RXD与TXD, 做中继, ENABLE,DISABLE

    B_TX1_Busy = 0;
    TX1_Cnt = 0;
    RX1_Cnt = 0;
    RX1_TimeOut = 0;
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


#define     IAP_STANDBY()   IAP_CMD = 0     //IAP空闲命令（禁止）
#define     IAP_READ()      IAP_CMD = 1     //IAP读出命令
#define     IAP_WRITE()     IAP_CMD = 2     //IAP写入命令
#define     IAP_ERASE()     IAP_CMD = 3     //IAP擦除命令

#define     IAP_ENABLE()    IAP_CONTR = IAP_EN; IAP_TPS = MAIN_Fosc / 1000000
#define     IAP_DISABLE()   IAP_CONTR = 0; IAP_CMD = 0; IAP_TRIG = 0; IAP_ADDRH = 0xff; IAP_ADDRL = 0xff

#define IAP_EN          (1<<7)
#define IAP_SWBS        (1<<6)
#define IAP_SWRST       (1<<5)
#define IAP_CMD_FAIL    (1<<4)


//========================================================================
// 函数: void DisableEEPROM(void)
// 描述: 禁止EEPROM.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2014-6-30
//========================================================================
void DisableEEPROM(void)        //禁止访问EEPROM
{
		IAP_CONTR = 0;          //关闭 IAP 功能
		IAP_CMD = 0;            //清除命令寄存器
		IAP_TRIG = 0;           //清除触发寄存器
		IAP_ADDRH = 0xff;       //将地址设置到非 IAP 区域
		IAP_ADDRL = 0xff;
}

//========================================================================
// 函数: void EEPROM_Trig(void)
// 描述: 触发EEPROM操作.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2014-6-30
//========================================================================
void EEPROM_Trig(void)
{
    F0 = EA;    //保存全局中断
    EA = 0;     //禁止中断, 避免触发命令无效
    IAP_TRIG = 0x5A;
    IAP_TRIG = 0xA5;                    //先送5AH，再送A5H到IAP触发寄存器，每次都需要如此
                                        //送完A5H后，IAP命令立即被触发启动
                                        //CPU等待IAP完成后，才会继续执行程序。
    _nop_();
    _nop_();
    EA = F0;    //恢复全局中断
}

//========================================================================
// 函数: void EEPROM_SectorErase(u16 EE_address)
// 描述: 擦除一个扇区.
// 参数: EE_address:  要擦除的EEPROM的扇区中的一个字节地址.
// 返回: none.
// 版本: V1.0, 2014-6-30
//========================================================================
void EEPROM_SectorErase(u16 EE_address)
{
    IAP_ENABLE();                       //设置等待时间，允许IAP操作，送一次就够
    IAP_ERASE();                        //宏调用, 送扇区擦除命令，命令不需改变时，不需重新送命令
                                        //只有扇区擦除，没有字节擦除，512字节/扇区。
                                        //扇区中任意一个字节地址都是扇区地址。
    IAP_ADDRH = EE_address / 256;       //送扇区地址高字节（地址需要改变时才需重新送地址）
    IAP_ADDRL = EE_address % 256;       //送扇区地址低字节
    EEPROM_Trig();                      //触发EEPROM操作
    DisableEEPROM();                    //禁止EEPROM操作
}

//========================================================================
// 函数: void EEPROM_read_n(u16 EE_address,u8 *DataAddress,u8 lenth)
// 描述: 读N个字节函数.
// 参数: EE_address:  要读出的EEPROM的首地址.
//       DataAddress: 要读出数据的指针.
//       length:      要读出的长度
// 返回: 0: 写入正确.  1: 写入长度为0错误.  2: 写入数据错误.
// 版本: V1.0, 2014-6-30
//========================================================================
void EEPROM_read_n(u16 EE_address,u8 *DataAddress,u8 length)
{
    IAP_ENABLE();                           //设置等待时间，允许IAP操作，送一次就够
    IAP_READ();                             //送字节读命令，命令不需改变时，不需重新送命令
    do
    {
        IAP_ADDRH = EE_address / 256;       //送地址高字节（地址需要改变时才需重新送地址）
        IAP_ADDRL = EE_address % 256;       //送地址低字节
        EEPROM_Trig();                      //触发EEPROM操作
        *DataAddress = IAP_DATA;            //读出的数据送往
        EE_address++;
        DataAddress++;
    }while(--length);

    DisableEEPROM();
}


//========================================================================
// 函数: u8 EEPROM_write_n(u16 EE_address,u8 *DataAddress,u8 length)
// 描述: 写N个字节函数.
// 参数: EE_address:  要写入的EEPROM的首地址.
//       DataAddress: 要写入数据的指针.
//       length:      要写入的长度
// 返回: 0: 写入正确.  1: 写入长度为0错误.  2: 写入数据错误.
// 版本: V1.0, 2014-6-30
//========================================================================
u8 EEPROM_write_n(u16 EE_address,u8 *DataAddress,u8 length)
{
    u8  i;
    u16 j;
    u8  *p;
    
    if(length == 0) return 1;   //长度为0错误

    IAP_ENABLE();                       //设置等待时间，允许IAP操作，送一次就够
    i = length;
    j = EE_address;
    p = DataAddress;
    IAP_WRITE();                            //宏调用, 送字节写命令
    do
    {
        IAP_ADDRH = EE_address / 256;       //送地址高字节（地址需要改变时才需重新送地址）
        IAP_ADDRL = EE_address % 256;       //送地址低字节
        IAP_DATA  = *DataAddress;           //送数据到IAP_DATA，只有数据改变时才需重新送
        EEPROM_Trig();                      //触发EEPROM操作
        EE_address++;                       //下一个地址
        DataAddress++;                      //下一个数据
    }while(--length);                       //直到结束

    EE_address = j;
    length = i;
    DataAddress = p;
    i = 0;
    IAP_READ();                             //读N个字节并比较
    do
    {
        IAP_ADDRH = EE_address / 256;       //送地址高字节（地址需要改变时才需重新送地址）
        IAP_ADDRL = EE_address % 256;       //送地址低字节
        EEPROM_Trig();                      //触发EEPROM操作
        if(*DataAddress != IAP_DATA)        //读出的数据与源数据比较
        {
            i = 2;
            break;
        }
        EE_address++;
        DataAddress++;
    }while(--length);

    DisableEEPROM();
    return i;
}

