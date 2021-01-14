#include<iostream>

using namespace std;
/*
bool is_big_endian()
{
	int a = 0x1234;
	return *((char*)&a)==0x12;
}*/

union NUM {
	int a;
	char b;
} num;

int main(int argc,char** argv)
{
	/*
	if(is_big_endian())
		cout<<"当前计算机的字节顺序是大端方式"<<endl;
	else
		cout<<"当前计算机的字节顺序是小端方式"<<endl;
	*/
	num.a=0x1234;
	if(num.b==0x12)
		cout<<"当前计算机的字节顺序是大端方式"<<endl;
	else
		cout<<"当前计算机的字节顺序是小端方式"<<endl;
	return 0;
}