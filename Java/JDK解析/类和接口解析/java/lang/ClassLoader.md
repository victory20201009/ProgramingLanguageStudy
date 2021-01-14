<center><font color="#FFA500" size="6">ClassLoader</font></center>

[TOC]



# 1 ClassLoader介绍

1. 这是一个抽象类，主要负责加载类，构成类的定义数据结构。一个典型的实现策略是，根据类的全限定名，从磁盘文件中获取类的文件名称，然后读取其二进制字节流。
2. 每一个Class对象，都有一个引用指向定义它的ClassLoader对象，可以通过`Class的getClassLoader()`方法获取
3. 数组类型的Class对象，不是由ClassLoader创建的，而是Java运行时创建的。但是数组类型的Class对象的getClassLoader()返回值与其元素类型的Class对象的getClassLoader()返回值相同；原始类型的Class对象没有相对应的ClassLoader对象，相应的，原始类型数组的Class对象也没有相对应的ClassLoader。
4. ClassLoader类使用类委派模型去加载类和资源，每一个ClassLoader对象，都有一个相关联的parent ClassLoader对象；当需要寻找一个类或资源时，在当前类加载器亲自寻找之前，会先把这个任务委派给他的parent加载器。JVM内置类加载器是Bootstrap ClassLoader，它没有parent加载器，但是它是ClassLoader类实例的父加载器。

# 2 类元素

## 2.1 字段



