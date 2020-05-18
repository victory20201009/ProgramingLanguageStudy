

<center><font size="8" color="#007acc">C++内置算法</font></center>

[TOC]

包含头文件: `#include<algorithm>`

# 1 sort排序

## 1 函数的使用

使用模板: `sort(start,end,method);`其中

- start 数组或vector的起始地址
- end 数组或vector的结束地址
- method 排序方法,是一个函数指针

method是可选的,默认的排序方法是按照自然排序从小到大.

想要自定义排序,可以自己实现一个比较函数,例如:

```C++
bool compare(int a,int b){
    return a>b;
}
```

sort排序时,在比较元素大小的时候,会调用这里的函数,如果返回true,就是逻辑"小",会往前放.这里实现了从大到小排序.

# 2 函数的原理

sort函数会根据传入的数据量的大小,采用不同的排序方法进行排序,先占个坑,后续更新 