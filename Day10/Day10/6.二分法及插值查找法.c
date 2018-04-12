#include<stdio.h>
#include<stdlib.h>
#define M 20
/*
	插值查找法:
		在增长比较均匀的序列下,插值查找比二分法查找要快.
	原理:
		在增长比较均匀的数列中,设需要查找的值为target,则有:
		target - start      target - a[start]
		——————————————  =  ————————————————————
		   end - start      a[end] - a[start]

		target = 
		start + (end - start) * (target - a[start]) / 
		(a[end] - a[start])
*/
void insertSearch(int a[20], int target) {
	int start = 0;
	int end = 20 - 1;
	int index = -1;
	int middle = 0;
	int count = 0;

	while (start <= middle) {
		middle = start + (end - start) * 1.0 *
			(target - a[start]) /
			(a[end] - a[start]);
		
		if (target == a[middle]) {
			index = middle;
			break;
		}
		else if (target > a[middle]) {
			start = middle + 1;
			
		}
		else if (target < a[middle]) {
			end = middle - 1;
		}
		count++;
	}

	if (index != -1) {
		printf("找到了,是第%d个数,共计%d次\n", index + 1, count);
	}
	else {
		printf("找不到\n");
	}
}
/*
	二分法的原理是通过比对目标值与中间值的大小关系,一次去掉一半的长度,提高查找效率
*/
void binarySearch(int a[20],int target) {
	int start = 0;
	int end = 20 - 1;
	int middle = (end - start) / 2;
	int index = -1;
	int count = 0;

	while (start <= end) {
		if (a[middle] == target) {
			index = middle;
			break;
		}
		else if (target > a[middle]) {
			start = middle + 1;
			middle = (end - start) / 2;
		}
		else if (target < a[middle]) {
			end = middle - 1;
			middle = (end - start) / 2;
		}

		count++;
	}
	
	if (index != -1) {
		printf("找到了,是第%d个数,共计%d次\n",index + 1,count);
	}
	else {
		printf("找不到\n");
	}
}
void main() {
	int a[20] = { 0 };
	for (int i = 0; i < 20; i++) {
		a[i] = i + 1;
	}

	//binarySearch(a,5);
	insertSearch(a,5);
	getchar();
}