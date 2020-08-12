#ifndef __STC8F_H_
#define __STC8F_H_

/////////////////////////////////////////////////

//包含本头文件后,不用另外再包含"REG51.H"

//内核特殊功能寄存器
__sfr         __at   (0xE0) ACC ;
__sfr         __at   (0xF0) B   ;
__sfr         __at   (0xD0) PSW ;
__sbit        __at   (0xD7) CY ;
__sbit        __at   (0xD6) AC ;
__sbit        __at   (0xD5) F0 ;
__sbit        __at   (0xD4) RS1;
__sbit        __at   (0xD3) RS0;
__sbit        __at   (0xD2) OV ;
__sbit        __at   (0xD0) P  ;
__sfr         __at   (0x81) SP  ;
__sfr         __at   (0x82) DPL ;
__sfr         __at   (0x83) DPH ;
__sfr         __at   (0xAE) TA  ;
__sfr         __at   (0xE3) DPS ;
__sfr         __at   (0xE4) DPL1;
__sfr         __at   (0xE5) DPH1;


//I/O 口特殊功能寄存器
__sfr         __at   (0x80) P0  ;
__sfr         __at   (0x90) P1  ;
__sfr         __at   (0xA0) P2  ;
__sfr         __at   (0xB0) P3  ;
__sfr         __at   (0xC0) P4  ;
__sfr         __at   (0xC8) P5  ;
__sfr         __at   (0xE8) P6  ;
__sfr         __at   (0xF8) P7  ;
__sfr         __at   (0x94) P0M0;
__sfr         __at   (0x93) P0M1;
__sfr         __at   (0x92) P1M0;
__sfr         __at   (0x91) P1M1;
__sfr         __at   (0x96) P2M0;
__sfr         __at   (0x95) P2M1;
__sfr         __at   (0xB2) P3M0;
__sfr         __at   (0xB1) P3M1;
__sfr         __at   (0xB4) P4M0;
__sfr         __at   (0xB3) P4M1;
__sfr         __at   (0xCA) P5M0;
__sfr         __at   (0xC9) P5M1;
__sfr         __at   (0xCC) P6M0;
__sfr         __at   (0xCB) P6M1;
__sfr         __at   (0xE2) P7M0;
__sfr         __at   (0xE1) P7M1;

__sbit        __at   (0x80) P00;
__sbit        __at   (0x81) P01;
__sbit        __at   (0x82) P02;
__sbit        __at   (0x83) P03;
__sbit        __at   (0x84) P04;
__sbit        __at   (0x85) P05;
__sbit        __at   (0x86) P06;
__sbit        __at   (0x87) P07;
__sbit        __at   (0x90) P10;
__sbit        __at   (0x91) P11;
__sbit        __at   (0x92) P12;
__sbit        __at   (0x93) P13;
__sbit        __at   (0x94) P14;
__sbit        __at   (0x95) P15;
__sbit        __at   (0x96) P16;
__sbit        __at   (0x97) P17;
__sbit        __at   (0xA0) P20;
__sbit        __at   (0xA1) P21;
__sbit        __at   (0xA2) P22;
__sbit        __at   (0xA3) P23;
__sbit        __at   (0xA4) P24;
__sbit        __at   (0xA5) P25;
__sbit        __at   (0xA6) P26;
__sbit        __at   (0xA7) P27;
__sbit        __at   (0xB0) P30;
__sbit        __at   (0xB1) P31;
__sbit        __at   (0xB2) P32;
__sbit        __at   (0xB3) P33;
__sbit        __at   (0xB4) P34;
__sbit        __at   (0xB5) P35;
__sbit        __at   (0xB6) P36;
__sbit        __at   (0xB7) P37;
__sbit        __at   (0xC0) P40;
__sbit        __at   (0xC1) P41;
__sbit        __at   (0xC2) P42;
__sbit        __at   (0xC3) P43;
__sbit        __at   (0xC4) P44;
__sbit        __at   (0xC5) P45;
__sbit        __at   (0xC6) P46;
__sbit        __at   (0xC7) P47;
__sbit        __at   (0xC0) P50;
__sbit        __at   (0xC1) P51;
__sbit        __at   (0xC2) P52;
__sbit        __at   (0xC3) P53;
__sbit        __at   (0xC4) P54;
__sbit        __at   (0xC5) P55;
__sbit        __at   (0xC6) P56;
__sbit        __at   (0xC7) P57;
__sbit        __at   (0xE0) P60;
__sbit        __at   (0xE1) P61;
__sbit        __at   (0xE2) P62;
__sbit        __at   (0xE3) P63;
__sbit        __at   (0xE4) P64;
__sbit        __at   (0xE5) P65;
__sbit        __at   (0xE6) P66;
__sbit        __at   (0xE7) P67;
__sbit        __at   (0xF0) P70;
__sbit        __at   (0xF1) P71;
__sbit        __at   (0xF2) P72;
__sbit        __at   (0xF3) P73;
__sbit        __at   (0xF4) P74;
__sbit        __at   (0xF5) P75;
__sbit        __at   (0xF6) P76;
__sbit        __at   (0xF7) P77;

