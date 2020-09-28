#ifndef __CORE_H__
#define __CORE_H__

#define MAX_TASK	3		//最大任务数(因为必须有一个空闲任务,所以实际任务数是MAX_TASK-1)

#include "task_switch.h"
/* 段保护 */
#define os_enter_critical()	{cpu_sr = os_cpu_sr_save();}
#define os_exit_critical()	{os_cpu_sr_restore(cpu_sr);}

#define os_true		 	1
#define os_false 		0

/*任务控制表 */
typedef struct os_task_control_table
{
	unsigned char os_tsak_wait_tick;
	unsigned char os_task_stcak_top;
	unsigned char os_task_stcak_bottom;
	unsigned char suspend;
}TCB;





extern volatile TCB idata os_tcb[MAX_TASK];
extern unsigned char idata os_tsak_stack[MAX_TASK][20];
extern const unsigned char os_map_tab[];
extern volatile unsigned char os_task_rdy_tab;				//任务就绪表
extern volatile unsigned char os_task_running_id;			//正在运行的任务id
extern volatile unsigned char os_int_count;					//进入中断嵌套层的次数
extern bit os_running;										//系统是否运行

void os_init(void);
void os_start(void);
void os_task_create(unsigned char task_id,void (*task)(void),unsigned char stack_point);
void os_int_enter(void);
void os_int_exit(void);
#endif

