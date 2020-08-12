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

��USB����ΪHID�����豸��

P0��4*4����ɨ�谴��ģ���С���̰������û����޸İ����붨����������ܰ�����

֧�ָ��ϰ��������� CTRL + ALT + DEL������ʶ��3������ͬʱ���£�

ʹ��P6����ʾ����ָʾ��״̬����P60��ӦNumLockָʾ�ƣ�P61��ӦCapsLockָʾ��...

����ʱ, ѡ��ʱ�� 24MHZ (�û��������޸�Ƶ��)��

******************************************/

#include "reg51.h"
#include "intrins.h"
#include "USB.h"

#define MAIN_Fosc       24000000L   //������ʱ��

sfr IE2 = 0xAF;
sfr USBCLK = 0xDC;
sfr USBADR = 0xFC;
sfr USBCON = 0xF4;
sfr USBDAT = 0xEC;

sfr TH2  = 0xD6;
sfr TL2  = 0xD7;
sfr INT_CLKO = 0x8F;
sfr AUXR = 0x8E;
sfr AUXR1 = 0xA2;
sfr P_SW1 = 0xA2;
sfr P_SW2 = 0xBA;
sfr S2CON = 0x9A;
sfr S2BUF = 0x9B;

#define Timer0_Reload   (65536UL -(MAIN_Fosc / 1000))       //Timer 0 �ж�Ƶ��, 1000��/��

#define IRC48MCR (*(unsigned char volatile xdata *)0xfe07)
#define RSTFLAG (*(unsigned char volatile xdata *)0xfe09)

#define KeyIO P0    //P0�������а�������

bit  B_1ms;         //1ms��־
WORD cnt50ms;
WORD KeyCode;       //����, 16������״̬
WORD OldKeyCode;    //�ɼ���״̬
WORD NewKeyCode;    //�¼���״̬

WORD KeyHoldTime;   //��������ʱ��
bit  KeyChangeTemp;
bit  KeyChangeFlag; //����״̬�Ѹ���(USB�ϴ���־)

char code DEVICEDESC[18] =
{
	0x12, //bLength(18);
	0x01, //bDescriptorType(Device);
	0x00,0x02, //bcdUSB(2.00);
	0x00, //bDeviceClass(0);
	0x00, //bDeviceSubClass0);
	0x00, //bDeviceProtocol(0);
	0x40, //bMaxPacketSize0(64);
	0x54,0x53, //idVendor(5354);
	0x80,0x44, //idProduct(4480);
	0x00,0x01, //bcdDevice(1.00);
	0x01, //iManufacturer(1);
	0x02, //iProduct(2);
	0x03, //iSerialNumber(3);
	0x01, //bNumConfigurations(1);
};

char code CONFIGDESC[41] =
{
	0x09, //bLength(9);
	0x02, //bDescriptorType(Configuration);
	0x29,0x00, //wTotalLength(41);
	0x01, //bNumInterfaces(1);
	0x01, //bConfigurationValue(1);
	0x00, //iConfiguration(0);
	0xa0, //bmAttributes(BUSPower);
	0xc8, //MaxPower(400mA);
	
	0x09, //bLength(9);
	0x04, //bDescriptorType(Interface);
	0x00, //bInterfaceNumber(0);
	0x00, //bAlternateSetting(0);
	0x02, //bNumEndpoints(2);
	0x03, //bInterfaceClass(HID);
	0x01, //bInterfaceSubClass(1);
	0x01, //bInterfaceProtocol(1);
	0x00, //iInterface(0);
	
	0x09, //bLength(9);
	0x21, //bDescriptorType(HID);
	0x01,0x10, //bcdHID(1.01);
	0x00, //bCountryCode(0);
	0x01, //bNumDescriptors(1);
	0x22, //bDescriptorType(HID Report);
	0x3f,0x00, //wDescriptorLength(63);
	0x07, //bLength(7);
	0x05, //bDescriptorType(Endpoint);
	0x81, //bEndpointAddress(EndPoint1 as IN);
	0x03, //bmAttributes(Interrupt);
	0x40,0x00, //wMaxPacketSize(64);
	0x0a, //bInterval(10ms);
	0x07, //bLength(7);
	0x05, //bDescriptorType(Endpoint);
	0x01, //bEndpointAddress(EndPoint1 as OUT);
	0x03, //bmAttributes(Interrupt);
	0x40,0x00, //wMaxPacketSize(64);
	0x0a, //bInterval(10ms);
};

