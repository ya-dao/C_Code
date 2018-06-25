#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#define N 10

void initData(int *array);
void show(int *array);
void quickSort(int *array, int low, int high);
int partition(int *array, int low, int high);

void main() {
	int array[N] = {0};
	initData(array);
	printf("排序前:\n");
	show(array);

	quickSort(array, 0, N - 1);

	printf("排序后:\n");
	show(array);

	system("pause");
}

void initData(int *array) {
	srand(time(NULL));
	for (int i = 0; i < N; i++)
	{
		array[i] = rand() % 100 + 1;
	}
}

void show(int *array) {
	for (int i = 0; i < N; i++)
	{
		printf("%2d ",array[i]);
	}
	printf("\n");
}

void quickSort(int *array, int low, int high) {
	if (low >= high) {
		return;
	}
	else {
		//划分
		int middle = partition(array, low ,high);
		quickSort(array, low, middle - 1);
		quickSort(array, middle + 1, high);
	}
}

int partition(int *array, int low, int high) {
	//定标准
	int stander = array[low];
	while (low < high) {
		while(low < high && array[high] > stander)
		{
			high--;
		}
		array[low] = array[high];
		while (low < high && array[low] < stander) {
			low++;
		}
		array[high] = array[low];
	}
	array[low] = stander;
	return low;
}




























