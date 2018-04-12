//1.请手动输入10个数到数组，实现从大到小，从小到大排序，请用冒泡，插入，选择实现。要求分别实现一个修改原来数组和不修改原来数组
#include<stdio.h>
#include<stdlib.h>
#define N 10

//冒泡排序 - 从小到大修改原来数组
void bubbleSortMinToMax(int *arr);
//冒泡排序-从小到大不修改原来数组
void bubbleSortMinToMaxNotModify(const int *pArr[N]);

//插入排序 - 从小到大修改原来数组
void insertSortMinToMax(int *arr);
//插入排序 - 从小到大不修改原来数组
void insertSortMinToMaxNotModify(const int *pArr[N]);

//选择排序 - 从小到大修改原来数组
void selectSortMinToMax(int *arr);
//选择排序 - 从小到大不修改原来数组
void selectSortMinToMaxNotModify(const int *pArr[N]);

void main() {
	int arr[N] = { 4,2,5,8,7,6,1,3,9,0 };
	int *pArr[N] = {&arr[0],&arr[1],&arr[2],&arr[3],&arr[4],&arr[5],&arr[6],&arr[7],&arr[8],&arr[9]};
	
	//bubbleSortMinToMax(arr);
	//bubbleSortMinToMaxNotModify(pArr);
	//insertSortMinToMax(arr);
	insertSortMinToMaxNotModify(pArr);
	//selectSortMinToMax(arr);
	//selectSortMinToMaxNotModify(pArr);
	for (int i = 0; i < N; i++)
	{
		//printf("%d ",arr[i]);
		printf("%d ", *pArr[i]);
	}

	printf("\n");
	system("pause");
}

//冒泡排序-从小到大,不修改数据,const:禁止修改该地址对应的值
void bubbleSortMinToMaxNotModify(const int *arr[N])
{
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = 0; j < N - 1 - i; j++)
		{
			if (*arr[j] > *arr[j + 1]) {
				int *temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

//冒泡排序-从小到大,修改数据
void bubbleSortMinToMax(int *arr) {
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = 0; j < N - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

//插入排序 - 从小到大修改原来数组
void insertSortMinToMax(int *arr) {
	for (int i = 1; i < N; i++)
	{
		int temp = arr[i];
		int index = i;
		while (index > 0 && arr[index - 1] > temp) {
			arr[index] = arr[index - 1];
			index--;
		}
		arr[index] = temp;
	}
}

//插入排序 - 从小到大不修改原来数组
void insertSortMinToMaxNotModify(const int *pArr[N]) {
	for (int i = 1; i < N; i++)
	{
		int* temp = pArr[i];
		int index = i;
		while (index > 0 && *pArr[index - 1] > *temp) {
			pArr[index] = pArr[index - 1];
			index--;
		}
		pArr[index] = temp;
	}
}

//选择排序,修改原来数组
void selectSortMinToMax(int *arr) {
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = i + 1; j < N; j++) {
			if (arr[i] > arr[j]) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

//选择排序 - 从小到大不修改原来数组
void selectSortMinToMaxNotModify(const int *pArr[N]) {
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = i + 1; j < N; j++) {
			if (*pArr[i] > *pArr[j]) {
				int *temp = pArr[i];
				pArr[i] = pArr[j];
				pArr[j] = temp;
			}
		}
	}
}