char code HIDREPORTDESC[63] =
{
	0x05, 0x01,    // USAGE_PAGE (Generic Desktop)
	0x09, 0x06,    // USAGE (Keyboard)
	0xa1, 0x01,    // COLLECTION (Application)
	0x05, 0x07,    //   USAGE_PAGE (Keyboard)
	0x19, 0xe0,    //   USAGE_MINIMUM (Keyboard LeftControl)
	0x29, 0xe7,    //   USAGE_MAXIMUM (Keyboard Right GUI)
	0x15, 0x00,    //   LOGICAL_MINIMUM (0)
	0x25, 0x01,    //   LOGICAL_MAXIMUM (1)
	0x75, 0x01,    //   REPORT_SIZE (1)
	0x95, 0x08,    //   REPORT_COUNT (8)
	0x81, 0x02,    //   INPUT (Data,Var,Abs)
	0x95, 0x01,    //   REPORT_COUNT (1)
	0x75, 0x08,    //   REPORT_SIZE (8)
	0x81, 0x03,    //   INPUT (Cnst,Var,Abs)
	0x95, 0x05,    //   REPORT_COUNT (5)
	0x75, 0x01,    //   REPORT_SIZE (1)
	0x05, 0x08,    //   USAGE_PAGE (LEDs)
	0x19, 0x01,    //   USAGE_MINIMUM (Num Lock)
	0x29, 0x05,    //   USAGE_MAXIMUM (Kana)
	0x91, 0x02,    //   OUTPUT (Data,Var,Abs)
	0x95, 0x01,    //   REPORT_COUNT (1)
	0x75, 0x03,    //   REPORT_SIZE (3)
	0x91, 0x03,    //   OUTPUT (Cnst,Var,Abs)
	0x95, 0x06,    //   REPORT_COUNT (6)
	0x75, 0x08,    //   REPORT_SIZE (8)
	0x15, 0x00,    //   LOGICAL_MINIMUM (0)
	0x25, 0xFF,    //   LOGICAL_MAXIMUM (255)
	0x05, 0x07,    //   USAGE_PAGE (Keyboard)
	0x19, 0x00,    //   USAGE_MINIMUM (Reserved (no event indicated))
	0x29, 0x65,    //   USAGE_MAXIMUM (Keyboard Application)
	0x81, 0x00,    //   INPUT (Data,Ary,Abs)
	0xc0           // END_COLLECTION
};

char code LANGIDDESC[4] =
{
	0x04,0x03,
	0x09,0x04,
};

char code MANUFACTDESC[8] =
{
	0x08,0x03,
	'S',0,
	'T',0,
	'C',0,
};

char code PRODUCTDESC[30] =
{
	0x1e,0x03,
	'S',0,
	'T',0,
	'C',0,
	' ',0,
	'U',0,
	'S',0,
	'B',0,
	' ',0,
	'D',0,
	'e',0,
	'v',0,
	'i',0,
	'c',0,
	'e',0,
};

char code KeyBoardCode[16] = {
	0x53,	//0: Num Lock��
	0xFF,	//1: NULL - ��Ctrl��
	0xFF,	//2: NULL - ��ALT��
	0x2A,	//3: BackSpace

	0x5F,	//4: 7��
	0x60,	//5: 8��
	0x61,	//6: 9��
	0x62,	//7: 0��

	0x5C,	//8: 4��
	0x5D,	//9: 5��
	0x5E,	//A: 6��
	0x63,	//B: DEL��

	0x59,	//C: 1��
	0x5A,	//D: 2��
	0x5B,	//E: 3��
	0x58,	//F: �س���
};

