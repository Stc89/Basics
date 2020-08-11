;兰花草音乐播放程序
;P1.6是喇叭输出端口，用杜邦线连接到J42插针 B1针脚，喇叭即播放音乐
org 00h
jmp start
org 0bh
jmp tim0
start:;JB P3.7,$   ;检测该口的按键是否按下？
      mov tmod,#01h
      mov ie,#82h
start0:mov 30h,#00
next:mov a,30h
     mov dptr,#table
     movc a,@a+dptr
     mov r2,a
     jz end0
     anl a,#0fh
     mov r5,a
     mov a,r2
     swap a
     anl a,#0fh
     jnz sing
     clR tr0
     jmp d1
sing:dec a
     mov 22h,a
     rl a
     mov dptr,#table1
     movc a,@a+dptr
     mov th0,a
     mov 21h,a
     mov a,22h
     rl a
     inc a
     movc a,@a+dptr
     mov tl0,a
     mov 20h,a
     setb tr0
  d1:call delay
     inc 30h
     jmp next
  end0:clr tr0
       jmp start0
  tim0:push acc
       push psw
       mov tl0,20h
       MOV th0,21h
       cpl P1.6       ;由该口输出音频数据；可以更改口线
       POP PSW
       pop acc
       reti
  delay:mov r7,#02
    d2:mov r4,#125
    d3:mov r3,#248
    djnz r3,$
    djnz r4,d3
    djnz r7,d2
    djnz r5,delay
    ret
 table1:
       dw 64021,64103,64260,64400
       dw 64524,64580,64684,64777
       dw 64820,64898,64968,65030
       dw 64934
 table:db 42h,82h,82h,82h,84h,02h,72h
       db 62h,72h,62h,52h,48h
       db 0b2h,0b2h,0b2h,0b2h,0b4h,02h,0a2h
       db 12h,0a2h,0d2h,92h,88h
       db 82h,0b2h,0b2h,0a2h,84h,02h,72h
       db 62h,72h,62h,52h,44h,02h,12h
       db 12h,62h,62h,52h,44h,02h,82h
       db 72h,62h,52h,32h,48h
       db 00h
       end

