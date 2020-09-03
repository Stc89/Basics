;------------------------------------------------------------------------------
; Copyright (C) 2020 STC Ltd. All rights reserved.
; Declarations for STC8 family based microcontroller.
;
; Devices:         STC8 family
;------------------------------------------------------------------------------
$SAVE
$NOLIST

P0        DATA 080H
P07       BIT  P0.7
P06       BIT  P0.6
P05       BIT  P0.5
P04       BIT  P0.4
P03       BIT  P0.3
P02       BIT  P0.2
P01       BIT  P0.1
P00       BIT  P0.0

SP        DATA 081H
DPL       DATA 082H
DPH       DATA 083H
S4CON     DATA 084H
S4SM0     EQU  (1 << 7)
S4ST4     EQU  (1 << 6)
S4SM2     EQU  (1 << 5)
S4REN     EQU  (1 << 4)
S4TB8     EQU  (1 << 3)
S4RB8     EQU  (1 << 2)
S4TI      EQU  (1 << 1)
S4RI      EQU  1

S4BUF     DATA 085H
PCON      DATA 087H
SMOD      EQU  (1 << 7)
SMOD0     EQU  (1 << 6)
LVDF      EQU  (1 << 5)
POF       EQU  (1 << 4)
GF1       EQU  (1 << 3)
GF0       EQU  (1 << 2)
PD        EQU  (1 << 1)
IDL       EQU  1

TCON      DATA 088H
TF1       BIT  TCON.7
TR1       BIT  TCON.6
TF0       BIT  TCON.5
TR0       BIT  TCON.4
IE1       BIT  TCON.3
IT1       BIT  TCON.2
IE0       BIT  TCON.1
IT0       BIT  TCON.0

TMOD      DATA 089H
GATE1     EQU  (1 << 7)
CT1       EQU  (1 << 6)
M11       EQU  (1 << 5)
M10       EQU  (1 << 4)
GATE0     EQU  (1 << 3)
CT0       EQU  (1 << 2)
M01       EQU  (1 << 1)
M00       EQU  1

TL0       DATA 08AH
TL1       DATA 08BH
TH0       DATA 08CH
TH1       DATA 08DH
AUXR      DATA 08EH
T012      EQU  (1 << 7)
T1x12     EQU  (1 << 6)
UART_M06  EQU  (1 << 5)
T2R       EQU  (1 << 4)
T2_CT    EQU  (1 << 3)
T2x12     EQU  (1 << 2)
EXTRAM    EQU  (1 << 1)
S1ST2     EQU  1

INTCLKO   DATA 08FH
EX4       EQU  (1 << 6)
EX3       EQU  (1 << 5)
EX2       EQU  (1 << 4)
T2CLKO    EQU  (1 << 2)
T1CLKO    EQU  (1 << 1)
T0CLKO    EQU  1

P1        DATA 090H
P17       BIT  P1.7
P16       BIT  P1.6
P15       BIT  P1.5
P14       BIT  P1.4
P13       BIT  P1.3
P12       BIT  P1.2
P11       BIT  P1.1
P10       BIT  P1.0

P1M1      DATA 091H
P1M0      DATA 092H
P0M1      DATA 093H
P0M0      DATA 094H
P2M1      DATA 095H
P2M0      DATA 096H
SCON      DATA 098H
SM0_FE    BIT  SCON.7
SM1       BIT  SCON.6
SM2       BIT  SCON.5
REN       BIT  SCON.4
TB8       BIT  SCON.3
RB8       BIT  SCON.2
TI        BIT  SCON.1
RI        BIT  SCON.0


SBUF      DATA 099H
S2CON     DATA 09AH
S2SM0     EQU  (1 << 7)
S2SM2     EQU  (1 << 5)
S2REN     EQU  (1 << 4)
S2TB8     EQU  (1 << 3)
S2RB8     EQU  (1 << 2)
S2TI      EQU  (1 << 1)
S2RI      EQU  1

S2BUF     DATA 09BH
LIRTRIM   DATA 09EH
LIRTRIMV  EQU  003H

IRTRIM    DATA 09FH
P2        DATA 0A0H
P27       BIT  P2.7
P26       BIT  P2.6
P25       BIT  P2.5
P24       BIT  P2.4
P23       BIT  P2.3
P22       BIT  P2.2
P21       BIT  P2.1
P20       BIT  P2.0

