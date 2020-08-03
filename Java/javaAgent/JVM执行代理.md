<center><font color="#FFA500" size="6">JVM执行代理</font></center>

[toc]

# 1. java agent

java的agent机制提供了在JVM运行时，动态的改变类的执行行为的机制。我们可以在用户main线程运行之前，执行一些自己的代理操作，或者埋点操作。可以理解为这是一种虚拟机层面的AOP操作。

它改变类的行为有两种方式：

- premain，在main函数执行之运行
- attach api，在jvm运行时，动态的执行。

首先看一下premain方式，java虚拟机会在运行前，找到代理类中的premain方法，JVM提供了两种重载的premain让我们重写：

```java
public static void premain(String agentArgs, Instrumentation inst);  //[1]
public static void premain(String agentArgs); //[2]
```

agentArgs是传递给代理程序的参数，Instrumentation是字节码转换的接口，后面讨论它。其中[1]的优先级比[2]高

下面演示一下premain的使用：

1. 写一个很简单的类，如下

   ```java
   package com.agent.test;
   
   public class Hello{
   	public static void main(String[] args){
   		System.out.println("Hello!");
   	}
   }
   ```

2. 写一个代理类，如下

   ```java
   package com.agent.test;
   
   public class HelloAgent{
   	public static void premain(String agentArgs){
   		System.out.println("I am running before main，my args is:"+agentArgs);
   	}
   }
   ```

3. 在com目录，执行以下命令：

   ```shell
   echo Premain-Class: com.agent.test.HelloAgent > MANIFEST.MF
   javac com/agent/test/HelloAgent.java
   javac com/agent/test/Hello.java
   jar cvmf MANIFEST.MF agent-test.jar com/
   java -javaagent:.\agent-test.jar=haha com/agent/test/Hello
   pause
   ```

   然后就会看到 I am running before main，my args is:haha 打印在Hello之前

# 2 Instrumentation

前面的demo展示了premain函数可以在main之前运行，一般来说，我们想要实现对JVM的监控，想在我们的方法前后做一些AOP的操作，就需要修改类的行为，那么如何修改类的行为呢？就是修改JVM加载的class文件。而Instrumentation就提供了一系列的操作字节码的接口，我们一般是在premain函数里通过添加类的转换器，类转化器可以监听JVM加载类的事件，从而在加载类的时候，实现对类的字节码的“偷天换日”。有关Instrumentation，下面有一段关于其的描述。

