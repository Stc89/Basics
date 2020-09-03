/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                          (c) Copyright 1992-2002, Jean J. Labrosse, Weston, FL
*                                           All Rights Reserved
*
*
*                                           uCOS_51 for MCS-51
*
* File : main.c
* Created by : QQ 591881218
*********************************************************************************************************
*/

#include "..\..\ucos-ii\inc\includes.h"

// ---------------------------------

#define APPSTARTPRIO 	TASK_START_PRIO	
#define UARTRCVPRIO		APPSTARTPRIO + 2
#define UARTSENDPRIO	UARTRCVPRIO + 2
#define POWERLEDPRIO 	OS_LOWEST_PRIO - 2

#define OK				0
#define ACK				1
#define ENTER			0x0D

// --------------------------------- 

sbit WorkLedCtrl=P6^0;

OS_EVENT *UartMbox;
OS_EVENT *AckMbox;

OS_STK AppStartStk[TASK_STK_SIZE];
OS_STK PowerLedStk[TASK_STK_SIZE];
OS_STK UartRcvStk[TASK_STK_SIZE];
OS_STK UartSendStk[TASK_STK_SIZE];

// ---------------------------------

void AppStart(void *p_arg) large reentrant;
void PowerLed(void *p_arg) large reentrant; 
void UartRcv(void *p_arg) large reentrant;
void UartSend(void *p_arg)	large reentrant;

// ---------------------------------

int main(void)
{
	InitSystem();

	OSTaskCreate(AppStart, (void *)0, AppStartStk, APPSTARTPRIO);

	OSStart();

	return OK;
}

/*
********************************************************************************************************* 
*                                             系统开始任务
*
* 描述       : 开定时器T0中断，创建消息邮箱以及所有其他的任务，然后自我删除。
*
* 参数       : p_arg
*
* 注意       : 系统启动后第一时间开定时器中断，否则系统其它任务无法得到执行。		                        	
*********************************************************************************************************
*/
void AppStart(void *p_arg) large reentrant
{
	p_arg=p_arg;
	ET0=1; /* 谨记：系统启动后第一时间开定时器中断 */

	UartMbox=OSMboxCreate((void *)0);
	AckMbox=OSMboxCreate((void *)0);

	LogoDisp();
	PrintStr("You can input by the terminal!\n\n\n");
	
	OSTaskCreate(PowerLed, (void *)0, PowerLedStk, POWERLEDPRIO);
	OSTaskCreate(UartRcv, (void *)0, UartRcvStk, UARTRCVPRIO);
	OSTaskCreate(UartSend, (void *)0, UartSendStk, UARTSENDPRIO);

	OSTaskDel(OS_PRIO_SELF);	
}

/*
********************************************************************************************************* 
*                                             工作状态指示任务
*
* 描述       : CPU正常工作时，每秒钟闪烁5次，不工作时不闪烁，控制端口P3.4。
*
* 参数       : p_arg
*
* 注意       : 一个时钟节拍为0.02s，建议优先级设为最低，高于系统空闲任务和系统统计任务。强烈引起您的重视：
*			   ..\ucos_51\ucos-ii\src\ucos_ii.h	
*			   		OS_EXT  DF_IDATA  volatile  INT32U  OSIdleCtr; 
*			   "OSIdleCtr" 变量务必设置为 "idata" 存储类型，否则任务运行节拍变慢。		                        	
*********************************************************************************************************
*/
void PowerLed(void *p_arg) large reentrant
{
#if OS_CRITICAL_METHOD == 3                                /* Allocate storage for CPU status register */
    OS_CPU_SR  cpu_sr;
#endif

	p_arg=p_arg;
	
	for(;;)
	{
		OS_ENTER_CRITICAL();
		WorkLedCtrl=!WorkLedCtrl; /* 保护临界资源 */
		OS_EXIT_CRITICAL();

		OSTimeDlyHMSM(0,0,0,200);
	}
}



/*
********************************************************************************************************* 
*                                             串口收发任务
*
* 描述       : UartRcv任务负责从键盘接收，通过消息邮箱发送给UartSend任务处理并在终端打印。
*
* 参数       : p_arg
*
* 注意       : 多任务的并发执行，须妥善处理对临界资源的访问以及多任务之间的通信。	                        	
*********************************************************************************************************
*/
// ------------------------------------------------------------------------------------------------------
void UartRcv(void *p_arg) large reentrant
{
	INT8U Rxbuf;
	INT8U err;

	p_arg=p_arg;
		
	for(;;)
	{
		if(Getch(&Rxbuf)) 
		{
			OSMboxPost(UartMbox, (void *)&Rxbuf);
			OSMboxPend(AckMbox, 0, &err);
		}	
		
		OSTimeDlyHMSM(0,0,0,100);
	}	
}

void UartSend(void *p_arg) large reentrant
{
	INT8U *Txbuf;
	INT8U err;
	INT16U count=0;	

	p_arg=p_arg;

	for(;;)
	{
		Txbuf=(INT8U *)OSMboxPend(UartMbox,0,&err);

		if(OS_ERR_NONE==err)
		{	
			PrintChar(*Txbuf);

			count++;
			
			if((ENTER == *Txbuf) || (0xFFFF == count)) count=1; 
		
			if(!(count%69))
			{ 
				PrintStr("\n");
			}	
		}
		else 
		{
			PrintStr("\n\nMboxRcv err!\n\n\n");
		}

		OSMboxPost(AckMbox,(void *)ACK);
	}
}
// ------------------------------------------------------------------------------------------------------


