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
* File : serial.c
* From : yang yi
* Last modified by : QQ 591881218
*********************************************************************************************************
*/

#ifndef  OS_MASTER_FILE
#include "..\..\ucos-ii\inc\includes.h"
#endif

unsigned char TxBuf[LenTxBuf],RxBuf[LenRxBuf];
unsigned char *inTxBuf,*outTxBuf,*inRxBuf,*outRxBuf;
bit TIflag=1;

void InitSerial(void) large reentrant // 串口初始化
{
	SCON=0x50;
    TMOD= 0x00;
    TL1=-(24000000UL / 115200 /4);
	TH1=(-(24000000UL / 115200 /4)) >> 8; 
	AUXR = 0x40;
	TR1=1;
}

void InitSerialBuffer(void) large reentrant // 串口缓冲区初始化
{
	inTxBuf=TxBuf;outTxBuf=TxBuf;
	inRxBuf=RxBuf;outRxBuf=RxBuf;
	ES=1;
}

void Serial(void) large reentrant	// 串口中断服务子程序，中断在汇编中实现，去掉interrupt 4 
{  
	unsigned char *t;
	
	/* 循环缓冲区 */
	if(TI){
		TI=0;
		if(inTxBuf==outTxBuf) {TIflag=1;return;} // TxBuf Empty
		SBUF=*outTxBuf;outTxBuf++;
		if(outTxBuf==TxBuf+LenTxBuf) outTxBuf=TxBuf;	
	}
	if(RI){
		RI=0;
		t=inRxBuf;t++;
		if(t==RxBuf+LenRxBuf) t=RxBuf;
		if(t==outRxBuf) return; // RxBuf Full
		*inRxBuf=SBUF;
		inRxBuf=t;
	}
}

bit Getch(unsigned char *ch) large reentrant // 从串口缓冲区读1字节数据
{
#if OS_CRITICAL_METHOD == 3                                /* Allocate storage for CPU status register */
    OS_CPU_SR  cpu_sr;
#endif
	
	OS_ENTER_CRITICAL();/* 进入临界区 */      
	if(inRxBuf==outRxBuf) {OS_EXIT_CRITICAL();/* 退出临界区 */return 0;} // RxBuf Empty
	*ch=*outRxBuf;outRxBuf++;
	if(outRxBuf==RxBuf+LenRxBuf) outRxBuf=RxBuf;  
	OS_EXIT_CRITICAL();/* 退出临界区 */     
	return 1;
}

void PrintChar(unsigned char ch) large reentrant // 显示字符
{
#if OS_CRITICAL_METHOD == 3                                /* Allocate storage for CPU status register */
    OS_CPU_SR  cpu_sr;
#endif

	unsigned char *t;

	OS_ENTER_CRITICAL();/* 进入临界区 */

/*
#pragma ASM
    PUSH IE; // 保存中断状态
    CLR EA; // 关中断
#pragma ENDASM
*/

	t=inTxBuf;t++;
	if(t==TxBuf+LenTxBuf) t=TxBuf;
	if(t==outTxBuf){
		OS_EXIT_CRITICAL();/* 退出临界区 */

		/*
		#pragma ASM
		    POP IE;	// 恢复之前中断状态
		#pragma ENDASM
		*/

		return;
	} // TxBuf Full
	*inTxBuf=ch;
	inTxBuf=t;

	OS_EXIT_CRITICAL();/* 退出临界区 */

/*
#pragma ASM
    POP IE; // 恢复之前中断状态
#pragma ENDASM
*/

	if(TIflag){	
		OS_ENTER_CRITICAL();/* 进入临界区 */	
		TIflag=0;
		OS_EXIT_CRITICAL();/* 退出临界区 */ 
		TI=1; // 产生串口发送中断	
	}
}

void PrintStr(unsigned char *str) large reentrant // 显示字符串
{ 
	int i;
	unsigned char j;
	unsigned char ch;
		
/*
#pragma ASM
    PUSH IE;
    CLR EA;
#pragma ENDASM
*/
    /* 本函数不需要临界保护 */
	for(i=0;i<MaxLenStr;i++){
		ch=*(str+i);
		if(ch=='\0') break;
		else if(ch=='\n'){PrintChar(10);PrintChar(13);} 
		else if(ch=='\t'){
			for(j=0;j<TABNum;j++)
				PrintChar(' ');
		}
		else PrintChar(ch);
	}

/*
#pragma ASM
    POP IE;
#pragma ENDASM
*/
}

void ClrScr(void) large reentrant // 清屏
{        
	PrintStr("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); // 25个回车换行清屏
}

