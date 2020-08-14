/******************************************
	作者：神秘藏宝室
	店铺：ILoveMCU.taobao.com
******************************************/


#include	"config.h"
#include	"delay.h"
#include  "uart.h"
#include  "intrins.h"

/*************	功能说明	**************

本程序演示LED闪烁  


******************************************/

/*************	本地常量声明	**************/


/*************	本地变量声明	**************/


/*************	本地函数声明	**************/



/*************  外部函数和变量声明 *****************/



/******************** IO配置函数 **************************/
void	GPIO_config(void)
{
	P1M0 = 0x00; 		//设置准双向口
	P1M1 = 0x00;

	P3M0 = 0x00;
	P3M1 = 0x00;
}


void IapIdle()
{
	IAP_CONTR = 0; //关闭 IAP 功能
	IAP_CMD = 0; //清除命令寄存器
	IAP_TRIG = 0; //清除触发寄存器
	IAP_ADDRH = 0x80; //将地址设置到非 IAP 区域
	IAP_ADDRL = 0;
}

char IapRead(int addr)
{
	char dat;
	IAP_CONTR = 0x80; //使能 IAP
	IAP_TPS = 12; //设置擦除等待参数 12MHz
	IAP_CMD = 1; //设置 IAP 读命令
	IAP_ADDRL = addr; //设置 IAP 低地址
	IAP_ADDRH = addr >> 8; //设置 IAP 高地址
	IAP_TRIG = 0x5a; //写触发命令(0x5a)
	IAP_TRIG = 0xa5; //写触发命令(0xa5)
	_nop_();
	dat = IAP_DATA; //读 IAP 数据
	IapIdle(); //关闭 IAP 功能

return dat;
}

void IapProgram(int addr, char dat)
{
	IAP_CONTR = 0x80; //使能 IAP
	IAP_TPS = 12; //设置擦除等待参数 12MHz
	IAP_CMD = 2; //设置 IAP 写命令
	IAP_ADDRL = addr; //设置 IAP 低地址
	IAP_ADDRH = addr >> 8; //设置 IAP 高地址
	IAP_DATA = dat; //写 IAP 数据
	IAP_TRIG = 0x5a; //写触发命令(0x5a)
	IAP_TRIG = 0xa5; //写触发命令(0xa5)
	_nop_();
	IapIdle(); //关闭 IAP 功能
}
void IapErase(int addr)
{
	IAP_CONTR = 0x80; //使能 IAP
	IAP_TPS = 12; //设置擦除等待参数 12MHz
	IAP_CMD = 3; //设置 IAP 擦除命令
	IAP_ADDRL = addr; //设置 IAP 低地址
	IAP_ADDRH = addr >> 8; //设置 IAP 高地址
	IAP_TRIG = 0x5a; //写触发命令(0x5a)
	IAP_TRIG = 0xa5; //写触发命令(0xa5)
	_nop_(); //
	IapIdle(); //关闭 IAP 功能
}



/******************** 主函数 **************************/
void main(void)
{
	char test = 0;
	P_SW1 = 0x00; //RXD/P3.0, TXD/P3.1

	GPIO_config();
	Uart_Init();

	
	
	while(1)
	{
		printf("uart test\r\n");

//		IapErase(0x0400);
//		test = IapRead(0x0400); //P0=0xff
//		printf("Erase:%x\r\n",test);
		IapProgram(0x0400, 0x22);
		test = IapRead(0x0400); //P1=0x12
		printf("Program:%x\r\n",test);

		P16 = 0;
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		P16 = 1;
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
	}
}
//
//
//
//
//
//#include "reg51.h"
//#include "intrins.h"
//sfr P0M1 = 0x93;
//sfr P0M0 = 0x94;
//sfr P1M1 = 0x91;
//sfr P1M0 = 0x92;
//sfr P2M1 = 0x95;
//sfr P2M0 = 0x96;
//sfr P3M1 = 0xb1;
//sfr P3M0 = 0xb2;
//sfr P4M1 = 0xb3;
//sfr P4M0 = 0xb4;
//sfr P5M1 = 0xc9;
//sfr P5M0 = 0xca;
//sfr IAP_DATA = 0xC2;
//sfr IAP_ADDRH = 0xC3;
//sfr IAP_ADDRL = 0xC4;
//sfr IAP_CMD = 0xC5;
//sfr IAP_TRIG = 0xC6;
//sfr IAP_CONTR = 0xC7;
//sfr IAP_TPS = 0xF5;
//void IapIdle()
//{
//IAP_CONTR = 0; //关闭 IAP 功能
//IAP_CMD = 0; //清除命令寄存器
//IAP_TRIG = 0; //清除触发寄存器
//IAP_ADDRH = 0x80; //将地址设置到非 IAP 区域
//IAP_ADDRL = 0;
//}
//char IapRead(int addr)
//{
//char dat;
//IAP_CONTR = 0x80; //使能 IAP
//IAP_TPS = 12; //设置擦除等待参数 12MHz
//IAP_CMD = 1; //设置 IAP 读命令
//IAP_ADDRL = addr; //设置 IAP 低地址
//IAP_ADDRH = addr >> 8; //设置 IAP 高地址
//IAP_TRIG = 0x5a; //写触发命令(0x5a)
//IAP_TRIG = 0xa5; //写触发命令(0xa5)
//_nop_();
//dat = IAP_DATA; //读 IAP 数据
//IapIdle(); //关闭 IAP 功能
//
//return dat;
//}
//void IapProgram(int addr, char dat)
//{
//IAP_CONTR = 0x80; //使能 IAP
//IAP_TPS = 12; //设置擦除等待参数 12MHz
//IAP_CMD = 2; //设置 IAP 写命令
//IAP_ADDRL = addr; //设置 IAP 低地址
//IAP_ADDRH = addr >> 8; //设置 IAP 高地址
//IAP_DATA = dat; //写 IAP 数据
//IAP_TRIG = 0x5a; //写触发命令(0x5a)
//IAP_TRIG = 0xa5; //写触发命令(0xa5)
//_nop_();
//IapIdle(); //关闭 IAP 功能
//}
//void IapErase(int addr)
//{
//	IAP_CONTR = 0x80; //使能 IAP
//	IAP_TPS = 12; //设置擦除等待参数 12MHz
//	IAP_CMD = 3; //设置 IAP 擦除命令
//	IAP_ADDRL = addr; //设置 IAP 低地址
//	IAP_ADDRH = addr >> 8; //设置 IAP 高地址
//	IAP_TRIG = 0x5a; //写触发命令(0x5a)
//	IAP_TRIG = 0xa5; //写触发命令(0xa5)
//	_nop_(); //
//	IapIdle(); //关闭 IAP 功能
//}
//void main()
//{
//	P0M0 = 0x00;
//	P0M1 = 0x00;
//	P1M0 = 0x00;
//	P1M1 = 0x00;
//	P2M0 = 0x00;
//	P2M1 = 0x00;
//	P3M0 = 0x00;
//	P3M1 = 0x00;
//	P4M0 = 0x00;
//	P4M1 = 0x00;
//	P5M0 = 0x00;
//	P5M1 = 0x00;
//	IapErase(0x0400);
//	P0 = IapRead(0x0400); //P0=0xff
//	IapProgram(0x0400, 0x12);
//	P1 = IapRead(0x0400); //P1=0x12
//	while (1);
//}