//如下特殊功能寄存器位于扩展RAM区域
//访问这些寄存器,需先将P_SW2的BIT7设置为1,才可正常读写
#define P0PU        ((*(__xdata volatile unsigned char *)(0xFE10))
#define P1PU        ((*(__xdata volatile unsigned char *)(0xFE11))
#define P2PU        ((*(__xdata volatile unsigned char *)(0xFE12))
#define P3PU        ((*(__xdata volatile unsigned char *)(0xFE13))
#define P4PU        ((*(__xdata volatile unsigned char *)(0xFE14))
#define P5PU        ((*(__xdata volatile unsigned char *)(0xFE15))
#define P6PU        ((*(__xdata volatile unsigned char *)(0xFE16))
#define P7PU        ((*(__xdata volatile unsigned char *)(0xFE17))
#define P0NCS       ((*(__xdata volatile unsigned char *)(0xFE18))
#define P1NCS       ((*(__xdata volatile unsigned char *)(0xFE19))
#define P2NCS       ((*(__xdata volatile unsigned char *)(0xFE1A))
#define P3NCS       ((*(__xdata volatile unsigned char *)(0xFE1B))
#define P4NCS       ((*(__xdata volatile unsigned char *)(0xFE1C))
#define P5NCS       ((*(__xdata volatile unsigned char *)(0xFE1D))
#define P6NCS       ((*(__xdata volatile unsigned char *)(0xFE1E))
#define P7NCS       ((*(__xdata volatile unsigned char *)(0xFE1F))

//系统管理特殊功能寄存器
__sfr         __at   (0x87) PCON;
#define SMOD        0x80
#define SMOD0       0x40
#define LVDF        0x20
#define POF         0x10
#define GF1         0x08
#define GF0         0x04
#define PD          0x02
#define IDL         0x01
__sfr         __at   (0x8E) AUXR;
#define T0x12       0x80
#define T1x12       0x40
#define UART_M0x6   0x20
#define T2R         0x10
#define T2_CT       0x08
#define T2x12       0x04
#define EXTRAM      0x02
#define S1ST2       0x01
__sfr        __at   (0x97) AUXR2;
#define TXLNRX      0x10
__sfr    __at   (0xa1) BUS_SPEED;
__sfr    __at   (0xa2) P_SW1    ;
__sfr    __at   (0xba) P_SW2    ;
#define EAXFR       0x80
__sfr       __at   (0xBB) VOCTRL;
__sfr       __at   (0xFF) RSTCFG;

//如下特殊功能寄存器位于扩展RAM区域
//访问这些寄存器,需先将P_SW2的BIT7设置为1,才可正常读写
#define CKSEL       ((*(__xdata volatile unsigned char *)(0xFE00))
#define CLKDIV      ((*(__xdata volatile unsigned char *)(0xFE01))
#define IRC24MCR    ((*(__xdata volatile unsigned char *)(0xFE02))
#define XOSCCR      ((*(__xdata volatile unsigned char *)(0xFE03))
#define IRC32KCR    ((*(__xdata volatile unsigned char *)(0xFE04))

