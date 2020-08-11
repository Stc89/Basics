;利用中断的99秒计时器 ，动态扫描两位数码管
;P0口接J3，数据端口
;P2.2接 J2 B端子，表示段码锁存
;P2.3接 J2 A端子，标志位码锁存

LATCH1 BIT P2.2
LATCH2 BIT P2.3

ORG 00H
JMP START
ORG 0BH
JMP TIM0
START:MOV R3,#00   ;中断循环次数
      MOV R4,#0    ;时间初值
      MOV DPTR,#TABLE
      MOV SP,#40H
      MOV TMOD,#01H  ;定时器工作方式
      MOV TH0,#HIGH(65536-3800)
      MOV TL0,#LOW(65536-3800)  ;初值4MS
      SETB TR0
      MOV IE,#82H  ;开中断
TIM0:
     MOV TH0,#HIGH(65536-3800)
     MOV TL0,#LOW(65536-3800)
     INC R3
     CJNE R3,#250,X1  ;1S
     MOV R3,#0
              
     MOV A,R4       ;十进制转换
     MOV B,#10
     DIV AB
     MOV 20H,B  ; 个位
     MOV 21H,A  ; 十位
     INC R4
     CJNE R4,#100,LEDSCAN  ;到100则清零
     MOV R4,#0
LEDSCAN: CALL SCAN  ;调用数码管扫描
X1:   PUSH ACC
      PUSH PSW
      CALL SCAN
      POP PSW
      POP ACC
      RETI
SCAN:
     MOV A,21H
     MOVC A,@A+DPTR
     MOV P0,A
     SETB LATCH1
     CLR LATCH1
     MOV P0,#11111110B ;扫描子程序
     SETB LATCH2
     CLR LATCH2
     CALL DELAY1

     MOV A,20H
     MOVC A,@A+DPTR
     MOV P0,A
     SETB LATCH1
     CLR LATCH1
     MOV P0,#11111101B  ;0代表选通该位数码管
     SETB LATCH2
     CLR LATCH2
     CALL DELAY1
     RET
DELAY:MOV R5,#50         ;典型延时程序
D1:   MOV R6,#40
D2:   MOV R7,#248
      CALL SCAN
      DJNZ R7,$
      DJNZ R6,D2
      DJNZ R5,D1
      RET
DELAY1:MOV R6,#4    ;扫描延时
D3:    MOV R7,#248
       DJNZ R7,$
       DJNZ R6,D3
       RET
TABLE:DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,6FH    ;共阴字码表
END
