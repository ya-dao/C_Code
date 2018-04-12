#include<stdio.h>
#include<stdlib.h>
void main() {
	//指针必须初始化,没初始化的指针都是野指针,如果没初始化就开始用会报错.
	//int *p;
	int *p = NULL;
	printf("%p\n",p);
	system("pause");
}