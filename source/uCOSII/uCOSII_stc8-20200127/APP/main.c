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
*                                             ϵͳ��ʼ����
*
* ����       : ����ʱ��T0�жϣ�������Ϣ�����Լ���������������Ȼ������ɾ����
*
* ����       : p_arg
*
* ע��       : ϵͳ�������һʱ�俪��ʱ���жϣ�����ϵͳ���������޷��õ�ִ�С�		                        	
*********************************************************************************************************
*/
void AppStart(void *p_arg) large reentrant
{
	p_arg=p_arg;
	ET0=1; /* ���ǣ�ϵͳ�������һʱ�俪��ʱ���ж� */

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
*                                             ����״ָ̬ʾ����
*
* ����       : CPU��������ʱ��ÿ������˸5�Σ�������ʱ����˸�����ƶ˿�P3.4��
*
* ����       : p_arg
*
* ע��       : һ��ʱ�ӽ���Ϊ0.02s���������ȼ���Ϊ��ͣ�����ϵͳ���������ϵͳͳ������ǿ�������������ӣ�
*			   ..\ucos_51\ucos-ii\src\ucos_ii.h	
*			   		OS_EXT  DF_IDATA  volatile  INT32U  OSIdleCtr; 
*			   "OSIdleCtr" �����������Ϊ "idata" �洢���ͣ������������н��ı�����		                        	
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
		WorkLedCtrl=!WorkLedCtrl; /* �����ٽ���Դ */
		OS_EXIT_CRITICAL();

		OSTimeDlyHMSM(0,0,0,200);
	}
}



/*
********************************************************************************************************* 
*                                             �����շ�����
*
* ����       : UartRcv������Ӽ��̽��գ�ͨ����Ϣ���䷢�͸�UartSend���������ն˴�ӡ��
*
* ����       : p_arg
*
* ע��       : ������Ĳ���ִ�У������ƴ�����ٽ���Դ�ķ����Լ�������֮���ͨ�š�	                        	
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


