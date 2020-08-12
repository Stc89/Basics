/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* Һ������������ο�wiki������վ�ṩ�Ŀ�ԴԴ�룬����ѧϰʹ��          */
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����        */
/*---------------------------------------------------------------------*/

//=========================================��Դ����================================================//
//VDD��DC 3.3V��Դ
//GND�ӵ�
//=======================================Һ���������߽���==========================================//
//��ģ��������������Ϊ8λ����
//Һ����ģ��             STC8H8K64U
// LCD_D0~D7     ��       P00~P07        //Һ����8λ������
//=======================================Һ���������߽���==========================================//
//Һ����ģ��             STC8H8K64U
// LCD_RS        ��        P45           //����/����ѡ������ź�
// LCD_RD        ��        P44           //�������ź�
// LCD_RST       ��        P43           //��λ�ź�
// LCD_WR        ��        P42           //д�����ź�
// LCD_CS        ��        P34           //Ƭѡ�����ź�
//===========================================����������============================================//
//��ʹ�ô�������ģ�鱾������������ɲ�����
//������ʹ�õ�������������ΪSPI
//������ģ��             STC8H8K64U
//  T_CS         ��        P52          //������Ƭѡ�����ź�
//  T_CLK        ��        P25          //������SPIʱ���ź�
//  T_DO         ��        P24          //������SPI���ź�
//  T_DIN        ��        P23          //������SPIд�ź�
//  T_IRQ        ��        P36          //��������Ӧ����ź�
//**************************************************************************************************/	
#include "sys.h"
#include "lcd.h"
#include "touch.h"

//LCD�Ļ�����ɫ�ͱ���ɫ	   
u16 POINT_COLOR=0x0000;	//������ɫ
u16 BACK_COLOR=0xFFFF;  //����ɫ 
//����LCD��Ҫ����
//Ĭ��Ϊ����
_lcd_dev lcddev;


void Write_Cmd(unsigned char DH,unsigned char DL)
{
	LCD_CS=0;
	LCD_RS=0;
	LCD_WR=0;
	LCD_DataPort=DH;
	LCD_WR=1;
	_nop_();
	LCD_WR=0;
	LCD_DataPort=DL;
	LCD_WR=1;
	LCD_CS=1;
}

void Write_Data(unsigned char DH,unsigned char DL)
{
	LCD_CS=0;
	LCD_RS=1;
	LCD_WR=0;
	LCD_DataPort=DH;
	LCD_WR=1;
	_nop_();
	LCD_WR=0;
	LCD_DataPort=DL;	
	LCD_WR=1;
	LCD_CS=1;
}

void LCD_WR_REG16(u8 Reg, u16 dat)	 
{	
	Write_Cmd(0x00,Reg);
	Write_Data((dat>>8)&0xFF,dat&0xFF);
} 

void LCD_WR_DATA16(u16 Data)
{
	Write_Data((Data>>8)&0xFF,Data&0xFF);
}


void LCD_write(u8 VAL)
{
	LCD_CS = 0;
	LCD_WR = 0;
	LCD_DataPort = VAL;
	LCD_WR = 1;
	LCD_CS = 1;
}

u16 LCD_read(void)
{
	u16 d;
	LCD_CS = 0;
	LCD_RD = 0;
	delay_us(1); //delay 1 us
	d = LCD_DataPort;
	LCD_RD = 1;
  LCD_CS = 1;
	return d;
}
/*****************************************************************************
 * @name       :void LCD_WR_REG(u8 Reg)	
 * @date       :2018-08-09 
 * @function   :Write an 16-bit command to the LCD screen
 * @parameters :data:Command value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_REG(u8 Reg)	 
{	
	LCD_RS=0;
	LCD_write(Reg);
} 

/*****************************************************************************
 * @name       :void LCD_WR_DATA(u8 Data)
 * @date       :2018-08-09 
 * @function   :Write an 16-bit data to the LCD screen
 * @parameters :data:data value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_DATA(u8 Data)
{
	LCD_RS=1;
	LCD_write(Data);
}

/*****************************************************************************
 * @name       :u16 LCD_RD_DATA(void)
 * @date       :2018-11-13 
 * @function   :Read an 16-bit value from the LCD screen
 * @parameters :None
 * @retvalue   :read value
******************************************************************************/
u16 LCD_RD_DATA(void)
{
	LCD_RS=1;
	return LCD_read();
}

