//7.生成一个二维数组，从左往右是递增的，从上到下是递增的。
//  请实现双二分查找法。先查找行，再查找列。
#include<stdio.h>
#include<stdlib.h>
#define N 10

void show(int *arr);
void initialize(int *arr);
void doubleBinarySearch(int *arr, int target);
int rowBinarySearch(int *arr, int row, int target);
int columnBinarySearch(int *arr, int column, int target);

void main() {
	int arr[2][2] = {1,2,3,4};
	//arr表示的地址是arr[0][0]的地址
	//*arr表示的地址是arr[0]的地址
	printf("%d\n", arr + 1);
	printf("%d\n", *arr + 1);
	system("pause");
}

void main1() {
	int arr[N][N] = { 0 };
	initialize(*arr);
	show(*arr);
	doubleBinarySearch(*arr, 16);
	system("pause");
}
void show(int *arr) {
	for (int i = 0; i < N; i++)
	{
		for (int  j = 0; j < N; j++)
		{
			printf("%2d ",*((arr + i * N) + j));
		}
		printf("\n");
	}
}
void initialize(int *arr) {
	int first = 1;
	for (int i = 0; i < N; i++)
	{
		if (i == 0) {
			*(arr + i * N) = first;
		}
		else {
			*(arr + i * N) = *(arr + (i - 1) * N) + 1;
		}
		for (int j = 1; j < N; j++)
		{
			*((arr + i * N) + j) = *((arr + i * N) + (j - 1)) + 1;
		}
	}
}

void doubleBinarySearch(int *arr, int target) {
	printf("行查找%d位于以下位置:\n",target);
	for (int i = 0; i < N; i++)
	{
		int column = rowBinarySearch(arr, i, target);
		if (-1 == column) {
			printf("第%d行不存在该数据\n", i);
		}
		else {
			printf("第%d行,第%d列.\n", i, column);
		}
	}
	printf("列查找%d位于以下位置:\n", target);
	for (int i = 0; i < N; i++)
	{
		int row = columnBinarySearch(arr, i, target);
		if (-1 == row) {
			printf("第%d列不存在该数据\n", i);
		}
		else {
			printf("第%d列,第%d行.\n", i,row);
		}
	}
}

int rowBinarySearch(int *arr, int row, int target) {
	int start = 0;
	int end = N - 1;
	int middle = start + (end - start) / 2;
	while (start <= middle && end >= middle)
	{
		if (*((arr + row * N) + middle) == target) {
			return middle;
		}
		else if (*((arr + row * N) + middle) > target)
		{
			end = middle - 1;
		}
		else if (*((arr + row * N) + middle) < target)
		{
			start = middle + 1;
		}
		middle = start + (end - start) / 2;
	}
	return -1;
}

int columnBinarySearch(int *arr, int column, int target) {
	int start = 0;
	int end = N - 1;
	int middle = start + (end - start) / 2;
	while (start <= middle && end >= middle)
	{
		if (*((arr + middle * N) + column) == target) {
			return middle;
		}
		else if (*((arr + middle * N) + column) > target)
		{
			end = middle - 1;
		}
		else if (*((arr + middle * N) + column) < target)
		{
			start = middle + 1;
		}
		middle = start + (end - start) / 2;
	}
	return -1;
}