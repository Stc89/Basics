/***************************************************************************
 *                                - STC8_IAR.h -
 *
 * Special header for the STC STC8 family Microcontroller.
 *
 ***************************************************************************/

#ifndef IO_STC8_H
#define IO_STC8_H
#define __STC8__
#ifdef __IAR_SYSTEMS_ICC__
#ifndef _SYSTEM_BUILD
   #pragma system_include
#endif
#pragma language=save
#pragma language=extended

__sfr __no_init volatile union
{ 
    unsigned char P0;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P0_bit;
} @ 0x80;

__sfr __no_init volatile union
{ 
    unsigned char SP;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } SP_bit;
} @ 0x81;

__sfr __no_init volatile union
{ 
    unsigned char DPL;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } DPL_bit;
} @ 0x82;

__sfr __no_init volatile union
{ 
    unsigned char DPH;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } DPH_bit;
} @ 0x83;

__sfr __no_init volatile union
{ 
    unsigned char S4CON;
    struct
        {
            unsigned char S4SM0 : 1;
            unsigned char S4ST4 : 1;
            unsigned char S4SM2 : 1;
            unsigned char S4REN : 1;
            unsigned char S4TB8 : 1;
            unsigned char S4RB8 : 1;
            unsigned char S4TI  : 1;
            unsigned char S4RI  : 1;
        } S4CON_bit;
} @ 0x84;

__sfr __no_init volatile union
{ 
    unsigned char S4BUF;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } S4BUF_bit;
} @ 0x85;

__sfr __no_init volatile union
{
    unsigned char PCON;
    struct
    {
        unsigned char SMOD  : 1;
        unsigned char SMOD0 : 1;
        unsigned char LVDF  : 1;
        unsigned char POF   : 1;
        unsigned char GF1   : 1;
        unsigned char GF0   : 1;
        unsigned char PD    : 1;
        unsigned char IDL   : 1;
    } PCON_bit;
} @ 0x87;

__sfr __no_init volatile union
{ 
    unsigned char TCON;
    struct
    {
        unsigned char TF1 : 1;
        unsigned char TR1 : 1;
        unsigned char TF0 : 1;
        unsigned char TR0 : 1;
        unsigned char IE1 : 1;
        unsigned char IT1 : 1;
        unsigned char IE0 : 1;
        unsigned char IT0 : 1;
    } TCON_bit;
} @ 0x88;

__sfr __no_init volatile union
{ 
unsigned char TMOD;
    struct
    {
        unsigned char GATE1 : 1;
        unsigned char C_T1  : 1;
        unsigned char M11   : 1;
        unsigned char M01   : 1;
        unsigned char GATE0 : 1;
        unsigned char C_T0  : 1;
        unsigned char M10   : 1;
        unsigned char M00   : 1;
    } TMOD_bit;
} @ 0x89;

__sfr __no_init volatile union
{ 
    unsigned char TL0;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } TL0_bit;
} @ 0x8A;

__sfr __no_init volatile union
{ 
    unsigned char TL1;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } TL1_bit;
} @ 0x8B;

__sfr __no_init volatile union
{ 
    unsigned char TH0;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } TH0_bit;
} @ 0x8C;

__sfr __no_init volatile union
{ 
    unsigned char TH1;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } TH1_bit;
} @ 0x8D;

__sfr __no_init volatile union
{ 
    unsigned char AUXR;
    struct
    {
        unsigned char T0x12     : 1;
        unsigned char T1x12     : 1;
        unsigned char UART_M0x6 : 1;
        unsigned char T2R       : 1;
        unsigned char T2_C_T    : 1;
        unsigned char T2x12     : 1;
        unsigned char EXTRAM    : 1;
        unsigned char S1ST2     : 1;
    } AUXR_bit;
} @ 0x8E;

__sfr __no_init volatile union
{ 
    unsigned char INTCLKO;
    struct
    {
        unsigned char        : 1;
        unsigned char EX4    : 1;
        unsigned char EX3    : 1;
        unsigned char EX2    : 1;
        unsigned char        : 1;
        unsigned char T2CLKO : 1;
        unsigned char T1CLKO : 1;
        unsigned char T0CLKO : 1;
    } INTCLKO_bit;
} @ 0x8F;

__sfr __no_init volatile union
{ 
    unsigned char P1;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P1_bit;
} @ 0x90;

__sfr __no_init volatile union
{ 
unsigned char P1M1;
struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P1M1_bit;
} @ 0x91;

__sfr __no_init volatile union
{ 
    unsigned char P1M0;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P1M0_bit;
} @ 0x92;

__sfr __no_init volatile union
{ 
    unsigned char P0M1;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P0M1_bit;
} @ 0x93;

__sfr __no_init volatile union
{ 
    unsigned char P0M0;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P0M0_bit;
} @ 0x94;

__sfr __no_init volatile union
{ 
    unsigned char P2M1;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P2M1_bit;
} @ 0x95;

__sfr __no_init volatile union
{ 
    unsigned char P2M0;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P2M0_bit;
} @ 0x96;

__sfr __no_init volatile union
{ 
    unsigned char AUXR2;
    struct
    {
        unsigned char        : 1;
        unsigned char        : 1;
        unsigned char        : 1;
        unsigned char TXLNRX : 1;
        unsigned char        : 1;
        unsigned char        : 1;
        unsigned char        : 1;
        unsigned char        : 1;
    } AUXR2_bit;
} @ 0x97;

__sfr __no_init volatile union
{ 
    unsigned char SCON;
    struct
    {
        unsigned char SM0_FE : 1;
        unsigned char SM1    : 1;
        unsigned char SM2    : 1;
        unsigned char REN    : 1;
        unsigned char TB8    : 1;
        unsigned char RB8    : 1;
        unsigned char TI     : 1;
        unsigned char RI     : 1;
    } SCON_bit;
} @ 0x98;

__sfr __no_init volatile union
{ 
    unsigned char SBUF;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } SBUF_bit;
} @ 0x99;

