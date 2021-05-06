## RISCV 汇编仿真器

这是一个 C++ 实现的 nodejs 模块，支持全平台。

### 使用方法

安装该模块
```bash
npm install riscv-simulator
```

使用该模块
```js
const sim = require("riscv-simulator");
core.setCodes(`addi	sp,sp,-32
sd	s0,24(sp)
addi	s0,sp,32
sw	zero,-20(s0)
li	a5,1
sw	a5,-24(s0)`);
while(!core.end()) {
    core.nextStep();
}
```


### 函数列表

setCodes(code) 设置执行的代码


nextStep() 单步执行


end() 指令是否结束


curLine() 当前执行到了输入代码的哪一行


getRegister(integer) 获取寄存器的值


getLogs() 获取当前日志


getUsedMemory() 获取上一条指令使用的所有内存地址


getMemory(addr) 获取内存地址的值


