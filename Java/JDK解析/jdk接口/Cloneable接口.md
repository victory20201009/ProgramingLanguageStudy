1. `java.lang.Cloneable`接口是一个标记接口，表示对象可以被克隆，里面没有任何方法
2. 克隆对象的方法在`java.lang.Object`中，是一个native方法，并且访问权限是`protected`
3. Object类对clone方法的实现是所谓的`浅拷贝`，即对于原始类型，拷贝其值，对于String类型，拷贝其引用，指向同一个字符串，对于引用类型，拷贝的是引用，引用同一个对象。
4. 我们自己写的类如果希望可以克隆的话，需要让类实现`java.lang.Cloneable`接口，然后重写clone方法，如果希望这个方法在任意地方可以被访问，需要修改访问权限为public，可以在重写的clone方法中调用父类的clone方法，获得一个当前类的对象浅拷贝，然后根据我们自己的逻辑做响应的拷贝
5. 如果没有实现`java.lang.Cloneable`接口的类，调用clone方法会抛出`java.lang.CloneNotSupportedException`

