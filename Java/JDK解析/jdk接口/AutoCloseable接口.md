1. 实现`java.lang.AutoCloseable`接口的类，在使用try-with-resource中声明的对象，在退出try-with-resoure之后会自动调用close方法释放资源。格式：

   try(AutoCloseable ac = new AutoCloseableImpl();AutoCloseable ac1 = new AutoCloseableImpl();...){

   }catch(Exception e){

   }