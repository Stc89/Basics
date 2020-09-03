;/*
;*********************************************************************************************************
;*                                                uC/OS-II
;*                                          The Real-Time Kernel
;*
;*                          (c) Copyright 1992-2002, Jean J. Labrosse, Weston, FL
;*                                           All Rights Reserved
;*
;*
;*                                           uCOS_51 for MCS-51
;*
;* File : OS_CPU_A.ASM
;* From : chen shi zhi
;* Last modified by : QQ 591881218
;*********************************************************************************************************
;*/

$NOMOD51
    
$include (../inc/stc8_regs.inc)

TIMER_20MS_TH0 	EQU	 070H	;CPU=22.1184MHz, OS_TICKS_PER_SEC=50, TH0=0x70
TIMER_20MS_TL0	EQU	 000H	;CPU=22.1184MHz, OS_TICKS_PER_SEC=50, TL0=0x00

        NAME OS_CPU_A	;模块名
        
;定义重定位段
;1：无参函数 ?PR?函数名?文件名
;2：有参函数 ?PR?_函数名?文件名
;3：再入函数 ?PR?_?函数名?文件名
?PR?_?OSStartHighRdy?OS_CPU_A    SEGMENT CODE
?PR?_?OSCtxSw?OS_CPU_A           SEGMENT CODE
?PR?_?OSIntCtxSw?OS_CPU_A        SEGMENT CODE
?PR?_?OSTickISR?OS_CPU_A         SEGMENT CODE

?PR?_?SerialISR?OS_CPU_A	   SEGMENT CODE
        
;声明引用全局变量和外部子程序
        EXTRN DATA  (?C_XBP)	;仿真堆栈指针用于可重入局部变量保存

        EXTRN XDATA (OSTCBCur)
        EXTRN XDATA (OSTCBHighRdy)
        EXTRN XDATA (OSRunning)
        EXTRN XDATA (OSPrioCur)
        EXTRN XDATA (OSPrioHighRdy)
    
        EXTRN CODE  (_?OSTaskSwHook)
        EXTRN CODE  (_?OSIntEnter)
        EXTRN CODE  (_?OSIntExit)
        EXTRN CODE  (_?OSTimeTick)

		EXTRN CODE  (_?Serial)        
            
;对外声明4个不可重入函数
        PUBLIC _?OSStartHighRdy
        PUBLIC _?OSCtxSw
        PUBLIC _?OSIntCtxSw
        PUBLIC OSTickISR
        
        ;PUBLIC SerialISR        
    
;分配堆栈空间。只关心大小，堆栈起点由keil决定，通过标号可以获得keil分配的SP起点
?STACK SEGMENT IDATA
        RSEG ?STACK

OSStack:
		;DS n：保留n个存储单元
        DS 40H		;分配硬件堆栈的大小

OSStkStart IDATA OSStack-1

;定义压栈出栈宏
PUSHALL    MACRO
        PUSH PSW
        PUSH ACC
        PUSH B
        PUSH DPL
        PUSH DPH
        MOV  A,R0	;R0~R7入栈
        PUSH ACC
        MOV  A,R1
        PUSH ACC
        MOV  A,R2
        PUSH ACC
        MOV  A,R3
        PUSH ACC
        MOV  A,R4
        PUSH ACC
        MOV  A,R5
        PUSH ACC
        MOV  A,R6
        PUSH ACC
        MOV  A,R7
        PUSH ACC
        ;PUSH SP	;不必保存SP，任务切换时由相应程序调整
        ENDM
    
POPALL    MACRO
        ;POP  ACC	;不必保存SP，任务切换时由相应程序调整
        POP  ACC	;R0~R7出栈
        MOV  R7,A
        POP  ACC
        MOV  R6,A
        POP  ACC
        MOV  R5,A
        POP  ACC
        MOV  R4,A
        POP  ACC
        MOV  R3,A
        POP  ACC
        MOV  R2,A
        POP  ACC
        MOV  R1,A
        POP  ACC
        MOV  R0,A
        POP  DPH
        POP  DPL
        POP  B
        POP  ACC
        POP  PSW
        ENDM
    
