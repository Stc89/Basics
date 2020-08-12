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


/*************  ����˵��    **************

��P1.7(PWM4N)���16λ��PWM, �����PWM����RC�˲���ֱ����ѹ��P1.1��ADC�����������ʾ����.

����1����Ϊ115200bps, 8,n, 1, �л���P3.0 P3.1, ���غ�Ϳ���ֱ�Ӳ���. ͨ������1����ռ�ձ�.

��������ʹ��ASCII������֣����磺 10����������ռ�ձ�Ϊ10/256�� 100�� ��������ռ�ձ�Ϊ100/256��

�������õ�ֵΪ0~256, 0Ϊ�����͵�ƽ, 256Ϊ�����ߵ�ƽ.

���4λ�������ʾPWM��ռ�ձ�ֵ���ұ�4λ�������ʾADCֵ��

����ʱ, ѡ��ʱ�� 22.1184MHz (�û��������޸�Ƶ��).

******************************************/

#include    "reg51.h"
#include    "intrins.h"

#define     MAIN_Fosc       22118400L   //������ʱ�ӣ���ȷ����115200�����ʣ�

typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;

sfr TH2  = 0xD6;
sfr TL2  = 0xD7;
sfr IE2   = 0xAF;
sfr INT_CLKO = 0x8F;
sfr AUXR = 0x8E;
sfr P_SW1 = 0xA2;
sfr P_SW2 = 0xBA;

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

/****************************** �û������ ***********************************/

#define Timer0_Reload   (65536UL -(MAIN_Fosc / 1000))       //Timer 0 �ж�Ƶ��, 1000��/��
#define ADCTIM (*(unsigned char volatile xdata *)0xfea8)

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

/*****************************************************************************/

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
bit B_1ms;          //1ms��־
u8  cnt200ms;

#define     Baudrate1           115200L
#define     UART1_BUF_LENGTH    128     //���ڻ��峤��

u8  RX1_TimeOut;
u8  TX1_Cnt;    //���ͼ���
u8  RX1_Cnt;    //���ռ���
bit B_TX1_Busy; //����æ��־
u16 adc;

u8  xdata   RX1_Buffer[UART1_BUF_LENGTH];   //���ջ���

void    UART1_config(u8 brt);   // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer1��������.
void    PrintString1(u8 *puts);
void    UART1_TxByte(u8 dat);
void    UpdatePwm(u16 pwm_value);
u16     Get_ADC12bitResult(u8 channel); //channel = 0~15

/******************** ������ **************************/
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
    P1M1 = 0x02;   P1M0 = 0x00;   //���� P1.1 Ϊ ADC ��

    display_index = 0;

    //  Timer0��ʼ��
    AUXR = 0x80;    //Timer0 set as 1T, 16 bits timer auto-reload, 
    TH0 = (u8)(Timer0_Reload / 256);
    TL0 = (u8)(Timer0_Reload % 256);
    ET0 = 1;    //Timer0 interrupt enable
    TR0 = 1;    //Tiner0 run

    //  ADC��ʼ��
		P_SW2 |= 0x80;
		ADCTIM = 0x3f;		//���� ADC �ڲ�ʱ��ADC����ʱ�佨�������ֵ
		P_SW2 &= 0x7f;
		ADCCFG = 0x2f;		//���� ADC ת������Ҷ���,ʱ��Ϊϵͳʱ��/2/16
		ADC_CONTR = 0x81; //ʹ�� ADC ģ��

		P_SW2 |= 0x80;
		
    PWM1_CCER2 = 0x00; //д CCMRx ǰ���������� CCxE �ر�ͨ��
    PWM1_CCMR4 = 0x60; //���� PWM4 ģʽ1 ���
    PWM1_CCER2 = 0x50; //ʹ�� CC4E ͨ��

    PWM1_ARRH = 2; //��������ʱ��
    PWM1_ARRL = 0;
    PWM1_CCR4H = 0;
    PWM1_CCR4L = 128; //����ռ�ձ�ʱ��

    PWM1_ENO = 0x80; //ʹ�� PWM4N ���
