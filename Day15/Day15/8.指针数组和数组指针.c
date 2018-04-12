#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void function1() {
	/*
		指针数组:int *p[10]
		用途:存储多个连续的地址,如数组
		实例:对一个数组进行排序输出,要求不能改变原数组
	*/
	int array[10] = { 0 };
	int *pArray[10] = { NULL };
	//初始化
	time_t t;
	srand((unsigned int)time(&t));
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 100 + 1;
	}
	for (int i = 0; i < 10; i++)
	{
		pArray[i] = &array[i];
	}

	//采用冒泡排序
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10 - 1 - i; j++)
		{
			//*(pArray + j)取出指针数组第j个元素所存储的地址,再*取出里面的值
			if (*(*(pArray + j)) < *(*(pArray + j + 1)))
			{
				int *temp = *(pArray + j);
				*(pArray + j) = *(pArray + j + 1);
				*(pArray + j + 1) = temp;
			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		printf("%d ",*(*(pArray + i)));
	}
	putchar(10);
}
void function2() {
	/*
		数组指针:int (*p)[10]
	*/
	int array[] = { 1,2,3 };
	//这是错误的,类型不匹配,a是一个int *类型,&a才是一个数组指针类型
	//int(*p)[3] = array;
	int(*p)[3] = &array;
	//这是一个一维数组,所以p直接指向这一行数组,+1往前移动一个单位,再*取出数据
	printf("%d\n",*(*p + 1));
}
void main() {
	//function1();
	function2();
	system("pause");
}