;打开任意串口调试软件
;打开对应的串口，可以在设备管理器中看到
;设置波特率为9600，8个数据位，1个停止位，无奇偶校验
;在发送栏输入任意数字或者字符串，点击发送，接收区能接收到相同的信息
;发送格式与接收格式必须相同，如都是字符或者都是十六进制格式
        ORG 0000H
        AJMP MAIN
        ORG 0023H
        AJMP RECEIVE          ;跳转到接收中断入口
        ORG 0030H

MAIN:   MOV TMOD,#20H         ;T1工作方式2
        MOV TH1,#0FDH         ;波特率9600
        MOV SCON,#50H         ;传口工作方式1，允许中断接受
        SETB EA               ;打开总中断
        SETB ES               ;打开串口中断
        SETB TR1              ;打开定时器1
        AJMP $


RECEIVE:
        CLR RI
        MOV A,SBUF            ;串口接收数据
        MOV R0,A
        MOV SBUF,A            ;将接收的数据再传送给计算机
        JNB TI,$
        CLR TI
        MOV A,R0

        ;送LED显示
        MOV P1,A
        RETI


TAB:    DB 0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H,90H    ;共阳字码表

        END
