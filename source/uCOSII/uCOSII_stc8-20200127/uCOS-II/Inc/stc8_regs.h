/*--------------------------------------------------------------------------
stc8_regs.h

Header file for STC STC8 series
Copyright (c) 2020-2028 STC LTD.
All rights reserved.
--------------------------------------------------------------------------*/

#ifndef __STC8_REGS_H__
#define __STC8_REGS_H__

sfr P0              = 0x80;
sbit P07            = P0^7;
sbit P06            = P0^6;
sbit P05            = P0^5;
sbit P04            = P0^4;
sbit P03            = P0^3;
sbit P02            = P0^2;
sbit P01            = P0^1;
sbit P00            = P0^0;

sfr SP              = 0x81;
sfr DPL             = 0x82;
sfr DPH             = 0x83;
sfr S4CON           = 0x84;
#define S4SM0       (1 << 7)
#define S4ST4       (1 << 6)
#define S4SM2       (1 << 5)
#define S4REN       (1 << 4)
#define S4TB8       (1 << 3)
#define S4RB8       (1 << 2)
#define S4TI        (1 << 1)
#define S4RI        1

sfr S4BUF           = 0x85;
sfr PCON            = 0x87;
#define SMOD        (1 << 7)
#define SMOD0       (1 << 6)
#define LVDF        (1 << 5)
#define POF         (1 << 4)
#define GF1         (1 << 3)
#define GF0         (1 << 2)
#define PD          (1 << 1)
#define IDL         1

sfr TCON            = 0x88;

sbit TF1            = TCON^7;
sbit TR1            = TCON^6;
sbit TF0            = TCON^5;
sbit TR0            = TCON^4;
sbit IE1            = TCON^3;
sbit IT1            = TCON^2;
sbit IE0            = TCON^1;
sbit IT0            = TCON^0;

sfr TMOD            = 0x89;
#define GATE1       (1 << 7)
#define CT1         (1 << 6)
#define M11         (1 << 5)
#define M10         (1 << 4)
#define GATE0       (1 << 3)
#define CT0         (1 << 2)
#define M01         (1 << 1)
#define M00         1

sfr TL0             = 0x8A;
sfr TL1             = 0x8B;
sfr TH0             = 0x8C;
sfr TH1             = 0x8D;
sfr AUXR            = 0x8E;
#define T0x12       (1 << 7)
#define T1x12       (1 << 6)
#define UART_M0x6   (1 << 5)
#define T2R         (1 << 4)
#define T2_CT       (1 << 3)
#define T2x12       (1 << 2)
#define EXTRAM      (1 << 1)
#define S1ST2       1

sfr INTCLKO         = 0x8F;
#define EX4         (1 << 6)
#define EX3         (1 << 5)
#define EX2         (1 << 4)
#define T2CLKO      (1 << 2)
#define T1CLKO      (1 << 1)
#define T0CLKO      1

sfr P1              = 0x90;
sbit P17            = P1^7;
sbit P16            = P1^6;
sbit P15            = P1^5;
sbit P14            = P1^4;
sbit P13            = P1^3;
sbit P12            = P1^2;
sbit P11            = P1^1;
sbit P10            = P1^0;

sfr P1M1            = 0x91;
sfr P1M0            = 0x92;
sfr P0M1            = 0x93;
sfr P0M0            = 0x94;
sfr P2M1            = 0x95;
sfr P2M0            = 0x96;
sfr SCON            = 0x98;
sbit SM0_FE         = SCON^7;
sbit SM1            = SCON^6;
sbit SM2            = SCON^5;
sbit REN            = SCON^4;
sbit TB8            = SCON^3;
sbit RB8            = SCON^2;
sbit TI             = SCON^1;
sbit RI             = SCON^0;


sfr SBUF            = 0x99;
sfr S2CON           = 0x9A;
#define S2SM0       (1 << 7)
#define S2SM2       (1 << 5)
#define S2REN       (1 << 4)
#define S2TB8       (1 << 3)
#define S2RB8       (1 << 2)
#define S2TI        (1 << 1)
#define S2RI        1

