#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
/*
	汉诺塔可以这样推导:
		A,B,C三个柱子,需要将N个盘子从A柱移动到C柱.
		要移动N个盘子,首先要移动上面的N-1个盘子到中间柱,才能移动最后一个盘子到目标柱.
		1.借助目标柱C柱移动N-1个盘子到中间柱B柱
		2.将第N个盘子移动目标C柱
		3.再将N-1个盘子从B柱借助A柱移动到C柱
*/
void move(char from,char to) {
	printf("%c---->%c\n",from,to);
}

void hannoi(int count,char from,char middle,char to) {
	if (count == 1) {
		move(from, to);
	}
	else {
		hannoi(count - 1, from, to, middle);
		move(from, to);
		hannoi(count - 1, middle, from, to);
	}
}
void main() {
	int count = 0;
	char from = 'A';
	char middle = 'B';
	char to = 'C';

	scanf("%d",&count);

	hannoi(count, from, middle, to);
	system("pause");
}