//  PWM1_ENO = 0x40; //ʹ�� PWM4P ���
		PWM1_PS = 0x00;  //�߼� PWM ͨ�� 4N �����ѡ��λ, 0x00:P1.7, 0x40:P2.7, 0x80:P6.7, 0xC0:P3.3
//  PWM1_PS = 0x00;  //�߼� PWM ͨ�� 4P �����ѡ��λ, 0x00:P1.6, 0x40:P2.6, 0x80:P6.6, 0xC0:P3.4
    PWM1_BKR = 0x80; //ʹ�������
    PWM1_CR1 |= 0x01; //��ʼ��ʱ
		P_SW2 &= 0x7f;

    UpdatePwm(128);

    UART1_config(1);    // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer1��������.
    EA = 1;     //�����ж�

    for(i=0; i<8; i++)  LED8[i] = DIS_; //�ϵ�ȫ����ʾ-
    
    LED8[0] = 1;    //��ʾPWMĬ��ֵ
    LED8[1] = 2;
    LED8[2] = 8;
    LED8[3] = DIS_BLACK;    //��λ����ʾ

    PrintString1("PWM��ADC���Գ���, ����ռ�ձ�Ϊ 0~256!\r\n");  //SUART1����һ���ַ���
    
    while (1)
    {
        if(B_1ms)   //1ms��
        {
            B_1ms = 0;
            if(++cnt200ms >= 200)   //200ms��һ��ADC
            {
                cnt200ms = 0;
                j = Get_ADC12bitResult(1);  //����0~15,��ѯ��ʽ��һ��ADC, ����ֵ���ǽ��, == 4096 Ϊ����
                if(j >= 1000)   LED8[4] = j / 1000;     //��ʾADCֵ
                else            LED8[4] = DIS_BLACK;
                LED8[5] = (j % 1000) / 100;
                LED8[6] = (j % 100) / 10;
                LED8[7] = j % 10;
            }

            if(RX1_TimeOut > 0)     //��ʱ����
            {
                if(--RX1_TimeOut == 0)
                {
                    if((RX1_Cnt > 0) && (RX1_Cnt <= 3)) //����Ϊ3λ����
                    {
                        F0 = 0; //�����־
                        j = 0;
                        for(i=0; i<RX1_Cnt; i++)
                        {
                            if((RX1_Buffer[i] >= '0') && (RX1_Buffer[i] <= '9'))    //�޶�Ϊ����
                            {
                                j = j * 10 + RX1_Buffer[i] - '0';
                            }
                            else
                            {
                                F0 = 1; //���յ��������ַ�, ����
                                PrintString1("����! ���յ��������ַ�! ռ�ձ�Ϊ0~256!\r\n");
                                break;
                            }
                        }
                        if(!F0)
                        {
                            if(j > 256) PrintString1("����! ����ռ�ձȹ���, �벻Ҫ����256!\r\n");
                            else
                            {
                                UpdatePwm(j);
                                if(j >= 100)    LED8[0] = j / 100,  j %= 100;   //��ʾPWMĬ��ֵ
                                else            LED8[0] = DIS_BLACK;
                                LED8[1] = j % 100 / 10;
                                LED8[2] = j % 10;
                                PrintString1("�Ѹ���ռ�ձ�!\r\n");
                            }
                        }
                    }
                    else  PrintString1("����! �����ַ�����! ����ռ�ձ�Ϊ0~256!\r\n");
                    RX1_Cnt = 0;
                }
            }
        }
    }
}

//========================================================================
// ����: void UART1_TxByte(u8 dat)
// ����: ����һ���ֽ�.
// ����: ��.
// ����: ��.
// �汾: V1.0, 2014-6-30
//========================================================================
void UART1_TxByte(u8 dat)
{
    SBUF = dat;
    B_TX1_Busy = 1;
    while(B_TX1_Busy);
}

//========================================================================
// ����: void PrintString1(u8 *puts)
// ����: ����1�����ַ���������
// ����: puts:  �ַ���ָ��.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void PrintString1(u8 *puts) //����һ���ַ���
{
    for (; *puts != 0;  puts++)   UART1_TxByte(*puts);  //����ֹͣ��0����
}