/*****************************************************************************
 * @name       :void LCD_WR_DATA_16Bit(u16 Data)
 * @date       :2018-08-09 
 * @function   :Write an 16-bit command to the LCD screen
 * @parameters :Data:Data to be written
 * @retvalue   :None
******************************************************************************/	 
void LCD_WR_DATA_16Bit(u16 Data)
{
	Write_Data((Data>>8)&0xFF,Data&0xFF);
}

u16 Color_To_565(u8 r, u8 g, u8 b)
{
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3);
}

/*****************************************************************************
 * @name       :u16 Lcd_ReadData_16Bit(void)
 * @date       :2018-11-13 
 * @function   :Read an 16-bit value from the LCD screen
 * @parameters :None
 * @retvalue   :read value
******************************************************************************/	
u16 Lcd_RD_DATA_16Bit(void)
{
	u16 r,g,b;
	LCD_RS = 1;
	LCD_CS = 0;
	
	//dummy data
	LCD_RD = 0;
	delay_us(1); //delay 1us
	r = LCD_DataPort;
	LCD_RD = 1;
	_nop_();
	
	//8bit:red data
	LCD_RD = 0;
	delay_us(1); //delay 1us
	r = LCD_DataPort;
	LCD_RD = 1;
	_nop_();
	
	//8bit:green data
	LCD_RD = 0;
	delay_us(1); //delay 1us
	g = LCD_DataPort;
	LCD_RD = 1;
	_nop_();
	
	LCD_RD = 0;
	delay_us(1); //delay 1us
	b = LCD_DataPort;
	LCD_RD = 1;
	LCD_CS = 1;
//	return Color_To_565(r, g, b);
	return (g<<8 | b);
}

/*****************************************************************************
 * @name       :void LCD_WriteReg(u8 LCD_Reg, u8 LCD_RegValue)
 * @date       :2018-08-09 
 * @function   :Write data into registers
 * @parameters :LCD_Reg:Register address
                LCD_RegValue:Data to be written
 * @retvalue   :None
******************************************************************************/
//void LCD_WriteReg(u8 LCD_Reg, u8 LCD_RegValue)
//{
//  LCD_WR_REG(LCD_Reg);
//	LCD_WR_DATA(LCD_RegValue);
//}

/*****************************************************************************
 * @name       :void LCD_ReadReg(u8 LCD_Reg,u8 *Rval,int n)
 * @date       :2018-11-13 
 * @function   :read value from specially registers
 * @parameters :LCD_Reg:Register address
 * @retvalue   :read value
******************************************************************************/
void LCD_ReadReg(u8 LCD_Reg,u8 *Rval,int n)
{
	LCD_WR_REG(LCD_Reg);
	LCD_DataPort = 0xFF; //����P0
  //P0�����ó������
	P0M0=0x00;
	P0M1=0xFF;
	while(n--)
	{		
		*(Rval++) = LCD_RD_DATA();
	}
  //P0�����ó��������
	P0M0=0xFF;
	P0M1=0x00;
	LCD_DataPort = 0xFF; //����P0
}

/*****************************************************************************
 * @name       :void LCD_Clear(u16 Color)
 * @date       :2018-08-09 
 * @function   :Full screen filled LCD screen
 * @parameters :color:Filled color
 * @retvalue   :None
******************************************************************************/	
void LCD_Clear(u16 Color)
{
	u16 i,j;
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);	
    for(i=0;i<lcddev.width;i++)
	 {
	  for (j=0;j<lcddev.height;j++)
	   {
        	 LCD_WR_DATA_16Bit(Color);
	   }

	  }
}

/*****************************************************************************
 * @name       :void LCD_DrawPoint(u16 x,u16 y)
 * @date       :2018-08-09 
 * @function   :Write a pixel data at a specified location
 * @parameters :x:the x coordinate of the pixel
                y:the y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/	
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetWindows(x,y,x,y);//���ù��λ�� 
	LCD_WR_DATA_16Bit(POINT_COLOR); 	    
} 	 


/*****************************************************************************
 * @name       :u16 LCD_ReadPoint(u16 x,u16 y)
 * @date       :2018-11-13 
 * @function   :Read a pixel color value at a specified location
 * @parameters :x:the x coordinate of the pixel
                y:the y coordinate of the pixel
 * @retvalue   :the read color value
******************************************************************************/	
u16 LCD_ReadPoint(u16 x,u16 y)
{
	u16 color;
	if(x>=lcddev.width||y>=lcddev.height)
	{
		return 0;	//�����˷�Χ,ֱ�ӷ���	
	}
	LCD_WR_REG(GRAMWR);
	LCD_SetCursor(x,y);//���ù��λ�� 
	LCD_DataPort = 0xFF; //����P0
	
  //P0�����ó������
	P0M0=0x00;
	P0M1=0xFF;
	color = Lcd_RD_DATA_16Bit();
  //P0�����ó��������
	P0M0=0xFF;
	P0M1=0x00;
	
	LCD_DataPort = 0xFF; //����P0
	return color;
}

