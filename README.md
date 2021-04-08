# RiscvSimulator

吉林大学程序设计综合课


### 编译运行

使用 make 自动编译
```bash
make
```

可执行文件在根目录，名字为 simulator

### 写代码简易规则

1. `.cpp` 文件放在 `src` 文件夹中
2. `.h` 文件放在 `include` 文件夹中
3. 每添加一个代码文件，记得修改 `makefile` 文件

### makefile 文件修改规则

为了方便编译，实现了一个最简单的 `makefile`
以下是修改规则：

例子：添加了一个 test.cpp 以及头文件 test.h

首先文件后面加入两行自动编译到 debug 目录，并且依赖好 test.h
```makefile
debug/test.o: src/test.cpp include/test.h
	cc -c $< -o $@
```

修改第一行，加入 .o 文件的路径
```makefile
simulator: debug/main.o debug/test.o
	cc $< -o $@
```

此时 makefile 可以自动编译。




