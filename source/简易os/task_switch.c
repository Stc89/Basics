#include "task_switch.h"
#include <stc12c5a60s2.h>
#include "core.h"


/* �����ٽ�� */
char os_cpu_sr_save(void)
{
	__asm mov r7,IE		//�õ��жϿ��ƼĴ���ֵ
	__asm mov IE,#0
	__asm ret			//����ֵ����r7��
	return 0;			//��������ָ��ʵ�ʲ��ᱻִ�е�,����Ϊ�������ȷʵҪ����ֵ,����дһ��(��Ȼ���о���)
}


/* �˳��ٽ�� */
void os_cpu_sr_restore(char cpu_sr)
{
	cpu_sr = cpu_sr;	//��һ������(char����)�Ǵ���r7�����,
	__asm mov IE,r7		//�ָ��жϿ��ƼĴ���ֵ
	__asm ret			//Ҳ����û��(��������ret)
}



/* �����ջ��ʼ�� */
unsigned char os_tesk_stack_init(unsigned char stack_point)
{
	unsigned char r_sp = SP;
	SP = stack_point;
	__asm PUSH ACC				//�Ĵ�����ջ(�ڴ�֮ǰ�������κ��������,��Ȼ��ı�Ĵ���ֵ)
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







/*��Ϊû�ж�PCֱ�Ӳ�����ָ��,���жϹ��̺͹��̵��ÿ���ʹPC��ջ,
�жϷ���,���̷��ؿ���,ʹPC��ջ,���Լ�ӵ����ô˷�����PC����*/

/* ϵͳ��ʱ */
void os_delay(unsigned char tisks)
{
	unsigned char i;
//	char cpu_sr;
	
	if(tisks > 0)
	{	
		//os_enter_critical();		
		EA = 0;						//ֱ�Ӳ���,�������ٽ�εķ�����Ҫ��Ϊ�������л�����
		__asm PUSH ACC				//�Ĵ�����ջ(�ڴ�֮ǰ�������κ��������,��Ȼ��ı�Ĵ���ֵ)
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
		

		os_tcb[os_task_running_id].os_tsak_wait_tick = tisks;	//��ʱʱ��
		os_tcb[os_task_running_id].suspend = 1;					//��Ϊ����ʱ,�����ȹ�������
		for(i=0; i<MAX_TASK; i++)								//�ҵ��Ѿ�����,δ������,�����ȼ���ߵ�����
		{
			if(os_task_rdy_tab & os_map_tab[i])
			{
				if(0 == os_tcb[i].suspend)
				{
					break;
				}
			}
		}
		os_task_running_id = i;								//��ִ�е�������ȼ�����

		SP = os_tcb[os_task_running_id].os_task_stcak_top;	//������ȼ������ջ��
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
		//__asm RET	//�����Ǻ�������,�� ret
		//__asm reti
	}
}

/* ϵͳ�������� */
void os_time_tick(void)
{
	unsigned char i;
	
	for(i=0; i<MAX_TASK; i++)
	{
		if(os_tcb[i].os_tsak_wait_tick)
		{
			os_tcb[i].os_tsak_wait_tick--;
			if(0 == os_tcb[i].os_tsak_wait_tick) 	//û�еȴ�ʱ��,������������״̬
			{
				os_tcb[i].suspend = 0;		//
			}
		}
	}
	
}


/* �����л����� */
void timer0_isr(void) interrupt 1 	//using 0 Ĭ����,���еļĴ������Զ���ջ, 
{							//  ��using 1 2 3 ����Ҫ�ֶ���r0-r7��ջ,��ջ(��鿴�Ĵ�����ѡ��(������һ����51����))
	unsigned char i;
	char cpu_sr;
	
	if(os_true == os_running)
	{
		os_enter_critical();
		
	/*	�Ĵ�����ջ(ע�͵Ĳ������ڽ����жϺ���ǰ�Ѿ�ѹ��ջ��
		(�������û���PCѹջ,�жϺ�����������PCѹջ,�������������Ĵ���ѹջ)
		,������д�����˳��)	*/
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
		if(1 == os_int_count)		//��Ȼ,51��Ƭ�����ֻ����һ���ж�Ƕ��,os_int_count���Ϊ2(+����)
		{
			os_tcb[os_task_running_id].os_task_stcak_top = SP;	
			
			for(i=0; i<MAX_TASK; i++)		//�ҵ��Ѿ�����,δ������,�����ȼ���ߵ�����(���������)
			{
				if(os_task_rdy_tab & os_map_tab[i])
				{
					if(0 == os_tcb[i].suspend)
					{
						break;
					}
				}
			}
			if(os_task_running_id != i)		//����ִ�е�����������ȼ���ߵ�,���Բ���Ҫ�����л�
			{
				os_task_running_id = i;			//��ִ�е�������ȼ�����
				SP = os_tcb[os_task_running_id].os_task_stcak_top;	//������ȼ������ջ��
			}
		}
		
		TF0 = 0;			//����жϱ�־
		TH0 = 0xee;			//ʱ����װ��
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
		/*��ǰ��ĵ�����ͬ(��Ȼѹջ��,��ȻҲҪ��ջ)(˵��,�����ֶ��ӵ�__asm RETI,��������⼸��POP�Ǳ���Ҫ��,
			����Ϊʲô��?    ����,��ΪĬ�������,RETIָ����Ҫ��,POP�ĺ���,��Ȼ�Ͳ���ִ��POP,�⼸���Ĵ���ֵ�ͻָ�����
			,����Ҫ����SPҲ�������� ,,,,,,,)*/
	//	__asm POP PSW			
	//	__asm POP DPL
	//	__asm POP DPH
	//	__asm POP B
	//	__asm POP ACC
		/*д��д��һ��(д��,�������ִ������������Ĵ�����PC��ջ,
		��д�Ļ�,C����д���жϺ���,������������,���ں����һ��retiָ��,������ִ����ͬ�Ĺ���)
		��д������,ͬѧ��ͻȻ����ôһ���뷨,�ܲ�����ret(reti���жϱ�־λ����������,���������ֶ������־λ�Ϳ�����)
		,��������ָ���������жϺ���,��Ȼ��ЩPOP֮���ָ�����Ҫ�յ�д��,�������������,��ҿ��Ծ���ĳ��Թ�^_^��*/
	//	__asm RETI	
	//	__asm	ret   //���񲻿���,Ϊʲô��?
	}
	
}