;--------------------
;子程序
;--------------------

;			--------------------------------------------------
;			---------------- OSStartHighRdy() ----------------
;			--------------------------------------------------

        RSEG ?PR?_?OSStartHighRdy?OS_CPU_A

;调用用户扩展函数OSTaskSwHook()
;OSRunning=TRUE
;取得将要恢复的任务的堆栈指针：Stack pointer=OSTCBHighRdy->OSTCBStkPtr
;将所有寄存器内容从任务栈中弹出来
;执行中断返回指令

_?OSStartHighRdy:

        USING 0		;上电后51自动关中断，此处不必用CLR EA指令，因为到此处还未开中断，本程序退出后，开中断
        LCALL _?OSTaskSwHook
        
        ;OSRunning=TRUE
        MOV  DPTR, #OSRunning  ;should use DPTR1
        MOV  A,  #001H
        MOVX @DPTR,  A
        ;MOV  R0,#LOW (OSRunning)
        ;MOV  @R0,#01

;--------------------
;OSCtxSw_in
;--------------------

OSCtxSw_in:

        ;OSTCBHighRdy ==> DPTR 获得当前就绪的最高优先级任务的TCB指针
        MOV  DPTR,  #OSTCBHighRdy  ;should use DPTR1
        INC  DPTR
        ;MOV  R0,#LOW (OSTCBHighRdy)	;获得OSTCBHighRdy指针低地址，指针占3B。+0类型 +1高8位数据 +2低8位数据
        ;INC  R0
        ;MOV  DPH,@R0    ;全局变量OSTCBHighRdy在IDATA中
        ;INC  R0
        ;MOV  DPL,@R0
        MOVX  A,  @DPTR
        MOV   R0, A
        INC   DPTR
        MOVX  A,  @DPTR
        MOV   DPL, A
        MOV   DPH, R0
    
        ;OSTCBHighRdy->OSTCBStkPtr ==> DPTR 获得用户堆栈指针
        INC  DPTR		;指针占3B。+0类型 +1高8位数据 +2低8位数据
        MOVX A,@DPTR	;OSTCBStkPtr是void指针
        MOV  R0,A
        INC  DPTR
        MOVX A,@DPTR
        MOV  R1,A
        MOV  DPH,R0
        MOV  DPL,R1
    
        ;*UserStkPtr ==> R5 用户堆栈起始地址内容(即用户堆栈长度放在此处)   
        MOVX A,@DPTR	;用户堆栈中是unsigned char类型数据
        MOV  R5,A		;R5=用户堆栈长度
    
        ;恢复现场堆栈内容
        MOV  R0,#OSStkStart

;--------------------
;restore_stack
;--------------------
        
restore_stack:
    
        INC  DPTR
        INC  R0
        MOVX A,@DPTR
        MOV  @R0,A
        DJNZ R5,restore_stack
    
        ;恢复堆栈指针SP
        MOV  SP,R0
    
        ;恢复仿真堆栈指针?C_XBP        
        INC  DPTR
        MOVX A,@DPTR
        MOV  ?C_XBP,A	;?C_XBP 仿真堆栈指针高8位
        INC  DPTR
        MOVX A,@DPTR
        MOV  ?C_XBP+1,A	;?C_XBP 仿真堆栈指针低8位
  
        POPALL
        SETB EA		;开中断
        RETI

;			--------------------------------------------------
;			------------------- OSCtxSw() --------------------
;			--------------------------------------------------

        RSEG ?PR?_?OSCtxSw?OS_CPU_A