BUS_SPEED DATA 0A1H
RW_S      EQU  (3 << 6)
SPEED     EQU  3

P_SW1     DATA 0A2H
S1_S      EQU  (3 << 6)
CCP_S     EQU  (3 << 4)
SPI_S     EQU  (3 << 2)

IE        DATA 0A8H
EA        BIT  IE.7
ELVD      BIT  IE.6
EADC      BIT  IE.5
ES        BIT  IE.4
ET1       BIT  IE.3
EX1       BIT  IE.2
ET0       BIT  IE.1
EX0       BIT  IE.0

SADDR     DATA 0A9H
WKTCL     DATA 0AAH
WKTCH     DATA 0ABH
WKTEN     EQU  (1 << 7)
S3CON     DATA 0ACH
S3SM0     EQU  (1 << 7)
S3ST3     EQU  (1 << 6)
S3SM2     EQU  (1 << 5)
S3REN     EQU  (1 << 4)
S3TB8     EQU  (1 << 3)
S3RB8     EQU  (1 << 2)
S3TI      EQU  (1 << 1)
S3RI      EQU  1

S3BUF     DATA 0ADH
TA        DATA 0AEH
IE2       DATA 0AFH
ECAN      EQU  (1 << 7)
ET4       EQU  (1 << 6)
ET3       EQU  (1 << 5)
ES4       EQU  (1 << 4)
ES3       EQU  (1 << 3)
ET2       EQU  (1 << 2)
ESPI      EQU  (1 << 1)
ES2       EQU  1

P3        DATA 0B0H
P37       BIT  P3.7
P36       BIT  P3.6
P35       BIT  P3.5
P34       BIT  P3.4
P33       BIT  P3.3
P32       BIT  P3.2
P31       BIT  P3.1
P30       BIT  P3.0

P3M1      DATA 0B1H
P3M0      DATA 0B2H
P4M1      DATA 0B3H
P4M0      DATA 0B4H
IP2       DATA 0B5H
PCAN      EQU  (1 << 7)
PI2C      EQU  (1 << 6)
PCMP      EQU  (1 << 5)
PX4       EQU  (1 << 4)
PPWMFD    EQU  (1 << 3)
PPWM      EQU  (1 << 2)
PSPI      EQU  (1 << 1)
PS2       EQU  1

IP2H      DATA 0B6H
PCANH     EQU  (1 << 7)
PI2CH     EQU  (1 << 6)
PCMPH     EQU  (1 << 5)
PX4H      EQU  (1 << 4)
PPWMFDH   EQU  (1 << 3)
PPWMH     EQU  (1 << 2)
PSPIH     EQU  (1 << 1)
PS2H      EQU  1

IPH       DATA 0B7H
PPCAH     EQU  (1 << 7)
PLVDH     EQU  (1 << 6)
PADCH     EQU  (1 << 5)
PSH       EQU  (1 << 4)
PT1H      EQU  (1 << 3)
PX1H      EQU  (1 << 2)
PT0H      EQU  (1 << 1)
PX0H      EQU  1

IP        DATA 0B8H
PPCA      BIT  IP.7
PLVD      BIT  IP.6
PADC      BIT  IP.5
PS        BIT  IP.4
PT1       BIT  IP.3
PX1       BIT  IP.2
PT0       BIT  IP.1
PX0       BIT  IP.0

SADEN     DATA 0B9H
P_SW2     DATA 0BAH
EAXFR     EQU  (1 << 7)
CAN_S     EQU  (1 << 6)
I2C_S     EQU  (3 << 4)
CMPO_S    EQU  (1 << 3)
S4_S      EQU  (1 << 2)
S3_S      EQU  (1 << 1)
S2_S      EQU  1

VOCTRL    DATA 0BBH
SCC       EQU  (1 << 7)

ADC_CONTR DATA 0BCH
DC_POWER  EQU  (1 << 7)
ADC_START EQU  (1 << 6)
ADC_FLAG  EQU  (1 << 5)
ADC_CHS   EQU  0FH

