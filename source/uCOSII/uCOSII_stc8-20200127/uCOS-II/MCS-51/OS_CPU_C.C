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
* File : OS_CPU_C.C
* Created by : QQ 591881218
*********************************************************************************************************
*/

//#define  OS_CPU_GLOBALS

#include "includes.h"

/*
*********************************************************************************************************
*                                             初始化任务栈
*
* 描述       : 本函数为OSTaskCreate()和OSTaskCreateExt()函数所调用，用于任务栈的初始化。初始化后的任务栈
*			   看起来像刚刚发生过一次中断并将所有的寄存器都保存进了堆栈的情形一样。
*
* 参数       : task		任务代码的指针。
*
*			   p_arg	当任务开始执行时传递给任务的参数的指针。
*
*			   ptos		分配给任务堆栈的栈顶指针。
*
*			   opt		用于设定OSTaskCreateExt()的选项，指定是否允许堆栈检验，是否将堆栈清零，是否进行
*						浮点操作等。当用OSTaskCreate()函数调用时，设置为0。
*
* 返回值	 : 返回栈顶指针
* 
* 注意       : 任务栈结构示意图(杨屹)
*
*                                    ---------- -
*                 用户栈最高地址---->|        | |
*                                    ---------- |
*                                    |   ...  | 仿真堆栈空间
*----------                          ---------- | 每任务一个
*|OSTCBCur|               ?C_XBP---->|        | | KEIL自动处理
*----------                          ---------- -
*    |                               |空闲间隔|
*    |     -----------------------   ----------                           ----------
*    \---->|OSTCBCur->OSTCBStkPtr|   |?C_XBP低|                    SP---->|        |
*          -----------------------   ----------                           ----------
*                     |              |?C_XBP高|                           |        |
*                     |              ---------- -                         ----------
*                     |              |        | |                         |   .    |
*                     |              ---------- |                         |   .    |
*                     |              |        | |                         |   .    |
*                     |              ---------- |                         ----------
*                     |              |   .    |长度                       |        | +1
*                     |              |   .    | |                         ----------
*                     |              |   .    | |             OSStack---->|        | 0
*                     |              ---------- |                         ----------
*                     |              |        | |          OSStkStart---->| 不关心 | -1  低地址
*                     |              ---------- -                         ----------
*                     \------------->|  长度  | 低地址                   系统硬件堆栈
*                                    ----------
*                                     用户堆栈                        长度=SP-OSStkStart
*********************************************************************************************************
*/
OS_STK         *OSTaskStkInit           (void           (*task)(void *p_arg),
                                       void            *p_arg,
                                       OS_STK          *ptos,
                                       INT16U           opt) large reentrant
{
	OS_STK *stk;
	p_arg=p_arg;
	opt	  =opt;						/* opt没被用到，保留此语句防止警告产生 			*/
	stk	  =(OS_STK *)ptos;			/* 任务堆栈最低有效地址 						*/
	*stk++=15;						/* 任务堆栈长度 								*/
	*stk++=(INT16U)task & 0xFF;		/* 任务代码地址低8位 							*/
	*stk++=(INT16U)task >> 8;		/* 任务代码地址高8位 							*/
	/* 处理器是按特定的顺序将寄存器存入堆栈的，所以用户在将寄存器存入堆栈的时候也要依照这一顺序 */
	*stk++=0x00;					/* PSW 											*/
	*stk++=0x0A;					/* ACC 											*/
	*stk++=0x0B;					/* B 											*/
	*stk++=0x00;					/* DPL 											*/
	*stk++=0x00;					/* DPH 											*/
	*stk++=0x00;					/* R0 											*/
	*stk++=0x01;					/* R1 											*/
	*stk++=0x02;					/* R2 											*/
	*stk++=0x03;					/* R3 											*/	
	*stk++=0x04;					/* R4 											*/
	*stk++=0x05;					/* R5 											*/
	*stk++=0x06;					/* R6 											*/
	*stk++=0x07;					/* R7 											*/
	/* 不用保存SP，任务切换时根据用户堆栈长度计算得出 								*/
	*stk++=(INT16U)(ptos+MAX_STK_SIZE) >> 8;	/* ?C_XBP 仿真堆栈指针高8位 		*/
	*stk++=(INT16U)(ptos+MAX_STK_SIZE) & 0xFF;	/* ?C_XBP 仿真堆栈低8位 			*/
	return ((void *)ptos);	/* 返回最低地址，这里不用弹出栈顶指针是为了提高计算效率 */
}

