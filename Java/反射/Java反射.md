<center><font color="#FFA500" size="6">反射</font></center>

[TOC]

# 1 反射试什么？

满分版回答：在运行时，对于任何的一个类，都可以动态获取其属性和方法，对于任何一个对象，都可以调用其方法，更改其属性；这种在运行时，动态获取类信息，动态执行对象方法的方式，叫做反射。

也就是说，我们可以通过java代码，获取某一个类的构造方法，静态方法，实例方法，以及各种字段的描述。

# 2 Class类

java中有一个特殊的泛型类，他的名称叫做Class。他的构造方法是私有的，这个类的的对象，不是用户通过代码创建的，而是JVM在加载一个类的时候，由JVM创建的。内存中Class类的对象，都指向一个类或者接口。这个Class对象，记录了类的信息，例如构造方法，成员方法，静态方法，字段描述，以及类的名称，包名，其父类，实现的接口等。如果获取到了一个Class对象，那么我们就可以通过它，获取类的所有信息。那么这个对象怎么获得呢？

## 2.1 获取Class对象

1. 通过class静态属性

   java里的所有类型都有一个静态属性class，例如String.class，int.class等。

2. Object类有一个getClass的公有实例方法，因此可以任意一个对象的getClass方法获取。

3. 通过Class类的静态方法：`Class.forName(String name)`，会抛出`ClassNotFoundException`异常，参数是一个类的全路径名。

## 2.2 Class的特性

在一个JVM进程里，Class对象是唯一的。通过上面三种方式，获取的同一个类型的Class对象是同一个。数组也是一种Class，例如：String[].class，他的签名是：`[Ljava.lang.String`

JVM加载Class的方式是懒加载的，就是啥时候用到，啥时候加载。一般来说，main方法所在的类，会被加载；还有其他时机，例如调用一个类的构造方法时，调用其静态方法时，访问其属性时，通过`Class.forName()`方法获取Class对象时等。

# 3 通过Class获取构造方法

1. `Constructor<?>[] getConstructors()`获取所有的public的构造方法
2. ` Constructor<T> getConstructor(Class<?>... parameterTypes)`，根据参数的类型，获取某一个public构造方法
3. `Constructor<?>[] getDeclaredConstructor()`，获取所有的构造方法。
4. `Constructor<T> getDeclaredConstructor(Class<?>... parameterTypes)`，根据参数的类型，获取任意一个构造方法

通过构造方法创建对象，

`T newInstance(Object ... initargs)`，调用Constructor类的实例方法即可，传需要的参数，可以使用Class类的`T newInstance()`实例方法，这时调用无参数的构造方法，要确保操作的类含有这样的构造方法。

如果调用的是私有的构造方法，需要在调用之前，调用Constructor类的`public void setAccessible(boolean flag);`方法，flag设置为true，表示禁用JVM的访问检查，否则报错。