sfr S2BUF           = 0x9B;
sfr LIRTRIM         = 0x9E;
#define LIRTRIMV    3

sfr IRTRIM          = 0x9F;
sfr P2              = 0xA0;
sbit P27            = P2^7;
sbit P26            = P2^6;
sbit P25            = P2^5;
sbit P24            = P2^4;
sbit P23            = P2^3;
sbit P22            = P2^2;
sbit P21            = P2^1;
sbit P20            = P2^0;

sfr BUS_SPEED       = 0xA1;
#define RW_S        (3 << 6)
#define SPEED       3

sfr P_SW1           = 0xA2;
#define S1_S        (3 << 6)
#define CCP_S       (3 << 4)
#define SPI_S       (3 << 2)

sfr IE              = 0xA8;
sbit EA             = IE^7;
sbit ELVD           = IE^6;
sbit EADC           = IE^5;
sbit ES             = IE^4;
sbit ET1            = IE^3;
sbit EX1            = IE^2;
sbit ET0            = IE^1;
sbit EX0            = IE^0;

sfr SADDR           = 0xA9;
sfr WKTCL           = 0xAA;
sfr WKTCH           = 0xAB;
#define WKTEN       (1 << 7)
sfr S3CON           = 0xAC;
#define S3SM0       (1 << 7)
#define S3ST3       (1 << 6)
#define S3SM2       (1 << 5)
#define S3REN       (1 << 4)
#define S3TB8       (1 << 3)
#define S3RB8       (1 << 2)
#define S3TI        (1 << 1)
#define S3RI        1

sfr S3BUF           = 0xAD;
sfr TA              = 0xAE;
sfr IE2             = 0xAF;
#define ECAN        (1 << 7)
#define ET4         (1 << 6)
#define ET3         (1 << 5)
#define ES4         (1 << 4)
#define ES3         (1 << 3)
#define ET2         (1 << 2)
#define ESPI        (1 << 1)
#define ES2         1

sfr P3              = 0xB0;
sbit P37            = P3^7;
sbit P36            = P3^6;
sbit P35            = P3^5;
sbit P34            = P3^4;
sbit P33            = P3^3;
sbit P32            = P3^2;
sbit P31            = P3^1;
sbit P30            = P3^0;

sfr P3M1            = 0xB1;
sfr P3M0            = 0xB2;
sfr P4M1            = 0xB3;
sfr P4M0            = 0xB4;
sfr IP2             = 0xB5;
#define PCAN        (1 << 7)
#define PI2C        (1 << 6)
#define PCMP        (1 << 5)
#define PX4         (1 << 4)
#define PPWMFD      (1 << 3)
#define PPWM        (1 << 2)
#define PSPI        (1 << 1)
#define PS2         1

sfr IP2H            = 0xB6;
#define PCANH       (1 << 7)
#define PI2CH       (1 << 6)
#define PCMPH       (1 << 5)
#define PX4H        (1 << 4)
#define PPWMFDH     (1 << 3)
#define PPWMH       (1 << 2)
#define PSPIH       (1 << 1)
#define PS2H        1

sfr IPH             = 0xB7;
#define PPCAH       (1 << 7)
#define PLVDH       (1 << 6)
#define PADCH       (1 << 5)
#define PSH         (1 << 4)
#define PT1H        (1 << 3)
#define PX1H        (1 << 2)
#define PT0H        (1 << 1)
#define PX0H        1

sfr IP              = 0xB8;
sbit PPCA           = IP^7;
sbit PLVD           = IP^6;
sbit PADC           = IP^5;
sbit PS             = IP^4;
sbit PT1            = IP^3;
sbit PX1            = IP^2;
sbit PT0            = IP^1;
sbit PX0            = IP^0;

sfr SADEN           = 0xB9;
sfr P_SW2           = 0xBA;
#define EAXFR       (1 << 7)
#define CAN_S       (1 << 6)
#define I2C_S       (3 << 4)
#define CMPO_S      (1 << 3)
#define S4_S        (1 << 2)
#define S3_S        (1 << 1)
#define S2_S        1

