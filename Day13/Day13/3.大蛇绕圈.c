#include<stdio.h>
#include<stdlib.h>
#define N 6
/*
	打印如下数字:
	1  2  3  4
	12 13 14 5
	11 16 15 6
	10 9  8  7
*/
void move(int (*arr)[N]);
void show(int (*arr)[N]);
void main() {
	int arr[N][N] = { 0 };
	move(arr);
	show(arr);
	system("pause");
}
void move(int (*arr)[N]) {
	//观察发现,从左往右开始的次数是每一行数/2,奇数需要加1次.即可以用(N+1)/2
	int number = 1;
	for (int i = 0; i < ((N + 1) / 2); i++)
	{
		//按照右,下,左,上的顺序打印即可
		int row = i;
		int column = i;
		//右
		while (column < (N - i))
		{
			(*(arr + row))[column++] = number++;
		}
		show(arr);
		column--;
		row++;

		//下
		while (row < (N - i))
		{
			(*(arr + row++))[column] = number++;
		}
		show(arr);
		row--;
		column--;

		//左
		while (column >= i)
		{
			(*(arr + row))[column--] = number++;
		}
		show(arr);
		column++;
		row--;

		//上
		while (row > i)
		{
			(*(arr + row--))[column] = number++;
		}

		show(arr);
	}
}

void show(int (*arr)[N]) {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%2d ",(*(arr + i))[j]);
		}
		printf("\n");
	}
	printf("\n");
}