 ;音乐生日快乐的播放
 ;P1.6是喇叭输出端口，用杜邦线连接到J42插针 B1针脚，喇叭即播放音乐
numtim equ 20h
gewei equ 21h
shiwei equ 22h
scanled equ 23h
org 000h
jmp start
org 00bh
jmp tim0
org 100h

start:; JB P3.7,$          ;检测播放按键是否按下
       mov tmod,#00000001b
       mov ie,#10000010b
       mov numtim,#01h
start0:mov 30h,#00h

  next:mov a,30h
       mov dptr,#table
       movc a,@a+dptr
       mov r2,a
       jz  end0
       anl a,#0fh
       mov r5,a
       mov a,r2
       swap a
       anl a,#0fh
       jnz sing
       clr tr0
       jmp d1
 sing: dec a
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
    d1:lcall delay
       inc 30h
       jmp next
  end0:clr tr0
       jmp start0
  tim0:push acc
       push psw
       mov tl0,20h
       mov th0,21h
       cpl p1.6            ;由该口输出音频数据
       pop psw
       pop acc
       reti



delay: mov r7,#02h
   d2: mov r4,#187
   d3: mov r3,#248
       djnz r3,$
       djnz r4,d3
       djnz r7,d2
       djnz r5,delay
       ret
 table1:                                       ;音乐码表
       dw  64260,64400,64524,64580
       dw  64684,64777,64820,64898
       dw  64968,65030,65058,65110
       dw  65157,65178,65217
  table:db 82h,01h,81h,94h,84h
        db 0b4h,0a4h,04h
        db 82h,01h,81h,94h,84h
        db 0c4h,0b4h,04h

        db 82h,01h,81h,0f4h,0d4h
        db 0b4h,0a4h,94h
        db 0e2h,01h,0e1h,0d4h,0b4h
        db 0c4h,0b4h,04h

        db 82h,01h,81h,94h,84h
        db 0b4h,0a4h,04h
        db 82h,01h,81h,94h,84h
        db 0c4h,0b4h,04h

        db 82h,01h,81h,0f4h,0d4h
        db 0b4h,0a4h,94h
        db 0e2h,01h,0e1h,0d4h,0b4h
        db 0c4h,0b4h,04h
        db 00

   TABLE2:DB 0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H,90H
        end


