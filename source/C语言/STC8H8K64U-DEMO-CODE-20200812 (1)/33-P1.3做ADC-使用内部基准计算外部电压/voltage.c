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

��ADC�����ⲿ��ѹ��ʹ���ڲ���׼�����ѹ.

��STC��MCU��IO��ʽ����8λ����ܡ�

ʹ��Timer0��16λ�Զ���װ������1ms����,�������������������, �û��޸�MCU��ʱ��Ƶ��ʱ,�Զ���ʱ��1ms.

�ұ�4λ�������ʾ�����ĵ�ѹֵ.

�ⲿ��ѹ�Ӱ��ϲ��µ�����������, �����ѹ0~VDD, ��Ҫ����VDD�����0V. 

ʵ����Ŀʹ���봮һ��1K�ĵ��赽ADC�����, ADC������ٲ�һ�����ݵ���.

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

sfr ADC_CONTR = 0xBC;   //��ADϵ��
sfr ADC_RES   = 0xBD;   //��ADϵ��
sfr ADC_RESL  = 0xBE;   //��ADϵ��
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


/***********************************************************/

#define DIS_DOT     0x20
#define DIS_BLACK   0x10
#define DIS_        0x11

#define P1n_pure_input(bitn)        P1M1 |=  (bitn),    P1M0 &= ~(bitn)

/****************************** �û������ ***********************************/

    #define Cal_MODE    0   //ÿ�β���ֻ��1��ADC. �ֱ���0.01V
//  #define Cal_MODE    1   //ÿ�β���������16��ADC ��ƽ������. �ֱ���0.01V

#define Timer0_Reload   (65536UL -(MAIN_Fosc / 1000))       //Timer 0 �ж�Ƶ��, 1000��/��
#define ADCTIM (*(unsigned char volatile xdata *)0xfea8)

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

u16 msecond;
u16 Bandgap;    //
u16 Get_ADC12bitResult(u8 channel); //channel = 0~15

/**********************************************/
void main(void)
{
    u8  i;
    u16 j;

    P0M1 = 0;   P0M0 = 0;   //����Ϊ׼˫���
    P2M1 = 0;   P2M0 = 0;   //����Ϊ׼˫���
    P3M1 = 0;   P3M0 = 0;   //����Ϊ׼˫���
    P4M1 = 0;   P4M0 = 0;   //����Ϊ׼˫���
    P5M1 = 0;   P5M0 = 0;   //����Ϊ׼˫���
    P6M1 = 0;   P6M0 = 0;   //����Ϊ׼˫���
    P7M1 = 0;   P7M0 = 0;   //����Ϊ׼˫���
    P1M1 = 0x08;   P1M0 = 0;   //���� P1.3 Ϊ ADC �����
    
    display_index = 0;
		P_SW2 |= 0x80;
		ADCTIM = 0x3f;		//���� ADC �ڲ�ʱ��ADC����ʱ�佨�������ֵ
		P_SW2 &= 0x7f;
		ADCCFG = 0x2f;		//���� ADC ʱ��Ϊϵͳʱ��/2/16
		ADC_CONTR = 0x80; //ʹ�� ADC ģ��

    AUXR = 0x80;    //Timer0 set as 1T, 16 bits timer auto-reload, 
    TH0 = (u8)(Timer0_Reload / 256);
    TL0 = (u8)(Timer0_Reload % 256);
    ET0 = 1;    //Timer0 interrupt enable
    TR0 = 1;    //Tiner0 run
    EA = 1;     //�����ж�
    
    for(i=0; i<8; i++)  LED8[i] = 0x10; //�ϵ�����

    while(1)
    {
        if(B_1ms)   //1ms��
        {
            B_1ms = 0;
            if(++msecond >= 300)    //300ms��
            {
                msecond = 0;

            #if (Cal_MODE == 0)
            //=================== ֻ��1��ADC, 12bit ADC. �ֱ���0.01V ===============================
                //Get_ADC12bitResult(15);  //�ȶ�һ�β��������, ���ڲ��Ĳ������ݵĵ�ѹ��������ֵ.
                Bandgap = Get_ADC12bitResult(15);    //���ڲ���׼ADC, ��15ͨ��
                j = Get_ADC12bitResult(3);  //���ⲿ��ѹADC
                j = (u16)((u32)j * 119 / Bandgap);  //�����ⲿ��ѹ, BandgapΪ1.19V, ���ѹ�ֱ���0.01V
            #endif
            //==========================================================================

            //===== ������16��ADC ��ƽ������. �ֱ���0.01V =========
            #if (Cal_MODE == 1)
                //Get_ADC12bitResult(15);  //�ȶ�һ�β��������, ���ڲ��Ĳ������ݵĵ�ѹ��������ֵ.
                for(j=0, i=0; i<16; i++)
                {
                    j += Get_ADC12bitResult(15); //���ڲ���׼ADC, ��15ͨ��
                }
                Bandgap = j >> 4;   //16��ƽ��
                for(j=0, i=0; i<16; i++)
                {
                    j += Get_ADC12bitResult(3); //���ⲿ��ѹADC
                }
                j = j >> 4; //16��ƽ��
                j = (u16)((u32)j * 119 / Bandgap);  //�����ⲿ��ѹ, BandgapΪ1.19V, ���ѹ�ֱ���0.01V
            #endif
            //==========================================================================

                LED8[5] = j / 100 + DIS_DOT;    //��ʾ�ⲿ��ѹֵ
                LED8[6] = (j % 100) / 10;
                LED8[7] = j % 10;
/*
                j = Bandgap;
                LED8[0] = j / 1000;     //��ʾBandgap ADCֵ
                LED8[1] = (j % 1000) / 100;
                LED8[2] = (j % 100) / 10;
                LED8[3] = j % 10;
*/
            }
        }
    }
} 
/**********************************************/

//========================================================================
// ����: u16 Get_ADC12bitResult(u8 channel)
// ����: ��ѯ����һ��ADC���.
// ����: channel: ѡ��Ҫת����ADC.
// ����: 12λADC���.
// �汾: V1.0, 2012-10-22
//========================================================================
u16 Get_ADC12bitResult(u8 channel)  //channel = 0~15
{
    ADC_RES = 0;
    ADC_RESL = 0;

    ADC_CONTR = (ADC_CONTR & 0xF0) | 0x40 | channel;    //���� AD ת��
    _nop_();
    _nop_();
    _nop_();
    _nop_();

    while((ADC_CONTR & 0x20) == 0)  ;   //wait for ADC finish
    ADC_CONTR &= ~0x20;     //���ADC������־
    return  (((u16)ADC_RES << 8) | ADC_RESL);
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

