#include<stdio.h>
#include<stdlib.h>
void function1() {
	/*
	1.指针的运算仅包括与数字的加减或者两个指针的减法,其他运算没有意义
	2.指针的减法仅对于同类型的指针
	3.相减的结果是两个指针之间间隔的内存数,再减去sizeof(该指针所指向的类型)
	*/
	int array[] = { 1,2,3,4,5 };
	int *p1 = &array[1];
	int *p2 = &array[4];
	//p2-p1 = (p2 - p1) / sizeof(int)
	printf("%d\n", (p2 - p1));
}
void function2() {
	/*
	指针一般不允许直接赋值,结果不可预知,除非已经确定这个地址可用.
	*/
	int *p = 0x123;
	*p = 10;
	printf("%d\n", *p);
}
void function3() {
	/*
		const指针
		1.const int *p;
			const在*号左边修饰类型int时,指针所指向的值*p不能被修改,指针的值p可以修改.
		2.int * const p;
			const在*号右边修饰指针变量p时,指针所指向的值*p可以被修改,指针的值p可以修改.
		3.const int * const p;
			当const修改类型int和指针变量p时,指针所指向的值*p和指针的值p都不能被修改
		4.数组名array的本质是int * const array类型
			即不能修改数组名的指向,但是可以修改其所指向的值.
		5.const指针可以用做权限控制.
			const int *p给予可读不可写权限.
			int * const p给予可读,可写,但不可跳转权限
			const int * const p给予可读,不可写,且不可跳转权限
	*/
	int array[] = { 1,2,3 };
	int array2[] = { 4,5,6};

	/*
	const int *p1 = &array;
	//*p1 = 40;
	p1 = &array2;

	for (int i = 0; i < 3; i++)
	{
		printf("%d ", *(p1 + i));
	}
	printf("\n");
	

	int * const p2 = &array;
	*p2 = 40;
	//p2 = &array2;

	for (int i = 0; i < 3; i++)
	{
	printf("%d ", *(p2 + i));
	}
	printf("\n");
	
	
	const int * const p3 = &array;
	//*p3 = 50;
	//p3 = &array2;

	for (int i = 0; i < 3; i++)
	{
		printf("%d ", *(p3 + i));
	}
	printf("\n");
	*/
	
	//array = &array2;
	*array = 60;
	for (int i = 0; i < 3; i++)
	{
		printf("%d ", *(array + i));
	}
	printf("\n");
}
void main() {
	//function1();
	//function2();
	function3();
	system("pause");
}