//========================================================================
// ����: void SetTimer2Baudraye(u16 dat)
// ����: ����Timer2�������ʷ�������
// ����: dat: Timer2����װֵ.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void SetTimer2Baudraye(u16 dat)  // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer1��������.
{
    AUXR &= ~(1<<4);    //Timer stop
    AUXR &= ~(1<<3);    //Timer2 set As Timer
    AUXR |=  (1<<2);    //Timer2 set as 1T mode
    TH2 = dat / 256;
    TL2 = dat % 256;
    IE2  &= ~(1<<2);    //��ֹ�ж�
    AUXR |=  (1<<4);    //Timer run enable
}

//========================================================================
// ����: void UART1_config(u8 brt)
// ����: UART1��ʼ��������
// ����: brt: ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer1��������.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void UART1_config(u8 brt)    // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer1��������.
{
    /*********** ������ʹ�ö�ʱ��2 *****************/
    if(brt == 2)
    {
        AUXR |= 0x01;       //S1 BRT Use Timer2;
        SetTimer2Baudraye(65536UL - (MAIN_Fosc / 4) / Baudrate1);
    }

    /*********** ������ʹ�ö�ʱ��1 *****************/
    else
    {
        TR1 = 0;
        AUXR &= ~0x01;      //S1 BRT Use Timer1;
        AUXR |=  (1<<6);    //Timer1 set as 1T mode
        TMOD &= ~(1<<6);    //Timer1 set As Timer
        TMOD &= ~0x30;      //Timer1_16bitAutoReload;
        TH1 = (u8)((65536UL - (MAIN_Fosc / 4) / Baudrate1) / 256);
        TL1 = (u8)((65536UL - (MAIN_Fosc / 4) / Baudrate1) % 256);
        ET1 = 0;    //��ֹ�ж�
        INT_CLKO &= ~0x02;  //�����ʱ��
        TR1  = 1;
    }
    /*************************************************/

    SCON = (SCON & 0x3f) | 0x40;    //UART1ģʽ, 0x00: ͬ����λ���, 0x40: 8λ����,�ɱ䲨����, 0x80: 9λ����,�̶�������, 0xc0: 9λ����,�ɱ䲨����
//  PS  = 1;    //�����ȼ��ж�
    ES  = 1;    //�����ж�
    REN = 1;    //�������
    P_SW1 &= 0x3f;
//    P_SW1 |= 0x00;      //UART1 switch to, 0x00: P3.0 P3.1, 0x40: P3.6 P3.7, 0x80: P1.6 P1.7 (����ʹ���ڲ�ʱ��)
//  PCON2 |=  (1<<4);   //�ڲ���·RXD��TXD, ���м�, ENABLE,DISABLE

    B_TX1_Busy = 0;
    TX1_Cnt = 0;
    RX1_Cnt = 0;
}


//========================================================================
// ����: void UART1_int (void) interrupt UART1_VECTOR
// ����: UART1�жϺ�����
// ����: nine.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
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

/********************** ��ʾɨ�躯�� ************************/
void DisplayScan(void)
{   
    P7 = ~T_COM[7-display_index];
    P6 = ~t_display[LED8[display_index]];
    if(++display_index >= 8)    display_index = 0;  //8λ������0
}


/********************** Timer0 1ms�жϺ��� ************************/
void timer0(void) interrupt 1
{
    DisplayScan();  //1msɨ����ʾһλ
    B_1ms = 1;      //1ms��־
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

//========================================================================
// ����: UpdatePwm(u16 pwm_value)
// ����: ����PWMֵ. 
// ����: pwm_value: pwmֵ, ���ֵ������ߵ�ƽ��ʱ��.
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================
void UpdatePwm(u16 pwm_value)
{
		P_SW2 |= 0x80;
	  PWM1_CCR4H = (u8)(pwm_value >> 8); //����ռ�ձ�ʱ��
    PWM1_CCR4L = (u8)(pwm_value);
		P_SW2 &= 0x7f;
}