ADC_RES   DATA 0BDH
ADC_RESL  DATA 0BEH
ADC_RESH  DATA 0BFH
P4        DATA 0C0H
P47       BIT  P4.7
P46       BIT  P4.6
P45       BIT  P4.5
P44       BIT  P4.4
P43       BIT  P4.3
P42       BIT  P4.2
P41       BIT  P4.1
P40       BIT  P4.0

WDT_CONTR DATA 0C1H
WDT_FLAG  EQU  (1 << 7)
EN_WDT    EQU  (1 << 5)
CLR_WDT   EQU  (1 << 4)
IDL_WDT   EQU  (1 << 3)
WDT_PS    EQU  07H


IAP_DATA  DATA 0C2H
IAP_ADDRH DATA 0C3H
IAP_ADDRL DATA 0C4H
IAP_CMD   DATA 0C5H
CMD       EQU  003H

IAP_TRIG  DATA 0C6H
IAP_CONTR DATA 0C7H
IAPEN     EQU  (1 << 7)
SWBS      EQU  (1 << 6)
SWRST     EQU  (1 << 5)
CMD_FAIL  EQU  (1 << 4)
IAP_WT    EQU  07H

P5        DATA 0C8H
P57       BIT  P5.7
P56       BIT  P5.6
P55       BIT  P5.5
P54       BIT  P5.4
P53       BIT  P5.3
P52       BIT  P5.2
P51       BIT  P5.1
P50       BIT  P5.0

P5M1      DATA 0C9H
P5M0      DATA 0CAH
P6M1      DATA 0CBH
P6M0      DATA 0CCH
SPSTAT    DATA 0CDH
SPIF      EQU  (1 << 7)
WCOL      EQU  (1 << 6)

SPCTL     DATA 0CEH
SSIG      EQU  (1 << 7)
SPEN      EQU  (1 << 6)
DORD      EQU  (1 << 5)
MSTR      EQU  (1 << 4)
CPOL      EQU  (1 << 3)
CPHA      EQU  (1 << 2)
SPR       EQU  03H

SPDAT     DATA 0CFH
PSW       DATA 0D0H
CY        BIT  PSW.7
AC        BIT  PSW.6
F0        BIT  PSW.5
RS1       BIT  PSW.4
RS0       BIT  PSW.3
OV        BIT  PSW.2
P         BIT  PSW.0

T4T3M     DATA 0D1H
T4R       EQU  (1 << 7)
T4_CT     EQU  (1 << 6)
T4x12     EQU  (1 << 5)
T4CLKO    EQU  (1 << 4)
T3R       EQU  (1 << 3)
T3_CT     EQU  (1 << 2)
T3x12     EQU  (1 << 1)
T3CLKO    EQU  1

T4H       DATA 0D2H
T4L       DATA 0D3H
T3H       DATA 0D4H
T3L       DATA 0D5H
T2H       DATA 0D6H
T2L       DATA 0D7H
CCON      DATA 0D8H
CF        BIT  CCON.7
CR        BIT  CCON.6
CCF3      BIT  CCON.3
CCF2      BIT  CCON.2
CCF1      BIT  CCON.1
CCF0      BIT  CCON.0

CMOD      DATA 0D9H
CIDL      EQU  (1 << 7)
CPS       EQU  (7 << 1)
ECF       EQU  1

CCAPM0    DATA 0DAH
ECOM0     EQU  (1 << 6)
CCAPP0    EQU  (1 << 5)
CCAPN0    EQU  (1 << 4)
MAT0      EQU  (1 << 3)
TOG0      EQU  (1 << 2)
PWM0      EQU  (1 << 1)
ECCF0     EQU  1

CCAPM1    DATA 0DBH
ECOM1     EQU  (1 << 6)
CCAPP1    EQU  (1 << 5)
CCAPN1    EQU  (1 << 4)
MAT1      EQU  (1 << 3)
TOG1      EQU  (1 << 2)
PWM1      EQU  (1 << 1)
ECCF1     EQU  1

CCAPM2    DATA 0DCH
ECOM2     EQU  (1 << 6)
CCAPP2    EQU  (1 << 5)
CCAPN2    EQU  (1 << 4)
MAT2      EQU  (1 << 3)
TOG2      EQU  (1 << 2)
PWM2      EQU  (1 << 1)
ECCF2     EQU  1