__sfr __no_init volatile union
{ 
    unsigned char S2CON;
    struct
    {
        unsigned char S2SM0 : 1;
        unsigned char       : 1;
        unsigned char S2SM2 : 1;
        unsigned char S2REN : 1;
        unsigned char S2TB8 : 1;
        unsigned char S2RB8 : 1;
        unsigned char S2TI  : 1;
        unsigned char S2RI  : 1;
    } S2CON_bit;
} @ 0x9A;

__sfr __no_init volatile union
{ 
    unsigned char S2BUF;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } S2BUF_bit;
} @ 0x9B;

__sfr __no_init volatile union
{ 
    unsigned char LIRTRIM;
    struct
    {
        unsigned char         : 1;
        unsigned char         : 1;
        unsigned char         : 1;
        unsigned char         : 1;
        unsigned char         : 1;
        unsigned char         : 1;
        unsigned char LIRTRIM : 2;
    } LIRTRIM_bit;
} @ 0x9E;

__sfr __no_init volatile union
{ 
    unsigned char IRTRIM;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } IRTRIM_bit;
} @ 0x9F;

__sfr __no_init volatile union
{ 
    unsigned char P2;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P2_bit;
} @ 0xA0;

__sfr __no_init volatile union
{ 
    unsigned char BUS_SPEED;
    struct
    {
        unsigned char RW_S  : 2; 
        unsigned char       : 1;
        unsigned char       : 1;
        unsigned char       : 1;
        unsigned char       : 1;
        unsigned char SPEED : 2;
    } BUS_SPEED_bit;
} @ 0xA1;

__sfr __no_init volatile union
{ 
    unsigned char P_SW1;
    struct
    {
        unsigned char  S1_S  : 2;
        unsigned char  CCP_S : 2;
        unsigned char  SPI_S : 2;
        unsigned char        : 1;
        unsigned char        : 1;
    } P_SW1_bit;
} @ 0xA2;

__sfr __no_init volatile union
{ 
    unsigned char IE;
    struct
    {
        unsigned char EA   : 1;
        unsigned char ELVD : 1;
        unsigned char EADC : 1;
        unsigned char ES   : 1;
        unsigned char ET1  : 1;
        unsigned char EX1  : 1;
        unsigned char ET0  : 1;
        unsigned char EX0  : 1;
    } IE_bit;
} @ 0xA8;

__sfr __no_init volatile union
{ 
    unsigned char SADDR;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } SADDR_bit;
} @ 0xA9;

__sfr __no_init volatile union
{ 
    unsigned char WKTCL;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } WKTCL_bit;
} @ 0xAA;

__sfr __no_init volatile union
{ 
    unsigned char WKTCH;
    struct
    {
        unsigned char WKTEN : 1;
        unsigned char       : 1;
        unsigned char       : 1;
        unsigned char       : 1;
        unsigned char       : 1;
        unsigned char       : 1;
        unsigned char       : 1;
        unsigned char       : 1;
    } WKTCH_bit;
} @ 0xAB;

__sfr __no_init volatile union
{ 
    unsigned char S3CON;
    struct
    {
        unsigned char S3SM0 : 1;
        unsigned char S3ST3 : 1;
        unsigned char S3SM2 : 1;
        unsigned char S3REN : 1;
        unsigned char S3TB8 : 1;
        unsigned char S3RB8 : 1;
        unsigned char S3TI  : 1;
        unsigned char S3RI  : 1;
    } S3CON_bit;
} @ 0xAC;

__sfr __no_init volatile union
{ 
    unsigned char S3BUF;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } S3BUF_bit;
} @ 0xAD;

__sfr __no_init volatile union
{ 
    unsigned char TA;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } TA_bit;
} @ 0xAE;

__sfr __no_init volatile union
{ 
    unsigned char IE2;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } IE2_bit;
} @ 0xAF;

__sfr __no_init volatile union
{ 
    unsigned char P3;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P3_bit;
} @ 0xB0;

__sfr __no_init volatile union
{ 
    unsigned char P3M1;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P3M1_bit;
} @ 0xB1;

__sfr __no_init volatile union
{ 
    unsigned char P3M0;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P3M0_bit;
} @ 0xB2;

__sfr __no_init volatile union
{ 
    unsigned char P4M1;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P4M1_bit;
} @ 0xB3;

__sfr __no_init volatile union
{ 
    unsigned char P4M0;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P4M0_bit;
} @ 0xB4;

__sfr __no_init volatile union
{ 
    unsigned char IP2;
    struct
    {
        unsigned char PCAN   : 1;
        unsigned char PI2C   : 1;
        unsigned char PCMP   : 1;
        unsigned char PX4    : 1;
        unsigned char PPWMFD : 1;
        unsigned char PPWM   : 1;
        unsigned char PSPI   : 1;
        unsigned char PS2    : 1;
    } IP2_bit;
} @ 0xB5;

__sfr __no_init volatile union
{ 
    unsigned char IP2H;
    struct
    {
        unsigned char PCANH   : 1;
        unsigned char PI2CH   : 1;
        unsigned char PCMPH   : 1;
        unsigned char PX4H    : 1;
        unsigned char PPWMFDH : 1;
        unsigned char PPWMH   : 1;
        unsigned char PSPIH   : 1;
        unsigned char PS2H    : 1;
    } IP2H_bit;
} @ 0xB6;

__sfr __no_init volatile union
{ 
    unsigned char IPH;
    struct
    {
        unsigned char PPCAH : 1;
        unsigned char PLVDH : 1;
        unsigned char PADCH : 1;
        unsigned char PSH   : 1;
        unsigned char PT1H  : 1;
        unsigned char PX1H  : 1;
        unsigned char PT0H  : 1;
        unsigned char PX0H  : 1;
    } IPH_bit;
} @ 0xB7;

__sfr __no_init volatile union
{ 
    unsigned char IP;
    struct
    {
        unsigned char PPCA : 1;
        unsigned char PLVD : 1;
        unsigned char PADC : 1;
        unsigned char PS   : 1;
        unsigned char PT1  : 1;
        unsigned char PX1  : 1;
        unsigned char PT0  : 1;
        unsigned char PX0  : 1;
    } IP_bit;
} @ 0xB8;

__sfr __no_init volatile union
{ 
    unsigned char SADEN;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } SADEN_bit;
} @ 0xB9;

