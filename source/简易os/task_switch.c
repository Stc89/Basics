#include "task_switch.h"
#include "reg51.h"
#include "core.h"


/* 进入临界段 */
char os_cpu_sr_save(void)
{
	__asm mov r7,IE		//得到 「IE」中断控制寄存器值
	__asm mov IE,#0
	__asm ret			//返回值是在r7中
	return 0;			//返回这条指令实际不会被执行到,但因为这个函数确实要返回值,所以写一下(不然会有警告)
}


/* 退出临界段 */
void os_cpu_sr_restore(char cpu_sr)
{
	cpu_sr = cpu_sr;	//第一个参数(char类型)是存在r7里面的,
	__asm mov IE,r7		//恢复中断控制寄存器值
	__asm ret			//也可以没有(函数会有ret)
}



/* 任务堆栈初始化 */
unsigned char os_tesk_stack_init(unsigned char stack_point)
{
	unsigned char r_sp = SP;
	SP = stack_point;	//寄存器入栈(在此之前不能有任何运算操作,不然会改变寄存器值)
	__asm PUSH ACC		//累加器	
	__asm PUSH B		//用于乘除的寄存器
	__asm PUSH DPH		//数据指针，用途大
	__asm PUSH DPL		//数据指针，用途大
	__asm PUSH PSW		//标志位寄存器
	__asm PUSH 0
	__asm PUSH 1
	__asm PUSH 2
	__asm PUSH 3
	__asm PUSH 4
	__asm PUSH 5
	__asm PUSH 6
	__asm PUSH 7

	stack_point = SP;
	SP = r_sp;

	return stack_point;
}


/*因为没有对PC直接操作的指令,但中断过程和过程调用可以使PC入栈,
中断返回,过程返回可以,使PC出栈,可以间接的利用此方法对PC操作*/

/* 系统延时 */
void os_delay(unsigned char tisks)
{
	unsigned char i;

	if(tisks > 0)
	{
		EA = 0;						//直接操作,而不用临界段的方法主要是为了任务切换更快
		/*压栈*/
		__asm PUSH ACC				//寄存器入栈(在此之前不能有任何运算操作,不然会改变寄存器值)
		__asm PUSH B
		__asm PUSH DPH
		__asm PUSH DPL
		__asm PUSH PSW
		__asm PUSH 0
		__asm PUSH 1
		__asm PUSH 2
		__asm PUSH 3
		__asm PUSH 4
		__asm PUSH 5
		__asm PUSH 6
		__asm PUSH 7
		os_tcb[os_task_running_id].os_task_stcak_top = SP;
		os_tcb[os_task_running_id].os_tsak_wait_tick = tisks;	//延时时间
		os_tcb[os_task_running_id].suspend = 1;					//因为有延时,所以先挂起本任务
		for(i=0; i<MAX_TASK; i++)								//找到已经就绪,未被挂起,且优先级最高的任务
		{
			if(os_task_rdy_tab & os_map_tab[i])
			{
				if(0 == os_tcb[i].suspend)
				{
					break;
				}
			}
		}
		/*可执行的最高优先级任务*/
		os_task_running_id = i;

		SP = os_tcb[os_task_running_id].os_task_stcak_top;	//最高优先级任务的栈顶
		/*出栈*/
		__asm POP 7
		__asm POP 6
		__asm POP 5
		__asm POP 4
		__asm POP 3
		__asm POP 2
		__asm POP 1
		__asm POP 0
		__asm POP PSW
		__asm POP DPL
		__asm POP DPH
		__asm POP B
		__asm POP ACC
		EA = 1;
	}
}

/* 系统心跳更新 */
void os_time_tick(void)
{
	unsigned char i;
	
	for(i=0; i<MAX_TASK; i++)
	{
		if(os_tcb[i].os_tsak_wait_tick)
		{
			os_tcb[i].os_tsak_wait_tick--;
			/*没有等待时间,则任务进入就绪状态*/
			if(0 == os_tcb[i].os_tsak_wait_tick)
			{
				os_tcb[i].suspend = 0;
			}
		}
	}
}

/* 
任务切换心跳 5ms
interrupt 1是定时器中断 
using 0 默认用,所有的寄存器会自动入栈
用using 1 2 3 则需要手动对r0-r7入栈,出栈(请查看寄存器组选择(看任意一本讲51的书))
*/
void timer0_isr(void) interrupt 1
{
	unsigned char i;
	char cpu_sr;

	if(os_true == os_running)
	{
		os_enter_critical();
		os_int_enter();
		
		os_time_tick();
		/*当然,51单片机最多只能有一次中断嵌套,os_int_count最大为2(+本次)*/
		if(1 == os_int_count)
		{
			os_tcb[os_task_running_id].os_task_stcak_top = SP;	
			/*找到已经就绪,未被挂起,且优先级最高的任务(任务调度器)*/
			for(i=0; i<MAX_TASK; i++)
			{
				if(os_task_rdy_tab & os_map_tab[i])
				{
					/*用suspend 判断休眠时间已经到，可以执行任务部分*/
					if(0 == os_tcb[i].suspend)
					{
						break;
					}
				}
			}
			/*现在执行的任务就是优先级最高的,所以不需要任务切换*/
			if(os_task_running_id != i)
			{
				/*可执行的最高优先级任务*/
				os_task_running_id = i;
				/*最高优先级任务的栈顶*/
				/*SP是堆栈指针，指向栈顶*/
				SP = os_tcb[os_task_running_id].os_task_stcak_top;
			}
		}
		/*清除中断标志*/
		TF0 = 0;
		/*时间重装载*/
		TH0 = 0xee;
		TL0 = 0x00;
		os_int_exit();
		os_exit_critical();
	}
	
}
