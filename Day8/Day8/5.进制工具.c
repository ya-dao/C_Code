#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
/*
	通过模拟计算一个数的二进制,八进制,十六进制
*/
/*
	10 % 2 = 0	10 / 2 = 5
	
	5  % 2 = 1	5  / 2 = 2
	
	2  % 2 = 0	2 / 2 = 1
	1  % 2 = 1	1 / 2 = 0 
*/
void binary(int number, char *arr) {
	int i = 31;
	arr[32] = '\0';
	for (; i >= 0; i--) {
		if (number > 0) {
			arr[i] = number % 2 + '0';
		}
		else {
			arr[i] = '0';
		}
		number /= 2;
	}
}
void octal(int number, char* arr) {
	int i = 10;
	arr[11] = '\0';
	for (; i >= 0; i--) {
		if (number > 0) {
			arr[i] = number % 8 + '0';
		}
		else {
			arr[i] = '0';
		}
		number /= 8;
	}
}
void hex(int number, char *arr) {
	int i = 7;
	arr[8] = '\0';
	for (; i >= 0; i--) {
		if (number % 16 >= 10) {
			arr[i] = number % 16 - 10 + 'A';
		}
		else {
			arr[i] = number % 16 + '0';
		}

		number /= 16;
	}
}

void recursiveBinary(int number, char *arr, int index) {
	if (number == 0) {
		return;
	}
	else {
		recursiveBinary(number /= 2, arr, index - 1);
		arr[index] = number % 2 + '0';
	}
}

void recursiveOctal(int number, char *arr, int index) {
	if (number == 0) {
		return;
	}
	else {
		recursiveBinary(number /= 8, arr, index - 1);
		arr[index] = number % 8 + '0';
	}
}

void recursiveHex(int number, char *arr, int index) {
	if (number == 0) {
		return;
	}
	else {
		recursiveBinary(number /= 16, arr, index - 1);
		if (number % 16 >= 10) {
			arr[index] = number % 16 - 10 + 'A';
		}
		arr[index] = number % 16 + '0';
	}
}
void main() {
	int number = 0;
	char binaryArr[33] = { 0 };
	char octalArr[12] = { 0 };
	char hexArr[9] = { 0 };

	scanf("%d",&number);

	binary(number, binaryArr);
	printf("%s\n",binaryArr);
	
	octal(number, octalArr);
	printf("%s\n", octalArr);
	
	hex(number, hexArr);
	printf("%s\n", hexArr);
	system("pause");
}