/******************************************
	���ߣ����زر���
	���̣�ILoveMCU.taobao.com
******************************************/
#include	"config.h"
#include	"delay.h"
#include  "intrins.h"

/*************	����˵��	**************




******************************************/

/*************	���س�������	**************/



/*************	���ر�������	**************/
int advalue = 0;

/*************	���غ�������	**************/



/*************  �ⲿ�����ͱ������� *****************/



/******************** IO���ú��� **************************/
void	GPIO_config(void)
{
	P1M0 = 0x00; 		//����˫������,P1.0��P1.1Ϊ�����������AD
	P1M1 = 0x03;

	P3M0 = 0x00;
	P3M1 = 0x00;
}

void AD_INIT(void)
{
	P_SW2 |= 0x80;
	ADCTIM = 0x3f; //���� ADC �ڲ�ʱ��
	P_SW2 &= 0x7f;
	ADCCFG = 0x0f; //���� ADC ʱ��Ϊϵͳʱ��/2/16/16
	ADC_CONTR = 0x80; //ʹ�� ADC ģ��
}

int analogRead(int channel)
{
	int res = 0;
	ADC_CONTR &= 0xf0;	//����λ����
	ADC_CONTR |= channel;	//��λͨ��
	ADC_CONTR |= 0x40; //���� AD ת��
	_nop_();
	_nop_();
	while (!(ADC_CONTR & 0x20)); //��ѯ ADC ��ɱ�־
	ADC_CONTR &= ~0x20; //����ɱ�־
	res = (int)(ADC_RES*4);
	res += ADC_RESL;
	return res; //��ȡ ADC ���	
}

/******************** ������ **************************/
void main(void)
{
	GPIO_config();
	AD_INIT();
	
	while(1)
	{
		advalue = analogRead(0);

		if(advalue > 1000)
		{
			RELAY1 = RELAY_ON;
		}
		else
		{
			RELAY1 = RELAY_OFF;
		}

		advalue = analogRead(1);

		if(advalue > 1000)
		{
			RELAY2 = RELAY_ON;
		}
		else
		{
			RELAY2 = RELAY_OFF;
		}

		delay_ms(100);
	
	}
}