/*****************************************************************************
 * @name       :void LCD_Set_GPIO(void)
 * @date       :2018-11-13 
 * @function   :Set the gpio to push-pull mode
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	
void LCD_Set_GPIO(void)
{
  //P0�����ó��������
	P0M0=0xff;
	P0M1=0x00;

	//P1�����ó�׼˫���
	P1M0=0x00;
	P1M1=0x00;

	//P2.4�����ó������
	//P2.3,P2.5�����ó��������
	P2M0=0x28;
	P2M1=0x10;

	//P3.4�����ó��������
	//P3.6�����ó������
	P3M0=0x10;
	P3M1=0x40;

	//P4.2~P4.5�����ó��������
	P4M0=0x3c;
	P4M1=0x00;

	//P5.2�����ó��������
	P5M0=0x04;
	P5M1=0x00;

	TCS=1;
	DCLK=1;
	DIN=1;
	DCLK=1;
}

/*****************************************************************************
 * @name       :void LCD_Reset(void)
 * @date       :2018-08-09 
 * @function   :Reset LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	
void LCD_Reset(void)
{
	LCD_CS=1;
	delay_ms(50);	
	LCD_RESET=0;
	delay_ms(150);
	LCD_RESET=1;
	delay_ms(50);
}

/*****************************************************************************
 * @name       :void LCD_Init(void)
 * @date       :2018-08-09 
 * @function   :Initialization LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	 	 
void LCD_Init(void)
{
	LCD_Set_GPIO();
	LCD_Reset(); //��ʼ��֮ǰ��λ
	delay_ms(150);                     //���ݲ�ͬ�����ٶȿ��Ե�����ʱ�������ȶ���ʾ
//*************2.4inch ILI9325��ʼ��**********//	
	LCD_WR_REG16(0x00E5,0x78F0); 
	LCD_WR_REG16(0x0001,0x0100); 
	LCD_WR_REG16(0x0002,0x0700); 
	LCD_WR_REG16(0x0003,0x1030); 
	LCD_WR_REG16(0x0004,0x0000); 
	LCD_WR_REG16(0x0008,0x0202);  
	LCD_WR_REG16(0x0009,0x0000);
	LCD_WR_REG16(0x000A,0x0000); 
	LCD_WR_REG16(0x000C,0x0000); 
	LCD_WR_REG16(0x000D,0x0000);
	LCD_WR_REG16(0x000F,0x0000);
	//power on sequence VGHVGL
	LCD_WR_REG16(0x0010,0x0000);   
	LCD_WR_REG16(0x0011,0x0007);  
	LCD_WR_REG16(0x0012,0x0000);  
	LCD_WR_REG16(0x0013,0x0000); 
	LCD_WR_REG16(0x0007,0x0000); 
	//vgh 
	LCD_WR_REG16(0x0010,0x1690);   
	LCD_WR_REG16(0x0011,0x0227);
	delay_ms(10);
	//vregiout 
	LCD_WR_REG16(0x0012,0x009D); //0x001b
	delay_ms(10); 
	//vom amplitude
	LCD_WR_REG16(0x0013,0x1900);
	delay_ms(10); 
	//vom H
	LCD_WR_REG16(0x0029,0x0025); 
	LCD_WR_REG16(0x002B,0x000D); 
	//gamma
	LCD_WR_REG16(0x0030,0x0007);
	LCD_WR_REG16(0x0031,0x0303);
	LCD_WR_REG16(0x0032,0x0003); //0006
	LCD_WR_REG16(0x0035,0x0206);
	LCD_WR_REG16(0x0036,0x0008);
	LCD_WR_REG16(0x0037,0x0406); 
	LCD_WR_REG16(0x0038,0x0304); //0200
	LCD_WR_REG16(0x0039,0x0007); 
	LCD_WR_REG16(0x003C,0x0602); //0504
	LCD_WR_REG16(0x003D,0x0008); 
	//ram
	LCD_WR_REG16(0x0050,0x0000); 
	LCD_WR_REG16(0x0051,0x00EF);
	LCD_WR_REG16(0x0052,0x0000); 
	LCD_WR_REG16(0x0053,0x013F);  
	LCD_WR_REG16(0x0060,0xA700); 
	LCD_WR_REG16(0x0061,0x0001); 
	LCD_WR_REG16(0x006A,0x0000); 
	//
	LCD_WR_REG16(0x0080,0x0000); 
	LCD_WR_REG16(0x0081,0x0000); 
	LCD_WR_REG16(0x0082,0x0000); 
	LCD_WR_REG16(0x0083,0x0000); 
	LCD_WR_REG16(0x0084,0x0000); 
	LCD_WR_REG16(0x0085,0x0000); 
	//
	LCD_WR_REG16(0x0090,0x0010); 
	LCD_WR_REG16(0x0092,0x0600); 
	
	LCD_WR_REG16(0x0007,0x0133);
	LCD_WR_REG16(0x0000,0x0022);

	//����LCD���Բ���
	LCD_direction(USE_HORIZONTAL);//����LCD��ʾ���� 
}
 
