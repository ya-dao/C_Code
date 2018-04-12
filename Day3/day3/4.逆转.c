#include<stdio.h>
/*
	4.19876 Íê³ÉÄæ×ª67891
*/
int main() {
	int number = 19876;
	int result = 0;

	int g = number % 10;
	number /= 10;
	int s = number % 10;
	number /= 10;
	int b = number % 10;
	number /= 10;
	int q = number % 10;
	int w = number /= 10;

	result = g * 10000 + s * 1000 + b * 100 + q * 10 + w;

	printf("%d\n",result);
	getchar();
	return 0;
}