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

�Ƚ���������ͨ�� P3.7 �˿����ӿɵ����裬��1.19V�ڲ��̶��Ƚϣ�

���ڿɵ����裬��P3.7�ڵ������ѹ����1.19Vʱ�����Ƚ����жϣ���ʱ�������ݵ�EEPROM��

��P3.7�ڵ������ѹ����1.19V�󣬻��������ϵ�ʱ����ȡEEPROM���ݽ��лָ���

��STC��MCU��IO��ʽ����8λ����ܡ�

ʹ��Timer0��16λ�Զ���װ������1ms����,�������������������,�û��޸�MCU��ʱ��Ƶ��ʱ,�Զ���ʱ��1ms.

�û�������"�û������"���޸ı������ݵ�EEPROM��ַ��

��ʾЧ��Ϊ: �ϵ����ʾ�����, ������ΧΪ0~10000����ʾ���ұߵ�5������ܡ�

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
ע�⣺����ʱ�����ؽ���"Ӳ��ѡ��"���������Ҫȷ����������:

�����û�EEPROM��С����ȷ��"�û������"���趨�ĵ�ַ��EEPROM���õĴ�С��Χ֮�ڡ�

ѡ��ʱ�� 24MHZ (�û��������޸�Ƶ��)��
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

******************************************/

#include    "reg51.h"
#include    "intrins.h"

#define     MAIN_Fosc       24000000L   //������ʱ��

#define     Timer0_16bitAutoReload()    TMOD &= ~0x03                   //16λ�Զ���װ
#define     Timer0_16bit()              TMOD  = (TMOD & ~0x03) | 0x01   //16λ
#define     Timer0_8bitAutoReload()     TMOD  = (TMOD & ~0x03) | 0x02   //8λ�Զ���װ
#define     Timer0_16bitAutoRL_NoMask() TMOD |=  0x03       //16λ�Զ���װ���������ж�
#define     Timer0_AsCounterP32()       TMOD |=  4      //ʱ��0����������
#define     Timer0_AsTimer()            TMOD &= ~4      //ʱ��0������ʱ��
#define     Timer0_ExtControlP34()      TMOD |=  4      //ʱ��0���ⲿINT0�ߵ�ƽ����ʱ����
#define     Timer0_Run()                TR0 = 1             //����ʱ��0����
#define     Timer0_Stop()               TR0 = 0             //��ֹ��ʱ��0����
#define     Timer0_InterruptEnable()    ET0 = 1             //����Timer1�ж�.
#define     Timer0_InterruptDisable()   ET0 = 0             //��ֹTimer1�ж�.
#define     Timer0_1T()                 AUXR |=  (1<<7) //Timer0 clodk = fo
#define     Timer0_12T()                AUXR &= ~(1<<7) //Timer0 clodk = fo/12  12��Ƶ, default
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

sbit ELVD = IE^6;   //��ѹ����ж�����λ
sbit PLVD = IP^6;

#define DIS_DOT     0x20
#define DIS_BLACK   0x10
#define DIS_        0x11

/****************************** �û������ ***********************************/

#define     EE_ADDRESS  0x0000  //�����EEPROM��ʼ��ַ

#define     Timer0_Reload   (65536UL -(MAIN_Fosc / 1000))       //Timer 0 �ж�Ƶ��, 1000��/��

#define     Tip_Delay   (MAIN_Fosc / 1000000)

/*****************************************************************************/


/*************  ���س�������    **************/
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
u16 msecond;
bit LowVolFlag;     //�͵�ѹ��־

u16 Test_cnt;   //�����õ����������
u16 Temp_cnt;   //�����õ����������
u8  tmp[2];     //ͨ������

void    CMP_config(void);
void    Display(void);
void    DisableEEPROM(void);
void    EEPROM_read_n(u16 EE_address,u8 *DataAddress,u16 number);
void    EEPROM_write_n(u16 EE_address,u8 *DataAddress,u16 number);
void    EEPROM_SectorErase(u16 EE_address);

