#include<stdio.h>
#include<stdlib.h>
int add(int a,int b) {
	return a + b;
}
int subtract(int a, int b) {
	return a - b;
}
int multiply(int a, int b) {
	return a * b;
}
void function1() {
	/*
		函数指针数组
			定义:类型 (*[])(形参类型);
			作用:保存多个函数地址,可连续调用多个地址
			调用:(*(p + i))(参数)
	*/
	int(*p[])(int, int) = { add,subtract,multiply };
	for (int i = 0; i < 3; i++)
	{
		int result = (*(p + i))(100,10);
		printf("%d\n",result);
	}
}
void function2(){
	/*
		二级函数指针
		定义:int (**pp)(int,int);
			由函数指针数组推导而来
			int (*p[])(int,int),将[]替换成一个*
			p是函数指针数组名,等价于二级函数指针pp
		作用:1.可以不用指定数量,直接通过控制指针的加减即可
	*/
	int (*p[])(int, int) = { add,subtract,multiply };
	int (**pp)(int, int) = p;
	for (pp = p; pp < p + 3; pp++)
	{
		//*没()优先级高,所以需要*pp加上()
		printf("%d\n",(*pp)(100,10));
	}
	pp = p;
	for (int i = 0; i < 3; i++)
	{
		printf("%d\n",(*(pp + i))(100,10));
	}
}
void function3() {
	/*
		malloc二级函数指针
			二级指针即指针数组,用malloc创建多个函数指针的空间即可
			int(**pp)(int, int) = malloc(sizeof(int (*)(int, int)) * 4);
	*/
	int(**pp)(int, int) = malloc(sizeof(int (*)(int, int)) * 4);
	*(pp + 0) = add;
	*(pp + 1) = subtract;
	*(pp + 2) = multiply;
	for (int i = 0; i < 3; i++)
	{
		printf("%d\n",(*(pp + i))(100,10));
	}
}
void main() {
	//function1();
	//function2();
	function3();
	system("pause");
}