char code SetReport[8] = {0x21,0x09,0x00,0x02,0x00,0x00,0x01,0x00};

void UsbInit();
BYTE ReadReg(BYTE addr);
void WriteReg(BYTE addr, BYTE dat);
BYTE ReadFifo(BYTE fifo, BYTE *pdat);
void WriteFifo(BYTE fifo, BYTE *pdat, BYTE cnt);
void Timer0_Config(WORD tReload);
void KeyScan(void);
void SendKeyStatus(void);

/******************** ������ **************************/
void main()
{
	BYTE i;
	
	P0M1 = 0;   P0M0 = 0;   //����Ϊ׼˫���
	P1M1 = 0;   P1M0 = 0;   //����Ϊ׼˫���
	P2M1 = 0;   P2M0 = 0;   //����Ϊ׼˫���
	P3M1 = 0;   P3M0 = 0;   //����Ϊ׼˫���
	P4M1 = 0;   P4M0 = 0;   //����Ϊ׼˫���
	P5M1 = 0;   P5M0 = 0;   //����Ϊ׼˫���
	P6M1 = 0;   P6M0 = 0;   //����Ϊ׼˫���
	P7M1 = 0;   P7M0 = 0;   //����Ϊ׼˫���
	
	Timer0_Config(Timer0_Reload);
	UsbInit();
	EA = 1;

   for(i=0;i<8;i++)
  {
	 HidInput[i]=0;
	}

	P40 = 0;      //��P6��LED��Դ
	while (1)
	{
		if(B_1ms)   //1ms��
		{
			B_1ms = 0;
		
			if(++cnt50ms >= 30)     //30msɨ��һ�����м���
			{
				cnt50ms = 0;
				KeyScan();
			}

			if(KeyChangeFlag)   //����״̬�����仯
			{
				KeyChangeFlag = 0;
				SendKeyStatus();
			}
		}
	}
}

BYTE ReadReg(BYTE addr)
{
	BYTE dat;
	while (USBADR & 0x80);
	USBADR = addr | 0x80;
	while (USBADR & 0x80);
	dat = USBDAT;
	return dat;
}

void WriteReg(BYTE addr, BYTE dat)
{
	while (USBADR & 0x80);
	USBADR = addr & 0x7f;
	USBDAT = dat;
}

BYTE ReadFifo(BYTE fifo, BYTE *pdat)
{
	BYTE cnt;
	BYTE ret;
	ret = cnt = ReadReg(COUNT0);
	while (cnt--)
	{
		*pdat++ = ReadReg(fifo);
	}
	return ret;
}

void WriteFifo(BYTE fifo, BYTE *pdat, BYTE cnt)
{
	while (cnt--)
	{
		WriteReg(fifo, *pdat++);
	}
}

void UsbInit()
{
	P3M0 = 0x00;
	P3M1 = 0x03;
	P_SW2 |= 0x80;
	RSTFLAG = 0x07;
	IRC48MCR = 0x80;
	while (!(IRC48MCR & 0x01));
	P_SW2 &= ~0x80;
	USBCLK = 0x00;
	USBCON = 0x90;
	WriteReg(FADDR, 0x00);
	WriteReg(POWER, 0x08);
	WriteReg(INTRIN1E, 0x3f);
	WriteReg(INTROUT1E, 0x3f);
	WriteReg(INTRUSBE, 0x00);
	WriteReg(POWER, 0x01);
	Ep0Stage.bStage = EPIDLE;
	IE2 |= 0x80;
}