//中断特殊功能寄存器
__sfr         __at   (0xa8) IE  ;
__sbit        __at   (0xAF) EA   ;
__sbit        __at   (0xAE) ELVD ;
__sbit        __at   (0xAD) EADC ;
__sbit        __at   (0xAC) ES   ;
__sbit        __at   (0xAB) ET1  ;
__sbit        __at   (0xAA) EX1  ;
__sbit        __at   (0xA9) ET0  ;
__sbit        __at   (0xA8) EX0  ;
__sfr         __at   (0xAF) IE2 ;
#define ET4         0x40
#define ET3         0x20
#define ES4         0x10
#define ES3         0x08
#define ET2         0x04
#define ESPI        0x02
#define ES2         0x01
__sfr         __at   (0xb8) IP   ;
__sbit        __at   (0xBF) PPCA ;
__sbit        __at   (0xBE) PLVD ;
__sbit        __at   (0xBD) PADC ;
__sbit        __at   (0xBC) PS   ;
__sbit        __at   (0xBB) PT1  ;
__sbit        __at   (0xBA) PX1  ;
__sbit        __at   (0xB9) PT0  ;
__sbit        __at   (0xB8) PX0  ;
__sfr         __at   (0xB5) IP2  ;
#define PI2C        0x40
#define PCMP        0x20
#define PX4         0x10
#define PPWMFD      0x08
#define PPWM        0x04
#define PSPI        0x02
#define PS2         0x01
__sfr          __at   (0xB7) IPH;
#define PPCAH       0x80
#define PLVDH       0x40
#define PADCH       0x20
#define PSH         0x10
#define PT1H        0x08
#define PX1H        0x04
#define PT0H        0x02
#define PX0H        0x01
__sfr         __at   (0xB6) IP2H;
#define PI2CH       0x40
#define PCMPH       0x20
#define PX4H        0x10
#define PPWMFDH     0x08
#define PPWMH       0x04
#define PSPIH       0x02
#define PS2H        0x01
__sfr      __at   (0x8F) INTCLKO;
#define EX4         0x40
#define EX3         0x20
#define EX2         0x10
#define T2CLKO      0x04
#define T1CLKO      0x02
#define T0CLKO      0x01
__sfr     __at   (0xEF) AUXINTIF;
#define INT4IF      0x40
#define INT3IF      0x20
#define INT2IF      0x10
#define T4IF        0x04
#define T3IF        0x02
#define T2IF        0x01

//定时器特殊功能寄存器
__sfr          __at   (0x88) TCON;
__sbit         __at   (0x8F) TF1;
__sbit         __at   (0x8E) TR1;
__sbit         __at   (0x8D) TF0;
__sbit         __at   (0x8C) TR0;
__sbit         __at   (0x8B) IE1;
__sbit         __at   (0x8A) IT1;
__sbit         __at   (0x89) IE0;
__sbit         __at   (0x88) IT0;
__sfr          __at   (0x89) TMOD;
#define T1_GATE     0x80
#define T1_CT       0x40
#define T1_M1       0x20
#define T1_M0       0x10
#define T0_GATE     0x08
#define T0_CT       0x04
#define T0_M1       0x02
#define T0_M0       0x01
__sfr        __at   (0x8A) TL0  ;
__sfr        __at   (0x8B) TL1  ;
__sfr        __at   (0x8C) TH0  ;
__sfr        __at   (0x8D) TH1  ;
__sfr        __at   (0xD1) T4T3M;
#define T4R         0x80
#define T4_CT       0x40
#define T4x12       0x20
#define T4CLKO      0x10
#define T3R         0x08
#define T3_CT       0x04
#define T3x12       0x02
#define T3CLKO      0x01
__sfr        __at   (0xD2) T4H  ;
__sfr        __at   (0xD3) T4L  ;
__sfr        __at   (0xD4) T3H  ;
__sfr        __at   (0xD5) T3L  ;
__sfr        __at   (0xD6) T2H  ;
__sfr        __at   (0xD7) T2L  ;
__sfr        __at   (0xD2) TH4  ;
__sfr        __at   (0xD3) TL4  ;
__sfr        __at   (0xD4) TH3  ;
__sfr        __at   (0xD5) TL3  ;
__sfr        __at   (0xD6) TH2  ;
__sfr        __at   (0xD7) TL2  ;
__sfr        __at   (0xAA) WKTCL;
__sfr        __at   (0xAB) WKTCH;
#define WKTEN       0x80
__sfr    __at   (0xC1) WDT_CONTR;
#define WDT_FLAG    0x80
#define EN_WDT      0x20
#define CLR_WDT     0x10
#define IDL_WDT     0x08