__sfr __no_init volatile union
{ 
    unsigned char P_SW2;
    struct
    {
        unsigned char EAXFR  : 1;
        unsigned char CAN_S  : 1;
        unsigned char I2C_S  : 2;
        unsigned char CMPO_S : 1;
        unsigned char S4_S   : 1;
        unsigned char S3_S   : 1;
        unsigned char S2_S   : 1;
    } P_SW2_bit;
} @ 0xBA;

__sfr __no_init volatile union
{ 
    unsigned char VOCTRL;
    struct
    {
        unsigned char SCC : 1;
        unsigned char     : 1;
        unsigned char     : 1;
        unsigned char     : 1;
        unsigned char     : 1;
        unsigned char     : 1;
        unsigned char     : 1;
        unsigned char     : 1;
    } VOCTRL_bit;
} @ 0xBB;

__sfr __no_init volatile union
{ 
    unsigned char ADC_CONTR;
    struct
    {
        unsigned char ADC_POWER : 1;
        unsigned char ADC_START : 1;
        unsigned char ADC_FLAG  : 1;
        unsigned char           : 1;
        unsigned char ADC_CHS   : 4;
    } ADC_CONTR_bit;
} @ 0xBC;

__sfr __no_init volatile union
{ 
    unsigned char ADC_RES;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } ADC_RES_bit;
} @ 0xBD;

__sfr __no_init volatile union
{ 
    unsigned char ADC_RESL;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } ADC_RESL_bit;
} @ 0xBE;

__sfr __no_init volatile union
{ 
    unsigned char P4;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P4_bit;
} @ 0xC0;

__sfr __no_init volatile union
{ 
    unsigned char WDT_CONTR;
    struct
    {
        unsigned char WDT_FLAG : 1;
        unsigned char -        : 1;
        unsigned char EN_WDT   : 1;
        unsigned char CLR_WDT  : 1;
        unsigned char IDL_WDT  : 1;
        unsigned char WDT_PS   : 3;
    } WDT_CONTR_bit;
} @ 0xC1;

__sfr __no_init volatile union
{ 
    unsigned char IAP_DATA;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } IAP_DATA_bit;
} @ 0xC2;

__sfr __no_init volatile union
{ 
    unsigned char IAP_ADDRH;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } IAP_ADDRH_bit;
} @ 0xC3;

__sfr __no_init volatile union
{ 
    unsigned char IAP_ADDRL;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } IAP_ADDRL_bit;
} @ 0xC4;

__sfr __no_init volatile union
{ 
    unsigned char IAP_CMD;
    struct
    {
        unsigned char     : 1;
        unsigned char     : 1;
        unsigned char     : 1;
        unsigned char     : 1;
        unsigned char     : 1;
        unsigned char     : 1;
        unsigned char CMD : 2;
    } IAP_CMD_bit;
} @ 0xC5;

__sfr __no_init volatile union
{ 
    unsigned char IAP_TRIG;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } IAP_TRIG_bit;
} @ 0xC6;

__sfr __no_init volatile union
{ 
    unsigned char IAP_CONTR;
    struct
    {
        unsigned char IAPEN    : 1;
        unsigned char SWBS     : 1;
        unsigned char SWRST    : 1;
        unsigned char CMD_FAIL : 1;
        unsigned char          : 1;
        unsigned char IAP_WT   : 3;
    } IAP_CONTR_bit;
} @ 0xC7;

__sfr __no_init volatile union
{ 
    unsigned char P5;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P5_bit;
} @ 0xC8;

__sfr __no_init volatile union
{ 
    unsigned char P5M1;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P5M1_bit;
} @ 0xC9;

__sfr __no_init volatile union
{ 
    unsigned char P5M0;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P5M0_bit;
} @ 0xCA;

__sfr __no_init volatile union
{ 
    unsigned char P6M1;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P6M1_bit;
} @ 0xCB;

__sfr __no_init volatile union
{ 
    unsigned char P6M0;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P6M0_bit;
} @ 0xCC;

__sfr __no_init volatile union
{ 
    unsigned char SPSTAT;
    struct
    {
        unsigned char SPIF : 1;
        unsigned char WCOL : 1;
        unsigned char      : 1;
        unsigned char      : 1;
        unsigned char      : 1;
        unsigned char      : 1;
        unsigned char      : 1;
        unsigned char      : 1;
    } SPSTAT_bit;
} @ 0xCD;

__sfr __no_init volatile union
{ 
    unsigned char SPCTL;
    struct
    {
        unsigned char SSIG : 1;
        unsigned char SPEN : 1;
        unsigned char DORD : 1;
        unsigned char MSTR : 1;
        unsigned char CPOL : 1;
        unsigned char CPHA : 1;
        unsigned char SPR  : 2;
    } SPCTL_bit;
} @ 0xCE;

__sfr __no_init volatile union
{ 
    unsigned char SPDAT;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } SPDAT_bit;
} @ 0xCF;

__sfr __no_init volatile union
{ 
    unsigned char PSW;
    struct
    {
        unsigned char CY  : 1;
        unsigned char AC  : 1;
        unsigned char F0  : 1;
        unsigned char RS1 : 1;
        unsigned char RS0 : 1;
        unsigned char OV  : 1;
        unsigned char     : 1;
        unsigned char P   : 1;
    } PSW_bit;
} @ 0xD0;

__sfr __no_init volatile union
{ 
    unsigned char T4T3M;
    struct
    {
        unsigned char T4R    : 1;
        unsigned char T4_CT  : 1;
        unsigned char T4x12  : 1;
        unsigned char T4CLKO : 1;
        unsigned char T3R    : 1;
        unsigned char T3_CT  : 1;
        unsigned char T3x12  : 1;
        unsigned char T3CLKO : 1;
    } T4T3M_bit;
} @ 0xD1;

__sfr __no_init volatile union
{ 
    unsigned char T4H;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } T4H_bit;
} @ 0xD2;

__sfr __no_init volatile union
{ 
    unsigned char T4L;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } T4L_bit;
} @ 0xD3;

