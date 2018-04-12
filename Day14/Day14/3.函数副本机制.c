#include<stdio.h>
#include<stdlib.h>
/*
	函数的参数有副本机制.除数组外,其它类型的参数传递形参都是实参的副本,所以下面这个交换是无效的.
	因为它只交换了两个参数副本的值,并未对实参造成任何影响.
*/
void swap(int a,int b) {
	int temp = a;
	a = b;
	b = temp;
}
/*
	要想避免副本机制对交换造成影响可以传递实参的地址,用指针进行操作,
*/
void swapByPoint(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
/*
	数组没有副本机制,因为对数组采用副本机制会浪费内存空间.
*/
void swapForArray(int *array1, int *array2,int length) {
	for (int i = 0; i < 2; i++)
	{
		int temp = *(array1 + i);
		*(array1 + i) = *(array2 + i);
		*(array2 + i) = temp;
	}
}
/*
	除了数组没有副本机制,指针也是有副本机制的.
	可以通过运行结果看到,指针所指向的值是一样的,但它们不是同一个指针了,因为它们地址不一样.
*/
void swapForPoint(int *p1, int *p2) {
	printf("函数中的指针指向的值:\n");
	printf("p1:%d\n", *p1);
	printf("p2:%d\n", *p2);
	printf("函数中的指针地址:\n");
	printf("p1:%p\n",&p1);
	printf("p2:%p\n", &p2);
}
void main() {
	int a = 10;
	int b = 5;
	//swap(a, b);
	swapByPoint(&a, &b);
	printf("a=%d,b=%d\n",a,b);

	int array1[] = { 1,2 };
	int array2[] = { 3,4 };
	swapForArray(array1, array2, 2);

	printf("array1:");
	for (int i = 0; i < 2; i++)
	{
		printf("%d ",array1[i]);
	}
	printf("\n");
	printf("array2:");
	for (int i = 0; i < 2; i++)
	{
		printf("%d ", array2[i]);
	}
	printf("\n");
	int *p1 = &a;
	int *p2 = &b;
	
	printf("main中的指针指向的值:\n");
	printf("p1:%d\n", *p1);
	printf("p2:%d\n", *p2);
	printf("main中的指针地址:\n");
	printf("p1:%p\n", &p1);
	printf("p2:%p\n", &p2);
	printf("\n");

	swapForPoint(p1, p2);

	system("pause");
}