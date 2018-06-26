#include "Stack.h"
//参数使用指针可以根据地址对其进行操作
STATUS initStack(Stack **stack){
	(*stack) = (Stack *)malloc(sizeof(Stack));
	(*stack)->maxSize = SIZE;
	(*stack)->top = 0;
	(*stack)->base = (ElemType *)malloc(sizeof(ElemType) * (*stack)->maxSize);
	memset((*stack)->base,0, (*stack)->maxSize);

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
	(*stack)->top = 0;
	return SUCCESS;
}

//结构作为参数开销过大，使用指针来进行参数传递，规避这种情况的发生
int isStackEmpty(Stack *stack){
	if(stack == NULL){
		return ERROR;
	}
	if(stack->top == 0){
		return TRUE;
	}else{
		return FALSE;
	}
}
int getLength(Stack *stack){
	return stack->top - 0;
}

ElemType getTop(Stack *stack){
	return *(stack->base + stack->top - 1);
}
STATUS push(Stack *stack,ElemType element){
	if (stack == NULL) {
		return ERROR;
	}
	if (stack->top > SIZE) {
		printf("越界了\n");
		return ERROR;
	}
	*(stack->base + stack->top) = element;
	(stack->top)++;
	return SUCCESS;
}
ElemType pop(Stack *stack){
	if(stack == NULL){
		return ERROR;
	}
	if (stack->top <= 0)
	{
		return ERROR;
	}
	(stack->top)--;
	int pop =  *(stack->base + stack->top);
	*(stack->base + stack->top) = '\0';
	return pop;
}

//取出栈底元素,如果是一个函数里面,则函数标志必然在栈底,不管上面有多少'{'或'/*'
ElemType getBottom(Stack *stack) {
	if (stack == NULL) {
		return ERROR;
	}
	if (stack->top <= 0)
	{
		return ERROR;
	}
	return stack->base [0];
}

//遍历该栈,显示栈内当前元素
STATUS stackTraverse(Stack *stack){
	int i = 0;
	if(stack == NULL){
		return ERROR;
	}
	printf("当前栈内元素:\n");
	for(int i = 0;i != stack->top;i++){
		printf("%d, ",*(stack->base + i));
	}
	printf("\n");
	return SUCCESS;
}