;保存处理器寄存器
;将当前任务的堆栈指针保存到当前任务的OS_TCB中：OSTCBCur->OSTCBStkPtr=Stack pointer
;调用用户扩展函数OSTaskSwHook()
;OSTCBCur=OSTCBHighRdy
;OSPrioCur=OSPrioHighRdy
;得到需要恢复的任务的堆栈指针：Stack pointer=OSTCBHighRdy->OSTCBStkPtr
;将所有处理器寄存器从新任务的堆栈中恢复出来
;执行中断返回指令

_?OSCtxSw:  

        USING 0  
        PUSHALL

;--------------------
;OSIntCtxSw_in
;--------------------
        
OSIntCtxSw_in:

        ;获得堆栈长度和起始地址，任务栈结构示意图(OS_CPU_C.C)
        MOV  A,SP
        CLR  C	;进位标志位Cy清零
        SUBB A,#OSStkStart	;A <- A-OSStkStart-Cy
        MOV  R5,A     ;获得堆栈长度        
    
        ;OSTCBCur ==> DPTR  获得当前TCB指针
        MOV  DPTR,  #OSTCBCur  ;should use DPTR1
        INC  DPTR
        MOVX A, @DPTR
        MOV  R0, A
        INC  DPTR
        MOVX A,  @DPTR
        MOV  DPL, A
        MOV  DPH, R0
        ;MOV  R0,#LOW (OSTCBCur) ;获得OSTCBCur指针低地址，指针占3B。+0类型 +1高8位数据 +2低8位数据
        ;INC  R0
        ;MOV  DPH,@R0	;全局变量OSTCBCur在IDATA中
        ;INC  R0
        ;MOV  DPL,@R0
    
        ;OSTCBCur->OSTCBStkPtr ==> DPTR  获得用户堆栈指针
        INC  DPTR        ;指针占3B。+0类型 +1高8位数据 +2低8位数据
        MOVX A,@DPTR     ;OSTCBStkPtr是void指针
        MOV  R0,A
        INC  DPTR
        MOVX A,@DPTR
        MOV  R1,A
        MOV  DPH,R0
        MOV  DPL,R1
        
        ;保存堆栈长度
        MOV  A,R5
        MOVX @DPTR,A

        MOV  R0,#OSStkStart	;获得堆栈起始地址

;--------------------
;save_stack
;--------------------

save_stack:
   
        INC  DPTR
        INC  R0
        MOV  A,@R0
        MOVX @DPTR,A
        DJNZ R5,save_stack
        
        ;保存仿真堆栈指针?C_XBP
        INC  DPTR
        MOV  A,?C_XBP	;?C_XBP 仿真堆栈指针高8位
        MOVX @DPTR,A
        INC  DPTR
        MOV  A,?C_XBP+1	;?C_XBP 仿真堆栈指针低8位
        MOVX @DPTR,A        
    
        ;调用用户程序
        LCALL _?OSTaskSwHook

;--------------------
;OSIntCtxSw_in
;--------------------
        
;OSIntCtxSw_in:

        ;OSTCBCur = OSTCBHighRdy
        MOV  DPTR,  #OSTCBHighRdy  ;should use DPTR1
        MOVX A,  @DPTR
        MOV  DPTR,  #OSTCBCur
        MOVX @DPTR,  A
        
        MOV  DPTR,  #OSTCBHighRdy
        INC  DPTR
        MOVX A,  @DPTR
        MOV  DPTR,  #OSTCBCur
        INC  DPTR
        MOVX @DPTR,  A
        
        MOV  DPTR,  #OSTCBHighRdy
        INC  DPTR
        INC  DPTR
        MOVX A,  @DPTR
        MOV  DPTR,  #OSTCBCur
        INC  DPTR
        INC  DPTR
        MOVX @DPTR,  A
        
        ;MOV  R0,#OSTCBCur
		;MOV  R1,#OSTCBHighRdy
		;MOV  A,@R1
        ;MOV  @R0,A
        ;INC  R0
		;INC  R1
		;MOV  A,@R1
        ;MOV  @R0,A
        ;INC  R0
		;INC  R1
		;MOV  A,@R1
        ;MOV  @R0,A
                
        ;OSPrioCur = OSPrioHighRdy 使用这两个变量主要目的是为了使指针比较变为字节比较，以便节省时间
        MOV  DPTR, #OSPrioHighRdy  ;should use DPTR1
        MOVX  A,  @DPTR
        MOV  DPTR,  #OSPrioCur
        MOVX  @DPTR, A
        ;MOV  R0,#OSPrioCur
		;MOV  R1,#OSPrioHighRdy
		;MOV  A,@R1
        ;MOV  @R0,A
        
        LJMP OSCtxSw_in