sfr VOCTRL          = 0xBB;
#define SCC         (1 << 7)

sfr ADC_CONTR       = 0xBC;
#define DC_POWER    (1 << 7)
#define ADC_START   (1 << 6)
#define ADC_FLAG    (1 << 5)
#define ADC_CHS     0x0F

sfr ADC_RES         = 0xBD;
sfr ADC_RESL        = 0xBE;
sfr ADC_RESH        = 0xBF;
sfr P4              = 0xC0;
sbit P47            = P4^7;
sbit P46            = P4^6;
sbit P45            = P4^5;
sbit P44            = P4^4;
sbit P43            = P4^3;
sbit P42            = P4^2;
sbit P41            = P4^1;
sbit P40            = P4^0;

sfr WDT_CONTR       = 0xC1;
#define WDT_FLAG    (1 << 7)
#define EN_WDT      (1 << 5)
#define CLR_WDT     (1 << 4)
#define IDL_WDT     (1 << 3)
#define WDT_PS      0x07


sfr IAP_DATA        = 0xC2;
sfr IAP_ADDRH       = 0xC3;
sfr IAP_ADDRL       = 0xC4;
sfr IAP_CMD         = 0xC5;
#define  CMD        0x03

sfr IAP_TRIG        = 0xC6;
sfr IAP_CONTR       = 0xC7;
#define IAPEN       (1 << 7)
#define SWBS        (1 << 6)
#define SWRST       (1 << 5)
#define CMD_FAIL    (1 << 4)
#define IAP_WT      0x07

sfr P5              = 0xC8;
sbit P57            = P5^7;
sbit P56            = P5^6;
sbit P55            = P5^5;
sbit P54            = P5^4;
sbit P53            = P5^3;
sbit P52            = P5^2;
sbit P51            = P5^1;
sbit P50            = P5^0;

sfr P5M1            = 0xC9;
sfr P5M0            = 0xCA;
sfr P6M1            = 0xCB;
sfr P6M0            = 0xCC;
sfr SPSTAT          = 0xCD;
#define SPIF        (1 << 7)
#define WCOL        (1 << 6)

sfr SPCTL           = 0xCE;
#define SSIG        (1 << 7)
#define SPEN        (1 << 6)
#define DORD        (1 << 5)
#define MSTR        (1 << 4)
#define CPOL        (1 << 3)
#define CPHA        (1 << 2)
#define SPR         3

sfr SPDAT           = 0xCF;
sfr PSW             = 0xD0;
sbit CY             = PSW^7;
sbit AC             = PSW^6;
sbit F0             = PSW^5;
sbit RS1            = PSW^4;
sbit RS0            = PSW^3;
sbit OV             = PSW^2;
sbit P              = PSW^0;

sfr T4T3M           = 0xD1;
#define T4R         (1 << 7)
#define T4_CT       (1 << 6)
#define T4x12       (1 << 5)
#define T4CLKO      (1 << 4)
#define T3R         (1 << 3)
#define T3_CT       (1 << 2)
#define T3x12       (1 << 1)
#define T3CLKO      1

sfr T4H             = 0xD2;
sfr T4L             = 0xD3;
sfr T3H             = 0xD4;
sfr T3L             = 0xD5;
sfr T2H             = 0xD6;
sfr T2L             = 0xD7;
sfr CCON            = 0xD8;
sbit CF             = CCON^7;
sbit CR             = CCON^6;
sbit CCF3           = CCON^3;
sbit CCF2           = CCON^2;
sbit CCF1           = CCON^1;
sbit CCF0           = CCON^0;

sfr CMOD            = 0xD9;
#define CIDL        (1 << 7)
#define CPS         (7 << 1)
#define ECF         1

sfr CCAPM0          = 0xDA;
#define ECOM0       (1 << 6)
#define CCAPP0      (1 << 5)
#define CCAPN0      (1 << 4)
#define MAT0        (1 << 3)
#define TOG0        (1 << 2)
#define PWM0        (1 << 1)
#define ECCF0       1

