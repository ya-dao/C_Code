#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#define N 11

void initData(int *array);
void show(int *array);
void heapSort(int *array);
void createHeap(int *array, int length);
void heapAdjust(int *array, int index, int length);
int getMax(int *array, int index1, int index2);

void main() {
	int array[N] = { 0 };
	initData(array);
	printf("ÅÅĞòÇ°:\n");
	show(array);

	heapSort(array);

	printf("ÅÅĞòºó:\n");
	show(array);

	system("pause");
}

void initData(int *array) {
	srand(time(NULL));
	for (int i = 1; i < N; i++)
	{
		array[i] = rand() % 100 + 1;
	}
}

void show(int *array) {
	for (int i = 0; i < N; i++)
	{
		printf("%2d ", array[i]);
	}
	printf("\n");
}

void heapSort(int *array) {
	createHeap(array, N);
	for (int i = N - 1; i > 0; i--)
	{
		int temp = array[1];
		array[1] = array[i];
		array[i] = temp;
		heapAdjust(array,1,i - 1);
		printf("%d ",temp);
	}
	pritnf("\n");
}

void createHeap(int *array,int length) {
	for (int i = length / 2; i > 0; i--)
	{
		heapAdjust(array, i, length);
	}
}

void heapAdjust(int *array,int index,int length) {
	for (int i = 2 * index; i <= length; i *= 2)
	{
		if (i < length && array[i] < array[i + 1])
		{
			i++;
		}

		if (array[index] >= array[i])
		{
			break;
		}
		array[index] = array[i];
		index = i;
	}

	/*int max = 0;
	if (NULL != array[2 * index + 1])
	{
		max = getMax(array, 2 *index, 2 * index + 1);
	}
	else
	{
		max = 2 * index;
	}
	if (array[index] < array[max])
	{
		int temp = array[index];
		array[index] = array[index * 2];
		array[index * 2] = temp;
	}*/
}

int getMax(int *array, int index1, int index2) {
	if (array[index1] > array[index2])
	{
		return index1;
	}
	else
	{
		return index2;
	}
}