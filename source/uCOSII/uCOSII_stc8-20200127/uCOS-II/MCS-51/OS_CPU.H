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
* File : OS_CPU.H
* Created by : QQ 591881218
*********************************************************************************************************
*/


#ifndef __OS_CPU_H__
#define __OS_CPU_H__

#ifdef  OS_CPU_GLOBALS
#define OS_CPU_EXT
#else
#define OS_CPU_EXT  extern
#endif

/*************************************** 与编译器有关的数据类型 ***************************************/

/* #define  BOOLEAN bit        if OS_MUTEX_EN = 0, bit can be used! */
typedef unsigned char 	BOOLEAN;	/* 不能使用bit定义，因为在结构体里无法使用 	*/
typedef unsigned char 	INT8U;		/* 无符号8位数 								*/
typedef signed char 	INT8S;		/* 有符号8位数 								*/
typedef unsigned int 	INT16U;		/* 无符号16位数 							*/
typedef signed int 		INT16S;		/* 有符号16位数								*/
typedef unsigned long 	INT32U;		/* 无符号32位数 							*/		
typedef signed long 	INT32S;		/* 有符号32位数 							*/
typedef float 			FP32;		/* 单精度浮点数 							*/
typedef double 			FP64;		/* 双精度浮点数 							*/
typedef unsigned char 	OS_STK;		/* 定义堆栈入口宽度为8位 					*/
typedef unsigned char 	OS_CPU_SR;	/* 定义CPU状态字的宽度为8位 				*/

// ---------------------------------

#define REENTRANT		reentrant 	/* 使Keil生成可重入代码 					*/

/* 存储类型的宏 																*/

#define DF_DATA			data
#define DF_BDATA		bdata
#define DF_IDATA		idata
#define DF_XDATA		xdata
#define DF_PDATA		pdata
#define DF_CODE			code

// ---------------------------------

/* 以下是兼容uC/OS v1.XX的数据类型，在uC/OS-II中没有使用  						*/

#define BYTE 			INT8S
#define UBYTE 			INT8U
#define WORD 			INT16S
#define UWORD 			INT16U
#define LONG 			INT32S
#define ULONG 			INT32U

/***************************************** 与处理器有关的代码 *****************************************/

#define OS_CRITICAL_METHOD	1 /* 本工程使用第一种方式开关中断 			*/

#if OS_CRITICAL_METHOD==1
#define OS_ENTER_CRITICAL()	EA=0 /* 直接禁止中断 						*/
#define OS_EXIT_CRITICAL()	EA=1 /* 直接允许中断 						*/
#endif

#if OS_CRITICAL_METHOD==2 
#define OS_ENTER_CRITICAL() /* 利用堆栈保存中断状态，再关中断 			*/
#define OS_EXIT_CRITICAL() /* 将程序状态字从堆栈弹出，再开中断 			*/
#endif

/* 很遗憾，第三种方式“屡试不爽” */
#if OS_CRITICAL_METHOD==3
#define OS_ENTER_CRITICAL()	cpu_sr=IE & 0x80;IE &= 0x7F /* 禁止中断 	*/
#define OS_EXIT_CRITICAL()	IE |= cpu_sr /* 允许中断 					*/
#endif 

#define OS_STK_GROWTH	0 /* MCS-51堆栈从下往上增长，1=向下，0=向上 	*/

#define OS_TASK_SW()	OSCtxSw() /* 任务级的任务切换宏 				*/


#endif
