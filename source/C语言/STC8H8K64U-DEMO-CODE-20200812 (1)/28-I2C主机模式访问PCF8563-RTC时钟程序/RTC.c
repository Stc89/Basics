/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����            */
/*---------------------------------------------------------------------*/


/*************  ��������˵��  **************

��дRTC, ICΪPCF8563.

��STC��MCU��IO��ʽ����8λ����ܡ�

ʹ��Timer0��16λ�Զ���װ������1ms����,�������������������, �û��޸�MCU��ʱ��Ƶ��ʱ,�Զ���ʱ��1ms.

8λ�������ʾʱ��(Сʱ-����-��).

����ɨ�谴������Ϊ17~32.

����ֻ֧�ֵ�������, ��֧�ֶ��ͬʱ����, ���������в���Ԥ֪�Ľ��.

�����³���1���,����10��/����ٶ��ṩ�ؼ����. �û�ֻ��Ҫ���KeyCode�Ƿ��0���жϼ��Ƿ���.

����ʱ���:
����17: Сʱ+.
����18: Сʱ-.
����19: ����+.
����20: ����-.

����ʱ, ѡ��ʱ�� 24MHZ (�û��������޸�Ƶ��).

******************************************/


#include    "reg51.h"
#include    "intrins.h"

#define     MAIN_Fosc       24000000L   //������ʱ��

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

#define I2CCFG          (*(unsigned char volatile xdata *)0xfe80)
#define I2CMSCR         (*(unsigned char volatile xdata *)0xfe81)
#define I2CMSST         (*(unsigned char volatile xdata *)0xfe82)
#define I2CSLCR         (*(unsigned char volatile xdata *)0xfe83)
#define I2CSLST         (*(unsigned char volatile xdata *)0xfe84)
#define I2CSLADR        (*(unsigned char volatile xdata *)0xfe85)
#define I2CTXD          (*(unsigned char volatile xdata *)0xfe86)
#define I2CRXD          (*(unsigned char volatile xdata *)0xfe87)
#define I2CMSAUX        (*(unsigned char volatile xdata *)0xfe88)

sbit SDA = P1^4;
sbit SCL = P1^5;

/***********************************************************/

#define DIS_DOT     0x20
#define DIS_BLACK   0x10
#define DIS_        0x11

#define SLAW    0xA2
#define SLAR    0xA3


/****************************** �û������ ***********************************/

#define Timer0_Reload   (65536UL -(MAIN_Fosc / 1000))       //Timer 0 �ж�Ƶ��, 1000��/��

/*****************************************************************************/


/*************  ���س�������    **************/
u8 code t_display[]={                       //��׼�ֿ�
//   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,
//black  -     H    J    K    L    N    o   P    U     t    G    Q    r   M    y
    0x00,0x40,0x76,0x1E,0x70,0x38,0x37,0x5C,0x73,0x3E,0x78,0x3d,0x67,0x50,0x37,0x6e,
    0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x46};    //0. 1. 2. 3. 4. 5. 6. 7. 8. 9. -1

u8 code T_COM[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};      //λ��


/*************  ���ر�������    **************/

u8  LED8[8];        //��ʾ����
u8  display_index;  //��ʾλ����
bit B_1ms;          //1ms��־

u8 IO_KeyState, IO_KeyState1, IO_KeyHoldCnt;    //���м��̱���
u8  KeyHoldCnt; //�����¼�ʱ
u8  KeyCode;    //���û�ʹ�õļ���
u8  cnt50ms;

u8  hour,minute,second; //RTC����
u16 msecond;


/*************  ���غ�������    **************/
void    CalculateAdcKey(u16 adc);
void    IO_KeyScan(void);   //50ms call
void    WriteNbyte(u8 addr, u8 *p, u8 number);
void    ReadNbyte( u8 addr, u8 *p, u8 number);
void    DisplayRTC(void);
void    ReadRTC(void);
void    WriteRTC(void);


