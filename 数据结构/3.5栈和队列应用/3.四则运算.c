#include "LinkStack.h"
#define N 100
#define BOOL int
/*
	利用后缀表达式计算值
	1.将中缀表达式转化成后缀表达式
	2.利用后缀表达式计算
*/
/*
	比较表达式中的运算符和栈顶运算符的优先级, 不考虑左括号的情况,因为左括号只能被右括号消掉
*/
BOOL isPrior(char currentOperator, char stackOpeator) {
	if (currentOperator == '*' || currentOperator == '/')
	{
		if (stackOpeator == '+' || stackOpeator == '-' || stackOpeator == '(')
		{
			return 1;
		}
	}
	else if (currentOperator == '+' || currentOperator == '-') 
	{
		if (stackOpeator == '(')
		{
			return 1;
		}
	}
	return 0;
}
/*
	规则:
		1.如果是操作数直接输出
		2.如果是左括号"("直接进运算符栈
		3.如果是右括号")",将运算符栈中运算符依次出栈,直到将左括号"("出栈
		4.如果是"+ - * /",先与运算符栈顶元素比较(所有运算符都大于左括号)
			4.1如果当前运算符优先级小于或者等于栈顶运算符,则依次将其出栈,并随后将该运算符进栈
			4.2如果当前运算符优先级大于栈顶运算符,则直接进栈
*/
char* infixToPostfix(char *expression) {
	char *p = expression;
	char *postfix = calloc(N, sizeof(char));
	int postfixIndex = 0;
	
	LinkStack operatorStack = NULL;//运算符栈
	init(&operatorStack);

	while (*p != '\0')
	{
		if (*p >= '0' && *p <= '9')
		{
			postfix[postfixIndex++] = *p;
		}
		else if (*p == '(') 
		{
			push(&operatorStack, *p);
		}
		else if (*p == ')')
		{
			while (getTop(operatorStack) != '(')
			{
				char operator = pop(&operatorStack);
				postfix[postfixIndex++] = ' ';
				postfix[postfixIndex++] = operator;
			}
			pop(&operatorStack);//处理栈中的左括号
		}
		else if (*p == '+' || *p == '-' || *p == '*' || *p == '/') 
		{
			while (operatorStack != NULL && isPrior(*p,getTop(operatorStack)) == 0)
			{
				postfix[postfixIndex++] = ' ';
				postfix[postfixIndex++] = pop(&operatorStack);
			}
			push(&operatorStack, *p);
		}

		//输出符号时加一个空格间隔开操作数,方便后面拼凑多位数的情况
		if (*p < '0' || *p > '9')
		{
			if (*p != '(' && *p != ')') {
				postfix[postfixIndex++] = ' ';
			}
		}
		p++;
	}
	while (operatorStack != NULL)
	{
		postfix[postfixIndex++] = ' ';
		postfix[postfixIndex++] = pop(&operatorStack);
	}
	free(operatorStack);
	postfix[postfixIndex] = '\0';
	return postfix;
}
int calculate(LinkStack *stack,char operator) {
	int operandA = 0, operandB = 0,result = 0;
	switch (operator)
	{
	case '+':
		operandB = pop(stack);
		operandA = pop(stack);
		result = operandA + operandB;
		break;
	case '-':
		operandB = pop(stack);
		operandA = pop(stack);
		result = operandA - operandB;
		break;
	case '*':
		operandB = pop(stack);
		operandA = pop(stack);
		result = operandA * operandB;
		break;
	case '/':
		operandB = pop(stack);
		operandA = pop(stack);
		result = operandA / operandB;
		break;
	}
	return result;
}
/*
	规则:
		从左往右读取字符串,如果是数字直接入栈,如果是运算符直接取出栈顶两个操作数进行运算,并将其结果入栈
*/
int parseExpression(char *postfixExpression) {
	char *p = postfixExpression;
	int result = 0;
	LinkStack operandStack = NULL;
	init(&operandStack);
	int operand = 0;

	while (*p != '\0')
	{
		if (*p >= '0' && *p <= '9')
		{
			//还原操作数
			operand = operand * 10 + *p - '0';
		}
		else if (*p == ' ') {
			//如果之前是在还原操作数,则现在将其入栈并清零
			if (operand > 0)
			{
				push(&operandStack, operand);
				operand = 0;
			}
		}
		else if (*p == '+' || *p == '-' || *p == '*' || *p == '/') {
			push(&operandStack, calculate(&operandStack, *p));
		}
		p++;
	}
	result = pop(&operandStack);
	free(operandStack);
	return result;
}
void main() {
	char *expression = "9+(2*3-1)*3+10/2";
	char *postfix = infixToPostfix(expression);
	printf("%s\n",postfix);

	int result = parseExpression(postfix);
	printf("%d\n",result);

	free(postfix);
	system("pause");
}