void usb_isr() interrupt 25
{
	BYTE intrusb;
	BYTE intrin;
	BYTE introut;
	BYTE csr;
	BYTE cnt;
	WORD len;
	intrusb = ReadReg(INTRUSB);
	intrin = ReadReg(INTRIN1);
	introut = ReadReg(INTROUT1);
	if (intrusb & RSTIF)
	{
		WriteReg(INDEX, 1);
		WriteReg(INCSR1, INCLRDT);
		WriteReg(INDEX, 1);
		WriteReg(OUTCSR1, OUTCLRDT);
		Ep0Stage.bStage = EPIDLE;
	}
	if (intrin & EP0IF)
	{
		WriteReg(INDEX, 0);
		csr = ReadReg(CSR0);
		if (csr & STSTL)
		{
			WriteReg(CSR0, csr & ~STSTL);
			Ep0Stage.bStage = EPIDLE;
		}
		if (csr & SUEND)
		{
			WriteReg(CSR0, csr | SSUEND);
		}
		switch (Ep0Stage.bStage)
		{
			case EPIDLE:
			if (csr & OPRDY)
			{
				Ep0Stage.bStage = EPSTATUS;
				ReadFifo(FIFO0, (BYTE *)&Setup);
				((BYTE *)&Ep0Stage.wResidue)[0] = Setup.wLengthH;
				((BYTE *)&Ep0Stage.wResidue)[1]= Setup.wLengthL;
				switch (Setup.bmRequestType & REQUEST_MASK)
				{
					case STANDARD_REQUEST:
					switch (Setup.bRequest)
					{
						case SET_ADDRESS:
							WriteReg(FADDR, Setup.wValueL);
						break;
						
						case SET_CONFIG:
							WriteReg(INDEX, 1);
							WriteReg(INCSR2, INMODEIN);
							WriteReg(INMAXP, 8);
							WriteReg(INDEX, 1);
							WriteReg(INCSR2, INMODEOUT);
							WriteReg(OUTMAXP, 8);
							WriteReg(INDEX, 0);
						break;
						
						case GET_DESCRIPTOR:
							Ep0Stage.bStage = EPDATAIN;
							switch (Setup.wValueH)
							{
								case DESC_DEVICE:
									Ep0Stage.pData = DEVICEDESC;
									len = sizeof(DEVICEDESC);
								break;
								
								case DESC_CONFIG:
									Ep0Stage.pData = CONFIGDESC;
									len = sizeof(CONFIGDESC);
								break;
								
								case DESC_STRING:
								switch (Setup.wValueL)
								{
									case 0:
										Ep0Stage.pData = LANGIDDESC;
										len = sizeof(LANGIDDESC);
									break;
									
									case 1:
										Ep0Stage.pData = MANUFACTDESC;
										len = sizeof(MANUFACTDESC);
									break;
									
									case 2:
										Ep0Stage.pData = PRODUCTDESC;
										len = sizeof(PRODUCTDESC);
									break;
									
									default:
										Ep0Stage.bStage = EPSTALL;
									break;
								}
								break;
								
								case DESC_HIDREPORT:
									Ep0Stage.pData = HIDREPORTDESC;
									len = sizeof(HIDREPORTDESC);
								break;
								
								default:
									Ep0Stage.bStage = EPSTALL;
								break;
							}
							if (len < Ep0Stage.wResidue)
							{
								Ep0Stage.wResidue = len;
							}
						break;
							
						default:
							Ep0Stage.bStage = EPSTALL;
						break;
					}
					break;
					
					case CLASS_REQUEST:
						switch (Setup.bRequest)
						{
							case GET_REPORT:
								Ep0Stage.pData = HidFreature;
								Ep0Stage.bStage = EPDATAIN;
							break;
							
							case SET_REPORT:
								Ep0Stage.pData = HidFreature;
								Ep0Stage.bStage = EPDATAOUT;
							break;
							
							case SET_IDLE:
							break;
							
							case GET_IDLE:
							case GET_PROTOCOL:
							case SET_PROTOCOL:
							default:
								Ep0Stage.bStage = EPSTALL;
							break;
						}
					break;
						
					default:
						Ep0Stage.bStage = EPSTALL;
					break;
				}
				
				switch (Ep0Stage.bStage)
				{
					case EPDATAIN:
						WriteReg(CSR0, SOPRDY);
						goto L_Ep0SendData;
					break;
					
					case EPDATAOUT:
						WriteReg(CSR0, SOPRDY);
					break;
					
					case EPSTATUS:
						WriteReg(CSR0, SOPRDY | DATEND);
						Ep0Stage.bStage = EPIDLE;
					break;
					
					case EPSTALL:
						WriteReg(CSR0, SOPRDY | SDSTL);
						Ep0Stage.bStage = EPIDLE;
					break;
				}
			}
			break;
			
			case EPDATAIN:
				if (!(csr & IPRDY))
				{
					L_Ep0SendData:
					cnt = Ep0Stage.wResidue > 64 ? 64 : Ep0Stage.wResidue;
					WriteFifo(FIFO0, Ep0Stage.pData, cnt);
					Ep0Stage.wResidue -= cnt;
					Ep0Stage.pData += cnt;
					if (Ep0Stage.wResidue == 0)
					{
						WriteReg(CSR0, IPRDY | DATEND);
						Ep0Stage.bStage = EPIDLE;
					}
					else
					{
						WriteReg(CSR0, IPRDY);
					}
				}
			break;
			
			case EPDATAOUT:
			if (csr & OPRDY)
			{
				cnt = ReadFifo(FIFO0, Ep0Stage.pData);
				Ep0Stage.wResidue -= cnt;
				Ep0Stage.pData += cnt;
				if (Ep0Stage.wResidue == 0)
				{
					WriteReg(CSR0, SOPRDY | DATEND);
					Ep0Stage.bStage = EPIDLE;
				}
				else
				{
					WriteReg(CSR0, SOPRDY);
				}
			}
			break;
		}
	}
	
	if (intrin & EP1INIF)
	{
		WriteReg(INDEX, 1);
		csr = ReadReg(INCSR1);
		if (csr & INSTSTL)
		{
			WriteReg(INCSR1, INCLRDT);
		}
		if (csr & INUNDRUN)
		{
			WriteReg(INCSR1, 0);
		}
	}
	
	if (introut & EP1OUTIF)
	{
		WriteReg(INDEX, 1);
		csr = ReadReg(OUTCSR1);
		if (csr & OUTSTSTL)
		{
			WriteReg(OUTCSR1, OUTCLRDT);
		}
		if (csr & OUTOPRDY)
		{
			ReadFifo(FIFO1, HidOutput);
			WriteReg(OUTCSR1, 0);
			
			P6 = ~HidOutput[0];	//��ʾָʾ��״̬
		}
	}
}

