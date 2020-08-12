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

��STC��MCU��IO��ʽ����8λ����ܡ�

��ʾЧ��Ϊ: ����ʱ��.

ʹ��Timer0��16λ�Զ���װ������1ms����,�������������������,�û��޸�MCU��ʱ��Ƶ��ʱ,�Զ���ʱ��1ms.

���4λLED��ʾʱ��(Сʱ,����), �ұ������λ��ʾ����ֵ.

ADC��������Ϊ1~16.

����ֻ֧�ֵ�������, ��֧�ֶ��ͬʱ����, ���������в���Ԥ֪�Ľ��.

�����³���1���,����10��/����ٶ��ṩ�ؼ����. �û�ֻ��Ҫ���KeyCode�Ƿ��0���жϼ��Ƿ���.

����ʱ���:
����1: Сʱ+.
����2: Сʱ-.
����3: ����+.
����4: ����-.

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


#define ADCTIM (*(unsigned char volatile xdata *)0xfea8)
#define Timer0_Reload   (65536UL -(MAIN_Fosc / 1000))       //Timer 0 �ж�Ƶ��, 1000��/��

#define DIS_DOT     0x20
#define DIS_BLACK   0x10
#define DIS_        0x11


u8 code t_display[]={                       //��׼�ֿ�
//   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,
//black  -     H    J    K    L    N    o   P    U     t    G    Q    r   M    y
    0x00,0x40,0x76,0x1E,0x70,0x38,0x37,0x5C,0x73,0x3E,0x78,0x3d,0x67,0x50,0x37,0x6e,
    0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x46};    //0. 1. 2. 3. 4. 5. 6. 7. 8. 9. -1

u8 code T_COM[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};      //λ��


u8  LED8[8];        //��ʾ����
u8  display_index;  //��ʾλ����
bit B_1ms;          //1ms��־

u8  ADC_KeyState,ADC_KeyState1,ADC_KeyState2,ADC_KeyState3; //��״̬
u8  ADC_KeyHoldCnt; //�����¼�ʱ
u8  KeyCode;    //���û�ʹ�õļ���, 1~16��Ч
u8  cnt10ms;

u8  hour,minute,second; //RTC����
u16 msecond;

void    CalculateAdcKey(u16 adc);
u16     Get_ADC12bitResult(u8 channel); //channel = 0~15
void    DisplayRTC(void);
void    RTC(void);


/**********************************************/
void main(void)
{
    u8  i;
    u16 j;

    P0M1 = 0;   P0M0 = 0;   //����Ϊ׼˫���
    P1M1 = 1;   P1M0 = 0;   //���� P1.0 Ϊ ADC �����
    P2M1 = 0;   P2M0 = 0;   //����Ϊ׼˫���
    P3M1 = 0;   P3M0 = 0;   //����Ϊ׼˫���
    P4M1 = 0;   P4M0 = 0;   //����Ϊ׼˫���
    P5M1 = 0;   P5M0 = 0;   //����Ϊ׼˫���
    P6M1 = 0;   P6M0 = 0;   //����Ϊ׼˫���
    P7M1 = 0;   P7M0 = 0;   //����Ϊ׼˫���
    
    display_index = 0;
	
		P_SW2 |= 0x80;
		ADCTIM = 0x3f;		//���� ADC �ڲ�ʱ��ADC����ʱ�佨�������ֵ
		P_SW2 &= 0x7f;
		ADCCFG = 0x2f;		//���� ADC ʱ��Ϊϵͳʱ��/2/16/16
		ADC_CONTR = 0x80; //ʹ�� ADC ģ��

    AUXR = 0x80;    //Timer0 set as 1T, 16 bits timer auto-reload, 
    TH0 = (u8)(Timer0_Reload / 256);
    TL0 = (u8)(Timer0_Reload % 256);
    ET0 = 1;    //Timer0 interrupt enable
    TR0 = 1;    //Tiner0 run
    EA = 1;     //�����ж�
    
    for(i=0; i<8; i++)  LED8[i] = 0x10; //�ϵ�����

    hour   = 12;    //��ʼ��ʱ��ֵ
    minute = 0;
    second = 0;
    DisplayRTC();

    ADC_KeyState  = 0;
    ADC_KeyState1 = 0;
    ADC_KeyState2 = 0;
    ADC_KeyState3 = 0;  //��״̬
    ADC_KeyHoldCnt = 0; //�����¼�ʱ
    KeyCode = 0;    //���û�ʹ�õļ���, 1~16��Ч
    cnt10ms = 0;

    while(1)
    {
        if(B_1ms)   //1ms��
        {
            B_1ms = 0;
            if(++msecond >= 1000)   //1�뵽
            {
                msecond = 0;
                RTC();
                DisplayRTC();
            }
            if(msecond == 500)  DisplayRTC();   //Сʱ���С����������

            if(++cnt10ms >= 10) //10ms��һ��ADC
            {
                cnt10ms = 0;
                j = Get_ADC12bitResult(0);  //����0~15,��ѯ��ʽ��һ��ADC, ����ֵ���ǽ��, == 4096 Ϊ����
                if(j < 4096)    CalculateAdcKey(j); //���㰴��
                        
            }

            if(KeyCode > 0)     //�м�����
            {
                LED8[6] = KeyCode / 10; //��ʾ����
                LED8[7] = KeyCode % 10; //��ʾ����

                if(KeyCode == 1)    //hour +1
                {
                    if(++hour >= 24)    hour = 0;
                    DisplayRTC();
                }
                if(KeyCode == 2)    //hour -1
                {
                    if(--hour >= 24)    hour = 23;
                    DisplayRTC();
                }
                if(KeyCode == 3)    //minute +1
                {
                    second = 0;
                    if(++minute >= 60)  minute = 0;
                    DisplayRTC();
                }
                if(KeyCode == 4)    //minute -1
                {
                    second = 0;
                    if(--minute >= 60)  minute = 59;
                    DisplayRTC();
                }
                KeyCode = 0;
            }
        }
    }
} 
/**********************************************/


