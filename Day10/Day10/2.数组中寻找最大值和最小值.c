#include<stdio.h>
#include<stdlib.h>

void main() {

	int a[10] = {5,2,3,6,7,1,9,4,8,10};
	int maxIndex = 0;
	int minIndex = 0;
	for (int i = 0; i < 10; i++) {
		if (a[maxIndex] <= a[i]) {
			maxIndex = i;
		}

		if (a[minIndex] >= a[i]) {
			minIndex = i;
		}
	}
	printf("最大值=%d\n最小值=%d\n",a[maxIndex],a[minIndex]);
	getchar();
}