sfr CCAPM1          = 0xDB;
#define ECOM1       (1 << 6)
#define CCAPP1      (1 << 5)
#define CCAPN1      (1 << 4)
#define MAT1        (1 << 3)
#define TOG1        (1 << 2)
#define PWM1        (1 << 1)
#define ECCF1       1

sfr CCAPM2          = 0xDC;
#define ECOM2       (1 << 6)
#define CCAPP2      (1 << 5)
#define CCAPN2      (1 << 4)
#define MAT2        (1 << 3)
#define TOG2        (1 << 2)
#define PWM2        (1 << 1)
#define ECCF2       1

sfr CCAPM3          = 0xDD;
#define ECOM3       (1 << 6)
#define CCAPP3      (1 << 5)
#define CCAPN3      (1 << 4)
#define MAT3        (1 << 3)
#define TOG3        (1 << 2)
#define PWM3        (1 << 1)
#define ECCF3       1

sfr ADCCFG          = 0xDE;
#define RESFMT      (1 << 5)
#define ADCSPEED    0x0F


sfr IP3             = 0xDF;
#define PS4         (1 << 1)
#define PS3         1

sfr ACC             = 0xE0;
sfr P7M1            = 0xE1;
sfr P7M0            = 0xE2;
sfr DPS             = 0xE3;
#define ID1         (1 << 7)
#define ID0         (1 << 6)
#define TSL         (1 << 5)
#define AU1         (1 << 4)
#define AU0         (1 << 3)
#define SEL         1

sfr DPL1            = 0xE4;
sfr DPH1            = 0xE5;
sfr CMPCR1          = 0xE6;
#define CMPEN       (1 << 7)
#define CMPIF       (1 << 6)
#define PIE         (1 << 5)
#define NIE         (1 << 4)
#define PIS         (1 << 3)
#define NIS         (1 << 2)
#define CMPOE       (1 << 1)
#define CMPRES      1

sfr CMPCR2          = 0xE7;
#define INVCMPO     (1 << 7)
#define DISFLT      (1 << 6)
#define LCDTY       0x3F

sfr P6              = 0xE8;
sbit P67            = P6^7;
sbit P66            = P6^6;
sbit P65            = P6^5;
sbit P64            = P6^4;
sbit P63            = P6^3;
sbit P62            = P6^2;
sbit P61            = P6^1;
sbit P60            = P6^0;

sfr CL              = 0xE9;
sfr CCAP0L          = 0xEA;
sfr CCAP1L          = 0xEB;
sfr CCAP2L          = 0xEC;
sfr CCAP3L          = 0xED;
sfr IP3H            = 0xEE;
#define PS4H        (1 << 1)
#define PS3H        1

sfr AUXINTIF        = 0xEF;
#define INT4IF      (1 << 6)
#define INT3IF      (1 << 5)
#define INT2IF      (1 << 4)
#define T4IF        (1 << 2)
#define T3IF        (1 << 1)
#define T2IF        1

sfr B               = 0xF0;
sfr PWMCFG          = 0xF1;
#define CBIF        (1 << 7)
#define ETADC       (1 << 6)

sfr PCA_PWM0        = 0xF2;
#define EBS0        (3 << 6)
#define XCCAP0H     (3 << 4)
#define XCCAP0L     (3 << 2)
#define EPC0H       (1 << 1)
#define EPC0L       1

sfr PCA_PWM1        = 0xF3;
#define EBS1        (3 << 6)
#define XCCAP1H     (3 << 4)
#define XCCAP1L     (3 << 2)
#define EPC1H       (1 << 1)
#define EPC1L       1

sfr PCA_PWM2        = 0xF4;
#define EBS2        (3 << 6)
#define XCCAP2H     (3 << 4)
#define XCCAP2L     (3 << 2)
#define EPC2H       (1 << 1)
#define EPC2L       1

