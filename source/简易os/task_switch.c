#include "task_switch.h"
#include <stc12c5a60s2.h>
#include "core.h"


/* 进入临界段 */
char os_cpu_sr_save(void)
{
	__asm mov r7,IE		//得到中断控制寄存器值
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
	SP = stack_point;
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
//	char cpu_sr;
	
	if(tisks > 0)
	{	
		//os_enter_critical();		
		EA = 0;						//直接操作,而不用临界段的方法主要是为了任务切换更快
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
		os_task_running_id = i;								//可执行的最高优先级任务

		SP = os_tcb[os_task_running_id].os_task_stcak_top;	//最高优先级任务的栈顶
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
		//os_exit_critical();
		//__asm RET	//后面是函数返回,即 ret
		//__asm reti
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
			if(0 == os_tcb[i].os_tsak_wait_tick) 	//没有等待时间,则任务进入就绪状态
			{
				os_tcb[i].suspend = 0;		//
			}
		}
	}
	
}


/* 任务切换心跳 */
void timer0_isr(void) interrupt 1 	//using 0 默认用,所有的寄存器会自动入栈, 
{							//  用using 1 2 3 则需要手动对r0-r7入栈,出栈(请查看寄存器组选择(看任意一本讲51的书))
	unsigned char i;
	char cpu_sr;
	
	if(os_true == os_running)
	{
		os_enter_critical();
		
	/*	寄存器入栈(注释的部分是在进入中断函数前已经压入栈中
		(函数调用会让PC压栈,中断函数不但会让PC压栈,还会对下面五个寄存器压栈)
		,就是我写的这个顺序)	*/
	//	__asm PUSH ACC			
	//	__asm PUSH B
	//	__asm PUSH DPH
	//	__asm PUSH DPL
	//	__asm PUSH PSW
//		__asm PUSH 0
//		__asm PUSH 1
//		__asm PUSH 2
//		__asm PUSH 3
//		__asm PUSH 4
//		__asm PUSH 5
//		__asm PUSH 6
//		__asm PUSH 7
		os_int_enter();
		
		os_time_tick();
		if(1 == os_int_count)		//当然,51单片机最多只能有一次中断嵌套,os_int_count最大为2(+本次)
		{
			os_tcb[os_task_running_id].os_task_stcak_top = SP;	
			
			for(i=0; i<MAX_TASK; i++)		//找到已经就绪,未被挂起,且优先级最高的任务(任务调度器)
			{
				if(os_task_rdy_tab & os_map_tab[i])
				{
					if(0 == os_tcb[i].suspend)
					{
						break;
					}
				}
			}
			if(os_task_running_id != i)		//现在执行的任务就是优先级最高的,所以不需要任务切换
			{
				os_task_running_id = i;			//可执行的最高优先级任务
				SP = os_tcb[os_task_running_id].os_task_stcak_top;	//最高优先级任务的栈顶
			}
		}
		
		TF0 = 0;			//清除中断标志
		TH0 = 0xee;			//时间重装载
		TL0 = 0x00;
		os_int_exit();
		
		
//		__asm POP 7
//		__asm POP 6
//		__asm POP 5
//		__asm POP 4
//		__asm POP 3
//		__asm POP 2
//		__asm POP 1
//		__asm POP 0
		
		os_exit_critical();
		/*和前面的道理相同(既然压栈了,当然也要出栈)(说明,后面手动加的__asm RETI,则下面的这几跳POP是必须要的,
			这是为什么呢?    哈哈,因为默认情况下,RETI指令是要在,POP的后面,不然就不能执行POP,这几个寄存器值就恢复不了
			,最重要的是SP也就乱套了 ,,,,,,,)*/
	//	__asm POP PSW			
	//	__asm POP DPL
	//	__asm POP DPH
	//	__asm POP B
	//	__asm POP ACC
		/*写不写都一样(写了,这条语句执行完会进行上面寄存器和PC出栈,
		不写的话,C语言写的中断函数,编译器汇编过后,会在后面加一条reti指令,和上面执行相同的功能)
		【写到这里,同学我突然有这么一个想法,能不能用ret(reti对中断标志位有清零作用,这里我们手动清除标志位就可以了)
		,函数返回指令来返回中断函数,当然这些POP之类的指令就需要收到写了,程序是玩出来的,大家可以尽情的尝试哈^_^】*/
	//	__asm RETI	
	//	__asm	ret   //好像不可以,为什么呢?
	}
	
}
