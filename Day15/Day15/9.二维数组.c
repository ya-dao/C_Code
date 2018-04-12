#include<stdio.h>
#include<stdlib.h>
void show(int (*p)[5]) {
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			printf("%2d ",*(*(p + i) + j));
		}
		printf("\n");
	}
}
void main() {
	int array[3][5];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			array[i][j] = j + i * 5;
		}
	}
	show(array);
	printf("array[1]=%p\n",&array[1]);
	printf("*(array + 1)=%p\n", array + 1);

	printf("array[1][0]=%d\n",array[1][0]);
	printf("*(*(array + 1) + 0)=%d\n", *(*(array + 1) + 0));
	system("pause");
}