/******************* �Ƚ����жϺ��� ********************/
void CMP_Isr() interrupt 21
{
    CMPCR1 &= ~0x40;                         //���жϱ�־
    P50 = CMPCR1 & 0x01;                     //�жϷ�ʽ��ȡ�Ƚ����ȽϽ��
    
    if(CMPCR1 & 0x01)
    {
        if(LowVolFlag)
        {
            LowVolFlag = 0;    //����͵�ѹ��־
            if(Test_cnt != Temp_cnt)
            {
                EEPROM_read_n(EE_ADDRESS,tmp,2);        //����2�ֽ�
                Test_cnt = ((u16)tmp[0] << 8) + tmp[1]; //�����
                if(Test_cnt > 10000)    Test_cnt = 0;   //�������ΧΪ0~10000
                Temp_cnt = Test_cnt;
            }
        }
    }
    else
    {
        P7 = 0xff;     //�ر���ʾ��ʡ��
        if(!LowVolFlag)
        {
            LowVolFlag = 1;    //���õ͵�ѹ��־
            if(Test_cnt != Temp_cnt)
            {
                Temp_cnt = Test_cnt;
                EEPROM_SectorErase(EE_ADDRESS); //��������
                tmp[0] = (u8)(Temp_cnt >> 8);
                tmp[1] = (u8)Temp_cnt;
                EEPROM_write_n(EE_ADDRESS,tmp,2);
            }
        }
    }
}

/********************** ������ ************************/
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
    for(i=0; i<8; i++)  LED8[i] = DIS_BLACK;    //ȫ������
    
    Timer0_1T();
    Timer0_AsTimer();
    Timer0_16bitAutoReload();
    Timer0_Load(Timer0_Reload);
    Timer0_InterruptEnable();
    Timer0_Run();

    CMP_config();
    EA = 1;     //�����ж�
    
    for(msecond=0; msecond < 200; ) //��ʱ200ms
    {
        if(B_1ms)   //1ms��
        {
            B_1ms = 0;
            msecond ++;
        }
    }

    EEPROM_read_n(EE_ADDRESS,tmp,2);        //����2�ֽ�
    Test_cnt = ((u16)tmp[0] << 8) + tmp[1]; //�����
    if(Test_cnt > 10000)    Test_cnt = 0;   //�������ΧΪ0~10000
    
    Display();      //��ʾ�����
    
    while(1)
    {
        if((B_1ms) && (LowVolFlag == 0))   //1ms�����͵�ѹʱ������
        {
            B_1ms = 0;
            if(++msecond >= 1000)   //1�뵽
            {
                msecond = 0;        //��1000ms����
                Test_cnt++;         //�����+1
                if(Test_cnt > 10000)    Test_cnt = 0;   //�������ΧΪ0~10000
                Display();          //��ʾ�����
            }
        }
    }
}

//========================================================================
// ����: void CMP_config(void)
// ����: �Ƚ�����ʼ��������
// ����: ��.
// ����: ��.
// �汾: V1.0, 2020-6-10
//========================================================================
void CMP_config(void)
{
    CMPCR2 = 0x00;
    CMPCR2 &= ~0x80;                            //�Ƚ����������
//  CMPCR2 |= 0x80;                             //�Ƚ����������
//  CMPCR2 &= ~0x40;                            //��ֹ0.1us�˲�
    CMPCR2 |= 0x40;                             //ʹ��0.1us�˲�
//  CMPCR2 &= ~0x3f;                            //�Ƚ������ֱ�����
    CMPCR2 |= 0x10;                             //�Ƚ����������16��ȥ��ʱ�Ӻ����
    CMPCR1 = 0x00;
    CMPCR1 |= 0x30;                             //ʹ�ܱȽ��������ж�
//  CMPCR1 &= ~0x20;                            //��ֹ�Ƚ����������ж�
//  CMPCR1 |= 0x20;                             //ʹ�ܱȽ����������ж�
//  CMPCR1 &= ~0x10;                            //��ֹ�Ƚ����½����ж�
//  CMPCR1 |= 0x10;                             //ʹ�ܱȽ����½����ж�

    CMPCR1 &= ~0x08;                            //P3.7ΪCMP+�����
//  CMPCR1 |= 0x08;                             //ADC�����ΪCMP+�����

    CMPCR1 &= ~0x04;                            //�ڲ��ο���ѹΪCMP-�����
//  CMPCR1 |= 0x04;                             //P3.6ΪCMP-�����

//  CMPCR1 &= ~0x02;                            //��ֹ�Ƚ������
    CMPCR1 |= 0x02;                             //ʹ�ܱȽ������
    P_SW2 &= ~0x08;                             //ѡ��P3.4��Ϊ�Ƚ��������
//  P_SW2 |= 0x08;                              //ѡ��P4.1��Ϊ�Ƚ��������
    CMPCR1 |= 0x80;                             //ʹ�ܱȽ���ģ��
}

/********************** ��ʾ�������� ************************/
void Display(void)
{
    u8  i;
    
    LED8[3] = Test_cnt / 10000;
    LED8[4] = (Test_cnt % 10000) / 1000;
    LED8[5] = (Test_cnt % 1000) / 100;
    LED8[6] = (Test_cnt % 100) / 10;
    LED8[7] = Test_cnt % 10;
    
    for(i=3; i<7; i++)  //����Ч0
    {
        if(LED8[i] > 0) break;
        LED8[i] = DIS_BLACK;
    }
}

