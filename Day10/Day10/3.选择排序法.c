#include<stdio.h>
#include<stdlib.h>

void main() {

	int a[10] = { 5,2,3,6,7,1,9,4,8,10 };
	//最后一个数不需要再进行排序
	for (int i = 0; i < 10 - 1; i++)
	{
		int index = 9 - i;
		for (int j = 0; j < 10 - i; j++)
		{
			if (a[index] <= a[j]) {
				index = j;
			}
		}
		
		//如果下标不等于初始值,则说明有更大的值出现,需要进行交换
		if (index != (9 - i)) {
			int temp = a[9 - i];
			a[9 - i] = a[index];
			a[index] = temp;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		printf("%d ",a[i]);
	}

	getchar();
}