//串行口特殊功能寄存器
__sfr          __at   (0x98) SCON;
__sbit         __at   (0x9F) SM0;
__sbit         __at   (0x9E) SM1;
__sbit         __at   (0x9D) SM2;
__sbit         __at   (0x9C) REN;
__sbit         __at   (0x9B) TB8;
__sbit         __at   (0x9A) RB8;
__sbit         __at   (0x99) TI ;
__sbit         __at   (0x98) RI ;
__sfr          __at   (0x99) SBUF ;
__sfr          __at   (0x9a) S2CON;
#define S2SM0       0x80
#define S2ST4       0x40
#define S2SM2       0x20
#define S2REN       0x10
#define S2TB8       0x08
#define S2RB8       0x04
#define S2TI        0x02
#define S2RI        0x01
__sfr        __at   (0x9B) S2BUF;
__sfr        __at   (0xAC) S3CON;
#define S3SM0       0x80
#define S3ST4       0x40
#define S3SM2       0x20
#define S3REN       0x10
#define S3TB8       0x08
#define S3RB8       0x04
#define S3TI        0x02
#define S3RI        0x01
__sfr        __at   (0xAD) S3BUF;
__sfr        __at   (0x84) S4CON;
#define S4SM0       0x80
#define S4ST4       0x40
#define S4SM2       0x20
#define S4REN       0x10
#define S4TB8       0x08
#define S4RB8       0x04
#define S4TI        0x02
#define S4RI        0x01
__sfr        __at   (0x85) S4BUF;
__sfr        __at   (0xA9) SADDR;
__sfr        __at   (0xB9) SADEN;

//ADC 特殊功能寄存器
__sfr    __at   (0xBC) ADC_CONTR;
#define ADC_POWER   0x80
#define ADC_START   0x40
#define ADC_FLAG    0x20
__sfr     __at   (0xBD) ADC_RES ;
__sfr     __at   (0xBE) ADC_RESL;
__sfr     __at   (0xDE) ADCCFG  ;
#define ADC_RESFMT  0x20

//SPI 特殊功能寄存器
__sfr       __at   (0xCD) SPSTAT;
#define SPIF        0x80
#define WCOL        0x40
__sfr        __at   (0xCE) SPCTL;
#define SSIG        0x80
#define SPEN        0x40
#define DORD        0x20
#define MSTR        0x10
#define CPOL        0x08
#define CPHA        0x04
__sfr        __at   (0xCF) SPDAT;

//IAP/ISP 特殊功能寄存器
__sfr    __at   (0xC2) IAP_DATA ;
__sfr    __at   (0xC3) IAP_ADDRH;
__sfr    __at   (0xC4) IAP_ADDRL;
__sfr    __at   (0xC5) IAP_CMD  ;
#define IAP_IDL     0x00
#define IAP_READ    0x01
#define IAP_WRITE   0x02
#define IAP_ERASE   0x03
__sfr    __at   (0xC6) IAP_TRIG ;
__sfr    __at   (0xC7) IAP_CONTR;
#define IAPEN       0x80
#define SWBS        0x40
#define SWRST       0x20
#define CMD_FAIL    0x10
__sfr    __at   (0xC2) ISP_DATA ;
__sfr    __at   (0xC3) ISP_ADDRH;
__sfr    __at   (0xC4) ISP_ADDRL;
__sfr    __at   (0xC5) ISP_CMD  ;
__sfr    __at   (0xC6) ISP_TRIG ;
__sfr    __at   (0xC7) ISP_CONTR;

