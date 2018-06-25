#include<stdio.h>
#include<stdlib.h>

#define ElemType int
#define SIZE 10
#define STATUS int
#define SUCCESS 2
#define ERROR -1
#define TRUE 1
#define FALSE 0

typedef struct {
	int maxSize;
	ElemType *top;
	ElemType *base;
}Stack;

//参数使用指针可以根据地址对其进行操作
STATUS initStack(Stack **stack);
STATUS destroyStack(Stack **stack);
STATUS clearStack(Stack **stack);

//结构作为参数开销过大，使用指针来进行参数传递，规避这种情况的发生
int isStackEmpty(Stack *stack);
int getLength(Stack *stack);

ElemType getTop(Stack *stack);
STATUS push(Stack *stack,ElemType element);
ElemType pop(Stack *stack);

STATUS stackTraverse(Stack *stack);