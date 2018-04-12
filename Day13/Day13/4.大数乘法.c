#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define N 20
/*
	计算123456789 * 123456789
	思路:分步乘
		 1 2 3
		*1 2 3
	------------
		 3 6 9
	   2 4 6
	 1 2 3
	-----------
	1 4 10 12 9
	再将最后的结果进行进位,得到最后结果
	1  5 1  2 9
*/
long long calculate(long long number_1, long long number_2);
int getTail(long long* products, int index);
int getLength(long long *products, int index);
long long getSum(int *sums, int length);
void show(int *sums);

void main() {
	//123456789
	char *arr_1 = "123456789";
	char *arr_2 = "123456789";
	long long number_1 = 0;
	long long number_2 = 0;
	sscanf(arr_1,"%lld",&number_1);
	sscanf(arr_2,"%lld",&number_2);

	long long sum = calculate(number_1, number_2);

	printf("the result of two big number multiply is %lld\n",sum);

	system("pause");
}

long long calculate(long long number_1, long long number_2) {
	long long products[N] = { 0 };
	int sums[N] = { 0 };
	int index = 0;
	while(number_2 > 0)
	{
		int tail = number_2 % 10;
		long long product = tail * number_1;
		//按照乘法的原则,被乘数与每一个乘数的积都要乘10
		for (int i = 0; i < index; i++)
		{
			product *= 10;
		}
		products[index] = product;
		number_2 /= 10;
		index++;
	}
	//将指针移回最后一个元素
	index--;

	//求出最长的最后一位是多少位
	int length = getLength(products, index);

	//取出每一个乘积进行加法运算
	for (int i = length - 1; i >= 0; i--)
	{
		int sum = 0;
		for (int j = index; j >= 0; j--)
		{
			int tail = getTail(products, j);
			sum += tail;
		}
		sums[i] = sum;
	}
	
	return getSum(sums,length - 1);
}

int getTail(long long* products,int index) {
	if (*(products + index) > 0) {
		int tail = *(products + index) % 10;
		*(products + index) /= 10;
		return tail;
	}
	else
	{
		return 0;
	}
}

long long getSum(int *sums,int length) {
	long long sum = 0;
	int carry = 0;
	long long number = 0;
	//i:第几位 j:乘以几个10
	for (int i = length,j = 0; i >= 0; i--,j++)
	{
		//	1 4 10 12 9
		if ((*(sums + i) + carry) < 10) {
			number = *(sums + i) + carry;
			carry = 0;
		}
		else
		{
			number = (*(sums + i) + carry) % 10;
			carry = (*(sums + i) + carry) / 10;
		}
		for (int  k = 0; k < j; k++)
		{
			number *= 10;
		}
		sum += number;
	}
	return sum;
}

int getLength(long long *products,int index) {
	long long number = *(products + index);
	int length = 0;
	while (number > 0)
	{
		number /= 10;
		length++;
	}
	return length;
}

void show(int *sums) {
	for (int i = 0; *(sums + i) != 0; i++)
	{
		printf("%d ",*(sums + i));
	}
	printf("\n");
}
