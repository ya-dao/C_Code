#include "LinkStack.h"
/*
	分析:由于是链栈,直接将头结点作为栈顶,略去头结点
*/

/*
	Note:这里的stack结点只作为一个栈顶指针的存在,不需要分配结点空间,避免浪费一个栈底结点
		存在价值不大
*/
STATUS init(LinkStack *stack) {
	(*stack) = NULL;
	return SUCCESS;
}

/*
	Note:
		1.第一次push时,这里的stack只作为一个指针而非一个结点,所以直接将其赋值将新结点的next
		循环往复进行
		2.由于是链栈,无需判断栈满
*/
STATUS push(LinkStack *stack, ElemType element) {
	LinkStack newNode = (LinkStack)malloc(sizeof(StackNode));
	newNode->element = element;
	newNode->next = (*stack);
	(*stack) = newNode;
	return SUCCESS;
}

/*
	尽管链栈不需要判断满与否,但是需要判空
*/
ElemType pop(LinkStack *stack) {
	if ((*stack) == NULL)
	{
		printf("The stack is empty!");
		return ERROR;
	}
	else {
		LinkStack topNode = (*stack);
		ElemType result = topNode->element;
		(*stack) = (*stack)->next;
		free(topNode);
		return result;
	}
}
/*
	Note:判空
*/
ElemType getTop(LinkStack stack) {
	if (stack == NULL)
	{
		printf("The stack is empty!");
		return ERROR;
	}
	else {
		return stack->element;
	}
}
/*
	由于该结构体所表示的链栈无头结点,不好保存长度这一属性.
	以及求链表的长度也就O(n)的复杂度,就直接遍历获取了.
*/
int getLength(LinkStack stack) {
	int length = 0;
	while (stack != NULL) {
		length++;
		stack = stack->next;
	}
	return length;
}

/*
	功能:将栈内结点逐个释放,当栈顶指针为空时无需释放
*/
STATUS destroy(LinkStack *stack) {
	if ((*stack) == NULL)
	{
		return SUCCESS;
	}
	else {
		LinkStack tempNode = NULL;
		while ((*stack) != NULL)
		{
			tempNode = (*stack);
			(*stack) = (*stack)->next;
			free(tempNode);
		}
	}
	return SUCCESS;
}