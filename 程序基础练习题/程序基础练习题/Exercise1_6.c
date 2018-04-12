//6.请自动生成1024个随机数（0 - 1024之间），排序后用二分查找，插值查找找到。
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 1024

void initialize(int arr[N]);
void showArr(int arr[N]);
void insertionSort(int arr[N]);
int binarySearch(int arr[N], int target);

void main() {
	int index = -1;
	int target = 3;
	int arr[N] = { 0 };
	initialize(arr);
	insertionSort(arr);
	showArr(arr);

	//index = binarySearch(arr, target);
	index = interpolationSearch(arr, target);

	if (-1 == index)
	{
		printf("该数列中不存在%d\n",target);
	}
	else {
		printf("第一个%d对应的下标为%d\n", target, index);
	}

	system("pause");
}

void showArr(int arr[N]) {
	for (int i = 0; i < N; i++)
	{
		printf("%-4d ",arr[i]);
		if ((i + 1) % 10 == 0) {
			printf("\n");
		}
	}
	printf("\n--------------------------------------\n");
}

void initialize(int arr[N]) {
	srand(NULL);
	for (int i = 0; i < N; i++)
	{
		arr[i] = rand() % N;
	}
}

/*貌似选择,冒泡,插入这几种排序算法复杂度都差不多是O(n^2),而插入有可能会减少些步骤*/
void insertionSort(int arr[N]) {
	//插入排序的精髓是读一个插一个,从第一个开始把每一个都放到合适的位置
	for (int i = 1; i < N; i++)//只有一个的时候不需要排序
	{
		//保存当前需要排序的下标的值,防止移动前面的元素的时候被覆盖
		int temp = arr[i];
		//由于会涉及到元素的移动,需要记录移动到哪一个下标了
		int index = i;
		while (index > 0 && arr[index - 1] > temp) {
			arr[index] = arr[index - 1];
			index--;
		}
		arr[index] = temp;
	}
}

/*
	二分法查找,找到返回下标,未找到返回-1
*/
int binarySearch(int arr[N],int target) {
	int count = 0;
	int start = 0;
	int end = N - 1;
	int middle = (start + end) / 2;

	while (middle >= start && middle <= end)
	{
		if (arr[middle] == target)
		{
			printf("binaryCount = %d\n", count);
			return middle;
		}
		else if (arr[middle] > target)
		{
			end = middle - 1;
		}
		else if (arr[middle] < target)
		{
			start = middle + 1;
		}
		middle = (start + end) / 2;
		count++;
	}
	return -1;
}

/*
	插值查找,核心是修改二分查找的公式
	二分:middle = start + (end - start) / 2
	插值:arr[middle] - arr[start]        middle - start
		-------------------------  ==   ----------------
		 arr[end] - arr[start]            end - start
	
	由上面的比例即可得到:
		middle = start + (end - start) * (arr[middle] - arr[start]) / (arr[end] - arr[start])
*/
int interpolationSearch(int arr[N],int target) {
	int count = 0;
	int start = 0;
	int end = N - 1;
	int middle = start + (end - start) * (target - arr[start]) / (arr[end] - arr[start]);

	while (middle >= start && middle <= end) {
		if (arr[middle] == target) {
			printf("interpolationCount = %d\n", count);
			return middle;
		}
		else if (arr[middle] < target)
		{
			start = middle + 1;
		}
		else if(arr[middle] > target)
		{
			end = middle - 1;
		}
		middle = start + (end - start) * (target - arr[start]) / (arr[end] - arr[start]);
		count++;
	}
	return -1;
}