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

�ڲ�����I2C�������߿��������ӻ�ģʽ��SCL->P3.2, SDA->P3.3;
IO��ģ��I2C������ģʽ��SCL->P0.0, SDA->P0.1;
ͨ���ⲿ�������� P0.0->P3.2, P0.1->P3.3��ʵ��I2C�Է����չ��ܡ�

��STC��MCU��IO��ʽ����8λ����ܡ�
ʹ��Timer0��16λ�Զ���װ������1ms����,�������������������,�û��޸�MCU��ʱ��Ƶ��ʱ,�Զ���ʱ��1ms.
������ÿ���Ӽ�1, ������ΧΪ0~9999.

��ʾЧ��Ϊ: �ϵ������ÿ���ӷ���һ�μ������ݣ��������4�����������ʾ�������ݣ��ӻ����յ����ݺ����ұ�4���������ʾ��

����ʱ, ѡ��ʱ�� 24MHZ (�û��������޸�Ƶ��).

******************************************/


#include "reg51.h"
#include "intrins.h"

#define MAIN_Fosc       24000000L   //������ʱ��

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

#define Timer0_Reload   (65536UL -(MAIN_Fosc / 1000))       //Timer 0 �ж�Ƶ��, 1000��/��

#define DIS_DOT     0x20
#define DIS_BLACK   0x10
#define DIS_        0x11

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

bit isda;                                       //�豸��ַ��־
bit isma;                                       //�洢��ַ��־
bit B_1ms;          //1ms��־
bit DisplayFlag;
u8 addr;
u8 pdata buffer[256];
u16 msecond;
u16 Test_cnt;   //�����õ����������
u8  tmp[4];     //ͨ������

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
        I2CSLST &= ~0x40;                       //����START�¼�
    }
    else if (I2CSLST & 0x20)
    {
        I2CSLST &= ~0x20;                       //����RECV�¼���SLACKO����Ϊ0
        if (isda)
        {
            isda = 0;                           //����RECV�¼���RECV DEVICE ADDR��
        }
        else if (isma)
        {
            isma = 0;                           //����RECV�¼���RECV MEMORY ADDR��
            addr = I2CRXD;
            I2CTXD = buffer[addr];
        }
        else
        {
            buffer[addr++] = I2CRXD;            //����RECV�¼���RECV DATA��
        }
    }
    else if (I2CSLST & 0x10)
    {
        I2CSLST &= ~0x10;                       //����SEND�¼�
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
        I2CSLST &= ~0x08;                       //����STOP�¼�
        isda = 1;
        isma = 1;
        DisplayFlag = 1;
    }

    P_SW2 = store;
}

void main()
{
    u8  i;

    P0M1 = 0;   P0M0 = 0;   //����Ϊ׼˫���
    P6M1 = 0;   P6M0 = 0;   //����Ϊ׼˫���
    P7M1 = 0;   P7M0 = 0;   //����Ϊ׼˫���
    P3M1 = 0x04;   P3M0 = 0x00;   //SCL����Ϊ����ڣ�SDA����Ϊ׼˫���

    P_SW2 = 0x80;
    P_SW2 |= 0x30;   //I2C���ܽ�ѡ��00:P1.5,P1.4; 01:P2.5,P2.4; 11:P3.2,P3.3

    I2CCFG = 0x80;                              //ʹ��I2C�ӻ�ģʽ
    I2CSLADR = 0x5a;                            //���ôӻ��豸��ַΪ5A
    I2CSLST = 0x00;
    I2CSLCR = 0x78;                             //ʹ�ܴӻ�ģʽ�ж�

    Timer0_config();
    display_index = 0;
    DisplayFlag = 0;
    EA = 1;

    isda = 1;                                   //�û�������ʼ��
    isma = 1;
    addr = 0;
    I2CTXD = buffer[addr];

    for(i=0; i<8; i++)  LED8[i] = DIS_; //�ϵ�ȫ����ʾ-
    
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
				
				if(++msecond >= 1000)   //1�뵽
				{
						msecond = 0;        //��1000ms����
						Test_cnt++;         //�����+1
						if(Test_cnt >= 10000)    Test_cnt = 0;   //�������ΧΪ0~9999

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
// ����: void Timer0_config(void)
// ����: Timer0��ʼ��������
// ����: ��.
// ����: ��.
// �汾: V1.0, 2020-6-10
//========================================================================
void Timer0_config(void)
{
    AUXR = 0x80;    //Timer0 set as 1T, 16 bits timer auto-reload, 
    TH0 = (u8)(Timer0_Reload / 256);
    TL0 = (u8)(Timer0_Reload % 256);
    ET0 = 1;    //Timer0 interrupt enable
    TR0 = 1;    //Tiner0 run
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


#define SLAW    0x5A
#define SLAR    0x5B

sbit    SDA = P0^1; //����SDA
sbit    SCL = P0^0; //����SCL

/****************************/
void    I2C_Delay(void) //for normal MCS51, delay (2 * dly + 4) T, for STC12Cxxxx delay (4 * dly + 10) T
{
    u8  dly;
    dly = MAIN_Fosc / 2000000UL;        //��2us����
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