CCAPM3    DATA 0DDH
ECOM3     EQU  (1 << 6)
CCAPP3    EQU  (1 << 5)
CCAPN3    EQU  (1 << 4)
MAT3      EQU  (1 << 3)
TOG3      EQU  (1 << 2)
PWM3      EQU  (1 << 1)
ECCF3     EQU  1

ADCCFG    DATA 0DEH
RESFMT    EQU  (1 << 5)
ADCSPEED  EQU  0FH


IP3       DATA 0DFH
PS4       EQU  (1 << 1)
PS3       EQU  1

ACC       DATA 0E0H
P7M1      DATA 0E1H
P7M0      DATA 0E2H
DPS       DATA 0E3H
ID1       EQU  (1 << 7)
ID0       EQU  (1 << 6)
TSL       EQU  (1 << 5)
AU1       EQU  (1 << 4)
AU0       EQU  (1 << 3)
SEL       EQU  1

DPL1      DATA 0E4H
DPH1      DATA 0E5H
CMPCR1    DATA 0E6H
CMPEN     EQU  (1 << 7)
CMPIF     EQU  (1 << 6)
PIE       EQU  (1 << 5)
NIE       EQU  (1 << 4)
PIS       EQU  (1 << 3)
NIS       EQU  (1 << 2)
CMPOE     EQU  (1 << 1)
CMPRES    EQU  1

CMPCR2    DATA 0E7H
INVCMPO   EQU  (1 << 7)
DISFLT    EQU  (1 << 6)
LCDTY     EQU  03FH

P6        DATA 0E8H
P67       BIT  P6.7
P66       BIT  P6.6
P65       BIT  P6.5
P64       BIT  P6.4
P63       BIT  P6.3
P62       BIT  P6.2
P61       BIT  P6.1
P60       BIT  P6.0

CL        DATA 0E9H
CCAP0L    DATA 0EAH
CCAP1L    DATA 0EBH
CCAP2L    DATA 0ECH
CCAP3L    DATA 0EDH
IP3H      DATA 0EEH
PS4H      EQU  (1 << 1)
PS3H      EQU  1

AUXINTIF  DATA 0EFH
INT4IF    EQU  (1 << 6)
INT3IF    EQU  (1 << 5)
INT2IF    EQU  (1 << 4)
T4IF      EQU  (1 << 2)
T3IF      EQU  (1 << 1)
T2IF      EQU  1

B         DATA 0F0H
PWMCFG    DATA 0F1H
CBIF      EQU  (1 << 7)
ETADC     EQU  (1 << 6)

PCA_PWM0  DATA 0F2H
EBS0      EQU  (3 << 6)
XCCAP0H   EQU  (3 << 4)
XCCAP0L   EQU  (3 << 2)
EPC0H     EQU  (1 << 1)
EPC0L     EQU  1

PCA_PWM1  DATA 0F3H
EBS1      EQU  (3 << 6)
XCCAP1H   EQU  (3 << 4)
XCCAP1L   EQU  (3 << 2)
EPC1H     EQU  (1 << 1)
EPC1L     EQU  1

PCA_PWM2  DATA 0F4H
EBS2      EQU  (3 << 6)
XCCAP2H   EQU  (3 << 4)
XCCAP2L   EQU  (3 << 2)
EPC2H     EQU  (1 << 1)
EPC2L     EQU  1

PCA_PWM3  DATA 0F5H
EBS3      EQU  (3 << 6)
XCCAP3H   EQU  (3 << 4)
XCCAP3L   EQU  (3 << 2)
EPC3H     EQU  (1 << 1)
EPC3L     EQU  1

PWMIF     DATA 0F6H
C7IF      EQU  (1 << 7)
C6IF      EQU  (1 << 6)
C5IF      EQU  (1 << 5)
C4IF      EQU  (1 << 4)
C3IF      EQU  (1 << 3)
C2IF      EQU  (1 << 2)
C1IF      EQU  (1 << 1)
C0IF      EQU  1

PWMFDCR   DATA 0F7H
INVCMP    EQU  (1 << 7)
INVIO     EQU  (1 << 6)
ENFD      EQU  (1 << 5)
FLTFLIO   EQU  (1 << 4)
EFDI      EQU  (1 << 3)
FDCMP     EQU  (1 << 2)
FDIO      EQU  (1 << 1)
FDIF      EQU  1

