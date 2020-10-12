#include "core.h"
#include "reg51.h"
#include "task_switch.h"


static void task_idle(void);


volatile TCB idata os_tcb[MAX_TASK];
/*�ö�ά����Ƚ��˷ѿռ�(������������ջҪ��ram������,����ʵ�����������ͬ�Ŀռ�)
,��һ��������ô��Ŀռ䲢�����(�������Ǹ�����������������һά����)*/
unsigned char idata os_tsak_stack[MAX_TASK][40];	


const unsigned char os_map_tab[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
	
volatile unsigned char os_task_rdy_tab;				//���������(ֻҪ����,�����)
volatile unsigned char os_task_running_id;			//�������е�����id
volatile unsigned char os_int_count;				//�����ж�Ƕ�ײ�Ĵ���
bit os_running = os_false;							//ϵͳ�Ƿ�����

/* ��ʼ��ϵͳ */
void os_init(void)
{
	EA = 0;
	ET0 = 1;			//��ʱ��0���ж�
	TMOD &= 0xf0;
	TMOD |= 0x01;		//16λ������
	TH0 = 0xee;
	TL0 = 0x00;			//5ms�ж�
	os_int_count = 0;
	os_task_rdy_tab = 0;
	os_task_create(MAX_TASK-1,task_idle,(unsigned char)os_tsak_stack[MAX_TASK-1]);
}


/* ��������,���봴��,��ϵͳ�������������ʱ,ϵͳҪ����������,һ���������ȼ����,��ʼ��ʱ������ */
static void task_idle(void)
{
	while(1)
	{
		//���Բ�������ʱ,
	}
}



/* �������� */
void os_task_create(unsigned char task_id,void (*task)(void),unsigned char stack_point)
{
	char cpu_sr;
	
	os_enter_critical();
	((unsigned char idata*)stack_point)[0] = (unsigned int)task;
	((unsigned char idata*)stack_point)[1] = (unsigned int)task >> 8;	//�����ַ����ջ�������ֽ�
	os_tcb[task_id].os_task_stcak_bottom = stack_point;					//ջ��
//	os_tcb[task_id].os_task_stcak_top = stack_point + 14;				//ջ��(��ʼ����Ӧ��,�������ջ��ʼ�����ָ��)
	//ΪʲôҪ��1?(��Ϊջ���Ѿ���������task)��Ȼ������ʼ��������,�������Ҳ��(ֻ�����ö��˶�Ϊʲô14���ɻ�)
	os_tcb[task_id].os_task_stcak_top = os_tesk_stack_init(stack_point + 1);	
	os_task_rdy_tab |= os_map_tab[task_id];								//�������������
	os_tcb[task_id].os_tsak_wait_tick = 0;								//�޵ȴ�
	os_tcb[task_id].suspend = 0;										//�����Ծ���
	os_exit_critical();
}

/* ����ʼ���� */
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
	os_task_running_id = i;		//���ȼ���ߵ�������
	EA = 1;
	SP = os_tcb[os_task_running_id].os_task_stcak_bottom + 1;	//�����������ַ
	TR0 = 1;
	os_running = os_true;
}

/* �����ж� */
void os_int_enter(void)
{
	if(os_true == os_running)
	{
		if(os_int_count < 256)	//51��Ƭ���ж����ֻ�ܽ���һ��Ƕ��,os_int_count���Ϊ2,���뱾����ǰ,���Ϊ1
		{
			os_int_count++;
		}
	}
}

/* �˳��ж� */
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


