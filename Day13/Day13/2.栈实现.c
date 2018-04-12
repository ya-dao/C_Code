#include<stdio.h>
#include<stdlib.h>
#define N 10
#define TRUE 1
#define FALSE 0

struct Stack{
	int currentIndex;
	int array[N];
};
typedef struct Stack Stack;

void push(Stack *stack,int element);
int pop(Stack *stack);
int isEmpty(Stack *stack);
int isFull(Stack *stack);

void main() {
	Stack myStack = {-1,0};
	for (int i = 0; i < N; i++)
	{
		push(&myStack, i);
	}
	push(&myStack, 11);
	//这句不能放到printf函数里面执行,因为printf函数参数执行的顺序可能是从左往右,可能是从右往左
	for (int i = N - 1; !isEmpty(&myStack); i--)
	{
		int popElement = pop(&myStack);
		printf("pop = %d,currentIndex = %d,next pop element = %d\n",
			popElement, myStack.currentIndex, myStack.array[myStack.currentIndex]);
	}
	system("pause");
}

void push(Stack *stack, int element) {
	if (isFull(stack))
	{
		printf("operation failed,current stack is full!\n");
		return;
	}
	else {
		stack->currentIndex++;
		stack->array[stack->currentIndex] = element;
	}
}
int pop(Stack *stack) {
	if (isEmpty(stack))
	{
		printf("operation failed,current stack is empty!\n");
		return 0;
	}
	else
	{
		int popElement = stack->array[stack->currentIndex];
		stack->currentIndex--;
		return popElement;
	}
}
int isEmpty(Stack *stack) {
	if (stack->currentIndex <= -1) {
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
int isFull(Stack *stack) {
	if (stack->currentIndex < (N - 1)) {
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}