__sfr __no_init volatile union
{ 
    unsigned char T3H;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } T3H_bit;
} @ 0xD4;

__sfr __no_init volatile union
{ 
    unsigned char T3L;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } T3L_bit;
} @ 0xD5;

__sfr __no_init volatile union
{ 
    unsigned char T2H;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } T2H_bit;
} @ 0xD6;

__sfr __no_init volatile union
{ 
    unsigned char T2L;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } T2L_bit;
} @ 0xD7;

__sfr __no_init volatile union
{ 
    unsigned char CCON;
    struct
    {
        unsigned char CF   : 1;
        unsigned char CR   : 1;
        unsigned char      : 1;
        unsigned char      : 1;
        unsigned char CCF3 : 1;
        unsigned char CCF2 : 1;
        unsigned char CCF1 : 1;
        unsigned char CCF0 : 1;
    } CCON_bit;
} @ 0xD8;

__sfr __no_init volatile union
{ 
    unsigned char CMOD;
    struct
    {
        unsigned char CIDL : 1;
        unsigned char      : 1;
        unsigned char      : 1;
        unsigned char      : 1;
        unsigned char CPS  : 3;
        unsigned char ECF  : 1;
    } CMOD_bit;
} @ 0xD9;

__sfr __no_init volatile union
{ 
    unsigned char CCAPM0;
    struct
    {
        unsigned char        : 1;
        unsigned char ECOM0  : 1;
        unsigned char CCAPP0 : 1;
        unsigned char CCAPN0 : 1;
        unsigned char MAT0   : 1;
        unsigned char TOG0   : 1;
        unsigned char PWM0   : 1;
        unsigned char ECCF0  : 1;
    } CCAPM0_bit;
} @ 0xDA;

__sfr __no_init volatile union
{ 
    unsigned char CCAPM1;
    struct
    {
        unsigned char        : 1;
        unsigned char ECOM1  : 1;
        unsigned char CCAPP1 : 1;
        unsigned char CCAPN1 : 1;
        unsigned char MAT1   : 1;
        unsigned char TOG1   : 1;
        unsigned char PWM1   : 1;
        unsigned char ECCF1  : 1;
    } CCAPM1_bit;
} @ 0xDB;

__sfr __no_init volatile union
{ 
    unsigned char CCAPM2;
    struct
    {
        unsigned char        : 1;
        unsigned char ECOM2  : 1;
        unsigned char CCAPP2 : 1;
        unsigned char CCAPN2 : 1;
        unsigned char MAT2   : 1;
        unsigned char TOG2   : 1;
        unsigned char PWM2   : 1;
        unsigned char ECCF2  : 1;
    } CCAPM2_bit;
} @ 0xDC;

__sfr __no_init volatile union
{ 
    unsigned char CCAPM3;
    struct
    {
        unsigned char        : 1;
        unsigned char ECOM3  : 1;
        unsigned char CCAPP3 : 1;
        unsigned char CCAPN3 : 1;
        unsigned char MAT3   : 1;
        unsigned char TOG3   : 1;
        unsigned char PWM3   : 1;
        unsigned char ECCF3  : 1;
    } CCAPM3_bit;
} @ 0xDD;

__sfr __no_init volatile union
{ 
    unsigned char IP3;
    struct
    {
        unsigned char     : 1;
        unsigned char     : 1;
        unsigned char     : 1;
        unsigned char     : 1;
        unsigned char     : 1;
        unsigned char     : 1;
        unsigned char PS4 : 1;
        unsigned char PS3 : 1;
    } IP3_bit;
} @ 0xDF;

__sfr __no_init volatile union
{ 
    unsigned char ADCCFG;
    struct
    {
        unsigned char        : 1;
        unsigned char        : 1;
        unsigned char RESFMT : 1;
        unsigned char        : 1;
        unsigned char SPEED  : 4;
    } ADCCFG_bit;
} @ 0xDE;

__sfr __no_init volatile union
{ 
    unsigned char ACC;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } ACC_bit;
} @ 0xE0;

__sfr __no_init volatile union
{ 
    unsigned char P7M1;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P7M1_bit;
} @ 0xE1;

__sfr __no_init volatile union
{ 
    unsigned char P7M0;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P7M0_bit;
} @ 0xE2;

__sfr __no_init volatile union
{ 
    unsigned char DPS;
    struct
    {
        unsigned char ID1 : 1;
        unsigned char ID0 : 1;
        unsigned char TSL : 1;
        unsigned char AU1 : 1;
        unsigned char AU0 : 1;
        unsigned char     : 1;
        unsigned char     : 1;
        unsigned char SEL : 1;
    } DPS_bit;
} @ 0xE3;

__sfr __no_init volatile union
{ 
    unsigned char DPL1;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } DPL1_bit;
} @ 0xE4;

__sfr __no_init volatile union
{ 
    unsigned char DPH1;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } DPH1_bit;
} @ 0xE5;

__sfr __no_init volatile union
{ 
    unsigned char CMPCR1;
    struct
    {
        unsigned char CMPEN  : 1;
        unsigned char CMPIF  : 1;
        unsigned char PIE    : 1;
        unsigned char NIE    : 1;
        unsigned char PIS    : 1;
        unsigned char NIS    : 1;
        unsigned char CMPOE  : 1;
        unsigned char CMPRES : 1;
    } CMPCR1_bit;
} @ 0xE6;

__sfr __no_init volatile union
{ 
    unsigned char CMPCR2;
    struct
    {
        unsigned char INVCMPO : 1;
        unsigned char DISFLT  : 1;
        unsigned char LCDTY   : 6;
    } CMPCR2_bit;
} @ 0xE7;

__sfr __no_init volatile union
{ 
    unsigned char P6;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P6_bit;
} @ 0xE8;

__sfr __no_init volatile union
{ 
    unsigned char CL;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } CL_bit;
} @ 0xE9;

__sfr __no_init volatile union
{ 
    unsigned char CCAP0L;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } CCAP0L_bit;
} @ 0xEA;

__sfr __no_init volatile union
{ 
    unsigned char CCAP1L;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } CCAP1L_bit;
} @ 0xEB;

