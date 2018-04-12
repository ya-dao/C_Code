//2.请手动输入10个数到数组，取出最大值，最小值
#include<stdio.h>
#include<stdlib.h>

#define N 10

int getMin(int *arr);
int getMax(int *arr);
void main() {
	int arr[N] = { 23,3456,546,756,213,42,765,8,67,867 };
	printf("min = %d,max = %d\n",getMin(arr),getMax(arr));
	system("pause");
}

int getMin(int *arr) {
	int min = arr[0];
	for (int i = 1; i < N; i++)
	{
		if (min > arr[i]) {
			min = arr[i];
		}
	}
	return min;
}

int getMax(int *arr) {
	int max = arr[0];
	for (int i = 1; i < N; i++)
	{
		if (max < arr[i]) {
			max = arr[i];
		}
	}
	return max;
}