;			-------------------------------------------
;			--------------- OSIntCtxSw() --------------
;			-------------------------------------------

        RSEG ?PR?_?OSIntCtxSw?OS_CPU_A

;调整堆栈指针来去掉在调用过程中压入堆栈的多余内容
;将当前任务堆栈指针保存到当前任务的OS_TCB中：OSTCBCur->OSTCBStkPtr=Stack pointer
;调用用户扩展函数OSTaskSwHook()
;OSTCBCur=OSTCBHighRdy
;OSPrioCur=OSPrioHighRdy
;得到需要恢复的任务的堆栈指针：Stack pointer=OSTCBHighRdy->OSTCBStkPtr
;将所有处理器寄存器从新任务的堆栈中恢复出来
;执行中断返回指令
        
_?OSIntCtxSw:

        USING 0

		;调整SP指针去掉在调用OSIntExit()、OSIntCtxSw()过程中压入堆栈的多余内容
		;SP=SP-4
		MOV  A,SP
		CLR  C
		SUBB A,#4
		MOV  SP,A

		LCALL _?OSTaskSwHook
        LJMP OSIntCtxSw_in

;			-------------------------------------------
;			--------------- OSTickISR() ---------------
;			-------------------------------------------

        CSEG AT 000BH	;定时器T0中断
;CSEG [AT 绝对地址表达式] //绝对代码段
;DSEG [AT 绝对地址表达式] //内部绝对数据段
;XSEG [AT 绝对地址表达式] //外部绝对数据段
;ISEG [AT 绝对地址表达式] //内部间接寻址绝对数据段
;BSEG [AT 绝对地址表达式] //绝对位寻址段
        LJMP OSTickISR
        RSEG ?PR?_?OSTickISR?OS_CPU_A

;关中断
;保存处理器寄存器的值
;调用OSIntEnter()或是将OSIntNesting加1
;关时钟中断
;调用OSTimeTick()
;开时钟中断
;调用OSIntExit()
;恢复处理器寄存器的值
;重新允许中断
;执行中断返回指令

OSTickISR:        
        
        USING 0		;工作寄存器0
        CLR  EA		;关中断，防止中断嵌套
        PUSHALL		;现场保护
        LCALL _?OSIntEnter	;通知内核进入中断
              
		CLR  TR0
        ;MOV  TH0,#TIMER_20MS_TH0	;定义Tick=50次/秒，即0.02秒/次
        ;MOV  TL0,#TIMER_20MS_TL0	;OS_CPU_C.C 和 OS_TICKS_PER_SEC
       	LCALL _?OSTimeTick	;调用中断服务子程序
		SETB TR0 

        LCALL _?OSIntExit	;通知内核退出中断
        POPALL		;恢复现场    
		SETB EA 	;开中断    
        RETI

;--------------------
;SerialISR
;--------------------

        CSEG AT 0023H	;串口中断
        LJMP SerialISR
        RSEG ?PR?_?SerialISR?OS_CPU_A
    
SerialISR:
        
        USING 0
        CLR  EA		;关中断，防止中断嵌套
        PUSHALL
        LCALL _?OSIntEnter	;通知内核进入中断
      	
		CLR ES
        LCALL _?Serial	;调用中断服务子程序	 
		SETB ES
		       
        LCALL _?OSIntExit	;通知内核退出中断
        POPALL
		SETB EA        
        RETI

;--------------------
END
;--------------------