__sfr __no_init volatile union
{ 
    unsigned char CCAP2L;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } CCAP2L_bit;
} @ 0xEC;

__sfr __no_init volatile union
{ 
    unsigned char CCAP3L;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } CCAP3L_bit;
} @ 0xED;

__sfr __no_init volatile union
{ 
    unsigned char IP3H;
    struct
    {
        unsigned char      : 1;
        unsigned char      : 1;
        unsigned char      : 1;
        unsigned char      : 1;
        unsigned char      : 1;
        unsigned char      : 1;
        unsigned char PS4H : 1;
        unsigned char PS3H : 1;
    } IP3H_bit;
} @ 0xEE;

__sfr __no_init volatile union
{ 
    unsigned char AUXINTIF;
    struct
    {
        unsigned char        : 1;
        unsigned char INT4IF : 1;
        unsigned char INT3IF : 1;
        unsigned char INT2IF : 1;
        unsigned char        : 1;
        unsigned char T4IF   : 1;
        unsigned char T3IF   : 1;
        unsigned char T2IF   : 1;
    } AUXINTIF_bit;
} @ 0xEF;

__sfr __no_init volatile union
{ 
    unsigned char B;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } B_bit;
} @ 0xF0;

__sfr __no_init volatile union
{ 
    unsigned char PWMCFG;
    struct
    {
        unsigned char CBIF  : 1;
        unsigned char ETADC : 1;
        unsigned char       : 1;
        unsigned char       : 1;
        unsigned char       : 1;
        unsigned char       : 1;
        unsigned char       : 1;
        unsigned char       : 1;
    } PWMCFG_bit;
} @ 0xF1;

__sfr __no_init volatile union
{ 
    unsigned char PCA_PWM0;
    struct
    {
        unsigned char EBS0    : 2;
        unsigned char XCCAP0H : 2;
        unsigned char XCCAP0L : 2;
        unsigned char EPC0H   : 1;
        unsigned char EPC0L   : 1;
    } PCA_PWM0_bit;
} @ 0xF2;

__sfr __no_init volatile union
{ 
    unsigned char PCA_PWM1;
    struct
    {
        unsigned char EBS1    : 2;
        unsigned char XCCAP1H : 2;
        unsigned char XCCAP1L : 2;
        unsigned char EPC1H   : 1;
        unsigned char EPC1L   : 1;
    } PCA_PWM1_bit;
} @ 0xF3;

__sfr __no_init volatile union
{ 
    unsigned char PCA_PWM2;
    struct
    {
        unsigned char EBS2    : 2;
        unsigned char XCCAP2H : 2;
        unsigned char XCCAP2L : 2;
        unsigned char EPC2H   : 1;
        unsigned char EPC2L   : 1;
    } PCA_PWM2_bit;
} @ 0xF4;

__sfr __no_init volatile union
{ 
    unsigned char PCA_PWM3;
    struct
    {
        unsigned char EBS3    : 2;
        unsigned char XCCAP3H : 2;
        unsigned char XCCAP3L : 2;
        unsigned char EPC3H   : 1;
        unsigned char EPC3L   : 1;
    } PCA_PWM3_bit;
} @ 0xF5;

__sfr __no_init volatile union
{ 
    unsigned char PWMIF;
    struct
    {
        unsigned char C7IF : 1;
        unsigned char C6IF : 1;
        unsigned char C5IF : 1;
        unsigned char C4IF : 1;
        unsigned char C3IF : 1;
        unsigned char C2IF : 1;
        unsigned char C1IF : 1;
        unsigned char C0IF : 1;
    } PWMFDCR_bit;
} @ 0xF6;

__sfr __no_init volatile union
{ 
    unsigned char PWMFDCR;
    struct
    {
        unsigned char INVCMP  : 1;
        unsigned char INVIO   : 1;
        unsigned char ENFD    : 1;
        unsigned char FLTFLIO : 1;
        unsigned char EFDI    : 1;
        unsigned char FDCMP   : 1;
        unsigned char FDIO    : 1;
        unsigned char FDIF    : 1;
    } PWMFDCR_bit;
} @ 0xF7;

__sfr __no_init volatile union
{ 
    unsigned char P7;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } P7_bit;
} @ 0xF8;

__sfr __no_init volatile union
{ 
    unsigned char CH;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } CH_bit;
} @ 0xF9;

__sfr __no_init volatile union
{ 
    unsigned char CCAP0H;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } CCAP0H_bit;
} @ 0xFA;

__sfr __no_init volatile union
{ 
    unsigned char CCAP1H;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } CCAP1H_bit;
} @ 0xFB;

__sfr __no_init volatile union
{ 
    unsigned char CCAP2H;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } CCAP2H_bit;
} @ 0xFC;

__sfr __no_init volatile union
{ 
    unsigned char CCAP3H;
    struct
    {
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
        unsigned char : 1;
    } CCAP3H_bit;
} @ 0xFD;

__sfr __no_init volatile union
{ 
    unsigned char PWMCR;
    struct
    {
        unsigned char ENPWM : 1;
        unsigned char ECB   : 1;
        unsigned char       : 1;
        unsigned char       : 1;
        unsigned char       : 1;
        unsigned char       : 1;
        unsigned char       : 1;
        unsigned char       : 1;
    } PWMCR_bit;
} @ 0xFE;

__sfr __no_init volatile union
{ 
    unsigned char RSTCFG;
    struct
    {
        unsigned char        : 1;
        unsigned char ENLVR  : 1;
        unsigned char        : 1;
        unsigned char P54RST : 1;
        unsigned char        : 1;
        unsigned char        : 1;
        unsigned char LVDS   : 2;
    } RSTCFG_bit;
} @ 0xFF;


