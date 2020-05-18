<center><font color="#FFA500" size="6">C语言的time函数</font></center>
time函数原型：

```C
time_t time(time_t *t);
```

是C标准库的函数，使用需要包含头文件：

```C
#include<time.h>
```

这个函数的目的是返回一个整数，是目前到 1970-1-1 00:00:00时刻的秒数值，返回值是time_t类型，time_t类型在time.h头文件中定义为long类型，在C语言中long类型是4个字节，范围是-3147483648-3147483647，这样的话，time函数能够返回的正确的时间，截至到 2038年1月18日19时14分07秒，为了支持更长的日期，一些厂商实现的C语言使用了64位的数值来表示这个时间值，例如Microsoft的Visual C

使用方式：

1. 传递NULL或0

   ```C
   #include<stdio.h>
   #include<time.h>
   
   int main() {
       time_t a = time(0);
       time_t b = time(NULL);
       printf("%ld,%ld\n", a, b);
       return 0;
   }
   ```

   

2. 传递一个指针

   ```C
   #include<stdio.h>
   #include<time.h>
   
   int main() {
       time_t a;
       time(&a);
       printf("%ld\n", a);
       return 0;
   }
   ```

   

