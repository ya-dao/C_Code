#include<stdio.h>
#include<stdlib.h>
#define ElemType int
#define STATUS int
#define ERROR -1
#define SUCCESS -2

typedef struct StackNode {
	ElemType element;
	struct StackNode *next;
}StackNode, *LinkStack;

STATUS init(LinkStack *stack);
STATUS push(LinkStack *stack, ElemType element);
ElemType pop(LinkStack *stack);
ElemType getTop(LinkStack stack);
int getLength(LinkStack stack);
STATUS destroy(LinkStack *stack);