//========================================================================
// ����: void   ISP_Disable(void)
// ����: ��ֹ����ISP/IAP.
// ����: non.
// ����: non.
// �汾: V1.0, 2012-10-22
//========================================================================
void DisableEEPROM(void)
{
		IAP_CONTR = 0;          //�ر� IAP ����
		IAP_CMD = 0;            //�������Ĵ���
		IAP_TRIG = 0;           //��������Ĵ���
		IAP_ADDRH = 0x80;       //����ַ���õ��� IAP ����
		IAP_ADDRL = 0;
}

//========================================================================
// ����: void EEPROM_read_n(u16 EE_address,u8 *DataAddress,u16 number)
// ����: ��ָ��EEPROM�׵�ַ����n���ֽڷ�ָ���Ļ���.
// ����: EE_address:  ����EEPROM���׵�ַ.
//       DataAddress: �������ݷŻ�����׵�ַ.
//       number:      �������ֽڳ���.
// ����: non.
// �汾: V1.0, 2012-10-22
//========================================================================
void EEPROM_read_n(u16 EE_address,u8 *DataAddress,u16 number)
{
    EA = 0;     //��ֹ�ж�

		IAP_CONTR = 0x80; //ʹ�� IAP
		IAP_TPS = Tip_Delay; //���ò����ȴ����� 24MHz
		IAP_CMD = 1;  //���� IAP ������
		do
		{
				IAP_ADDRH = EE_address / 256; //���� IAP ��ַ���ֽ�
				IAP_ADDRL = EE_address % 256; //���� IAP ��ַ���ֽ�
				IAP_TRIG = 0x5a; //д��������(0x5a)
				IAP_TRIG = 0xa5; //д��������(0xa5)
				_nop_();
				*DataAddress = IAP_DATA; //�� IAP ����
        EE_address++;
        DataAddress++;
    }while(--number);
    DisableEEPROM();
    EA = 1;     //���������ж�
}


/******************** ������������ *****************/
//========================================================================
// ����: void EEPROM_SectorErase(u16 EE_address)
// ����: ��ָ����ַ��EEPROM��������.
// ����: EE_address:  Ҫ����������EEPROM�ĵ�ַ.
// ����: non.
// �汾: V1.0, 2013-5-10
//========================================================================
void EEPROM_SectorErase(u16 EE_address)
{
    EA = 0;     //��ֹ�ж�

		IAP_CONTR = 0x80; //ʹ�� IAP
		IAP_TPS = Tip_Delay; //���ò����ȴ����� 24MHz
		IAP_CMD = 3;      //���� IAP ��������
		IAP_ADDRH = EE_address / 256; //���� IAP ��ַ���ֽ�
		IAP_ADDRL = EE_address % 256; //���� IAP ��ַ���ֽ�
		IAP_TRIG = 0x5a; //д��������(0x5a)
		IAP_TRIG = 0xa5; //д��������(0xa5)
		_nop_();
    DisableEEPROM();
    EA = 1;     //���������ж�
}

//========================================================================
// ����: void EEPROM_write_n(u16 EE_address,u8 *DataAddress,u16 number)
// ����: �ѻ����n���ֽ�д��ָ���׵�ַ��EEPROM.
// ����: EE_address:  д��EEPROM���׵�ַ.
//       DataAddress: д��Դ���ݵĻ�����׵�ַ.
//       number:      д����ֽڳ���.
// ����: non.
// �汾: V1.0, 2012-10-22
//========================================================================
void EEPROM_write_n(u16 EE_address,u8 *DataAddress,u16 number)
{
    EA = 0;     //��ֹ�ж�

		IAP_CONTR = 0x80; //ʹ�� IAP
		IAP_TPS = Tip_Delay; //���ò����ȴ����� 24MHz
		IAP_CMD = 2;  //���� IAP д����
    do
    {
				IAP_ADDRH = EE_address / 256; //���� IAP ��ַ���ֽ�
				IAP_ADDRL = EE_address % 256; //���� IAP ��ַ���ֽ�
				IAP_DATA = *DataAddress; //д IAP ����
				IAP_TRIG = 0x5a; //д��������(0x5a)
				IAP_TRIG = 0xa5; //д��������(0xa5)
				_nop_();
        EE_address++;
        DataAddress++;
    }while(--number);

    DisableEEPROM();
    EA = 1;     //���������ж�
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
    if(LowVolFlag == 0)
    {
        DisplayScan();  //1msɨ����ʾһλ
        B_1ms = 1;      //1ms��־
    }
}
