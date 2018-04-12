#include<stdio.h>
#include<stdlib.h>
#define N 10
void show(int *array) {
	for (int i = 0; i < N; i++)
	{
		printf("%d ",*(array + i));
	}
	printf("\n");
}
void swap(int *pA,int *pB) {
	int temp = *pA;
	*pA = *pB;
	*pB = temp;
}
void quickSort1(int *s,int l,int r) {
	if (l < r)
	{
		int i = l, j = r, x = s[l];
		while (i<j)
		{
			while (i<j && s[j] >= x)//从右到左找到第一个小于x的数  
				j--;
			if (i<j)
				s[i++] = s[j];

			while (i<j && s[i] <= x)//从左往右找到第一个大于x的数  
				i++;
			if (i<j)
				s[j--] = s[i];

		}

		s[i] = x;//i = j的时候，将x填入中间位置  
		quickSort1(s, l, i - 1);//递归调用 
		quickSort1(s, i + 1, r);
	}
}
void quickSort(int *array,int left,int right) {
	int iLeft = left;
	int jRight = right;

	if (iLeft > jRight) {
		return;
	}

	while (iLeft < jRight)
	{
		while ((*(array + jRight) >= *(array + left)) && jRight > iLeft)
		{
			jRight--;
		}
		while ((*(array + iLeft) <= *(array + left)) && iLeft < jRight)
		{
			iLeft++;
		}
		if (iLeft < jRight)
		{
			swap(array + iLeft, array + jRight);
		}
	}
	swap(array + left, array + jRight);

	quickSort(array, left, iLeft - 1);
	quickSort(array, iLeft + 1, right);
}
void main() {
	int array[N] = { 2,5,1,6,7,3,4,8,0,9 };

	quickSort(array, 0, N - 1);
	show(array);
	system("pause");
}
