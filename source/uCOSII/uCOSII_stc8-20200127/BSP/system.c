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
* File : system.c
* Created by : QQ 591881218
*********************************************************************************************************
*/

#ifndef  OS_MASTER_FILE
#include "..\..\ucos-ii\inc\includes.h"
#endif

void InitSystem(void) large reentrant // 系统初始化
{
	OSInit();
	InitTimer0();	
	InitSerial();
	InitSerialBuffer();
}

void LogoDisp(void) large reentrant // Logo display
{
	PrintStr("\n\t\t\t\t\t********************************\n");
   	PrintStr("\t\t\t\t\t*           uC/OS-II           *\n");
	PrintStr("\t\t\t\t\t*     The Real-Time Kernel     *\n");
	PrintStr("\t\t\t\t\t*      uCOS_51 for MCS-51      *\n");
    PrintStr("\t\t\t\t\t********************************\n\n\n");	
}