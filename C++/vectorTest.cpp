#include <iostream>
#include <vector>

using namespace std;

void printVector(vector<int>& iv) {
        putchar('[');
        if(iv.size()>0) {
                for (auto int i = 0; i != iv.size(); ++i) {
                        //vector重载了[]操作符
                        printf("%d", iv[i]);
                        if(i+1==iv.size()) putchar(']');
                        else putchar(',');
                }
        }else
                putchar(']');
        putchar('\n');
}

//下面的代码在gcc version 4.8.2 下编译调试
int main(int argc, char const *argv[]) {
        //定义一个长度为10的向量，初始值不确定 进过测试是0 构造方法vector<int>(长度，[初始值]，[分配器]) []表示可选,分配器一般采用默认
        vector<int> iv(10);
        printVector(iv);
        vector<int> iv2(10,1);
        printVector(iv2);

        //如果直接定义一个vector，则不分配内存
        vector<int> iv3;
        printVector(iv3);
        //下面的调用就会使程序崩溃，后面的打印语句没有被执行,程序被终止
        //iv3[0]=1;
        //printf("ssss");

        //push_back函数可以在尾部插入，为vector动态分配内存
        iv3.push_back(1);
        printVector(iv3);

        //用一个vector初始化另一个
        vector<int> iv4(iv2);
        printVector(iv4);

        //判断是否为空的函数empty
        if(iv4.empty()) {
                printf("iv4 is empty\n");
        }else{
                printf("iv4 is not empty\n");
        }
        int iarr[] = {17,56,1,22,4,3};
        //可以使用数组的一部分初始化vector 包左不包右
        vector<int> iv5(iarr,iarr+5);
        printVector(iv5);
        //vector的迭代器
        vector<int>::iterator iv5_iter = iv5.begin();
        //begin函数返回的迭代器指向向量的第一个元素
        printf("%d\n",*iv5_iter);
        //地带器可以+1，向后移动，vector的end函数返回指向最后一个元素的下一个位置的指针
        for(; iv5_iter!=iv5.end(); ++iv5_iter)
                printf("%d\n",*iv5_iter);

        //可以使用vector的一部分来初始化另一个vector
        vector<int> iv6(iv5.begin(),iv5.begin()+3);
        printVector(iv6);

        //空向量的的begin和end函数相等
        vector<int> iv7;
        if(iv7.begin()==iv7.end())
                printf("begin and end are equals\n");
        else
                printf("begin and end are not equals\n");

        //fron和back函数分别返回向量的第一个和最后一个元素
        printf("%d\n",iv6.front());
        printf("%d\n",iv6.back());

        //清空iv6中的元素
        printf("clear iv6\n");
        iv6.clear();
        printf("after clear\n");
        printf("%d\n",iv6.size());
        printVector(iv6);

        printf("test pop_back before\n" );
        printVector(iv5);
        iv5.pop_back();
        printf("after pop back\n" );
        printVector(iv5);

        printf("test insert before\n" );
        printVector(iv5);
        iv5.insert(iv5.begin(),123);
        printf("after insert 123\n" );
        printVector(iv5);
        printf("after insert 456 five times\n" );
        iv5.insert(iv5.begin()+1,5,456);
        printVector(iv5);

        printf("after insert a part of array\n" );
        //插入数组的一部分 包左不包右
        iv5.insert(iv5.begin(),iarr+1,iarr+3);
        printVector(iv5);
        vector<int> iv8(10,2);
        printf("after insert a part of vector\n" );
        //迭代器也是一种指针，插入vector的一部分 包左不包右
        iv5.insert(iv5.begin(),iv8.begin(),iv8.end());
        printVector(iv5);
        printf("the capacity of iv5 is %d,size is %d\n",iv5.capacity(),iv5.size());

        //erase vector
        printf("before erase vector\n");
        printVector(iv5);
        printf("after erase a part elsement\n");
        iv5.erase(iv5.begin(),iv5.begin()+18);
        printVector(iv5);

        //resize 多的会被初始化为0 少的会被截断
        printf("before resize 10\n");
        iv5.resize(10);
        printf("after resize 10\n");
        printVector(iv5);
        printf("after resize 2\n");
        iv5.resize(2);
        printVector(iv5);
        printf("after resize 100 with defaule value 1\n");
        iv5.resize(100,1);
        printVector(iv5);

        //reserve函数，预留空间
        printf("before reserve iv5 size is %d, capacity is %d\n",iv5.size(),iv5.capacity());
        iv5.reserve(200);
        printf("after reserve iv5 size id %d, capacity is %d\n",iv5.size(),iv5.capacity());

        //赋值操作符和assign函数 都是深拷贝
        printf("test = operator and assign\n");
        printf("print iv8\n");
        printVector(iv8);
        vector<int> iv9;
        printf("iv9=iv8\n");
        printf("print iv9\n");
        iv9 = iv8;
        printVector(iv9);
        printf("iv8[0]=10\n");
        iv8[0]=10;
        printf("print iv8\n");
        printVector(iv8);
        printf("print iv9\n");
        printVector(iv9);

        printf("iv9.assign(iv8.begin(),iv8.begin()+3)\n");
        iv9.assign(iv8.begin(),iv8.begin()+3);
        printVector(iv9);
        printf("iv8[0]=0\n");
        iv8[0]=0;
        printf("print iv8\n");
        printVector(iv8);
        printf("print iv9\n");
        printVector(iv9);
        return 0;
}
