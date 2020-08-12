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

����ʱ, ѡ��ʱ�� 24MHZ (�û��������޸�Ƶ��).

��ʾЧ��Ϊ: �ϵ����ʾ�����, ������ΧΪ0~255����ʾ���ұߵ�3�������.

��ʾ5���, ˯��. �����ϵ�SW17��SW18����, ����������ʾ. 5�����˯��.

���MCU��׼��˯��ʱ, SW17/SW18����(INT0/INT1Ϊ�͵�ƽ), ��MCU��˯��, ֱ��INT0/INT1Ϊ�ߵ�ƽΪֹ.

INT2, INT3, INT4 ʵ�����û���������԰���������Ҫʱ�ο�ʹ��.

******************************************/
#include    "reg51.h"
#include    "intrins.h"

#define MAIN_Fosc       24000000L   //������ʱ��


typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;

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

sfr INTCLKO = 0x8F;
#define EX2 0x10
#define EX3 0x20
#define EX4 0x40

#define DIS_DOT     0x20
#define DIS_BLACK   0x10
#define DIS_        0x11

/****************************** �û������ ***********************************/

#define     Timer0_Reload   (65536UL -(MAIN_Fosc / 1000))       //Timer 0 �ж�Ƶ��, 1000��/��

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
u16 msecond;        //1000ms����

u8  Test_cnt;   //�����õ����������
u8  SleepDelay; //���Ѻ��ٽ���˯������ʱ��ʱ��

void    delay_ms(u8 ms);
void    Display(void);
void    DisplayScan(void);

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
    
    Test_cnt = 0;   //�������ΧΪ0~255
    SleepDelay = 0;
    LED8[5] = 0;
    LED8[6] = 0;
    LED8[7] = 0;
    
    EA = 1;     //�������ж�

    while(1)
    {
        delay_ms(1);    //��ʱ1ms
        DisplayScan();
        
        if(++msecond >= 1000)   //1�뵽
        {
            msecond = 0;        //��1000ms����
            Test_cnt++;         //�����+1
            LED8[5] = Test_cnt / 100;
            LED8[6] = (Test_cnt % 100) / 10;
            LED8[7] = Test_cnt % 10;

            if(++SleepDelay >= 5)   //5���˯��
            {
                SleepDelay = 0;

                if(INT0 && INT1)    //�����ж϶��Ǹߵ�ƽʱ�Ž���˯�ߣ��½��ػ��ѡ�
                {
                    SleepDelay = 0;
                    P7 = 0xff;     //�ȹر���ʾ��ʡ��

                    IE0  = 0;   //���ж�0��־λ
                    IE1  = 0;   //���ж�1��־λ
                    EX0 = 1;    //INT0 Enable
                    EX1 = 1;    //INT1 Enable

                    IT0 = 1;        //INT0 �½����ж�       
                //  IT0 = 0;        //INT0 ����,�½����ж�  
                    IT1 = 1;        //INT1 �½����ж�       
                //  IT1 = 0;        //INT1 ����,�½����ж�  

//                  INTCLKO = EX2;  //ʹ�� INT2 �½����ж�
//                  INTCLKO |= EX3; //ʹ�� INT3 �½����ж�
//                  INTCLKO |= EX4; //ʹ�� INT4 �½����ж�
									
                    PCON |= 0x02;   //Sleep
                    _nop_();
                    _nop_();
                    _nop_();
                }
            }
        }
    }
} 
/**********************************************/

//========================================================================
// ����: void  delay_ms(unsigned char ms)
// ����: ��ʱ������
// ����: ms,Ҫ��ʱ��ms��, ����ֻ֧��1~255ms. �Զ���Ӧ��ʱ��.
// ����: none.
// �汾: VER1.0
// ����: 2013-4-1
// ��ע: 
//========================================================================
void  delay_ms(u8 ms)
{
     u16 i;
     do{
          i = MAIN_Fosc / 13000;
          while(--i)    ;   //14T per loop
     }while(--ms);
}

/********************* INT0�жϺ��� *************************/
void INT0_int (void) interrupt 0      //���ж�ʱ�Ѿ������־
{
    EX0 = 0;    //INT0 Disable
    IE0 = 0;    //���ж�0��־λ
}

/********************* INT1�жϺ��� *************************/
void INT1_int (void) interrupt 2      //���ж�ʱ�Ѿ������־
{
    EX1 = 0;    //INT1 Disable
    IE1 = 0;    //���ж�1��־λ
}

/********************* INT2�жϺ��� *************************/
void INT2_int (void) interrupt 10     //���ж�ʱ�Ѿ������־
{
    INTCLKO &= ~EX2;    //INT2 Disable
}

/********************* INT3�жϺ��� *************************/
void INT3_int (void) interrupt 11     //���ж�ʱ�Ѿ������־
{
    INTCLKO &= ~EX3;    //INT3 Disable
}

/********************* INT4�жϺ��� *************************/
void INT4_int (void) interrupt 16     //���ж�ʱ�Ѿ������־
{
    INTCLKO &= ~EX4;    //INT4 Disable
}

/********************** ��ʾɨ�躯�� ************************/
void DisplayScan(void)
{   
		P7 = ~T_COM[7-display_index];
		P6 = ~t_display[LED8[display_index]];
    if(++display_index >= 8)    display_index = 0;  //8λ������0
}