sfr PCA_PWM3        = 0xF5;
#define EBS3        (3 << 6)
#define XCCAP3H     (3 << 4)
#define XCCAP3L     (3 << 2)
#define EPC3H       (1 << 1)
#define EPC3L       1

sfr PWMIF           = 0xF6;
#define C7IF        (1 << 7)
#define C6IF        (1 << 6)
#define C5IF        (1 << 5)
#define C4IF        (1 << 4)
#define C3IF        (1 << 3)
#define C2IF        (1 << 2)
#define C1IF        (1 << 1)
#define C0IF        1

sfr PWMFDCR         = 0xF7;
#define INVCMP      (1 << 7)
#define INVIO       (1 << 6)
#define ENFD        (1 << 5)
#define FLTFLIO     (1 << 4)
#define EFDI        (1 << 3)
#define FDCMP       (1 << 2)
#define FDIO        (1 << 1)
#define FDIF        1

sfr P7              = 0xF8;
sbit P77            = P7^7;
sbit P76            = P7^6;
sbit P75            = P7^5;
sbit P74            = P7^4;
sbit P73            = P7^3;
sbit P72            = P7^2;
sbit P71            = P7^1;
sbit P70            = P7^0;

sfr CH              = 0xF9;
sfr CCAP0H          = 0xFA;
sfr CCAP1H          = 0xFB;
sfr CCAP2H          = 0xFC;
sfr CCAP3H          = 0xFD;
sfr PWMCR           = 0xFE;
#define ENPWM       (1 << 7)
#define ECBI        (1 << 6)
sfr RSTCFG          = 0xFF;
#define ENLVR       (1 << 6)
#define P54RST      (1 << 4)
#define LVDS        3

#define PWMCH       (*(unsigned char volatile xdata *)0xFFF0)
#define PWMCL       (*(unsigned char volatile xdata *)0xFFF1)
#define PWMCKS      (*(unsigned char volatile xdata *)0xFFF2)
#define SELT2       (1 << 4)
#define PWM_PS      0x0F

#define TADCPH      (*(unsigned char volatile xdata *)0xFFF3)
#define TADCPL      (*(unsigned char volatile xdata *)0xFFF4)
#define PWM0T1H     (*(unsigned char volatile xdata *)0xFF00)
#define PWM0T1L     (*(unsigned char volatile xdata *)0xFF01)
#define PWM0T2H     (*(unsigned char volatile xdata *)0xFF02)
#define PWM0T2L     (*(unsigned char volatile xdata *)0xFF03)
#define PWM0CR      (*(unsigned char volatile xdata *)0xFF04)
#define ENC0O       (1 << 7)
#define C0INI       (1 << 6)
#define C0_S        (3 << 3)
#define EC0I        (1 << 2)
#define EC0T2SI     (1 << 1)
#define EC0T1SI     1

#define PWM0HLD     (*(unsigned char volatile xdata *)0xFF05)
#define HC0H        (1 << 1)
#define HC0L        1
#define PWM1T1H     (*(unsigned char volatile xdata *)0xFF10)
#define PWM1T1L     (*(unsigned char volatile xdata *)0xFF11)
#define PWM1T2H     (*(unsigned char volatile xdata *)0xFF12)
#define PWM1T2L     (*(unsigned char volatile xdata *)0xFF13)
#define PWM1CR      (*(unsigned char volatile xdata *)0xFF14)
#define ENC1O       (1 << 7)
#define C1INI       (1 << 6)
#define C1_S        (3 << 3)
#define EC1I        (1 << 2)
#define EC1T2SI     (1 << 1)
#define EC1T1SI     1

#define PWM1HLD     (*(unsigned char volatile xdata *)0xFF15)
#define HC1H        (1 << 1)
#define HC1L        1
#define PWM2T1H     (*(unsigned char volatile xdata *)0xFF20)
#define PWM2T1L     (*(unsigned char volatile xdata *)0xFF21)
#define PWM2T2H     (*(unsigned char volatile xdata *)0xFF22)
#define PWM2T2L     (*(unsigned char volatile xdata *)0xFF23)
#define PWM2CR      (*(unsigned char volatile xdata *)0xFF24)
#define ENC2O       (1 << 7)
#define C2INI       (1 << 6)
#define C2_S        (3 << 3)
#define EC2I        (1 << 2)
#define EC2T2SI     (1 << 1)
#define EC2T1SI     1

