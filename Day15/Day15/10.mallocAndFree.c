#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
void function1()
{
	/*
		测试一个进程最大内存
		结论:一个进程最大内存为2GB
	*/
	while (1) {
		malloc(10 * 1024 * 1024);
		Sleep(500);
	}
}
void function2() {
	/*
		malloc(动态内存)解决程序运行中需要动态分配内存的问题.
		int array[10] = { 0 };
		C语言中不能动态定义数组长度,代码中定义的数组属于静态内存,程序运行过程中不能修改其大小.
		程序栈的大小默认1MB,可以修改,但是太大影响效率.
	*/
	//根据输入的数组动态的创建一个指定长度的数组
	int length = 0;
	printf("输入数组长度:\n");
	scanf("%d", &length);
	int *p = (int *)malloc(length * sizeof(int));
	for (int i = 0; i < length; i++)
	{
		*(p + i) = i + 1;
	}
	for (int i = 0; i < length; i++)
	{
		printf("%d ",*(p + i));
	}
	printf("\n");
	free(p);
}
void function3() {
	/*
		malloc
		原型:void* malloc(size_t size);
			1.1 返回指向该片内存的首地址,如果分配失败,返回0x00000000
			1.2 size_t 是unsigned int,如果传入-1,则对应的值为int的最大值,造成分配失败
			1.3 malloc的返回值可以用一维数组来处理,也可以用其他结构来处理,主要取决于类型
			1.4 malloc可以分配0,但是没有意义
	*/
	//1.1
	//int length = 4123456789;
	
	//1.2
	//int length = -1;//这时-1为补码

	//1.3
	int length = 30 * sizeof(int);
	int (*p)[6] = malloc(length);
	printf("%p\n",p);
}
void function4() {
	/*
		2.free
			原型 : void free(void *block);
			2.1 malloc申请的动态内存在程序退出前不会自动释放, 必须手动释放,不释放会造成内存泄露.
			2.2 free只能释放一次,不允许反复释放,会触发断点
			2.3 free释放之后再次操作该内存可能会引发问题,
				所以free释放之后最好将该指针指向NULL,操作空指针会报错,避免出现未知错误	
			2.4 释放之后未指向NULL的指针称为"迷途指针"
	*/
	int length = 30;
	int *p = (int *)malloc(length);
	printf("%p\n",p);
	free(p);
	//2.3
	//*p = 123;
	p = NULL;
	//2.2
	//free(p);
}
void main() {
	//function1();
	//function2();
	//function3();
	function4();
	system("pause");
}