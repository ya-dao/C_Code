/*
	需求 ：给定N个元素，找出第m个小的元素，所用时间最坏为O(n)
*/
#include<stdio.h>
#include<stdlib.h>
#define N 22
#define DIVISION 5

int findMiddle(int *arr,int division,int start ,int end);
void sort(int *arr,int start,int end);
void swap(int *arr,int index1,int index2);
int partition(int *arr,int start,int end);
void show(int *arr);
int select(int *arr, int division, int start, int end, int total,int* middleCount,int targetOrder);

void main(){
	int targetOrder = 2;
	int arr[] = {2,3,7,5,1,8,4,9,10,34,12,57,56,45,13,16,41,24,39,43,22,54};
	int middleCount = 0;
	int result = 0;
	findMiddle(arr,DIVISION,0,N - 1);
	result = select(arr, DIVISION, 0, 4,N,&middleCount,targetOrder);
	printf("第%d小的数=%d\n",targetOrder,result);
	system("pause");
}
//1.找出中位数序列
int findMiddle(int *arr,int division,int start ,int end){
	int i;
	for (i = 0; i < N; i += division)
	{
		//对每个N/division的序列进行排序
		if((i + division - 1) > N){
			sort(arr,i,N - 1);
		}else{
			sort(arr,i,i + division - 1);
		}
	}
	show(arr);
}

/*针对排完序的子序列找出中位数
	思路:递归将每一个N/5的序列中的中位数交换到对应的前五个元素,
	然后再从这里面找到中位数的中位数.
*/
int select(int *arr,int division,int start,int end,int total,int* middleCount,int targetOrder){
/*
	1  2  3  5  7
	4  8  9  10 34
	12 13 45 56 57
	16 24 39 41 43
	22 54
*/
	if ((end - start + 1) < division)
	{

		int middleIndex = 0;
		//在递归的结束条件里面选择所有中位数的中位数
		//先排个序
		sort(arr, 0, (*middleCount) - 1);
		//确定中位数的中位数的位置
		if ((*middleCount) % 2 != 0)
		{
			middleIndex = (*middleCount / 2);
		}
		else
		{
			if ((*middleCount / 2) > (*middleCount / 2 + 1))
			{
				middleIndex = (*middleCount / 2);
			}
			else
			{
				middleIndex = (*middleCount / 2 + 1);
			}
		}
		show(arr);
		//做一趟划分
		swap(arr, 0, middleIndex);
		//x:中位数的中位数
		int x = partition(arr, 0, N - 1);
		show(arr);
		if (targetOrder == x) {
			return *(arr + x);
		}
		else if(targetOrder >= x){
			*middleCount = 0;
			findMiddle(arr, division, x + 1, (N - x + 1));
			return select(arr, division, x + 1, (x + 1 + 4), (N - x + 1), middleCount, targetOrder);
		}
		else if (targetOrder <= x) {
			*middleCount = 0;
			findMiddle(arr, division, 0, x);
			return select(arr, division, 0, 4, x, middleCount, targetOrder);
		}
	}
	else
	{
		int changeIndex = start / division;
		int middleIndex = start + (end - start) / 2;
		//把第n个子序列的中位数交换到第一行
		swap(arr, changeIndex, middleIndex);
		//当前交换了几个中位数
		(*middleCount)++;
		if (start + division < total)
		{
			if (end + division < total)
			{
				return select(arr, division, start + division, end + division,total,middleCount,targetOrder);
			}
			else
			{
				return select(arr, division, start + division, total - 1,total,middleCount,targetOrder);
			}
		}
		else {
			return select(arr, division, end, end,total,middleCount,targetOrder);
		}
	}
}

//快速排序对每个子序列进行排序
void sort(int *arr,int start,int end){
	if (start < end)
	{
		int index = partition(arr,start,end);
		sort(arr,start,index - 1);
		sort(arr,index + 1,end);
	}
}

//划分
int partition(int *arr,int start,int end){
	int base = *(arr + start);
	int i = start,j = end;
	while(i < j){
		while(*(arr + j) > base){
			j--;
		}
		
		while(*(arr + i) < base){
			i++;
		}
		swap(arr,i,j);
	}
	*(arr + j) = base;
	return i;
}
//交换数组中的两个元素
void swap(int *arr,int index1,int index2){
	int temp = *(arr + index1);
	*(arr + index1) = *(arr + index2);
	*(arr + index2) = temp;
}

//显示排序后的每个子序列
void show(int *arr){
	int i;
	for (i = 0; i < N; i++)
	{
		printf("%-2d ",*(arr + i));
		if((i + 1) % 5 == 0){
			putchar(10);
		}
	}
	putchar(10);
}