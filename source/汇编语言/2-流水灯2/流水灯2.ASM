;查表法流水灯
;使用杜邦线连接P1与LED端口J9
       ORG   00H

START:  MOV   DPTR,#TABLE    ; 将表的地址存入数据指针
LOOP:   CLR   A
        MOVC  A,@A+DPTR      ;到数据指针所指的地址取码
        CJNE  A,#01,LOOP1    ; 取出的码是否01H？否则跳到LOOP1
        JMP   START
LOOP1:  MOV   P1,A           ;取出的值输出到P1端口
        MOV   R3,#20         ;用于改变延时长度
        CALL  DELAY
        INC   DPTR
        JMP   LOOP
DELAY: MOV   R4,#20
D1:    MOV   R5,#248
        DJNZ  R5,$
        DJNZ  R4,D1
        DJNZ  R3,DELAY
        RET
TABLE:  DB    0FEH,0FDH,0FBH,0F7H  ;左移
        DB    0EFH,0DFH,0BFH,7FH
        DB    0FEH,0FDH,0FBH,0F7H  ;左移
        DB    0EFH,0DFH,0BFH,7FH
        DB    7FH,0BFH,0DFH,0EFH    ;右移
        DB    0F7H,0FBH,0FDH,0FEH
        DB    7FH,0BFH,0DFH,0EFH    ;右移
        DB    0F7H,0FBH,0FDH,0FEH
        DB    00H,0FFH,00H,0FFH     ;闪烁
        DB    01H                   ;结束码
        END

