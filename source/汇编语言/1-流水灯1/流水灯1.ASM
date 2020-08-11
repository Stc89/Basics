;流水灯程序
;使用杜邦线连接P1与LED端口J9

ORG 00H

START:MOV A,#0FFH    ;赋初值
      CLR C
      MOV R2,#8
      
LOOP1:RRC A           ; 带进位右移
     MOV P1,A
     CALL DELAY
     DJNZ R2,LOOP1
     MOV R2,#7
     
LOOP2:RLC A          ;  带进位左移
      MOV P1,A
      CALL DELAY
      DJNZ R2,LOOP2
      JMP START
      
DELAY:MOV R3,#20     ;   延时0.2秒
D1:   MOV R4,#20
D2:   MOV R5,#248
      DJNZ R5,$
      DJNZ R4,D2
      DJNZ R3,D1
      RET
      
END


