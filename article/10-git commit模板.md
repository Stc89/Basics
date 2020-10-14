# 10-git commit模板

git commit 模板是我们提交commit的时候需要的，如果没有模板的话，我们每次提交都需要写上一些常规的注释，作为程序员没有这个模板是比较尴尬的。

# #新建一个文件 - cong_complate.txt

在里面写入

```
[master][article]
[简述]:
[时间]：
```

# #注意文件的格式设置成utf-8 

# #配置git

```
git config --global commit.template  /home/work/song_complate.txt
```

# #当然也可以配置git commit编译器

```
git config --global core.editor vim 
git config --global core.editor nano
```



