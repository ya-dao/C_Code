#include "LinkStack.h"
/*
	利用栈来检查括号是否匹配的问题,根据检测完之后stack是否为空来判断该字符串是否正确
*/
void verify(char *signal,LinkStack *stack) {
	char *p = signal;
	while (*p != '\0')
	{
		switch (*p)
		{
		case ')':
			if ((*stack) == NULL || getTop(*stack) != '(')
			{
				push(stack, *p);
			}
			else {
				pop(stack);
			}
			break;
		case ']':
			if ((*stack) == NULL || getTop(*stack) != '[')
			{
				push(stack, *p);
			}
			else {
				pop(stack);
			}
			break;
		default:
			push(stack, *p);
			break;
		}
		
		p++;
	}
}
/*
	增加一个标志变量,检测到错误直接结束返回,无需等待全部检测完
*/
int verifyImprove(char *signal, LinkStack *stack) {
	int errorFlag = 0;
	char *p = signal;
	while (*p != '\0' && errorFlag != 1) {
		switch (*p)
		{
		case '(':
		case '[':
			//如果检测到这两个直接入栈
			push(stack, *p);
			break;
		case ')':
			if ((*stack) != NULL && getTop(*stack) == '(')
			{
				pop(stack);
			}
			else {
				push(stack, *p);
				errorFlag = 1;
			}
			break;
		case ']':
			if ((*stack) != NULL && getTop(*stack) == '[')
			{
				pop(stack);
			}
			else {
				push(stack, *p);
				errorFlag = 1;
			}
			break;
		}
		p++;
	}
	return errorFlag;
}
void main() {
	char *signal = "([]))(";
	LinkStack stack = NULL;
	init(&stack);

	/*verify(signal, &stack);
	if (stack != NULL)
	{
		printf("\"%s\"格式错误\n",signal);
	}
	else {
		printf("\"%s\"格式正确\n", signal);
	}*/

	int flag = verifyImprove(signal, &stack);
	if (flag)
	{
		printf("\"%s\"格式错误\n", signal);
	}
	else {
		printf("\"%s\"格式正确\n", signal);
	}
	system("pause");
}