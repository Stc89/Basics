
/*------------------------------------------------------------------*/
/* --- STC MCU International Limited -------------------------------*/
/* --- STC 1T Series MCU RC Demo -----------------------------------*/
/* --- Mobile: (86)13922805190 -------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ---------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ---------------------*/
/* --- Web: www.GXWMCU.com -----------------------------------------*/
/* --- QQ:  800003751 ----------------------------------------------*/
/* If you want to use the program or the program referenced in the  */
/* article, please specify in which data and procedures from STC    */
/*------------------------------------------------------------------*/


#include	"config.h"
#include	"GPIO.h"
#include	"delay.h"

/*************	����˵��	**************

��������ʾ����ơ�
����ʹ��P2������ʾ��������������û������޸�Ϊ��Ŀڡ�

******************************************/

/*************	���س�������	**************/


/*************	���ر�������	**************/


/*************	���غ�������	**************/



/*************  �ⲿ�����ͱ������� *****************/



/******************** IO���ú��� **************************/
void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_All;		//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);	//��ʼ��
}



/******************** ������ **************************/
void main(void)
{
	u8	i,tmp;
	
	GPIO_config();
	
	while(1)
	{
		tmp = 1;
		for(i=0; i<8; i++)
		{
			P2 = ~tmp;
			tmp <<= 1;
			delay_ms(250);
		}

		tmp = 0x80;
		for(i=0; i<8; i++)
		{
			P2 = ~tmp;
			tmp >>= 1;
			delay_ms(250);
		}
	}
}




