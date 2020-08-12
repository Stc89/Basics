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
//**************************************************************************************************/	
#ifndef __LCD_H
#define __LCD_H		
#include "sys.h"

//STC��Ƭ��IO����������ö���
sfr P4   = 0xC0;
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

sfr P_SW2 = 0xBA;
#define P0PU     (*(unsigned char  volatile xdata *)  0xFE10)
#define P0DR     (*(unsigned char  volatile xdata *)  0xFE28)

/////////////////////////////////////�û�������///////////////////////////////////	 
//֧�ֺ��������ٶ����л�
#define USE_HORIZONTAL  	  3   //����Һ����˳ʱ����ת���� 	0-0����ת��1-90����ת��2-180����ת��3-270����ת
#define LCD_USE8BIT_MODEL   1 	//�������������Ƿ�ʹ��8λģʽ 0,ʹ��16λģʽ.1,ʹ��8λģʽ
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////	  
//����LCD�ĳߴ�
#define LCD_W 240
#define LCD_H 320

//IO����
#define  LCD_DataPortH P0     //��8λ���ݿ�,8λģʽ��ֻʹ�ø�8λ 
#define  LCD_DataPortL P2     //��8λ���ݿ�,8λģʽ�µ�8λ���Բ�����
sbit LCD_RS = P4^5;  		//����/�����л�
sbit LCD_WR = P4^2;		  //д����
sbit LCD_RD = P4^4;		  //������
sbit LCD_CS = P3^4;		  //Ƭѡ	
sbit LCD_RESET = P4^3;	//��λ 

//LCD�Ļ�����ɫ�ͱ���ɫ	   
extern u16  POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern u16  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ
//LCD��Ҫ������
typedef struct  
{										    
	u16 width;			//LCD ���
	u16 height;			//LCD �߶�
	u16 id;				//LCD ID
	u8  dir;			//���������������ƣ�0��������1��������	
	u16	 wramcmd;		//��ʼдgramָ��
	u16  rramcmd;   //��ʼ��gramָ��
	u16  setxcmd;		//����x����ָ��
	u16  setycmd;		//����y����ָ��	 
}_lcd_dev; 	

//LCD����
extern _lcd_dev lcddev;	//����LCD��Ҫ����
void LCD_Init(void); 
void LCD_Clear(u16 Color);
void LCD_write(u8 HVAL,u8 LVAL);
u16 LCD_read(void);
void LCD_WR_DATA(u16 Data);
u16 LCD_RD_DATA(void);
void LCD_WR_REG(u16 Reg);
void LCD_SetCursor(u16 Xpos, u16 Ypos);//���ù��λ��
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);//������ʾ����
void LCD_DrawPoint(u16 x,u16 y);//����
u16 LCD_ReadPoint(u16 x,u16 y);
void LCD_WriteRAM_Prepare(void);
void LCD_ReadRAM_Prepare(void);
void LCD_direction(u8 direction );
void LCD_WR_DATA_16Bit(u16 Data);
u16 Lcd_RD_DATA_16Bit(void);
void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue);
void LCD_ReadReg(u16 LCD_Reg,u8 *Rval,int n);
u16 LCD_Read_ID(void);
u16 Color_To_565(u8 r, u8 g, u8 b);


//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE             0x001F  
#define BRED             0XF81F
#define GRED             0XFFE0
#define GBLUE            0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN            0XBC40 //��ɫ
#define BRRED            0XFC07 //�غ�ɫ
#define GRAY             0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY            0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)


					  		 
#endif  
	 
	 



