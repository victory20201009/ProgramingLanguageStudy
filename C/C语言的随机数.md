<center><font color="#FFA500" size="6">C语言的随机数</font></center>

[TOC]

# 1 使用方法

包含头文件

```C
#include<stdlib.h>
```

里面有一个rand函数，函数原型如下：

```C
int rand(void);
```

没有参数，返回一个随机整数值，范围是  0 ~ RAND_MAX ，RAND_MAX 是定义在stdlib标准库中的一个宏，大于等于32767

示例代码：

```C
#include<stdlib.h>
#include<stdio.h>

int main(){
	int a = rand();
	printf("%d\n",a);
	return 0;
}
```

多次运行上面的代码，结果和第一次是一样的

C语言的rand函数产生的随机数，是伪随机数，他是**根据某一个值，使用公式计算出来的**，计算出来的随机数和这个值服从正态分布，根据的这个值就是种子。当种子一定时，一次运行中多次调用rand计算出来的随机数序列也是固定的，当然这个种子是计算机启动的时候设定的，是定值，貌似是1。我们只需要重新改变种子值，使得层序每次运行时种子值都不一样，这样获得的随机值序列才是变化的。

把上面的代码改下，一次产生10个随机数：

```C
#include<stdlib.h>
#include<stdio.h>

int main() {
	for (int i = 0; i < 10; ++i)
		printf("%d\n", rand());
	return 0;
}
```

运行第一次结果：

![image-20200321235023352](md_img\image-20200321235023352.png)

运行第二次结果：

![image-20200321235210207](md_img\image-20200321235210207.png)

随机数序列一样的

使用srand函数可以改变随机数种子，当种子不一样时，随机数序列也不一样。函数原型如下：

```C
void srand(unsigned int seed);
```

我们可以在调用rand函数之前，调用这个函数，可以传入1，2，3等每次不一样的值，为了一劳永逸，我们可以使用time函数返回的值(参考C语言的time函数)，即：

```C
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

int main() {
    srand(time(NULL));
	for (int i = 0; i < 10; ++i)
		printf("%d\n", rand());
	return 0;
}
```



# 2 生成指定范围内的随机数

生成[a,b]之间的随机数，我们可以先生成[0,b-a]之间的随机数，方法是对rand函数的结果取模（b-a+1）即可，然后加上偏移值a，结果为：

```C
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

/*
生成[5,10]之间的随机数
*/
int main() {
    srand(time(NULL));
    int a=5,b=10;
    int mod = b-a+1;
	for (int i = 0; i < 10; ++i)
		printf("%d\n", rand()%mod+a);
	return 0;
}
```

