<center><font color="#FFA500" size="6">volatile和CAS</font></center>

[TOC]

# 1 volatile

## 1.1 实例

```java
package com.victory.volatile_test;

import java.util.concurrent.TimeUnit;

public class VolatileTest{
    /*volatile*/
    boolean running=true;
    
    void m(){
        System.out.println("start");
        while(running){}
        System.out.println("end");
    }
    
    public static void main(String[] args)throws InterruptedException{
        VolatileTest vTest = new VolatileTest();
        new Thread(vTest::m,"t").start();
        TimeUnit.SECONDS.sleep(1);
        vTest.running=false;
    }
}
```

当加上volatile关键字时，main线程一秒以后把running修改为false，这时t线程会立即看到修改后的值，从而退出while循环，根据java的内存模型，每个线程在运行时，会把共享数据拷贝一份到自己的工作内存中，修改后的数据，不会立即写回共享区域。volatile关键字简单来说就是让线程修改完共享数据以后，通知其他线程，读取的时候从共享存储区读取，这样保证线程之间的可见性。

那JVM是如何保证线程可见性的呢？首先要引入一个概念：缓存一致性协议。



