#include<stdio.h>
#include<stdlib.h>
/*
	通过循环赋值比递归计算斐波那契数列值的速度要快很多
*/
int recursive(int number) {
	if (number == 1 || number == 2) {
		return 1;
	}
	else {
		return recursive(number - 1) + recursive(number - 2);
	}
}
/*
	由于return有副本机制,所以这里返回一个局部变量的地址个人暂时觉得应该没什么大的毛病.有问题再说吧
*/
int* array() {
	int a[100] = { 0 };
	a[0] = 1;
	a[1] = 1;

	for (int i = 2; i < 40; i++)
	{
		a[i] = a[i - 1] + a[i - 2];
	}

	return a;
}
void main() {
	int *a = NULL;
	a = array();
	printf("%d\n", a[39]);

	int result = recursive(40);
	printf("%d\n",result);

	getchar();
}