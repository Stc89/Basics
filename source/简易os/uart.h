#ifndef __UART_H
#define __UART_H
typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;
void    UART1_config(u8 brt);   // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer1��������.
void    PrintString1(u8 *puts);
#endif