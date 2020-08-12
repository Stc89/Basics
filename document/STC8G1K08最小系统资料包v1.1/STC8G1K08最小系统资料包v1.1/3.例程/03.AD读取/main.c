/******************************************
	作者：神秘藏宝室
	店铺：ILoveMCU.taobao.com
******************************************/
#include	"config.h"
#include	"delay.h"
#include  "intrins.h"

/*************	功能说明	**************




******************************************/

/*************	本地常量声明	**************/



/*************	本地变量声明	**************/
int advalue = 0;

/*************	本地函数声明	**************/



/*************  外部函数和变量声明 *****************/



/******************** IO配置函数 **************************/
void	GPIO_config(void)
{
	P1M0 = 0x00; 		//设置双向输入,P1.0和P1.1为输入高阻用于AD
	P1M1 = 0x03;

	P3M0 = 0x00;
	P3M1 = 0x00;
}

void AD_INIT(void)
{
	P_SW2 |= 0x80;
	ADCTIM = 0x3f; //设置 ADC 内部时序
	P_SW2 &= 0x7f;
	ADCCFG = 0x0f; //设置 ADC 时钟为系统时钟/2/16/16
	ADC_CONTR = 0x80; //使能 ADC 模块
}

int analogRead(int channel)
{
	int res = 0;
	ADC_CONTR &= 0xf0;	//底四位清零
	ADC_CONTR |= channel;	//置位通道
	ADC_CONTR |= 0x40; //启动 AD 转换
	_nop_();
	_nop_();
	while (!(ADC_CONTR & 0x20)); //查询 ADC 完成标志
	ADC_CONTR &= ~0x20; //清完成标志
	res = (int)(ADC_RES*4);
	res += ADC_RESL;
	return res; //读取 ADC 结果	
}

/******************** 主函数 **************************/
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