BYTE KeyCount(WORD dat)
{
	BYTE i;

	i = 0;
	while(dat)
	{
		if(dat & 0x8000) i++;
		dat <<= 1;
	}
	return i;
}

//HidInput ��һ�ֽ�������ʾ���ⰴ�����ڶ��ֽڱ�������������ֽ�Ϊ��ͨ����
void SendKeyStatus(void)
{
	BYTE i,n;
	
	if(KeyCode) //����а�������
	{
		//4*4�ļ��̣�����ܹ�ʶ��3������ͬʱ���£�
		//��������ϽӶ����ܿ���ͬʱʶ�����İ���
		if(KeyCount(KeyCode) > 3) 
		{
			return;  //��������
		}
		else
		{
			n = 2;
			for(i=0;i<16;i++)
			{
				if(i == 1)
				{
					if(KeyCode & (1<<i)) //��Ctrl��
					{
						HidInput[0] |= 1;
					}
					else
					{
						HidInput[0] &= ~1;
					}
				}
				else if(i == 2)
				{
					if(KeyCode & (1<<i)) //��ALT��
					{
						HidInput[0] |= 1<<2;
					}
					else
					{
						HidInput[0] &= ~(1<<2);
					}
				}
				else
				{
					if(KeyCode & (1<<i))
					{
						HidInput[n++] = KeyBoardCode[i];   //�������
					}
				}
			}
			
			for(;n<8;n++)
			{
				HidInput[n]=0;  //�������0
			}
		}
	}
	else //����ް������£��򷵻�0
	{
		for(i=0;i<8;i++)
		{
			HidInput[i]=0;
		}
  }

	//����8���ֽ�����
	WriteReg(INDEX, 1);
	for(i=0;i<8;i++)
	{
		WriteReg(FIFO1, HidInput[i]);
	}
	WriteReg(INCSR1, INIPRDY);
}

