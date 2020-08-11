;独立键盘的输入程序
;P0口接J3，数据端口
;P2.2接 J2 B端子，表示段码锁存
;P2.3接 J2 A端子，标志位码锁存
;P3口接 J26 独立按键

  LATCH1 BIT P2.2
  LATCH2 BIT P2.3

org 00h
mov p2,#80h
main:
     jnb p3.0,s1ok  ;检测按键是否按下
     jnb p3.1,s2ok
     jnb p3.2,s3ok
     jnb p3.3,s4ok

     JMP MAIN
 s1ok:mov p0,#06H   ;写段码和位码
      SETB LATCH1
     CLR LATCH1
      mov p0,#11111110B
     SETB LATCH2
     CLR LATCH2
      jmp main
s2ok:mov p0,#5BH
     SETB LATCH1
     CLR LATCH1
      mov p0,#11111110B
     SETB LATCH2
     CLR LATCH2
      jmp main
s3ok:mov p0,#04FH
     SETB LATCH1
     CLR LATCH1
      mov p0,#11111110B
     SETB LATCH2
     CLR LATCH2
      jmp main
s4ok:mov p0,#66H
     SETB LATCH1
     CLR LATCH1
      mov p0,#11111110B
     SETB LATCH2
     CLR LATCH2
      jmp main

end

