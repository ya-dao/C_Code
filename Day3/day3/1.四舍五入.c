#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
/*
	1.实现输入一个实数，实现1.234 ，第二位四舍五入，第三位五舍6入
*/
int main() {
	float number = 0.0f;
	scanf("%f", &number);
	printf("输入的数为%.3f\n",number);
	int integer = 0;

	//第三位5舍6入
	float third = number;
	third *= 100;				//123.4
	third += 0.4f;				//123.8
	integer = (int)third;		//123
	third = integer / 100.0f;	//1.23
	printf("第三位5舍6入为%.3f\n", third);

	//第二位四舍五入	1.234
	//求出第三位小数
	float thirdDecimal = number * 100 - (int)(number * 100); //123.4 - 123

	float second = number;
	second *= 10;	//12.34
	second += 0.5f;	//12.84
	integer = (int)second;
	second = (integer + thirdDecimal / 10.0f) / 10;
	printf("第二位4舍5入为%.3f\n", second);

	getchar();
	getchar();
	return 0;
}