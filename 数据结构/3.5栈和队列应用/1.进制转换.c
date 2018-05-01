#include "LinkStack.h"
/*
	分析:利用栈保存每次运算的余数,结束之后依次出栈即可得到正确结果
		用栈的话可以避免考虑存入和取出时数组的下标之间处理
*/
void decimalToOctal(LinkStack *stack,int number) {
	while (number != 0) {
		int remainder = 0;
		remainder = number % 8;
		push(stack, remainder);
		number = number / 8;
	}
}
void main() {
	LinkStack stack = NULL;
	init(&stack);

	int number = 127;
	decimalToOctal(&stack, number);
	while (stack != NULL) {
		printf("%d",pop(&stack));
	}
	printf("\n");
	system("pause");
}