__xdata __no_init volatile unsigned char PWMCH       @ 0xFFF0;
__xdata __no_init volatile unsigned char PWMCL       @ 0xFFF1;
__xdata __no_init volatile unsigned char PWMCKS      @ 0xFFF2;
__xdata __no_init volatile unsigned char TADCPH      @ 0xFFF3;
__xdata __no_init volatile unsigned char TADCPL      @ 0xFFF4;
__xdata __no_init volatile unsigned char PWM0T1H     @ 0xFF00;
__xdata __no_init volatile unsigned char PWM0T1L     @ 0xFF01;
__xdata __no_init volatile unsigned char PWM0T2H     @ 0xFF02;
__xdata __no_init volatile unsigned char PWM0T2L     @ 0xFF03;
__xdata __no_init volatile unsigned char PWM0CR      @ 0xFF04;
__xdata __no_init volatile unsigned char PWM0HLD     @ 0xFF05;
__xdata __no_init volatile unsigned char PWM1T1H     @ 0xFF10;
__xdata __no_init volatile unsigned char PWM1T1L     @ 0xFF11;
__xdata __no_init volatile unsigned char PWM1T2H     @ 0xFF12;
__xdata __no_init volatile unsigned char PWM1T2L     @ 0xFF13;
__xdata __no_init volatile unsigned char PWM1CR      @ 0xFF14;
__xdata __no_init volatile unsigned char PWM1HLD     @ 0xFF15;
__xdata __no_init volatile unsigned char PWM2T1H     @ 0xFF20;
__xdata __no_init volatile unsigned char PWM2T1L     @ 0xFF21;
__xdata __no_init volatile unsigned char PWM2T2H     @ 0xFF22;
__xdata __no_init volatile unsigned char PWM2T2L     @ 0xFF23;
__xdata __no_init volatile unsigned char PWM2CR      @ 0xFF24;
__xdata __no_init volatile unsigned char PWM2HLD     @ 0xFF25;
__xdata __no_init volatile unsigned char PWM3T1H     @ 0xFF30;
__xdata __no_init volatile unsigned char PWM3T1L     @ 0xFF31;
__xdata __no_init volatile unsigned char PWM3T2H     @ 0xFF32;
__xdata __no_init volatile unsigned char PWM3T2L     @ 0xFF33;
__xdata __no_init volatile unsigned char PWM3CR      @ 0xFF34;
__xdata __no_init volatile unsigned char PWM3HLD     @ 0xFF35;
__xdata __no_init volatile unsigned char PWM4T1H     @ 0xFF40;
__xdata __no_init volatile unsigned char PWM4T1L     @ 0xFF41;
__xdata __no_init volatile unsigned char PWM4T2H     @ 0xFF42;
__xdata __no_init volatile unsigned char PWM4T2L     @ 0xFF43;
__xdata __no_init volatile unsigned char PWM4CR      @ 0xFF44;
__xdata __no_init volatile unsigned char PWM4HLD     @ 0xFF45;
__xdata __no_init volatile unsigned char PWM5T1H     @ 0xFF50;
__xdata __no_init volatile unsigned char PWM5T1L     @ 0xFF51;
__xdata __no_init volatile unsigned char PWM5T2H     @ 0xFF52;
__xdata __no_init volatile unsigned char PWM5T2L     @ 0xFF53;
__xdata __no_init volatile unsigned char PWM5CR      @ 0xFF54;
__xdata __no_init volatile unsigned char PWM5HLD     @ 0xFF55;
__xdata __no_init volatile unsigned char PWM6T1H     @ 0xFF60;
__xdata __no_init volatile unsigned char PWM6T1L     @ 0xFF61;
__xdata __no_init volatile unsigned char PWM6T2H     @ 0xFF62;
__xdata __no_init volatile unsigned char PWM6T2L     @ 0xFF63;
__xdata __no_init volatile unsigned char PWM6CR      @ 0xFF64;
__xdata __no_init volatile unsigned char PWM6HLD     @ 0xFF65;
__xdata __no_init volatile unsigned char PWM7T1H     @ 0xFF70;
__xdata __no_init volatile unsigned char PWM7T1L     @ 0xFF71;
__xdata __no_init volatile unsigned char PWM7T2H     @ 0xFF72;
__xdata __no_init volatile unsigned char PWM7T2L     @ 0xFF73;
__xdata __no_init volatile unsigned char PWM7CR      @ 0xFF74;
__xdata __no_init volatile unsigned char PWM7HLD     @ 0xFF75;
__xdata __no_init volatile unsigned char I2CCFG      @ 0xFE80;
__xdata __no_init volatile unsigned char I2CMSCR     @ 0xFE81;
__xdata __no_init volatile unsigned char I2CMSST     @ 0xFE82;
__xdata __no_init volatile unsigned char I2CSLCR     @ 0xFE83;
__xdata __no_init volatile unsigned char I2CSLST     @ 0xFE84;
__xdata __no_init volatile unsigned char I2CSLADR    @ 0xFE85;
__xdata __no_init volatile unsigned char I2CTXD      @ 0xFE86;
__xdata __no_init volatile unsigned char I2CRXD      @ 0xFE87;
__xdata __no_init volatile unsigned char I2CMSAUX    @ 0xFE88;
__xdata __no_init volatile unsigned char P0PU        @ 0xFE10;
__xdata __no_init volatile unsigned char P1PU        @ 0xFE11;
__xdata __no_init volatile unsigned char P2PU        @ 0xFE12;
__xdata __no_init volatile unsigned char P3PU        @ 0xFE13;
__xdata __no_init volatile unsigned char P4PU        @ 0xFE14;
__xdata __no_init volatile unsigned char P5PU        @ 0xFE15;
__xdata __no_init volatile unsigned char P6PU        @ 0xFE16;
__xdata __no_init volatile unsigned char P7PU        @ 0xFE17;
__xdata __no_init volatile unsigned char P0NCS       @ 0xFE18;
__xdata __no_init volatile unsigned char P1NCS       @ 0xFE19;
__xdata __no_init volatile unsigned char P2NCS       @ 0xFE1A;
__xdata __no_init volatile unsigned char P3NCS       @ 0xFE1B;
__xdata __no_init volatile unsigned char P4NCS       @ 0xFE1C;
__xdata __no_init volatile unsigned char P5NCS       @ 0xFE1D;
__xdata __no_init volatile unsigned char P6NCS       @ 0xFE1E;
__xdata __no_init volatile unsigned char P7NCS       @ 0xFE1F;
__xdata __no_init volatile unsigned char CKSEL       @ 0xFE00;
__xdata __no_init volatile unsigned char CLKDIV      @ 0xFE01;
__xdata __no_init volatile unsigned char IRC24MCR    @ 0xFE02;
__xdata __no_init volatile unsigned char XOSCCR      @ 0xFE03;
__xdata __no_init volatile unsigned char IRC32KCR    @ 0xFE04;