//比较器特殊功能寄存器
__sfr       __at   (0xE6) CMPCR1;
#define CMPEN       0x80
#define CMPIF       0x40
#define PIE         0x20
#define NIE         0x10
#define PIS         0x08
#define NIS         0x04
#define CMPOE       0x02
#define CMPRES      0x01
__sfr       __at   (0xE7) CMPCR2;
#define INVCMPO     0x80
#define DISFLT      0x40

//PCA/PWM 特殊功能寄存器
__sfr         __at   (0xD8) CCON;
__sbit        __at   (0xDF) CF  ;
__sbit        __at   (0xDE) CR  ;
__sbit        __at   (0xDD) CCF3;
__sbit        __at   (0xDA) CCF2;
__sbit        __at   (0xD9) CCF1;
__sbit        __at   (0xD8) CCF0;
__sfr         __at   (0xD9) CMOD;
#define CIDL        0x80
#define ECF         0x01
__sfr       __at   (0xE9)CL    ;
__sfr       __at   (0xF9)CH    ;
__sfr       __at   (0xDA)CCAPM0;
#define ECOM0       0x40
#define CCAPP0      0x20
#define CCAPN0      0x10
#define MAT0        0x08
#define TOG0        0x04
#define PWM0        0x02
#define ECCF0       0x01
__sfr       __at   (0xDB) CCAPM1;
#define ECOM1       0x40
#define CCAPP1      0x20
#define CCAPN1      0x10
#define MAT1        0x08
#define TOG1        0x04
#define PWM1        0x02
#define ECCF1       0x01
__sfr       __at   (0xDC) CCAPM2;
#define ECOM2       0x40
#define CCAPP2      0x20
#define CCAPN2      0x10
#define MAT2        0x08
#define TOG2        0x04
#define PWM2        0x02
#define ECCF2       0x01
__sfr       __at   (0xDD) CCAPM3;
#define ECOM3       0x40
#define CCAPP3      0x20
#define CCAPN3      0x10
#define MAT3        0x08
#define TOG3        0x04
#define PWM3        0x02
#define ECCF3       0x01
__sfr     __at   (0xEA) CCAP0L  ;
__sfr     __at   (0xEB) CCAP1L  ;
__sfr     __at   (0xEC) CCAP2L  ;
__sfr     __at   (0xED) CCAP3L  ;
__sfr     __at   (0xFA) CCAP0H  ;
__sfr     __at   (0xFB) CCAP1H  ;
__sfr     __at   (0xFC) CCAP2H  ;
__sfr     __at   (0xFD) CCAP3H  ;
__sfr     __at   (0xF2) PCA_PWM0;
__sfr     __at   (0xF3) PCA_PWM1;
__sfr     __at   (0xF4) PCA_PWM2;
__sfr     __at   (0xF5) PCA_PWM3;

//增强型PWM波形发生器特殊功能寄存器
__sfr       __at   (0xF1) PWMCFG;
#define CBIF        0x80
#define ETADC       0x40
__sfr        __at   (0xF6) PWMIF;
#define C7IF        0x80
#define C6IF        0x40
#define C5IF        0x20
#define C4IF        0x10
#define C3IF        0x08
#define C2IF        0x04
#define C1IF        0x02
#define C0IF        0x01
__sfr      __at   (0xF7) PWMFDCR;
#define INVCMP      0x80
#define INVIO       0x40
#define ENFD        0x20
#define FLTFLIO     0x10
#define EFDI        0x08
#define FDCMP       0x04
#define FDIO        0x02
#define FDIF        0x01
__sfr        __at   (0xFE) PWMCR;
#define ENPWM       0x80
#define ECBI        0x40

