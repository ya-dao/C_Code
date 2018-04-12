/*
	设a[0:n-1]是有n个元素的数组,k(0<=k<=n-1)是一个非负整数,
	试设计一个算法将子数组a[0:k-1]与a[k:n-1]换位
	要求算法在最坏情况下耗时O(n),且只用到O(1)的辅助空间.
*/
#include<stdio.h>
#include<stdlib.h>
#define N 10

void swap(int *arr,int k);

void main(){
	int arr[N] = {1,3,6,7,9,0,4,2,5,8};
	int k = 3;
	int i = 0;
	
	swap(arr,k);

	printf("k=%d时:\n",k);
	for(i = 0;i < N;i++){
		printf("%d ",arr[i]);
	}
	putchar(10);
	system("pause");
}

void swap(int *arr,int k){
	int i = 0;
	if(k <= 0 || k >= N){
		return;
	}
	for(i = 0; i < k;i++){
		int temp = *(arr + i);
		*(arr + i) = *(arr + (k + i));
		*(arr + (k + i)) = temp;
	}
}