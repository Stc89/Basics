/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                           (c) Copyright 1992-2001, Jean J. Labrosse, Weston, FL
*                                           All Rights Reserved
*
*
*                                           uCOS_51 for MCS-51
*
* File : OS_CFG.H
* By   : Jean J. Labrosse
* Last modified by : QQ 591881218 
*********************************************************************************************************
*/

#ifndef __OS_CFG_H__
#define __OS_CFG_H__


/*
*********************************************************************************************************
*                                         uC/OS-II CONFIGURATION
*********************************************************************************************************
*/

#define OS_EVENT_NAME_EN          0u   /* Disable names for Sem, Mutex, Mbox and Q                      */

#define OS_EVENT_MULTI_EN         0u   /* Not include code for OSEventPendMulti()                          */

#define OS_DEBUG_EN               0u   /* Disable(1) debug variables                                    */

#define OS_TASK_SW_HOOK_EN        1u   /*  Not include code for OSTaskSwHook()                          */

#define OS_APP_HOOKS_EN           0u   /* Application-defined hooks are called from the uC/OS-II hooks */

#define MAX_STK_SIZE		   1024	   /* Max. stack size 											   */

#define OS_MAX_EVENTS             5    /* Max. number of event control blocks in your application ...  */
                                       /* ... MUST be > 0                                              */
#define OS_MAX_FLAGS              2    /* Max. number of Event Flag Groups    in your application ...  */
                                       /* ... MUST be > 0                                              */
#define OS_MAX_MEM_PART           5    /* Max. number of memory partitions ...                         */
                                       /* ... MUST be > 0                                              */
#define OS_MAX_QS                 2    /* Max. number of queue control blocks in your application ...  */
                                       /* ... MUST be > 0                                              */
#define OS_MAX_TASKS             11    /* Max. number of tasks in your application ...                 */
                                       /* ... MUST be >= 2                                             */

#define OS_TICK_STEP_EN           0u   /* Disable tick stepping feature for uC/OS-View                  */

#define TASK_START_PRIO			  2	   /* App start prio  											   */
#define OS_LOWEST_PRIO           12    /* Defines the lowest priority that can be assigned ...         */
                                       /* ... MUST NEVER be higher than 63!                            */

#define TASK_STK_SIZE 			512    /* Default task stack size 									   */

#define OS_TASK_IDLE_STK_SIZE   512    /* Idle task stack size (# of OS_STK wide entries)              */

#define OS_TASK_STAT_EN           0    /* Enable (1) or Disable(0) the statistics task                 */
#define OS_TASK_STAT_STK_SIZE   512    /* Statistics task stack size (# of OS_STK wide entries)        */

#define OS_TASK_PROFILE_EN        0u   /*  Not include variables in OS_TCB for profiling               */

#define OS_TASK_NAME_EN           0u   /*     Disable task names                                        */

#define OS_TASK_STAT_STK_CHK_EN   0u   /*     Check task stacks from statistic task                    */

#define OS_TMR_EN                 0u   /* Enable (1) or Disable (0) code generation for TIMERS         */

#define OS_TASK_REG_TBL_SIZE      0u   /*     Size of task variables array (#of INT32U entries)        */

#define OS_ARG_CHK_EN             0    /* Enable (1) or Disable (0) argument checking                  */
#define OS_CPU_HOOKS_EN           1    /* uC/OS-II hooks are found in the processor port files         */


                                       /* ----------------------- EVENT FLAGS ------------------------ */
#define OS_FLAG_EN                0    /* Enable (1) or Disable (0) code generation for EVENT FLAGS    */
#define OS_FLAG_WAIT_CLR_EN       0    /* Include code for Wait on Clear EVENT FLAGS                   */
#define OS_FLAG_ACCEPT_EN         0    /*     Include code for OSFlagAccept()                          */
#define OS_FLAG_DEL_EN            0    /*     Include code for OSFlagDel()                             */
#define OS_FLAG_QUERY_EN          0    /*     Include code for OSFlagQuery()                           */

#define OS_FLAG_NAME_EN           0u   /*     Disable names for event flag group                        */
#define OS_FLAGS_NBITS           8u   /* Size in #bits of OS_FLAGS data type (8, 16 or 32)            */

                                       /* -------------------- MESSAGE MAILBOXES --------------------- */
#define OS_MBOX_EN                1    /* Enable (1) or Disable (0) code generation for MAILBOXES      */
#define OS_MBOX_ACCEPT_EN         0    /*     Include code for OSMboxAccept()                          */
#define OS_MBOX_DEL_EN            0    /*     Include code for OSMboxDel()                             */
#define OS_MBOX_POST_EN           1    /*     Include code for OSMboxPost()                            */
#define OS_MBOX_POST_OPT_EN       0    /*     Include code for OSMboxPostOpt()                         */
#define OS_MBOX_QUERY_EN          0    /*     Include code for OSMboxQuery()                           */

