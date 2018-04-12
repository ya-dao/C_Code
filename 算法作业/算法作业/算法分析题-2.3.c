#include<stdio.h>
#include<stdlib.h>

#define N 10

/*1。设a[0:n-1]是已排好序的数组。请改写二分搜索算法，
	使得当搜索元素不在数组中时，返回小于x的最大元素位置i和大于x的最小位置j.
	当搜索元素在数组中时,i和j相同,均为x在数组中的位置
*/

void enhanceBinarySearch(int *arr,int target,int *i,int *j);

void main(){
	int arr[N] = {1,2,3,4,5,6,7,8,9,12};
	int target = 2;
	int i = 0;
	int j = N - 1;
	enhanceBinarySearch(arr,target,&i,&j);
	printf("i = %d,j = %d\n",i + 1,j + 1);
	system("pause");
}

void enhanceBinarySearch(int *arr,int target,int *i,int *j){
	int first = 0;
	int last = N - 1;
	int middle = (first + last) / 2;
	while(middle > first && middle < last){
		if(*(arr + middle) == target){
			*j = middle;
			*i = middle;
			return;
		}else if(*(arr + middle) > target){
			last = middle - 1;
			
		}else if(*(arr + middle) < target){
			first = middle + 1;
			
		}
		*j = last;
		*i = first;
		middle = (first + last) / 2;
	}
}