/********************** ��ʾʱ�Ӻ��� ************************/
void DisplayRTC(void)
{
    if(hour >= 10)  LED8[0] = hour / 10;
    else            LED8[0] = DIS_BLACK;
    LED8[1] = hour % 10;
    LED8[2] = minute / 10;
    LED8[3] = minute % 10;
    if(msecond >= 500)      LED8[1] |= DIS_DOT; //Сʱ���С����������
}

/********************** RTC��ʾ���� ************************/
void RTC(void)
{
    if(++second >= 60)
    {
        second = 0;
        if(++minute >= 60)
        {
            minute = 0;
            if(++hour >= 24)    hour = 0;
        }
    }
}


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

/***************** ADC���̼������ *****************************
��·������㷨���: Coody
��ADC���̷����ںܶ�ʵ�ʲ�Ʒ�����, ��֤�����ȶ��ɿ�, ��ʹ����ʹ�õ���Ĥ,���ܿɿ�.
16����,�����ϸ�������Ӧ��ADCֵΪ (4096 / 16) * k = 256 * k, k = 1 ~ 16, �ر��, k=16ʱ,��Ӧ��ADCֵ��4095.
����ʵ�ʻ���ƫ��,���ж�ʱ�������ƫ��, ADC_OFFSETΪ+-ƫ��, ��ADCֵ�� (256*k-ADC_OFFSET) �� (256*k+ADC_OFFSET)֮��Ϊ����Ч.
���һ����ʱ��,�Ͳ���һ��ADC,����10ms.
Ϊ�˱���żȻ��ADCֵ����, ���߱���ADC���������½�ʱ����, ʹ������3��ADCֵ����ƫ�Χ��ʱ, ADCֵ����Ϊ��Ч.
�����㷨, �ܱ�֤�����ǳ��ɿ�.
**********************************************/
#define ADC_OFFSET  64
void CalculateAdcKey(u16 adc)
{
    u8  i;
    u16 j;
    
    if(adc < (256-ADC_OFFSET))
    {
        ADC_KeyState = 0;   //��״̬��0
        ADC_KeyHoldCnt = 0;
    }
    j = 256;
    for(i=1; i<=16; i++)
    {
        if((adc >= (j - ADC_OFFSET)) && (adc <= (j + ADC_OFFSET)))  break;  //�ж��Ƿ���ƫ�Χ��
        j += 256;
    }
    ADC_KeyState3 = ADC_KeyState2;
    ADC_KeyState2 = ADC_KeyState1;
    if(i > 16)  ADC_KeyState1 = 0;  //����Ч
    else                        //����Ч
    {
        ADC_KeyState1 = i;
        if((ADC_KeyState3 == ADC_KeyState2) && (ADC_KeyState2 == ADC_KeyState1) &&
           (ADC_KeyState3 > 0) && (ADC_KeyState2 > 0) && (ADC_KeyState1 > 0))
        {
            if(ADC_KeyState == 0)   //��һ�μ�⵽
            {
                KeyCode  = i;   //�������
                ADC_KeyState = i;   //�����״̬
                ADC_KeyHoldCnt = 0;
            }
            if(ADC_KeyState == i)   //������⵽ͬһ������
            {
                if(++ADC_KeyHoldCnt >= 100) //����1���,��10��ÿ����ٶ�Repeat Key
                {
                    ADC_KeyHoldCnt = 90;
                    KeyCode  = i;   //�������
                }
            }
            else ADC_KeyHoldCnt = 0; //����ʱ�������0
        }
    }
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

