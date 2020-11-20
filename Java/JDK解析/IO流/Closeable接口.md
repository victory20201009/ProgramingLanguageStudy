1. `java.io.Closeable`接口继承自`java.lang.AutoCloseable`接口
2. 当资源释放失败的时候，强烈建议在抛出异常之前，先在内部标识为已关闭，并忽略底层的资源。