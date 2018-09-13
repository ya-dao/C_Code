#include "StackAndQueue.h"

//参数使用指针可以根据地址对其进行操作
STATUS initStack(Stack **stack){
	(*stack) = (Stack *)malloc(sizeof(Stack));
	(*stack)->maxSize = SIZE;
	(*stack)->top = 0;
	for (int i = 0; i < SIZE; i++)
	{
		(*stack)->base[i] = NULL;
	}
	return SUCCESS;
}
STATUS destroyStack(Stack **stack){
	int i = 0;
	if((*stack) == NULL){
		return ERROR;
	}
	
	//空间的释放只能从申请的地址开始释放,不能从其他地址释放
	free((*stack));
	return SUCCESS;
}
STATUS clearStack(Stack **stack){
	if((*stack) == NULL){
		return ERROR;
	}
	(*stack)->top = 0;
	return SUCCESS;
}

//结构作为参数开销过大，使用指针来进行参数传递，规避这种情况的发生
BOOL isStackEmpty(Stack *stack){
	if(stack == NULL){
		return ERROR;
	}
	if(stack->top == 0){
		return TRUE;
	}else{
		return FALSE;
	}
}

BOOL isStackFull(Stack *stack) {
	if (stack == NULL) {
		return ERROR;
	}

	if (stack->top == SIZE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int getStackLength(Stack *stack){
	return stack->top;
}

ElemType getTop(Stack *stack){
	//下标从0开始,相差1
	return *(stack->base + stack->top - 1);
}
STATUS push(Stack *stack,ElemType element){
	if(stack == NULL || element == NULL){
		return ERROR;
	}
	if (isStackFull(stack) == TRUE)
	{
		return FALSE;
	}
	stack->base[stack->top] = element;
	stack->top++;
	return SUCCESS;
}
ElemType pop(Stack *stack){
	if(stack == NULL){
		return NULL;
	}
	if (isStackEmpty(stack) == TRUE)
	{
		return NULL;
	}
	//弹栈后top要自减1,如果拆开写要保存临时变量,麻烦
	return stack->base[(stack->top--) - 1];
}

//遍历该栈,显示栈内当前元素
STATUS traverseStack(Stack *stack){
	if(stack == NULL){
		return ERROR;
	}
	printf("当前栈内元素:\n");
	for (int i = 0; i < stack->top; i++) {
		printf("%d, ",(*(stack->base + i))->data);
	}
	printf("\n");
	return SUCCESS;
}