P7        DATA 0F8H
P77       BIT  P7.7
P76       BIT  P7.6
P75       BIT  P7.5
P74       BIT  P7.4
P73       BIT  P7.3
P72       BIT  P7.2
P71       BIT  P7.1
P70       BIT  P7.0

CH        DATA 0F9H
CCAP0H    DATA 0FAH
CCAP1H    DATA 0FBH
CCAP2H    DATA 0FCH
CCAP3H    DATA 0FDH
PWMCR     DATA 0FEH
ENPWM     EQU  (1 << 7)
ECBI      EQU  (1 << 6)
RSTCFG    DATA 0FFH
ENLVR     EQU  (1 << 6)
P54RST    EQU  (1 << 4)
LVDS      EQU  3

PWMCH     EQU  0FFF0H
PWMCL     EQU  0FFF1H
PWMCKS    EQU  0FFF2H
SELT2     EQU  (1 << 4)
PWM_PS    EQU  0FH

TADCPH    EQU  0FFF3H
TADCPL    EQU  0FFF4H
PWM0T1H   EQU  0FF00H
PWM0T1L   EQU  0FF01H
PWM0T2H   EQU  0FF02H
PWM0T2L   EQU  0FF03H
PWM0CR    EQU  0FF04H
ENC0O     EQU  (1 << 7)
C0INI     EQU  (1 << 6)
C0_S      EQU  (3 << 3)
EC0I      EQU  (1 << 2)
EC0T2SI   EQU  (1 << 1)
EC0T1SI   EQU  1

PWM0HLD   EQU  0FF05H
HC0H      EQU  (1 << 1)
HC0L      EQU  1
PWM1T1H   EQU  0FF10H
PWM1T1L   EQU  0FF11H
PWM1T2H   EQU  0FF12H
PWM1T2L   EQU  0FF13H
PWM1CR    EQU  0FF14H
ENC1O     EQU  (1 << 7)
C1INI     EQU  (1 << 6)
C1_S      EQU  (3 << 3)
EC1I      EQU  (1 << 2)
EC1T2SI   EQU  (1 << 1)
EC1T1SI   EQU  1

PWM1HLD   EQU  0FF15H
HC1H      EQU  (1 << 1)
HC1L      EQU  1
PWM2T1H   EQU  0FF20H
PWM2T1L   EQU  0FF21H
PWM2T2H   EQU  0FF22H
PWM2T2L   EQU  0FF23H
PWM2CR    EQU  0FF24H
ENC2O     EQU  (1 << 7)
C2INI     EQU  (1 << 6)
C2_S      EQU  (3 << 3)
EC2I      EQU  (1 << 2)
EC2T2SI   EQU  (1 << 1)
EC2T1SI   EQU  1

PWM2HLD   EQU  0FF25H
HC2H      EQU  (1 << 1)
HC2L      EQU  1

PWM3T1H   EQU  0FF30H
PWM3T1L   EQU  0FF31H
PWM3T2H   EQU  0FF32H
PWM3T2L   EQU  0FF33H
PWM3CR    EQU  0FF34H
ENC3O     EQU  (1 << 7)
C3INI     EQU  (1 << 6)
C3_S      EQU  (3 << 3)
EC3I      EQU  (1 << 2)
EC3T2SI   EQU  (1 << 1)
EC3T1SI   EQU  1

PWM3HLD   EQU  0FF35H
HC3H      EQU  (1 << 1)
HC3L      EQU  1

PWM4T1H   EQU  0FF40H
PWM4T1L   EQU  0FF41H
PWM4T2H   EQU  0FF42H
PWM4T2L   EQU  0FF43H
PWM4CR    EQU  0FF44H
ENC4O     EQU  (1 << 7)
C4INI     EQU  (1 << 6)
C4_S      EQU  (3 << 3)
EC4I      EQU  (1 << 2)
EC4T2SI   EQU  (1 << 1)
EC4T1SI   EQU  1

PWM4HLD   EQU  0FF45H
HC4H      EQU  (1 << 1)
HC4L      EQU  1
PWM5T1H   EQU  0FF50H
PWM5T1L   EQU  0FF51H
PWM5T2H   EQU  0FF52H
PWM5T2L   EQU  0FF53H
PWM5CR    EQU  0FF54H
ENC5O     EQU  (1 << 7)
C5INI     EQU  (1 << 6)
C5_S      EQU  (3 << 3)
EC5I      EQU  (1 << 2)
EC5T2SI   EQU  (1 << 1)
EC5T1SI   EQU  1

