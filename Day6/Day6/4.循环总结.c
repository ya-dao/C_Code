#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	
#include<stdlib.h>
/*
	·´×ªÊý×Ö
		124567=>7654321
*/
void whileMethod (int number) {
	int result = 0;
	while (number)
	{
		result = result * 10 + number % 10;
		number /= 10;
	}
	printf("%d\n",result);
}
void doWhileMethod(int number) {
	int result = 0;
	
	do {
		result = result * 10 + number % 10;
		number /= 10;
	} while (number);

	printf("%d\n", result);
}
void forMethod(int number) {
	int result = 0;
	for (; number;number /= 10) {
		result = result * 10 + number % 10;
	}
	printf("%d\n", result);
}
void gotoMethod(int number) {
	int result = 0;
A:	if (number) {
		result = result * 10 + number % 10;
		number /= 10;
		goto A;
	}
	printf("%d\n", result);
}

void main() {
	int number = 0;
	scanf("%d",&number);
	//whileMethod(number);
	//doWhileMethod(number);
	//forMethod(number);
	gotoMethod(number);
	system("pause");
}