/*
 * Interrupt Vectors
 */
#define extern0 0x03 /* External interrupt 0 */
#define timer0 0x0B /* Timer 0 Interrupt */
#define extern1 0x13 /* External interrupt 1 */
#define timer1 0x1B /* Timer 1 Interrupt */
#define sio_ti 0x23 /* Serial Port Interrupt */
#define sio_ri 0x23 /* Serial Port Interrupt */

#pragma language=restore
#endif  /* __IAR_SYSTEMS_ICC__  */

/***************************************************************************
 *   Assembler definitions
 *
 *   The following SFRs are built in in the a8051.exe and can not be
 *   defined explicitly in this file:
 *     ACC,B,PSW,SP,DPL,DPH
 *   The PSW-bits are built-in in the a8051.exe
 *     OV,AC,F0,RS0,RS1,P
 *
 ***************************************************************************/

#ifdef __IAR_SYSTEMS_ASM__

P0          DEFINE 0x80
SP          DEFINE 0x81
DPL         DEFINE 0x82
DPH         DEFINE 0x83
S4CON       DEFINE 0x84
S4BUF       DEFINE 0x85
PCON        DEFINE 0x87
TCON        DEFINE 0x88
TMOD        DEFINE 0x89
TL0         DEFINE 0x8A
TL1         DEFINE 0x8B
TH0         DEFINE 0x8C
TH1         DEFINE 0x8D
AUXR        DEFINE 0x8E
INTCLKO     DEFINE 0x8F
P1          DEFINE 0x90
P1M1        DEFINE 0x91
P1M0        DEFINE 0x92
P0M1        DEFINE 0x93
P0M0        DEFINE 0x94
P2M1        DEFINE 0x95
P2M0        DEFINE 0x96
AUXR2       DEFINE 0x97
SCON        DEFINE 0x98
SBUF        DEFINE 0x99
S2CON       DEFINE 0x9A
S2BUF       DEFINE 0x9B
LIRTRIM     DEFINE 0x9E
IRTRIM      DEFINE 0x9F
P2          DEFINE 0xA0
BUS_SPEED   DEFINE 0xA1
P_SW1       DEFINE 0xA2
IE          DEFINE 0xA8
SADDR       DEFINE 0xA9
WKTCL       DEFINE 0xAA
WKTCH       DEFINE 0xAB
S3CON       DEFINE 0xAC
S3BUF       DEFINE 0xAD
TA          DEFINE 0xAE
IE2         DEFINE 0xAF
P3          DEFINE 0xB0
P3M1        DEFINE 0xB1
P3M0        DEFINE 0xB2
P4M1        DEFINE 0xB3
P4M0        DEFINE 0xB4
IP2         DEFINE 0xB5
IP2H        DEFINE 0xB6
IPH         DEFINE 0xB7
IP          DEFINE 0xB8
SADEN       DEFINE 0xB9
P_SW2       DEFINE 0xBA
VOCTRL      DEFINE 0xBB
ADC_CONTR   DEFINE 0xBC
ADC_RES     DEFINE 0xBD
ADC_RESL    DEFINE 0xBE
P4          DEFINE 0xC0
P4          DEFINE 0xC0
WDT_CONTR   DEFINE 0xC1
IAP_DATA    DEFINE 0xC2
IAP_ADDRH   DEFINE 0xC3
IAP_ADDRL   DEFINE 0xC4
IAP_CMD     DEFINE 0xC5
IAP_TRIG    DEFINE 0xC6
IAP_CONTR   DEFINE 0xC7
P5          DEFINE 0xC8
P5M1        DEFINE 0xC9
P5M0        DEFINE 0xCA
P6M1        DEFINE 0xCB
P6M0        DEFINE 0xCC
SPSTAT      DEFINE 0xCD
SPCTL       DEFINE 0xCE
SPDAT       DEFINE 0xCF
PSW         DEFINE 0xD0
T4T3M       DEFINE 0xD1
T4H         DEFINE 0xD2
T4L         DEFINE 0xD3
T3H         DEFINE 0xD4
T3L         DEFINE 0xD5
T2H         DEFINE 0xD6
T2L         DEFINE 0xD7
CCON        DEFINE 0xD8
CMOD        DEFINE 0xD9
CCAPM0      DEFINE 0xDA
CCAPM1      DEFINE 0xDB
CCAPM2      DEFINE 0xDC
CCAPM3      DEFINE 0xDD
IP3         DEFINE 0xDF
ADCCFG      DEFINE 0xDE
ACC         DEFINE 0xE0
P7M1        DEFINE 0xE1
P7M0        DEFINE 0xE2
DPS         DEFINE 0xE3
DPL1        DEFINE 0xE4
DPH1        DEFINE 0xE5
CMPCR1      DEFINE 0xE6
CMPCR2      DEFINE 0xE7
P6          DEFINE 0xE8
CL          DEFINE 0xE9
CCAP0L      DEFINE 0xEA
CCAP1L      DEFINE 0xEB
CCAP2L      DEFINE 0xEC
CCAP3L      DEFINE 0xED
IP3H        DEFINE 0xEE
AUXINTIF    DEFINE 0xEF
B           DEFINE 0xF0
PWMCFG      DEFINE 0xF1
PCA_PWM0    DEFINE 0xF2
PCA_PWM1    DEFINE 0xF3
PCA_PWM2    DEFINE 0xF4
PCA_PWM3    DEFINE 0xF5
PWMIF       DEFINE 0xF6
PWMFDCR     DEFINE 0xF7
P7          DEFINE 0xF8
CH          DEFINE 0xF9
CCAP0H      DEFINE 0xFA
CCAP1H      DEFINE 0xFB
CCAP2H      DEFINE 0xFC
CCAP3H      DEFINE 0xFD
PWMCR       DEFINE 0xFE
RSTCFG      DEFINE 0xFF

