#ifndef __UART_H
#define __UART_H
typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;
void    UART1_config(u8 brt);   // 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer1做波特率.
void    PrintString1(u8 *puts);
#endif