//如下特殊功能寄存器位于扩展RAM区域
//访问这些寄存器,需先将P_SW2的BIT7设置为1,才可正常读写
#define PWMC        (*(__xdata volatile unsigned int *)(0xFFF0))
#define PWMCH       (*(__xdata volatile unsigned char *)(0xFFF0))
#define PWMCL       (*(__xdata volatile unsigned char *)(0xFFF1))
#define PWMCKS      (*(__xdata volatile unsigned char *)(0xFFF2))
#define TADCP       (*(__xdata volatile unsigned char *)(0xFFF3))
#define TADCPH      (*(__xdata volatile unsigned char *)(0xFFF3))
#define TADCPL      (*(__xdata volatile unsigned char *)(0xFFF4))
#define PWM0T1      (*(__xdata volatile unsigned int *)(0xFF00))
#define PWM0T1H     (*(__xdata volatile unsigned char *)(0xFF00))
#define PWM0T1L     (*(__xdata volatile unsigned char *)(0xFF01))
#define PWM0T2      (*(__xdata volatile unsigned int *)(0xFF02))
#define PWM0T2H     (*(__xdata volatile unsigned char *)(0xFF02))
#define PWM0T2L     (*(__xdata volatile unsigned char *)(0xFF03))
#define PWM0CR      (*(__xdata volatile unsigned char *)(0xFF04))
#define PWM0HLD     (*(__xdata volatile unsigned char *)(0xFF05))
#define PWM1T1      (*(__xdata volatile unsigned int *)(0xFF10))
#define PWM1T1H     (*(__xdata volatile unsigned char *)(0xFF10))
#define PWM1T1L     (*(__xdata volatile unsigned char *)(0xFF11))
#define PWM1T2      (*(__xdata volatile unsigned int *)(0xFF12))
#define PWM1T2H     (*(__xdata volatile unsigned char *)(0xFF12))
#define PWM1T2L     (*(__xdata volatile unsigned char *)(0xFF13))
#define PWM1CR      (*(__xdata volatile unsigned char *)(0xFF14))
#define PWM1HLD     (*(__xdata volatile unsigned char *)(0xFF15))
#define PWM2T1      (*(__xdata volatile unsigned int *)(0xFF20))
#define PWM2T1H     (*(__xdata volatile unsigned char *)(0xFF20))
#define PWM2T1L     (*(__xdata volatile unsigned char *)(0xFF21))
#define PWM2T2      (*(__xdata volatile unsigned int *)(0xFF22))
#define PWM2T2H     (*(__xdata volatile unsigned char *)(0xFF22))
#define PWM2T2L     (*(__xdata volatile unsigned char *)(0xFF23))
#define PWM2CR      (*(__xdata volatile unsigned char *)(0xFF24))
#define PWM2HLD     (*(__xdata volatile unsigned char *)(0xFF25))
#define PWM3T1      (*(__xdata volatile unsigned int *)(0xFF30))
#define PWM3T1H     (*(__xdata volatile unsigned char *)(0xFF30))
#define PWM3T1L     (*(__xdata volatile unsigned char *)(0xFF31))
#define PWM3T2      (*(__xdata volatile unsigned int *)(0xFF32))
#define PWM3T2H     (*(__xdata volatile unsigned char *)(0xFF32))
#define PWM3T2L     (*(__xdata volatile unsigned char *)(0xFF33))
#define PWM3CR      (*(__xdata volatile unsigned char *)(0xFF34))
#define PWM3HLD     (*(__xdata volatile unsigned char *)(0xFF35))
#define PWM4T1      (*(__xdata volatile unsigned int *)(0xFF40))
#define PWM4T1H     (*(__xdata volatile unsigned char *)(0xFF40))
#define PWM4T1L     (*(__xdata volatile unsigned char *)(0xFF41))
#define PWM4T2      (*(__xdata volatile unsigned int *)(0xFF42))
#define PWM4T2H     (*(__xdata volatile unsigned char *)(0xFF42))
#define PWM4T2L     (*(__xdata volatile unsigned char *)(0xFF43))
#define PWM4CR      (*(__xdata volatile unsigned char *)(0xFF44))
#define PWM4HLD     (*(__xdata volatile unsigned char *)(0xFF45))
#define PWM5T1      (*(__xdata volatile unsigned int *)(0xFF50))
#define PWM5T1H     (*(__xdata volatile unsigned char *)(0xFF50))
#define PWM5T1L     (*(__xdata volatile unsigned char *)(0xFF51))
#define PWM5T2      (*(__xdata volatile unsigned int *)(0xFF52))
#define PWM5T2H     (*(__xdata volatile unsigned char *)(0xFF52))
#define PWM5T2L     (*(__xdata volatile unsigned char *)(0xFF53))
#define PWM5CR      (*(__xdata volatile unsigned char *)(0xFF54))
#define PWM5HLD     (*(__xdata volatile unsigned char *)(0xFF55))
#define PWM6T1      (*(__xdata volatile unsigned int *)(0xFF60))
#define PWM6T1H     (*(__xdata volatile unsigned char *)(0xFF60))
#define PWM6T1L     (*(__xdata volatile unsigned char *)(0xFF61))
#define PWM6T2      (*(__xdata volatile unsigned int *)(0xFF62))
#define PWM6T2H     (*(__xdata volatile unsigned char *)(0xFF62))
#define PWM6T2L     (*(__xdata volatile unsigned char *)(0xFF63))
#define PWM6CR      (*(__xdata volatile unsigned char *)(0xFF64))
#define PWM6HLD     (*(__xdata volatile unsigned char *)(0xFF65))
#define PWM7T1      (*(__xdata volatile unsigned int *)(0xFF70))
#define PWM7T1H     (*(__xdata volatile unsigned char *)(0xFF70))
#define PWM7T1L     (*(__xdata volatile unsigned char *)(0xFF71))
#define PWM7T2      (*(__xdata volatile unsigned int *)(0xFF72))
#define PWM7T2H     (*(__xdata volatile unsigned char *)(0xFF72))
#define PWM7T2L     (*(__xdata volatile unsigned char *)(0xFF73))
#define PWM7CR      (*(__xdata volatile unsigned char *)(0xFF74))
#define PWM7HLD     (*(__xdata volatile unsigned char *)(0xFF75))