/**********************************************/
void main(void)
{
    u8  i;

    P0M1 = 0;   P0M0 = 0;   //����Ϊ׼˫���
    P1M1 = 0;   P1M0 = 0;   //����Ϊ׼˫���
    P2M1 = 0;   P2M0 = 0;   //����Ϊ׼˫���
    P3M1 = 0;   P3M0 = 0;   //����Ϊ׼˫���
    P4M1 = 0;   P4M0 = 0;   //����Ϊ׼˫���
    P5M1 = 0;   P5M0 = 0;   //����Ϊ׼˫���
    P6M1 = 0;   P6M0 = 0;   //����Ϊ׼˫���
    P7M1 = 0;   P7M0 = 0;   //����Ϊ׼˫���
    
    display_index = 0;
    
    for(i=0; i<8; i++)  LED8[i] = 0x10; //�ϵ�����
    
    AUXR = 0x80;    //Timer0 set as 1T, 16 bits timer auto-reload, 
    TH0 = (u8)(Timer0_Reload / 256);
    TL0 = (u8)(Timer0_Reload % 256);
    ET0 = 1;    //Timer0 interrupt enable
    TR0 = 1;    //Tiner0 run

    P_SW2 |= 0x80;
    I2CCFG = 0xe0;                  //ʹ��I2C����ģʽ
    I2CMSST = 0x00;

    EA = 1;     //�����ж�
    
    ReadRTC();
    F0 = 0;
    if(second >= 60)    F0 = 1; //����
    if(minute >= 60)    F0 = 1; //����
    if(hour   >= 24)    F0 = 1; //����
    if(F0)  //�д���, Ĭ��12:00:00
    {
        second = 0;
        minute = 0;
        hour  = 12;
        WriteRTC();
    }

    DisplayRTC();
    LED8[2] = DIS_;
    LED8[5] = DIS_;

    KeyHoldCnt = 0; //�����¼�ʱ
    KeyCode = 0;    //���û�ʹ�õļ���

    IO_KeyState = 0;
    IO_KeyState1 = 0;
    IO_KeyHoldCnt = 0;
    cnt50ms = 0;

    while(1)
    {
        if(B_1ms)   //1ms��
        {
            B_1ms = 0;
            if(++msecond >= 1000)   //1�뵽
            {
                msecond = 0;
                ReadRTC();
                DisplayRTC();
            }

            if(++cnt50ms >= 50)     //50msɨ��һ�����м���
            {
                cnt50ms = 0;
                IO_KeyScan();
            }
            
            if(KeyCode != 0)        //�м�����
            {
                if(KeyCode == 17)   //hour +1
                {
                    if(++hour >= 24)    hour = 0;
                    WriteRTC();
                    DisplayRTC();
                }
                if(KeyCode == 18)   //hour -1
                {
                    if(--hour >= 24)    hour = 23;
                    WriteRTC();
                    DisplayRTC();
                }
                if(KeyCode == 19)   //minute +1
                {
                    second = 0;
                    if(++minute >= 60)  minute = 0;
                    WriteRTC();
                    DisplayRTC();
                }
                if(KeyCode == 20)   //minute -1
                {
                    second = 0;
                    if(--minute >= 60)  minute = 59;
                    WriteRTC();
                    DisplayRTC();
                }

                KeyCode = 0;
            }

        }
    }
} 

/********************** ��ʾʱ�Ӻ��� ************************/
void    DisplayRTC(void)
{
    if(hour >= 10)  LED8[0] = hour / 10;
    else            LED8[0] = DIS_BLACK;
    LED8[1] = hour % 10;
    LED8[2] = DIS_;
    LED8[3] = minute / 10;
    LED8[4] = minute % 10;
    LED8[6] = second / 10;
    LED8[7] = second % 10;
}

/********************** ��RTC���� ************************/
void    ReadRTC(void)
{
    u8  tmp[3];

    ReadNbyte(2, tmp, 3);
    second = ((tmp[0] >> 4) & 0x07) * 10 + (tmp[0] & 0x0f);
    minute = ((tmp[1] >> 4) & 0x07) * 10 + (tmp[1] & 0x0f);
    hour   = ((tmp[2] >> 4) & 0x03) * 10 + (tmp[2] & 0x0f);
}

/********************** дRTC���� ************************/
void    WriteRTC(void)
{
    u8  tmp[3];

    tmp[0] = ((second / 10) << 4) + (second % 10);
    tmp[1] = ((minute / 10) << 4) + (minute % 10);
    tmp[2] = ((hour / 10) << 4) + (hour % 10);
    WriteNbyte(2, tmp, 3);
}


