//3.Çó1!+ 2!+ 3!+ ... + 20!
#include<stdio.h>
#include<stdlib.h>

int main() {
	double sum = 0;
	for (int i = 1; i <= 20;i++) {
		double result = i;
		for (int j = i - 1; j >= 1; j--) {
			result *= j;
		}
		sum += result;
	}
	printf("%.0lf\n",sum);
	getchar();
	return 0;
}