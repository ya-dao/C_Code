#include<stdio.h>
#include<stdlib.h>
#define N 7

void swap(int *arr, int i, int j);
void sort(int *arr, int start, int end);
int partition(int *arr,int start,int end);
void show(int *arr);

void main() {
	int arr[N] = {2,5,4,7,3,1,6};
	sort(arr,0,N - 1);

	show(arr);
	system("pause");
}

void sort(int *arr,int start,int end) {
	if (start < end)
	{
		int index = partition(arr,start,end);
		sort(arr,start,index - 1);
		sort(arr, index + 1,end);
	}
}
/*
思路:
	把首元素当成基准值,从最后一个元素开始往前与基准值进行比较,如果发现小于基准值的元素就停止住前.
	将该元素与前面的指针进行交换.
	然后再从第一个元素开始住后与基准值进行比较,如果发现比基准值大的就停止往后.
	将该元素与前面的指针进行交换.
	如此往复,直到两头元素在某一个下标碰头,就直接将基准值与其下标进行交换.
*/
int partition(int *arr,int start,int end) {
	int i = start;
	int j = end;
	int base = *(arr + start);
	while(i < j)
	{
		while ((*(arr + j)) > base && j > i)
		{
			j--;
		}
		*(arr + i) = *(arr + j);

		while ((*(arr + i)) < base && j > i)
		{
			i++;
		}
		*(arr + j) = *(arr + i);
	}
	*(arr + i) = base;
	return i;
}

void swap(int *arr,int i,int j) {
	int temp = *(arr + i);
	*(arr + i) = *(arr + j);
	*(arr + j) = temp;
}

void show(int *arr) {
	for (int i = 0; i < N; i++)
	{
		printf("%d ", arr[i]);
	}
	putchar(10);
}