#define PWM2HLD     (*(unsigned char volatile xdata *)0xFF25)
#define HC2H        (1 << 1)
#define HC2L        1

#define PWM3T1H     (*(unsigned char volatile xdata *)0xFF30)
#define PWM3T1L     (*(unsigned char volatile xdata *)0xFF31)
#define PWM3T2H     (*(unsigned char volatile xdata *)0xFF32)
#define PWM3T2L     (*(unsigned char volatile xdata *)0xFF33)
#define PWM3CR      (*(unsigned char volatile xdata *)0xFF34)
#define ENC3O       (1 << 7)
#define C3INI       (1 << 6)
#define C3_S        (3 << 3)
#define EC3I        (1 << 2)
#define EC3T2SI     (1 << 1)
#define EC3T1SI     1

#define PWM3HLD     (*(unsigned char volatile xdata *)0xFF35)
#define HC3H        (1 << 1)
#define HC3L        1

#define PWM4T1H     (*(unsigned char volatile xdata *)0xFF40)
#define PWM4T1L     (*(unsigned char volatile xdata *)0xFF41)
#define PWM4T2H     (*(unsigned char volatile xdata *)0xFF42)
#define PWM4T2L     (*(unsigned char volatile xdata *)0xFF43)
#define PWM4CR      (*(unsigned char volatile xdata *)0xFF44)
#define ENC4O       (1 << 7)
#define C4INI       (1 << 6)
#define C4_S        (3 << 3)
#define EC4I        (1 << 2)
#define EC4T2SI     (1 << 1)
#define EC4T1SI     1

#define PWM4HLD     (*(unsigned char volatile xdata *)0xFF45)
#define HC4H        (1 << 1)
#define HC4L        1
#define PWM5T1H     (*(unsigned char volatile xdata *)0xFF50)
#define PWM5T1L     (*(unsigned char volatile xdata *)0xFF51)
#define PWM5T2H     (*(unsigned char volatile xdata *)0xFF52)
#define PWM5T2L     (*(unsigned char volatile xdata *)0xFF53)
#define PWM5CR      (*(unsigned char volatile xdata *)0xFF54)
#define ENC5O       (1 << 7)
#define C5INI       (1 << 6)
#define C5_S        (3 << 3)
#define EC5I        (1 << 2)
#define EC5T2SI     (1 << 1)
#define EC5T1SI     1

#define PWM5HLD     (*(unsigned char volatile xdata *)0xFF55)
#define HC5H        (1 << 1)
#define HC5L        1
#define PWM6T1H     (*(unsigned char volatile xdata *)0xFF60)
#define PWM6T1L     (*(unsigned char volatile xdata *)0xFF61)
#define PWM6T2H     (*(unsigned char volatile xdata *)0xFF62)
#define PWM6T2L     (*(unsigned char volatile xdata *)0xFF63)
#define PWM6CR      (*(unsigned char volatile xdata *)0xFF64)
#define ENC6O       (1 << 7)
#define C6INI       (1 << 6)
#define C6_S        (3 << 3)
#define EC6I        (1 << 2)
#define EC6T2SI     (1 << 1)
#define EC6T1SI     1

#define PWM6HLD     (*(unsigned char volatile xdata *)0xFF65)
#define HC6H        (1 << 1)
#define HC6L        1
#define PWM7T1H     (*(unsigned char volatile xdata *)0xFF70)
#define PWM7T1L     (*(unsigned char volatile xdata *)0xFF71)
#define PWM7T2H     (*(unsigned char volatile xdata *)0xFF72)
#define PWM7T2L     (*(unsigned char volatile xdata *)0xFF73)
#define PWM7CR      (*(unsigned char volatile xdata *)0xFF74)
#define ENC7O       (1 << 7)
#define C7INI       (1 << 6)
#define C7_S        (3 << 3)
#define EC7I        (1 << 2)
#define EC7T2SI     (1 << 1)
#define EC7T1SI     1