/********************** Timer0 1ms�жϺ��� ************************/
void timer0 (void) interrupt 1
{
    B_1ms = 1;      //1ms��־
}

//========================================================================
// ����: void Timer0_Config(u16 tReload)
// ����: ��ʱ������.
// ����: tReload: ��ʱʱ��..
// ����: NULL.
// �汾: V1.0, 2012-10-22
//========================================================================
void Timer0_Config(WORD tReload)
{
	AUXR = 0x80;    //Timer0 set as 1T, 16 bits timer auto-reload, 
	TH0 = (BYTE)(tReload / 256);
	TL0 = (BYTE)(tReload % 256);
	ET0 = 1;    //Timer0 interrupt enable
	TR0 = 1;    //Tiner0 run
}

/*****************************************************
    ���м�ɨ�����
    ʹ��XY����4x4���ķ�����ֻ�ܵ������ٶȿ�

   Y     P04      P05      P06      P07
          |        |        |        |
X         |        |        |        |
P00 ---- K00 ---- K01 ---- K02 ---- K03 ----
          |        |        |        |
P01 ---- K04 ---- K05 ---- K06 ---- K07 ----
          |        |        |        |
P02 ---- K08 ---- K09 ---- K10 ---- K11 ----
          |        |        |        |
P03 ---- K12 ---- K13 ---- K14 ---- K15 ----
          |        |        |        |
******************************************************/
void IO_KeyDelay(void)
{
    BYTE i;
    i = 5;
    while(--i)  ;
}

void KeyScan(void)
{
	BYTE temp;
	
	KeyIO = 0x0F;
	IO_KeyDelay();
	if((KeyIO & 0x0F) == 0x0F)  //�������û�а�������
	{
		NewKeyCode = 0;   //û�м�����
	}
	else  //��ʼ����ɨ��
	{
		//ɨ���һ��
		KeyIO = ~0x10;
		IO_KeyDelay();
		//�����ĸ�����״̬
		temp = KeyIO & 0x0F;

		//ɨ��ڶ���
		KeyIO = ~0x20;
		IO_KeyDelay();
		//�����ĸ�����״̬
		temp |= KeyIO<<4;

		//���浱ǰ����״̬
		NewKeyCode = (~temp) & 0xFF;

		//ɨ�������
		KeyIO = ~0x40;
		IO_KeyDelay();
		//�����ĸ�����״̬
		temp = KeyIO & 0x0F;

		//ɨ�������
		KeyIO = ~0x80;
		IO_KeyDelay();
		//�����ĸ�����״̬
		temp |= KeyIO<<4; 
		 
		//����ȫ��16�����ص�״̬
		//�ܹ���16��bit����ĳ�����ذ���ʱ����Ӧ��bitΪ1
		NewKeyCode |= (((WORD)~temp)<<8);
	}

	if(NewKeyCode != OldKeyCode) //�жϰ����Ƿ����˸ı�
	{
		KeyHoldTime = 0;           //���̰���ʱ��Ϊ0
		OldKeyCode = NewKeyCode;   //���浱ǰ����״̬
		KeyChangeTemp = 1;
	}
	else
	{
		KeyHoldTime++;         //����ʱ���ۼ�
		if(KeyHoldTime >= 1)	 //�������ʱ���㹻
		{
			KeyHoldTime = 1;
			KeyCode = OldKeyCode;  //���水��
			if(KeyChangeTemp)
			{
				KeyChangeTemp = 0;
				KeyChangeFlag = 1;   //���÷��ͱ�־
			}
		}
	}
}