PWMCH       DEFINE 0xFFF0
PWMCL       DEFINE 0xFFF1
PWMCKS      DEFINE 0xFFF2
TADCPH      DEFINE 0xFFF3
TADCPL      DEFINE 0xFFF4
PWM0T1H     DEFINE 0xFF00
PWM0T1L     DEFINE 0xFF01
PWM0T2H     DEFINE 0xFF02
PWM0T2L     DEFINE 0xFF03
PWM0CR      DEFINE 0xFF04
PWM0HLD     DEFINE 0xFF05
PWM1T1H     DEFINE 0xFF10
PWM1T1L     DEFINE 0xFF11
PWM1T2H     DEFINE 0xFF12
PWM1T2L     DEFINE 0xFF13
PWM1CR      DEFINE 0xFF14
PWM1HLD     DEFINE 0xFF15
PWM2T1H     DEFINE 0xFF20
PWM2T1L     DEFINE 0xFF21
PWM2T2H     DEFINE 0xFF22
PWM2T2L     DEFINE 0xFF23
PWM2CR      DEFINE 0xFF24
PWM2HLD     DEFINE 0xFF25
PWM3T1H     DEFINE 0xFF30
PWM3T1L     DEFINE 0xFF31
PWM3T2H     DEFINE 0xFF32
PWM3T2L     DEFINE 0xFF33
PWM3CR      DEFINE 0xFF34
PWM3HLD     DEFINE 0xFF35
PWM4T1H     DEFINE 0xFF40
PWM4T1L     DEFINE 0xFF41
PWM4T2H     DEFINE 0xFF42
PWM4T2L     DEFINE 0xFF43
PWM4CR      DEFINE 0xFF44
PWM4HLD     DEFINE 0xFF45
PWM5T1H     DEFINE 0xFF50
PWM5T1L     DEFINE 0xFF51
PWM5T2H     DEFINE 0xFF52
PWM5T2L     DEFINE 0xFF53
PWM5CR      DEFINE 0xFF54
PWM5HLD     DEFINE 0xFF55
PWM6T1H     DEFINE 0xFF60
PWM6T1L     DEFINE 0xFF61
PWM6T2H     DEFINE 0xFF62
PWM6T2L     DEFINE 0xFF63
PWM6CR      DEFINE 0xFF64
PWM6HLD     DEFINE 0xFF65
PWM7T1H     DEFINE 0xFF70
PWM7T1L     DEFINE 0xFF71
PWM7T2H     DEFINE 0xFF72
PWM7T2L     DEFINE 0xFF73
PWM7CR      DEFINE 0xFF74
PWM7HLD     DEFINE 0xFF75
I2CCFG      DEFINE 0xFE80
I2CMSCR     DEFINE 0xFE81
I2CMSST     DEFINE 0xFE82
I2CSLCR     DEFINE 0xFE83
I2CSLST     DEFINE 0xFE84
I2CSLADR    DEFINE 0xFE85
I2CTXD      DEFINE 0xFE86
I2CRXD      DEFINE 0xFE87
I2CMSAUX    DEFINE 0xFE88
P0PU        DEFINE 0xFE10
P1PU        DEFINE 0xFE11
P2PU        DEFINE 0xFE12
P3PU        DEFINE 0xFE13
P4PU        DEFINE 0xFE14
P5PU        DEFINE 0xFE15
P6PU        DEFINE 0xFE16
P7PU        DEFINE 0xFE17
P0NCS       DEFINE 0xFE18
P1NCS       DEFINE 0xFE19
P2NCS       DEFINE 0xFE1A
P3NCS       DEFINE 0xFE1B
P4NCS       DEFINE 0xFE1C
P5NCS       DEFINE 0xFE1D
P6NCS       DEFINE 0xFE1E
P7NCS       DEFINE 0xFE1F
CKSEL       DEFINE 0xFE00
CLKDIV      DEFINE 0xFE01
IRC24MCR    DEFINE 0xFE02
XOSCCR      DEFINE 0xFE03
IRC32KCR    DEFINE 0xFE04

P0_P00 DEFINE 0x80.0
P0_P01 DEFINE 0x80.1
P0_P02 DEFINE 0x80.2
P0_P03 DEFINE 0x80.3
P0_P04 DEFINE 0x80.4
P0_P05 DEFINE 0x80.5
P0_P06 DEFINE 0x80.6
P0_P07 DEFINE 0x80.7


TF1 DEFINE  TCON.7
TR1 DEFINE  TCON.6
TF0 DEFINE  TCON.5
TR0 DEFINE  TCON.4
IE1 DEFINE  TCON.3
IT1 DEFINE  TCON.2
IE0 DEFINE  TCON.1
IT0 DEFINE  TCON.0

SM0_FE DEFINE   SCON.7
SM1    DEFINE   SCON.6
SM2    DEFINE   SCON.5
REN    DEFINE   SCON.4
TB8    DEFINE   SCON.3
RB8    DEFINE   SCON.2
TI     DEFINE   SCON.1
RI     DEFINE   SCON.0

EA   DEFINE IE.7
ELVD DEFINE IE.6
EADC DEFINE IE.5
ES   DEFINE IE.4
ET1  DEFINE IE.3
EX1  DEFINE IE.2
ET0  DEFINE IE.1
EX0  DEFINE IE.0

PPCA DEFINE IP.7
PLVD DEFINE IP.6
PADC DEFINE IP.5
PS   DEFINE IP.4
PT1  DEFINE IP.3
PX1  DEFINE IP.2
PT0  DEFINE IP.1
PX0  DEFINE IP.0

CY  DEFINE PSW.7
AC  DEFINE PSW.6
F0  DEFINE PSW.5
RS1 DEFINE PSW.4
RS0 DEFINE PSW.3
OV  DEFINE PSW.2
P   DEFINE PSW.0

CF   DEFINE CCON.7
CR   DEFINE CCON.6
CCF3 DEFINE CCON.3
CCF2 DEFINE CCON.2
CCF1 DEFINE CCON.1
CCF0 DEFINE CCON.0

#endif /* __IAR_SYSTEMS_ASM__*/
#endif /* STC8_H */