PWM5HLD   EQU  0FF55H
HC5H      EQU  (1 << 1)
HC5L      EQU  1
PWM6T1H   EQU  0FF60H
PWM6T1L   EQU  0FF61H
PWM6T2H   EQU  0FF62H
PWM6T2L   EQU  0FF63H
PWM6CR    EQU  0FF64H
ENC6O     EQU  (1 << 7)
C6INI     EQU  (1 << 6)
C6_S      EQU  (3 << 3)
EC6I      EQU  (1 << 2)
EC6T2SI   EQU  (1 << 1)
EC6T1SI   EQU  1

PWM6HLD   EQU  0FF65H
HC6H      EQU  (1 << 1)
HC6L      EQU  1
PWM7T1H   EQU  0FF70H
PWM7T1L   EQU  0FF71H
PWM7T2H   EQU  0FF72H
PWM7T2L   EQU  0FF73H
PWM7CR    EQU  0FF74H
ENC7O     EQU  (1 << 7)
C7INI     EQU  (1 << 6)
C7_S      EQU  (3 << 3)
EC7I      EQU  (1 << 2)
EC7T2SI   EQU  (1 << 1)
EC7T1SI   EQU  1

PWM7HLD   EQU  0FF75H
HC7H      EQU  (1 << 1)
HC7L      EQU  1
I2CCFG    EQU  0FE80H
ENI2C     EQU  (1 << 7)
MSSL      EQU  (1 << 6)
MSSPEED   EQU  03FH

I2CMSCR   EQU  0FE81H
EMSI      EQU  (1 << 7)
MSCMD     EQU  0FH

I2CMSST   EQU  0FE82H
MSBUSY    EQU  (1 << 7)
MSIF      EQU  (1 << 6)
MSACKI    EQU  (1 << 1)
MSACKO    EQU  1

I2CSLCR   EQU  0FE83H
ESTAI     EQU  (1 << 6)
ERXI      EQU  (1 << 5)
ETXI      EQU  (1 << 4)
ESTOI     EQU  (1 << 3)
SLRST     EQU  1

I2CSLST   EQU  0FE84H
SLBUSY    EQU  (1 << 7)
STAIF     EQU  (1 << 6)
RXIF      EQU  (1 << 5)
TXIF      EQU  (1 << 4)
STOIF     EQU  (1 << 3)
TXING     EQU  (1 << 2)
SLACKI    EQU  (1 << 1)
SLACKO    EQU  1

I2CSLADR  EQU  0FE85H
SLADR     EQU  (07FH << 1)
MA        EQU  1

I2CTXD    EQU  0FE86H
I2CRXD    EQU  0FE87H
I2CMSAUX  EQU  0FE88H
WDTA      EQU  1
P0PU      EQU  0FE10H
P1PU      EQU  0FE11H
P2PU      EQU  0FE12H
P3PU      EQU  0FE13H
P4PU      EQU  0FE14H
P5PU      EQU  0FE15H
P6PU      EQU  0FE16H
P7PU      EQU  0FE17H
P0NCS     EQU  0FE18H
P1NCS     EQU  0FE19H
P2NCS     EQU  0FE1AH
P3NCS     EQU  0FE1BH
P4NCS     EQU  0FE1CH
P5NCS     EQU  0FE1DH
P6NCS     EQU  0FE1EH
P7NCS     EQU  0FE1FH
CKSEL     EQU  0FE00H
MCLKODIV  EQU  (0FH << 4)
MCLKO_S   EQU  (1 << 3)
MCKSEL    EQU  3

CLKDIV    EQU  0FE01H
IRC24MCR  EQU  0FE02H
ENIRC24M  EQU  (1 << 7)
IRC24MST  EQU  1
XOSCCR    EQU  0FE03H
ENXOSC    EQU  (1 << 7)
XITYPE    EQU  (1 << 6)
XOSCST    EQU  1
IRC32KCR  EQU  0FE04H
ENIRC32K  EQU  (1 << 7)
IRC32KST  EQU  1

$RESTORE