/*****************************************************************************
 * @name       :void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
 * @date       :2018-08-09 
 * @function   :Setting LCD display window
 * @parameters :xStar:the bebinning x coordinate of the LCD display window
								yStar:the bebinning y coordinate of the LCD display window
								xEnd:the endning x coordinate of the LCD display window
								yEnd:the endning y coordinate of the LCD display window
 * @retvalue   :None
******************************************************************************/ 
void LCD_SetWindows(u16 xStar0, u16 yStar0,u16 xEnd0,u16 yEnd0)
{	
	u16 xStar; u16 yStar;u16 xEnd;u16 yEnd;
	#if USE_HORIZONTAL==1
	xStar = yStar0;
	xEnd = yEnd0;
	yStar = xStar0;
	yEnd = xEnd0;
	#else
	xStar = xStar0;
	xEnd = xEnd0;
	yStar = yStar0;
	yEnd = yEnd0;
	#endif 

  LCD_WR_REG16(WINDOW_XADDR_START,xStar);
  LCD_WR_REG16(WINDOW_XADDR_END,xEnd);
  LCD_WR_REG16(WINDOW_YADDR_START,yStar);
  LCD_WR_REG16(WINDOW_YADDR_END,yEnd);
  LCD_WR_REG16(GRAM_XADDR,xStar);
  LCD_WR_REG16(GRAM_YADDR,yStar);
	LCD_WR_REG(GRAMWR);
}   

/*****************************************************************************
 * @name       :void LCD_SetCursor(u16 Xpos, u16 Ypos)
 * @date       :2018-08-09 
 * @function   :Set coordinate value
 * @parameters :Xpos:the  x coordinate of the pixel
								Ypos:the  y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/ 
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	  	    			
	LCD_SetWindows(Xpos,Ypos,Xpos,Ypos);	
} 

/*****************************************************************************
 * @name       :void LCD_direction(u8 direction)
 * @date       :2018-08-09 
 * @function   :Setting the display direction of LCD screen
 * @parameters :direction:0-0 degree
                          1-90 degree
													2-180 degree
													3-270 degree
 * @retvalue   :None
******************************************************************************/ 
void LCD_direction(u8 direction)
{ 
			lcddev.setxcmd=0x50;
			lcddev.setycmd=0x52;
			lcddev.wramcmd=0x22;
			lcddev.rramcmd=0x22;
	switch(direction){		  
		case 0:
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;
			LCD_WR_REG16(0x0003, 0x1030); // set GRAM write direction and BGR=1.
			LCD_WR_REG16(0x0001, 0x0100); // set SS and SM bit
		break;
		case 1:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;	
			LCD_WR_REG16(0x0003, 0x1038); // set GRAM write direction and BGR=1.
			LCD_WR_REG16(0x0001, 0x0000); // set SS and SM bit
		break;
		default:
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;
			LCD_WR_REG16(0x0003, 0x1030); // set GRAM write direction and BGR=1.
			LCD_WR_REG16(0x0001, 0x0100); // set SS and SM bit
		break;
	}
}	 

/*****************************************************************************
 * @name       :u16 LCD_Read_ID(void)
 * @date       :2018-11-13 
 * @function   :Read ID
 * @parameters :None
 * @retvalue   :ID value
******************************************************************************/ 
u16 LCD_Read_ID(void)
{
	u8 val[2] = {0};
	LCD_ReadReg(0x00,val,2);
	return (val[0]<<8)|val[1];
}



