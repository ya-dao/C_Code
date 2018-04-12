#include<stdio.h>
#include<stdlib.h>
#define N 8

/*
	设子数组a[0:k-1]和a[k:n-1]已排好序(0<=k<=n-1).
		试设计一个合并之两个子数组为排好序的数组a[0:n-1]的算法.
		要求算法在最坏情况下所用的计算时间为O(n),且只用到O(1)辅助空间.
		(0:k-1): 2 4 6 8
		(k:n-1): 1 3 5 7
		(0:n-1): 1 2 3 4 5 6 7 8
*/
void merge(int *arr,int k,int *result);
void main(){
	int arr[N] = {1,3,5,7,2,4,6,8};
	int k = 4;
	int result[N] = {0};
	int i = 0;

	merge(arr,k,result);

	for (i = 0; i < N; i++)
	{
		printf("%d ",result[i]);
	}
	system("pause");
}

void merge(int *arr,int k,int *result){
	int i = 0;
	int j = k;
	int resultIndex = 0;
	while(i < k && j < N)
	{
		if(*(arr + i) > *(arr + j)){
			*(result + resultIndex) = *(arr + j);
			j++;
		}else{
			*(result + resultIndex) = *(arr + i);
			i++;
		}
		resultIndex++;
	}
	while (i < k)
	{
		*(result + (resultIndex++)) = *(arr + (i++));
	}
	while (j < N)
	{
		*(result + (resultIndex++)) = *(arr + (j++));
	}
}