/*********************************************** 钩子函数 ***********************************************/

#if OS_CPU_HOOKS_EN
/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                            (BEGINNING)
*
* Description: This function is called by OSInit() at the beginning of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSInitHookBegin (void) large reentrant
{
}
#endif

/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                               (END)
*
* Description: This function is called by OSInit() at the end of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSInitHookEnd (void) large reentrant
{
}
#endif

/*
*********************************************************************************************************
*                                          TASK CREATION HOOK
*
* Description: This function is called when a task is created.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being created.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
void OSTaskCreateHook (OS_TCB *ptcb) large reentrant
{
    ptcb = ptcb;                       /* Prevent compiler warning                                     */
}

/*
*********************************************************************************************************
*                                           TASK DELETION HOOK
*
* Description: This function is called when a task is deleted.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
void OSTaskDelHook (OS_TCB *ptcb) large reentrant
{
    ptcb = ptcb;                       /* Prevent compiler warning                                     */
}

/*
*********************************************************************************************************
*                                           TASK SWITCH HOOK
*
* Description: This function is called when a task switch is performed.  This allows you to perform other
*              operations during a context switch.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are disabled during this call.
*              2) It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                 will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the 
*                 task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/
void OSTaskSwHook (void) large reentrant
{
}

/*
*********************************************************************************************************
*                                           STATISTIC TASK HOOK
*
* Description: This function is called every second by uC/OS-II's statistics task.  This allows your 
*              application to add functionality to the statistics task.
*
* Arguments  : none
*********************************************************************************************************
*/
void OSTaskStatHook (void) large reentrant
{
}

/*
*********************************************************************************************************
*                                            TASK RETURN HOOK
*
* Description: This function is called if a task accidentally returns.  In other words, a task should
*              either be an infinite loop or delete itself when done.
*
* Arguments  : ptcb      is a pointer to the task control block of the task that is returning.
*
* Note(s)    : none
*********************************************************************************************************
*/

#if OS_CPU_HOOKS_EN > 0u
void  OSTaskReturnHook (OS_TCB  *ptcb) large reentrant
{
#if OS_APP_HOOKS_EN > 0u
    App_TaskReturnHook(ptcb);
#else
    (void)ptcb;
#endif
}
#endif

/*
*********************************************************************************************************
*                                           OSTCBInit() HOOK
*
* Description: This function is called by OSTCBInit() after setting up most of the TCB.
*
* Arguments  : ptcb    is a pointer to the TCB of the task being created.
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSTCBInitHook (OS_TCB *ptcb) large reentrant
{
    ptcb = ptcb;                                           /* Prevent Compiler warning                 */
}
#endif

/*
*********************************************************************************************************
*                                               TICK HOOK
*
* Description: This function is called every tick.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
void OSTimeTickHook (void) large reentrant
{
}

/*
*********************************************************************************************************
*                                             IDLE TASK HOOK
*
* Description: This function is called by the idle task.  This hook has been added to allow you to do  
*              such things as STOP the CPU to conserve power.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are enabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION >= 251
void OSTaskIdleHook (void) large reentrant
{
}
#endif

#endif

/********************************************************************************************************/

/* 初始化定时器0，用于产生时钟节拍 */
void InitTimer0(void) large reentrant
{
    TMOD = 0x03;                                //模式3
    TL0 = -(24000000UL/12/50);//0x66;                                 //65536-11.0592M/12/1000
    TH0 = (-(24000000UL/12/50)) >> 8;//0xfc;
    TR0 = 1;                                    //启动定时器
    ET0 = 1;                                    //使能定时器中断
	//EA=0; /* EA和ET0，51上电缺省值为0，EA将在OSStartHighRdy()中打开 */
  
}

