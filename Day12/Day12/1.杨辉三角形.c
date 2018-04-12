#define N 5
#include<stdio.h>
#include<stdlib.h>

/*
	杨辉三角形:左右边界上都为1,且每一个数都等于上方两数之和
*/
void main() {
	int a[N][N] = { 0 };

	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < N;j++)
		{
			a[i][0] = 1;//初始化左边界上的值为1
			if (i == j) {
				//初始化对角线上的值为1
				a[i][j] = 1;
			}
			else if(j < i){
				//初始化其他值等于上方两个数之和
				a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
			}
		}
	}

	for (int i = 0;i < N;i++)
	{
		printf("%*d", 21 - 2 * i, a[i][0]);
		for (int j = 1;j < N;j++)
		{
			if (j <= i) {
				printf("%4d",a[i][j]);
			}
		}
		printf("\n");
	}

	system("pause");
}