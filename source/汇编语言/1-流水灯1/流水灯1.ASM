;流水灯程序

P1M0 DATA 092H
P1M1 DATA 091H
ORG 00H
MOV P1M0,#00000000B
MOV P1M1,#00000000B
MOV P1,#11111111B

START:
    CLR P1.4        ; 置0，
    CLR P1.5        ; 置0，
    CLR P1.6        ; 置0，
    LCALL DELAY     ; 延时0.2s
    SETB P1.4       ; 置1，点亮LED
    SETB P1.5       ; 置1，点亮LED
    SETB P1.6       ; 置1，点亮LED
    LCALL DELAY     ; 延时0.2s
    LJMP START      ; 进行重新循环
DELAY:
    MOV R5,#200      ; 执行MOV指令为1个机器周期
D1:
    MOV R6, #200     ; 执行的时间为：1*20 个机器周期
D2:
    MOV R7, #248    ; 该条指令执行了: 1*20*20
    DJNZ R7,$       ; 该条指令执行了: 2*20*20*248
    DJNZ R6, D2     ; 该条指令执行了: 2*20*20 个机器周期
    DJNZ R5, D1     ; 该条指令执行了: 2*20
    RET             ; 该条指令执行了: 2

END


