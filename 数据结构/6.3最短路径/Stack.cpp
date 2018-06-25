#include "Stack.h"
//参数使用指针可以根据地址对其进行操作
STATUS initStack(Stack **stack){
	(*stack) = (Stack *)malloc(sizeof(Stack));
	(*stack)->maxSize = SIZE;
	(*stack)->base = (ElemType *)malloc(sizeof(ElemType) * (*stack)->maxSize);
	(*stack)->top = (*stack)->base;

	return SUCCESS;
}
STATUS destroyStack(Stack **stack){
	int i = 0;
	if((*stack) == NULL){
		return ERROR;
	}
	
	//空间的释放只能从申请的地址开始释放,不能从其他地址释放
	free((*stack)->base);
	free((*stack));
	return SUCCESS;
}
STATUS clearStack(Stack **stack){
	if((*stack) == NULL){
		return ERROR;
	}
	(*stack)->top = (*stack)->base;
	return SUCCESS;
}

//结构作为参数开销过大，使用指针来进行参数传递，规避这种情况的发生
int isStackEmpty(Stack *stack){
	if(stack == NULL){
		return ERROR;
	}
	if(stack->top == stack->base){
		return TRUE;
	}else{
		return FALSE;
	}
}
int getLength(Stack *stack){
	return stack->top - stack->base;
}

ElemType getTop(Stack *stack){
	return *(stack->top - 1);
}
STATUS push(Stack *stack,ElemType element){
	if(stack == NULL){
		return ERROR;
	}
	*(stack->top++) = element;
	return SUCCESS;
}
ElemType pop(Stack *stack){
	if(stack == NULL){
		return ERROR;
	}
	return *((stack->top--) - 1);
}

//遍历该栈,显示栈内当前元素
STATUS stackTraverse(Stack *stack){
	int i = 0;
	if(stack == NULL){
		return ERROR;
	}
	printf("当前栈内元素:\n");
	for(;(stack->base + i) != stack->top;i++){
		printf("%d, ",*(stack->base + i));
	}
	printf("\n");
	return SUCCESS;
}