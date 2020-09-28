#include "core.h"
#include "task_switch.h"
#include <stc12c5a60s2.h>

sbit led2 = P1^2;
sbit led3 = P1^3;


/* 系统初始化 */
void system_init(void)
{

}

void test(void)
{
	char i = 0;
	
	os_delay(10);	
	i++;
	i++;
}

void task_0(void)
{
	while(1)
	{
		led2 = 0;
		test();
		led2 = 1;
		os_delay(10);
	}
}

void task_1(void)
{
	while(1)
	{
		led3 = 0;
		os_delay(100);
		led3 = 1;
		os_delay(100);
	}
}

char *p = "hello";

int main(void)
{
	system_init();
	os_init();
	os_task_create(1,task_1,(unsigned char)os_tsak_stack[1]);
	os_task_create(0,task_0,(unsigned char)os_tsak_stack[0]);
	os_start();
	
	return 0;
}