#define PWM7HLD     (*(unsigned char volatile xdata *)0xFF75)
#define HC7H        (1 << 1)
#define HC7L        1
#define I2CCFG      (*(unsigned char volatile xdata *)0xFE80)
#define ENI2C       (1 << 7)
#define MSSL        (1 << 6)
#define MSSPEED     0x3F

#define I2CMSCR     (*(unsigned char volatile xdata *)0xFE81)
#define EMSI        (1 << 7)
#define MSCMD       0x0F

#define I2CMSST     (*(unsigned char volatile xdata *)0xFE82)
#define MSBUSY      (1 << 7)
#define MSIF        (1 << 6)
#define MSACKI      (1 << 1)
#define MSACKO      1

#define I2CSLCR     (*(unsigned char volatile xdata *)0xFE83)
#define ESTAI       (1 << 6)
#define ERXI        (1 << 5)
#define ETXI        (1 << 4)
#define ESTOI       (1 << 3)
#define SLRST       1

#define I2CSLST     (*(unsigned char volatile xdata *)0xFE84)
#define SLBUSY      (1 << 7)
#define STAIF       (1 << 6)
#define RXIF        (1 << 5)
#define TXIF        (1 << 4)
#define STOIF       (1 << 3)
#define TXING       (1 << 2)
#define SLACKI      (1 << 1)
#define SLACKO      1

#define I2CSLADR    (*(unsigned char volatile xdata *)0xFE85)
#define SLADR       (0x7F << 1)
#define MA          1

#define I2CTXD      (*(unsigned char volatile xdata *)0xFE86)
#define I2CRXD      (*(unsigned char volatile xdata *)0xFE87)
#define I2CMSAUX    (*(unsigned char volatile xdata *)0xFE88)
#define WDTA        1
#define P0PU        (*(unsigned char volatile xdata *)0xFE10)
#define P1PU        (*(unsigned char volatile xdata *)0xFE11)
#define P2PU        (*(unsigned char volatile xdata *)0xFE12)
#define P3PU        (*(unsigned char volatile xdata *)0xFE13)
#define P4PU        (*(unsigned char volatile xdata *)0xFE14)
#define P5PU        (*(unsigned char volatile xdata *)0xFE15)
#define P6PU        (*(unsigned char volatile xdata *)0xFE16)
#define P7PU        (*(unsigned char volatile xdata *)0xFE17)
#define P0NCS       (*(unsigned char volatile xdata *)0xFE18)
#define P1NCS       (*(unsigned char volatile xdata *)0xFE19)
#define P2NCS       (*(unsigned char volatile xdata *)0xFE1A)
#define P3NCS       (*(unsigned char volatile xdata *)0xFE1B)
#define P4NCS       (*(unsigned char volatile xdata *)0xFE1C)
#define P5NCS       (*(unsigned char volatile xdata *)0xFE1D)
#define P6NCS       (*(unsigned char volatile xdata *)0xFE1E)
#define P7NCS       (*(unsigned char volatile xdata *)0xFE1F)
#define CKSEL       (*(unsigned char volatile xdata *)0xFE00)
#define MCLKODIV    (0x0F << 4)
#define MCLKO_S     (1 << 3)
#define MCKSEL      3

#define CLKDIV      (*(unsigned char volatile xdata *)0xFE01)
#define IRC24MCR    (*(unsigned char volatile xdata *)0xFE02)
#define ENIRC24M    (1 << 7)
#define IRC24MST    1
#define XOSCCR      (*(unsigned char volatile xdata *)0xFE03)
#define ENXOSC      (1 << 7)
#define XITYPE      (1 << 6)
#define XOSCST      1
#define IRC32KCR    (*(unsigned char volatile xdata *)0xFE04)
#define ENIRC32K    (1 << 7)
#define IRC32KST    1

#endif

