# 1 注解的使用

1. 注解是JDK1.5的新特性，所有的注解直接父接口都是`java.lang.annotation.Annotation`

2. 作用

   - 生成文档。这是最常见的，也是java 最早提供的注解。常用的有@see @param @return 等；
   - 替代配置文件。比较常见的是spring 2.5 开始的基于注解配置。作用就是减少配置。现在的框架基本都使用了这种配置来减少配置文件的数量
   - 编译时进行格式检查。如@Override放在方法前，如果你这个方法并不是覆盖了超类方法，则编译时就能检查出；
   - 实现代码复用，增强可维护性

3. 元注解(JDK1.5)

   - @Target 表示注解标记的范围，其参数是`ElementType`类型的数组：
     - 　　CONSTRUCTOR:用于描述构造器
     - 　　FIELD:用于描述域即类成员变量
     - 　　LOCAL_VARIABLE:用于描述局部变量
     - 　　METHOD:用于描述方法
     - 　　PACKAGE:用于描述包
     - 　　PARAMETER:用于描述参数
     - 　　TYPE:用于描述类、接口(包括注解类型) 或enum声明
     - 　　TYPE_PARAMETER:1.8版本开始，描述类、接口或enum参数的声明
     - 　　TYPE_USE:1.8版本开始，描述一种类、接口或enum的使用声明
   - @Retention，用于描述注解的生命周期，表示需要在什么级别保存该注解，即保留的时间长短。取值类型（RetentionPolicy）有以下几种：
     - 　　SOURCE:在源文件中有效（即源文件保留）
     - 　　CLASS:在class文件中有效（即class保留）
     - 　　RUNTIME:在运行时有效（即运行时保留）
   - @Documented，　用于描述其它类型的annotation应该被作为被标注的程序成员的公共API，因此可以被例如javadoc此类的工具文档化。它是一个标记注解，没有成员。
   - @Inherited，用于表示某个注解的作用是可以被继承的。如果一个使用了@Inherited修饰的annotation类型被用于一个class，则这个annotation将被用于该class的子类，但是互相继承的接口，或者类实现接口时，注解的作用都不会被继承

4. 定义一个注解的格式：

   访问修饰符 @interface 注解名称{

   ​	数据类型 方法名称() [default 默认值];

   }，

   @interface 是编译器的语法糖，会被解析为一个继承于`java.lang.annotation.Annotation`的接口

   注解的数据类型只有一下几种：

   - 八种原始类型
   - String
   - Class
   - 枚举类型
   - 注解类型
   - 以上的数组

5. 注解处理

   使用反射可以获取所有被指定注解标记的java语言元素(类，方法，字段，参数等)，然后做自定义的处理

# 2 注解的原理

注解实质上是一个接口，接口是不可以被实例化的，那么注解的方法是怎样被调用的呢？答案是：对于被`@Retention(RetentionPolicy.RUNTIME)`标记的注解，JVM会使用动态代理生成一个代理类实现注解的接口，我们通过反射获取到的注解实例，就是代理类，我们通过代理就可以调用注解的方法，拿到返回值。