# 生命很短，我用tldr

我们平时使用命令的是否，如果忘记的，会去百度，也会去使用man 或者 -- help 查看，如果你看了这篇文章，就会知道tldr是怎么样的存在。

tldr 的含义

> TL;DR stands for "Too Long; Didn't Read". It originates in Internet slang, where it is used to indicate that a long text (or parts of it) has been skipped as too lengthy. Read more in Wikipedia's TL;DR essay

这个是从github上截取的一段解释，全称是 `Too Long;Didn't Read` ，翻译成中文的意思就是什么？

我昨天带我儿子去参加英语培训课程，其中他们老师给我做了一个测试，让我把自己的电话号码说出来，然后又说，让我把我的电话号码用英语说出来。

用中文说出来很简单，但是用因为说出来，我还是比较困难，因为我说英文的是否，总是先翻译再说，这就导致了速度的下降。

说中文的是否是这样
![img](https://raw.githubusercontent.com/weiqifa0/pic/master/image-20201102154625435.png)

说英文的是否是这样
![img](https://raw.githubusercontent.com/weiqifa0/pic/master/image-20201102154726176.png)

说这个我想表达一个观点，我们对中文的认知是感觉来的，但是对英文的认知是思考来的，所以对于`Too Long;Didn't Read` 这句话的理解，如果真的要翻译，就失去它的味道了。

从目前为止，我看到的最好的翻译是

> 太长了不看

# #如何使用

```
weiqifa@bsp-ubuntu1804:~/in10$ tldr ls
✔ Page not found. Updating cache...
✔ Creating index...

  ls

  List directory contents.

  - List files one per line:
    ls -1

  - List all files, including hidden files:
    ls -a

  - List all files, with trailing / added to directory names:
    ls -F

  - Long format list (permissions, ownership, size and modification date) of all files:
    ls -la

  - Long format list with size displayed using human readable units (KB, MB, GB):
    ls -lh

  - Long format list sorted by size (descending):
    ls -lS

  - Long format list of all files, sorted by modification date (oldest first):
    ls -ltr


weiqifa@bsp-ubuntu1804:~/in10$ tldr  --update
✔ Updating...
✔ Creating index...
weiqifa@bsp-ubuntu1804:~/in10$ tldr zip

  zip

  Package and compress (archive) files into zip file.

  - Package and compress a directory and its contents, [r]ecursively:
    zip -r compressed.zip path/to/directory

  - E[x]clude unwanted files from being added to the compressed archive:
    zip -r compressed.zip path/to/directory -x path/to/exclude

  - Archive a directory and its contents with the highest level [9] of compression:
    zip -r -9 compressed.zip path/to/directory

  - Package and compress multiple directories and files:
    zip -r compressed.zip path/to/directory1 path/to/directory2 path/to/file

  - Create an encrypted archive (user will be prompted for a password):
    zip -e -r compressed.zip path/to/directory

  - Add files to an existing zip file:
    zip compressed.zip path/to/file

  - Delete files from an existing zip file:
    zip -d compressed.zip "foo/*.tmp"

  - Archive a directory and its contents to a multi-part [s]plit zip file (e.g. 3GB parts):
    zip -r -s 3g compressed.zip path/to/directory


weiqifa@bsp-ubuntu1804:~/in10$ 
```

从上面可以看到，我们可以直接看到比较简短的使用介绍

如果我们使用man的话，是这样的。

![img](https://raw.githubusercontent.com/weiqifa0/pic/master/image-20201102155123778.png)

# #如何安装？

> sudo apt-get install nodejs
> sudo apt-get install npm
> sudo npm install -g tldr

执行上面三条指令后，需要再执行

> tldr  --update

来更新tldr 到最新的状态

之后就可以让tldr 带你享受人生了，说实话，我用了这个命令后，觉得自己的时间可以节省下至少 10分钟。

```
weiqifa@bsp-ubuntu1804:~$ tldr dd    

  dd

  Convert and copy a file.

  - Make a bootable usb drive from an isohybrid file (such like archlinux-xxx.iso) and show the progress:
    dd if=file.iso of=/dev/usb_drive status=progress

  - Clone a drive to another drive with 4MB block, ignore error and show progress:
    dd if=/dev/source_drive of=/dev/dest_drive bs=4M conv=noerror status=progress

  - Generate a file of 100 random bytes by using kernel random driver:
    dd if=/dev/urandom of=random_file bs=100 count=1

  - Benchmark the write performance of a disk:
    dd if=/dev/zero of=file_1GB bs=1024 count=1000000

  - Check progress of an ongoing dd operation (Run this command from another shell):
    kill -USR1 $(pgrep ^dd)
```

# #相关链接

> https://github.com/tldr-pages/tldr