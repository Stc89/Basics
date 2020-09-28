#ifndef __TASK_SWITCH_H__
#define __TASK_SWITCH_H__


char os_cpu_sr_save(void);
void os_cpu_sr_restore(char cpu_sr);
void os_delay(unsigned char tisks);
unsigned char os_tesk_stack_init(unsigned char stack_point);
#endif



