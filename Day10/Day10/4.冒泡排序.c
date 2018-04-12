#include<stdio.h>
#include<stdlib.h>
/*
	沉底一个最大或最小值即可找出极值
*/
void getExtremeValue(int a[10]) {
	for (int i = 0; i < 9; i++)
	{
		if (a[i] >= a[i + 1]) {
			int temp = a[j];
			a[j] = a[j + 1];
			a[j + 1] = temp;
		}
	}
}
/*
	多次将最大值或者最小值沉底即可完成排序
*/
void sort(int a[10]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9 - i; j++)
		{
			if (a[j] >= a[j + 1])
			{
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		printf("%d ", a[i]);
	}
}

void main() {
	int a[10] = { 5,2,3,6,7,10,9,4,8,1 };
	//sort(a);
	


	getchar();
}