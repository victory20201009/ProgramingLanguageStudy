1. `java.io.OutputStream`类是一个抽象类，是所有字节输出流的基类，这样的对象可以接受输出的字节，并把它们发送到某个接收器。

2. > ```java
   > /* Applications that need to define a subclass of
   > * <code>OutputStream</code> must always provide at least a method
   > * that writes one byte of output. 
   > * 定义一个OutputStream的子类，必须至少实现写一个方法可以写一个字节
   > */
   > ```
   
3. ```java
   /*
   * 写入方法的一般约定是写入一个字节，这个方法会写入b的低8为，高24位会被忽略，子类必须实现这个方法。
   */
   public abstract void write(int b) throws IOException;
   ```

4. ```java
   /*
   * 按照顺序写入一个字节数组的一部分，从索引off开始，写入len个，调用写入一个字节的方法实现的。
   */
   public void write(byte b[], int off, int len) throws IOException {
           if (b == null) {
               throw new NullPointerException();
           } else if ((off < 0) || (off > b.length) || (len < 0) ||
                      ((off + len) > b.length) || ((off + len) < 0)) {
               throw new IndexOutOfBoundsException();
           } else if (len == 0) {
               return;
           }
           for (int i = 0 ; i < len ; i++) {
               write(b[off + i]);
           }
       }
   ```

5. ```java
   /*
   * 写入一个字节数组，通过write(byte b[], int off, int len)方法实现。
   */
   public void write(byte b[]) throws IOException {
           write(b, 0, b.length);
   }
   ```

6. `public void close() throws IOException;`和`public void flush() throws IOException;`方法都是空实现

