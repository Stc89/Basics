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
* File : serial.h
* From : yang yi
* Last modified by : QQ 591881218
*********************************************************************************************************
*/

#ifndef __SERIAL_H__
#define __SERIAL_H__


/* 收发缓冲区长度 */
#define LenTxBuf        2000    // Don't too small, because it will cause display abnormal.
#define LenRxBuf        50

#define MaxLenStr       100     // buf[MaxLenStr+1] for '\0'

#define	TABNum          4       // TAB键移动长度


void Serial(void) large reentrant; // 串口中断服务子程序

void InitSerial(void) large reentrant; // 串口初始化
void InitSerialBuffer(void) large reentrant; // 串口缓冲区初始化
bit Getch(unsigned char *ch) large reentrant;	// 从串口缓冲区读1字节数据
void PrintChar(unsigned char ch) large reentrant;	// 显示字符
void PrintStr(unsigned char *str) large reentrant; // 显示字符串
void ClrScr(void) large reentrant; // 清屏


#endif
