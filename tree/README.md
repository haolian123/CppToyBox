# my_tree简介
使用组合模式编写的tree指令。

# 使用

## 添加环境路径
将编译生成后的exe文件所在的目录添加到系统环境变量中。
如： mytree的路径为D:\myCommand\mytree.exe,则将D:\myCommand\添加到系统环境变量Path中

## 用法

```shell
mytree [相对文件夹路径|绝对文件夹路径]
```

比如 

```
//当前路径
mytree . 
//上一级路径
mytree ..
```

