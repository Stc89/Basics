# 01-使用汇编点亮LED灯.md

# #硬件连接

![硬件连接图](https://raw.githubusercontent.com/weiqifa0/pic/master/image-20200928195802610.png)

# #使用软件

![image-20200928195846926](https://raw.githubusercontent.com/weiqifa0/pic/master/image-20200928195846926.png)

# #文档

先查看文档 `STC8G中文用户手册-20200520.pdf`

里面有对应的寄存器地址

![image-20200928200154322](https://raw.githubusercontent.com/weiqifa0/pic/master/image-20200928200154322.png)

![image-20200928200221581](https://raw.githubusercontent.com/weiqifa0/pic/master/image-20200928200221581.png)

# #汇编代码

```
;流水灯程序
P1M0 DATA 092H
P1M1 DATA 091H
ORG 00H
MOV P1M0,#11111111B ;设置GPIO口模式
MOV P1M1,#00000000B ;设置GPIO口模式
MOV P1,#11111111B ;设置GPIO口的状态
sjmp $ ;表示程序停止在这里
END

```

# # 编译烧录

![image-20200928200605585](https://raw.githubusercontent.com/weiqifa0/pic/master/image-20200928200605585.png)

![image-20200928200618783](https://raw.githubusercontent.com/weiqifa0/pic/master/image-20200928200618783.png)

![运行效果图](https://raw.githubusercontent.com/weiqifa0/pic/master/image-20200928200643897.png)