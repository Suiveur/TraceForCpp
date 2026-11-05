# TraceForCpp

## 是什么

这是一个关于c++的Tracing可视化文件生成库，生成的文件扔进[Perfetto UI](https://ui.perfetto.dev/)中，可以对项目调用的函数进行可视化，方便对出现的问题进行调试

## 怎么用

确保你有CMake编译工具以及MinGW，如果是linux环境确保有gcc

### 编译库

在此项目根目录中依次执行

```shell
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

在build目录中会生成一个名为libTraceForCpp.a的文件，可以更改后缀为.lib(这里不进行更改)

### 编译测试程序（非必要，可用用作查看是否编译成功）

在test/目录下创建lib文件夹，将libTraceForCpp.a放入此文件夹中，在test目录依次执行

```shell
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

在test/build/中会生成test.exe 文件，执行此文件，会在本级目录下生成一个json文件，将这个文件拖入到[Perfetto UI](https://ui.perfetto.dev/)中，会有以下结果，说明编译没有问题

![image-20261106024116859](C:\Users\54143\AppData\Roaming\Typora\typora-user-images\image-20261106024116859.png)

### 正确使用

将include/目录中的所有头(.h)文件你的项目中，并在main()函数所在文件中包含Instrumentor.h头文件，并在第一行添加上``` #define PROFILEING``` 并在main()函数第一行添加上 ``` BEGIN_SESSION("PROFILE", "生成的文件名");```，在主函数返回之前添加上 ``` END_SESSION();``` 例如

```  c++
#define PROFILEING   // Enable profiling, if you want to disable profiling, comment out this line

...
#include "Instrumentor.h"
...
int main(){
    BEGIN_SESSION("PROFILE", "[your files name]");
    ...
    ...
    END_SESSION();
    return 0;
}

```

在说有.c/.cpp文件中加入``` #include "InstrumentationTimer.h"```,并所有函数实现的第一行加入``` PROFILE_FUNCTION();```例如

``` c++
#include "InstrumentationTimer.h"

void function() {
    PROFILE_FUNCTION();
    ...			//以下是函数的具体实现
}
```

当不想进行可视化时，只需将main函数所在的文件中的``` #define PROFILEING```注释掉就行，注释之后文件能正常编译，对性能也没有影响

