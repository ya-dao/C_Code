#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
/*
	可变参数需要导入标准参数(stdarg.h)头文件,有两种表明参数个数的方法
		1.将第一个参数作为标识参数个数
		2.将最后一个参数作为参数结束的标志
	va_start(list,start)是不会读取start参数的,只会从它的后面开始读
*/
//第一个标识参数个数 ...是可变参数的标识
void test1(int count,...){
	va_list list;//存放参数的起始地址
	int i = 0;
	int result = 0;
	va_start(list,count);//传入参数开始地址和参数个数,从首地址开始读取count个数据
	for(i = 0;i < count;i++){
		result += va_arg(list,int);//从起始地址开始读取数据,将读取的每个数据转换为int类型
	}
	va_end(list);
	printf("%d\n",result);
}
//以某一个值作为参数结束的标志
void test2(int start,...){
	va_list list;
	int i = 0;
	int result = 0;
	int arg = start;
	
	va_start(list,start);
	
	do{
		printf("%d ",arg);	
		arg = va_arg(list,int);
		result += arg;
	}while(arg != -1);
	
	va_end(list);
	printf("\n%d\n",result);
}
void main(){
	test1(3,2,1,4);
	test2(5,3,5,2,-1);
	system("pause");
}