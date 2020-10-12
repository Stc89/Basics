#include "core.h"
#include "reg51.h"
#include "task_switch.h"


static void task_idle(void);


volatile TCB idata os_tcb[MAX_TASK];
/*用二维数组比较浪费空间(比如空闲任务堆栈要的ram并不大,但和实际任务分配相同的空间)
,且一块连续这么大的空间并不多见(常见的是更具任务具体任务分配一维数组)*/
unsigned char idata os_tsak_stack[MAX_TASK][40];	


const unsigned char os_map_tab[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
	
volatile unsigned char os_task_rdy_tab;				//任务就绪表(只要创建,则就绪)
volatile unsigned char os_task_running_id;			//正在运行的任务id
volatile unsigned char os_int_count;				//进入中断嵌套层的次数
bit os_running = os_false;							//系统是否运行

/* 初始化系统 */
void os_init(void)
{
	EA = 0;
	ET0 = 1;			//定时器0开中断
	TMOD &= 0xf0;
	TMOD |= 0x01;		//16位计数器
	TH0 = 0xee;
	TL0 = 0x00;			//5ms中断
	os_int_count = 0;
	os_task_rdy_tab = 0;
	os_task_create(MAX_TASK-1,task_idle,(unsigned char)os_tsak_stack[MAX_TASK-1]);
}


/* 空闲任务,必须创建,在系统中其他任务挂起时,系统要有任务运行,一般任务优先级最低,初始化时被创建 */
static void task_idle(void)
{
	while(1)
	{
		//绝对不能有延时,
	}
}



/* 创建任务 */
void os_task_create(unsigned char task_id,void (*task)(void),unsigned char stack_point)
{
	char cpu_sr;
	
	os_enter_critical();
	((unsigned char idata*)stack_point)[0] = (unsigned int)task;
	((unsigned char idata*)stack_point)[1] = (unsigned int)task >> 8;	//任务地址放在栈底两个字节
	os_tcb[task_id].os_task_stcak_bottom = stack_point;					//栈底
//	os_tcb[task_id].os_task_stcak_top = stack_point + 14;				//栈顶(起始这里应该,对任务堆栈初始化后的指针)
	//为什么要加1?(因为栈中已经有数据了task)当然初不初始化都可以,用上面的也行(只不过好多人对为什么14有疑惑)
	os_tcb[task_id].os_task_stcak_top = os_tesk_stack_init(stack_point + 1);	
	os_task_rdy_tab |= os_map_tab[task_id];								//更新任务就绪表
	os_tcb[task_id].os_tsak_wait_tick = 0;								//无等待
	os_tcb[task_id].suspend = 0;										//任务以就绪
	os_exit_critical();
}

/* 任务开始运行 */
void os_start(void)
{
	unsigned char i;
	
	for(i=0; i<MAX_TASK; i++)
	{
		if(os_task_rdy_tab & os_map_tab[i])
		{
			break;
		}
	}
	os_task_running_id = i;		//优先级最高的先运行
	EA = 1;
	SP = os_tcb[os_task_running_id].os_task_stcak_bottom + 1;	//弹出是任务地址
	TR0 = 1;
	os_running = os_true;
}

/* 进入中断 */
void os_int_enter(void)
{
	if(os_true == os_running)
	{
		if(os_int_count < 256)	//51单片机中断最多只能进行一次嵌套,os_int_count最大为2,进入本函数前,最多为1
		{
			os_int_count++;
		}
	}
}

/* 退出中断 */
void os_int_exit(void)
{
	if(os_true == os_running)
	{
		if(os_int_count >= 1)
		{
			os_int_count--;
		}
	}
}


