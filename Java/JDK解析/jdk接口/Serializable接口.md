1. java把对象，转化成字节序列，保存在磁盘或者在网络中传输，叫做对象的序列化；把磁盘或者从网络中加载的字节序列，还原成对象的过程，叫做对象的反序列化。

2. 需要序列化和反序列化的类，需要显式或者隐式的实现`java.io.Serializable`接口，不实现此接口的类，在序列化的时候会抛出`java.io.NotSerializableException`异常。

3. 一般来说，使用`java.io.ObjectOutputStream`的`writeObject()`方法，把一个对象写入文件，使用`java.io.ObjectInputStream`的`readObject()`方法，从文件中反序列化对象。

4. 当一个类实现了序列化接口时，最好在类中写一个序列化ID，格式如下：

   `ANY-ACCESS-MODIFIER static final long serialVersionUID = 42L;`，因为如果自己不声明，编译器会自己生成一个，生成的规则时根据类的各种信息，例如字段个数，字段名称等做摘要计算，生成一个hash值，当我们修改源代码时，编译器生成的hash值就会变化。对象在序列化的时候，这个值也会被序列化到字节流中，当反序列化时，对比发现两个类的序列化ID不一致，就会抛出` java.io.InvalidClassException`异常，所以最好是自己写死一个序列化ID

5. 序列化是把对象的信息存储在字节序列中，但是静态数据是类的信息，不会被序列化，除此之外被`transient`修饰的字段也不会被序列化。