//I2C特殊功能寄存器
//如下特殊功能寄存器位于扩展RAM区域
//访问这些寄存器,需先将P_SW2的BIT7设置为1,才可正常读写
#define I2CCFG      (*(__xdata volatile unsigned char *)(0xFE80))
#define ENI2C       0x80
#define MSSL        0x40
#define I2CMSCR     (*(__xdata volatile unsigned char *)(0xFE81))
#define EMSI        0x80
#define I2CMSST     (*(__xdata volatile unsigned char *)(0xFE82))
#define MSBUSY      0x80
#define MSIF        0x40
#define MSACKI      0x02
#define MSACKO      0x01
#define I2CSLCR     (*(__xdata volatile unsigned char *)(0xFE83))
#define ESTAI       0x40
#define ERXI        0x20
#define ETXI        0x10
#define ESTOI       0x08
#define SLRST       0x01
#define I2CSLST     (*(__xdata volatile unsigned char *)(0xFE84))
#define SLBUSY      0x80
#define STAIF       0x40
#define RXIF        0x20
#define TXIF        0x10
#define STOIF       0x08
#define TXING       0x04
#define SLACKI      0x02
#define SLACKO      0x01
#define I2CSLADR    (*(__xdata volatile unsigned char *)(0xFE85))
#define I2CTXD      (*(__xdata volatile unsigned char *)(0xFE86))
#define I2CRXD      (*(__xdata volatile unsigned char *)(0xFE87))

/////////////////////////////////////////////////

#endif

