#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
/*
	通过在主线程监视发现,alloca分配的这块内存不会一直保留,会被回收.
	所以得出结论,alloca分配的内存是在栈中
*/
void function1() {
	int *p = alloca(sizeof(int) * 10);
	for (int i = 0; i < 10; i++)
	{
		*(p + i) = i + 1;
	}
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", *(p + i));
	}
	printf("\n");

}
void main() {
	function1();
	//多添加几个断点查看内存中的变化
	printf("\n");
	printf("\n");
	printf("\n");
	system("pause");
}