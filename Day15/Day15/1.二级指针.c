#include<stdio.h>
#include<stdlib.h>
void main() {
	double array[100];
	for (int i = 0; i < 100; i++)
	{
		array[i] = i + 1;
	}
	/*
		double*一级指针一次需要移动8个字节
	*/
	double* p = array + 1;
	printf("此时的值:%f\n",*p);
	double** pp = &p;
	printf("double**的大小=%d\n",sizeof(pp));
	/*
		指针的类型非常重要,这里是直接取的array的地址,有类型.
		如果是直接输入它的地址0x0000这样的十六进制的数值,那么前进的地址还需要乘上它的类型一次所移动的字节长度
	*/
	*pp = array + 80;
	printf("修改之后的值:%f\n", *p);
	system("pause");
}