> Instrumentation是JDK1.5的新特性，使用 Instrumentation，开发者可以构建一个独立于应用程序的代理程序（Agent），用来监测和协助运行在 JVM 上的程序，甚至能够**替换和修改某些类的定义**。有了这样的功能，开发者就可以实现更为灵活的运行时虚拟机监控和 Java 类操作了，这样的特性实际上提供了一种虚拟机级别支持的 AOP 实现方式，使得开发者无需对 JDK 做任何升级和改动，就可以实现某些 **AOP** 的功能了。[来源于网络](https://www.cnblogs.com/yelao/p/9841810.html)
>

先看一下Instrumentation接口都有什么方法和属性：

```java
//......
public interface Instrumentation {
    /**
    * 通过翻译JDK的文档，得知这个方法会添加一个转换器，ClassFileTransformer是类转换器接口，需要具体
    * 的agent程序实现。
    * canRetransform 标识该转化器的转换结果是否可以被重新转换。如果JVM的配置不允许重新转换，那么当把它设置为true时，就会报错，抛出UnsupportedOperationException，可参考下面的isRetransformClassesSupported方法。
    * 当transformer为null时，抛出NullPointerException。
    * 这个转换器，可以看到所有类的定义，除了它以及它之前已经被注册的转换器所依赖的那些类
    * 当有新的类被加载的时候，或者当有的类被重新定义的时候，以及被重新转换的时候，这个方法就会被调用
    * 可以添加多个类转换器，当有一个转换器抛出了异常，JVM会依次调用下一个转换器，当然同一个转换器可以被添加多次，但是这样做强烈不推荐。
    */
    void
    addTransformer(ClassFileTransformer transformer, boolean canRetransform);
    
    /**
    * 相当于调用addTransformer(transformer,false);其他情况相同
    */
    void
    addTransformer(ClassFileTransformer transformer);
    
    /**
    * 移除一个转换器，移除了之后，后面类的定义信息，不会被这个转换器看到。移除的规则是，移除最近被添加的	   * transformer实例(原文：Removes the most-recently-added matching instance of the 		* transformer) 由于类加载是多线程的，有可能一个类转换器被移除了以后，还会被调用。因此应该小心谨慎	* 编写转换器代码。
    * @param transformer 需要被移除的转换器实例，为null时，抛出NullPointerException
    * @return 当类转换器被找到并移除时，返回true，当没有找到时，返回false
    */
    boolean
    removeTransformer(ClassFileTransformer transformer);
    
    /**
    * 对于一个已经被加载的类的重新转换是JVM的一个可选功能，这个方法返回了当前JVM的配置，是否支持对类的重新转换。支持重新转换的条件是：
    * 1. 在代理jar的MANIFEST.MF文件中，添加Can-Retransform-Classes为true
    * 2. JVM配置支持这个特性
    * 对于单个实例的JVM进程来说，这个方法的返回值是固定的。
    * @return true支持，否则不支持
    */
    boolean
    isRetransformClassesSupported();
    
    /**
    * 这个方法可以促进那些已经被加载的类的转换(原文：This function facilitates the 			* instrumentation of already loaded classes.)
    * 当类被最初加载或者重新定义的时候，他们的字节码文件可以使用ClassFileTransformer转换，这个方法会	   * 重新运行转换的过程，而不管一个转换器先前是否执行过。
    * 重新转换的过程如下：
    * 1. 从第一个被加载的的字节码开始，直到最后一个被加载的类，
    * 2. 对于被添加的每一个canRetransform被设置为false的转换器，他们输出的字节码是复用原先的字节码		* 作为最后的结果；
    * 3. 对于被添加的每一个canRetransform被设置为true的转换器，它们的transform方法被被调用。
    * 最终转换的结果，会替换原来类的新的定义。
    * 当方法抛出异常的时候，任何一个类不会被重新转换，可以传递0个参数，在这种情况下，这个方法什么也不做
   	* 如果一个类不能被修改，抛出UnmodifiableClassException
   	* 当JVM不支持重新转换的时候，或者转换器做了不支持的转换操作时，抛出						 	 * UnsupportedOperationException
   	* .....
    */
    void
    retransformClasses(Class<?>... classes) throws UnmodifiableClassException;
    
    /**
    * 对于一个已经被加载的类的重新定义，是JVM的一个可选功能
    * 判断JVM配置是否支持类的重定义，代理程序支持重定义的条件：
    * 1. 在代理jar的MANIFEST.MF文件中，添加Can-Redefine-Classes为true
    * 2. JVM配置支持这个特性
    * 对于单个实例的JVM进程来说，这个方法的返回值是固定的。
    * @return true支持，否则不支持
    */
    boolean
    isRedefineClassesSupported();
    
    /**
    * 重新定义类
    */
    void
    redefineClasses(ClassDefinition... definitions)throws  ClassNotFoundException, 		UnmodifiableClassException;
    
    /**
    * 判断一个类是否可以被修改 
    * 原始类型，数组类型都是不可被修改的
    */
    boolean
    isModifiableClass(Class<?> theClass);
    
    /**
    * 返回JVM加载的所有Class
    */
    Class[]
    getAllLoadedClasses();
    
    /**
    * 返回所有的初始化类加载器是loader的类，如果传递null，则返回bootstrap类加载器初始化加载的类
    */
    Class[]
    getInitiatedClasses(ClassLoader loader);
    
    //.........
}
```

ClassFileTransformer是类转换器接口，里面只有一个方法：

```java
/**
* 通过Instrumentation的addTransformer方法注册的类转换器，转换器的transform方法在新的类被定义和所有的类被重新定义的时候被调用，那些			* * canRetransform参数为true的转换器，还会在类被重新转换的时候被调用，都是在class文件被校验和应用之前被调用。调用的时机如下：
* 1. 当类被定义的时候，也就是ClassLoader.defineClass方法被调用；
* 2. 当类被重新定义的时候，也就是Instrumentation.redefineClasses方法被调用
* 3. 当类被重新转换的时候，也就是Instrumentation.retransformClasses方法被调时候。 
* 如果有多个转换器，那么transform方法的调用组成转换器链，也就是上一个转换器的返回值，会作为下一个转换器的参数。
* 转化器的调用顺序如下：
* 1. canRetransform参数为false的转换器
* 2. canRetransform参数为false的本地转换器(本地转换器是通过ClassFileLoadHook事件添加进来的)
* 3. canRetransform参数为true的转换器
* 4. canRetransform参数为true的本地转换器
* 对于需要重新定义的类，canRetransform参数为false的转换器是不会被调用的，而是复用先前转换器的结果
* 在这四种情况内部，他们的调用顺序是被add的顺序
* ......
* 如果一个转换器抛出了一个它未捕捉到的异常，后续的转换器仍就会被执行，并且类的加载，重新转换，重新定义仍然会被尝试执行
* @param loader 类加载器，需要被转换的类的defining loader，如果是null，就是引导类加载器
* @param className 类的名称
* @param classBeingRedefined 如果方法的调用是重新定义或者重新转换触发的时候，classBeingRedefined指向被重转换，重定义的class
* @param protectionDomain class的保护区域
* @param classfileBuffer 组成class文件的字节数组，不能被修改
*/
byte[] transform(ClassLoader         loader,
                String              className,
                Class<?>            classBeingRedefined,
                ProtectionDomain    protectionDomain,
                byte[]              classfileBuffer)
        throws IllegalClassFormatException;
```

那么如何获取Instrumentation实例呢？

两种方法：

1. 上面所说的premain方法，当 JVM 以指示一个代理类的方式启动时，将传递给代理类的 premain 方法一个 Instrumentation 实例；
2. 当 JVM 提供某种机制在 JVM 启动之后某一时刻启动代理时，将传递给代理代码的 agentmain 方法一个 Instrumentation 实例。

# 3 修改/替换类的定义

一般通过ASM或者javasis等框架完成字节码的修改操作，此处后续更新

[Instrumentation简介](https://www.cnblogs.com/yelao/p/9841810.html)

[JVMTI 和 Agent 实现](https://developer.ibm.com/zh/articles/j-lo-jpda2/)