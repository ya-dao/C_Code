#include<stdio.h>
#include<stdlib.h>
/*
	比较器
		

	Compare 函数的返回值			描述
		< 0				elem1将被排在elem2前面
		= 0				elem1 等于 elem2
		> 0				elem1 将被排在elem2后面 
*/
int compartor(const void *pA, const void *pB) {
	int a = *((int *)pA);
	int b = *((int *)pB);
	if (a == b)
	{
		return 0;
	}
	if (a > b)
	{
		return 1;
	}
	if (a < b)
	{
		return -1;
	}
}
void show(int *array) {
	for (int i = 0; i < 6; i++)
	{
		printf("%d ",array[i]);
	}
	printf("\n");
}
void main() {
	int array[] = { 1,3,2,6,4,5 };
	qsort(array,6,sizeof(int),compartor);
	show(array);
	system("pause");
}