/*****************************************************
    ���м�ɨ�����
    ʹ��XY����4x4���ķ�����ֻ�ܵ������ٶȿ�

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

    j = IO_KeyState1;   //������һ��״̬

    P0 = 0xf0;  //X�ͣ���Y
    IO_KeyDelay();
    IO_KeyState1 = P0 & 0xf0;

    P0 = 0x0f;  //Y�ͣ���X
    IO_KeyDelay();
    IO_KeyState1 |= (P0 & 0x0f);
    IO_KeyState1 ^= 0xff;   //ȡ��
    
    if(j == IO_KeyState1)   //�������ζ����
    {
        j = IO_KeyState;
        IO_KeyState = IO_KeyState1;
        if(IO_KeyState != 0)    //�м�����
        {
            F0 = 0;
            if(j == 0)  F0 = 1; //��һ�ΰ���
            else if(j == IO_KeyState)
            {
                if(++IO_KeyHoldCnt >= 20)   //1����ؼ�
                {
                    IO_KeyHoldCnt = 18;
                    F0 = 1;
                }
            }
            if(F0)
            {
                j = T_KeyTable[IO_KeyState >> 4];
                if((j != 0) && (T_KeyTable[IO_KeyState& 0x0f] != 0)) 
                    KeyCode = (j - 1) * 4 + T_KeyTable[IO_KeyState & 0x0f] + 16;    //������룬17~32
            }
        }
        else    IO_KeyHoldCnt = 0;
    }
    P0 = 0xff;
}


/********************** ��ʾɨ�躯�� ************************/
void DisplayScan(void)
{   
    P7 = ~T_COM[7-display_index];
    P6 = ~t_display[LED8[display_index]];
    if(++display_index >= 8)    display_index = 0;  //8λ������0
}


/********************** Timer0 1ms�жϺ��� ************************/
void timer0 (void) interrupt 1
{
    DisplayScan();  //1msɨ����ʾһλ
    B_1ms = 1;      //1ms��־
}


void Wait()
{
    while (!(I2CMSST & 0x40));
    I2CMSST &= ~0x40;
}

void Start()
{
    I2CMSCR = 0x01;                         //����START����
    Wait();
}

void SendData(char dat)
{
    I2CTXD = dat;                           //д���ݵ����ݻ�����
    I2CMSCR = 0x02;                         //����SEND����
    Wait();
}

void RecvACK()
{
    I2CMSCR = 0x03;                         //���Ͷ�ACK����
    Wait();
}

char RecvData()
{
    I2CMSCR = 0x04;                         //����RECV����
    Wait();
    return I2CRXD;
}

void SendACK()
{
    I2CMSST = 0x00;                         //����ACK�ź�
    I2CMSCR = 0x05;                         //����ACK����
    Wait();
}

void SendNAK()
{
    I2CMSST = 0x01;                         //����NAK�ź�
    I2CMSCR = 0x05;                         //����ACK����
    Wait();
}

void Stop()
{
    I2CMSCR = 0x06;                         //����STOP����
    Wait();
}

void WriteNbyte(u8 addr, u8 *p, u8 number)  /*  WordAddress,First Data Address,Byte lenth   */
{
    Start();                                //������ʼ����
    SendData(SLAW);                         //�����豸��ַ+д����
    RecvACK();
    SendData(addr);                         //���ʹ洢��ַ
    RecvACK();
    do
    {
        SendData(*p++);
        RecvACK();
    }
    while(--number);
    Stop();                                 //����ֹͣ����
}

void ReadNbyte(u8 addr, u8 *p, u8 number)   /*  WordAddress,First Data Address,Byte lenth   */
{
    Start();                                //������ʼ����
    SendData(SLAW);                         //�����豸��ַ+д����
    RecvACK();
    SendData(addr);                         //���ʹ洢��ַ
    RecvACK();
    Start();                                //������ʼ����
    SendData(SLAR);                         //�����豸��ַ+������
    RecvACK();
    do
    {
        *p = RecvData();
        p++;
        if(number != 1) SendACK();          //send ACK
    }
    while(--number);
    SendNAK();                              //send no ACK	
    Stop();                                 //����ֹͣ����
}
/****************************/