#define OS_MBOX_PEND_ABORT_EN     0u   /*     Not include code for OSMboxPendAbort()                       */


                                       /* --------------------- MEMORY MANAGEMENT -------------------- */
#define OS_MEM_EN                 0    /* Enable (1) or Disable (0) code generation for MEMORY MANAGER */
#define OS_MEM_QUERY_EN           0    /*     Include code for OSMemQuery()                            */

#define OS_MEM_NAME_EN            0u   /*     Disable memory partition names                            */


                                       /* ---------------- MUTUAL EXCLUSION SEMAPHORES --------------- */
#define OS_MUTEX_EN               0    /* Enable (1) or Disable (0) code generation for MUTEX          */
#define OS_MUTEX_ACCEPT_EN        0    /*     Include code for OSMutexAccept()                         */
#define OS_MUTEX_DEL_EN           0    /*     Include code for OSMutexDel()                            */
#define OS_MUTEX_QUERY_EN         0    /*     Include code for OSMutexQuery()                          */


                                       /* ---------------------- MESSAGE QUEUES ---------------------- */
#define OS_Q_EN                   0    /* Enable (1) or Disable (0) code generation for QUEUES         */
#define OS_Q_ACCEPT_EN            0    /*     Include code for OSQAccept()                             */
#define OS_Q_DEL_EN               0    /*     Include code for OSQDel()                                */
#define OS_Q_FLUSH_EN             0    /*     Include code for OSQFlush()                              */
#define OS_Q_POST_EN              0    /*     Include code for OSQPost()                               */
#define OS_Q_POST_FRONT_EN        0    /*     Include code for OSQPostFront()                          */
#define OS_Q_POST_OPT_EN          0    /*     Include code for OSQPostOpt()                            */
#define OS_Q_QUERY_EN             0    /*     Include code for OSQQuery()                              */

#define OS_Q_PEND_ABORT_EN        0u   /*     Not include code for OSQPendAbort()                          */


                                       /* ------------------------ SEMAPHORES ------------------------ */
#define OS_SEM_EN                 0    /* Enable (1) or Disable (0) code generation for SEMAPHORES     */
#define OS_SEM_ACCEPT_EN          0    /*    Include code for OSSemAccept()                            */
#define OS_SEM_DEL_EN             0    /*    Include code for OSSemDel()                               */
#define OS_SEM_QUERY_EN           0    /*    Include code for OSSemQuery()                             */

#define OS_SEM_SET_EN             0u   /*    Not include code for OSSemSet()                               */
#define OS_SEM_PEND_ABORT_EN      0u   /*    Not include code for OSSemPendAbort()                         */


                                       /* --------------------- TASK MANAGEMENT ---------------------- */
#define OS_TASK_CHANGE_PRIO_EN    0    /*     Include code for OSTaskChangePrio()                      */
#define OS_TASK_CREATE_EN         1    /*     Include code for OSTaskCreate()                          */
#define OS_TASK_CREATE_EXT_EN     0    /*     Include code for OSTaskCreateExt()                       */
#define OS_TASK_DEL_EN            1    /*     Include code for OSTaskDel()                             */
#define OS_TASK_SUSPEND_EN        0    /*     Include code for OSTaskSuspend() and OSTaskResume()      */
#define OS_TASK_QUERY_EN          0    /*     Include code for OSTaskQuery()                           */


                                       /* --------------------- TIME MANAGEMENT ---------------------- */
#define OS_TIME_DLY_HMSM_EN       1    /*     Include code for OSTimeDlyHMSM()                         */
#define OS_TIME_DLY_RESUME_EN     0    /*     Include code for OSTimeDlyResume()                       */
#define OS_TIME_GET_SET_EN        0    /*     Include code for OSTimeGet() and OSTimeSet()             */


                                       /* ---------------------- MISCELLANEOUS ----------------------- */
#define OS_SCHED_LOCK_EN          0    /*     Include code for OSSchedLock() and OSSchedUnlock()       */


#define OS_TICKS_PER_SEC         50    /* Set the number of ticks in one second                        */

#define OS_TMR_CFG_NAME_EN        0u   /*     Determine timer names                                    */


#define TIMER_20MS_TH0    	   0x70    /* CPU=22.1184MHz, OS_TICKS_PER_SEC=50, TH0=0x70 			   */
#define TIMER_20MS_TL0    	   0x00	   /* CPU=22.1184MHz, OS_TICKS_PER_SEC=50, TL0=0x00 			   */

#define OS_TIME_TICK_HOOK_EN      0u   /*     Not include code for OSTimeTickHook()                        */


typedef INT16U             OS_FLAGS;   /* Date type for event flag bits (8, 16 or 32 bits)             */

#endif

