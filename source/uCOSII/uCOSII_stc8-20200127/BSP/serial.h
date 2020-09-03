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


/* �շ����������� */
#define LenTxBuf        2000    // Don't too small, because it will cause display abnormal.
#define LenRxBuf        50

#define MaxLenStr       100     // buf[MaxLenStr+1] for '\0'

#define	TABNum          4       // TAB���ƶ�����


void Serial(void) large reentrant; // �����жϷ����ӳ���

void InitSerial(void) large reentrant; // ���ڳ�ʼ��
void InitSerialBuffer(void) large reentrant; // ���ڻ�������ʼ��
bit Getch(unsigned char *ch) large reentrant;	// �Ӵ��ڻ�������1�ֽ�����
void PrintChar(unsigned char ch) large reentrant;	// ��ʾ�ַ�
void PrintStr(unsigned char *str) large reentrant; // ��ʾ�ַ���
void ClrScr(void) large reentrant; // ����


#endif
