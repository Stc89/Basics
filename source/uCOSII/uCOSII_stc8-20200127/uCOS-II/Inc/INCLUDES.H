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
* File : INCLUDES.H
* Created by : QQ 591881218
*********************************************************************************************************
*/

#ifndef __INCLUDES_H__
#define __INCLUDES_H__


// ---------------------------------

#include "stc8_regs.h" 
#include <string.h>

// ---------------------------------


// ---------------------------------

#include "..\..\ucos-ii\mcs-51\os_cpu.h"
#include "..\..\ucos-ii\inc\os_cfg.h"
#include "..\..\ucos-ii\src\ucos_ii.h"

// ---------------------------------


// ---------------------------------

#include "..\..\bsp\serial.h"
#include "..\..\bsp\system.h"

// ---------------------------------

void InitTimer0(void) large reentrant;


#endif

