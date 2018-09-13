#include<stdio.h>
#include<stdlib.h>

#define ElemType BTNode*
#define STATUS int
#define BOOL int
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define SUCCESS -2
#define SIZE 10

typedef struct Tree {
	int data;
	struct Tree *leftChild;
	struct Tree *rightChild;
}BTNode, *BinaryTree;

/*
	这里针对结点类型作出统一修改,不存入具体对象,只保存地址即可(用指针数组)
*/
typedef struct {
	int maxSize;
	int top;
	ElemType base[SIZE];
}Stack;

//参数使用指针可以根据地址对其进行操作
STATUS initStack(Stack **stack);
STATUS destroyStack(Stack **stack);
STATUS clearStack(Stack **stack);

//结构作为参数开销过大，使用指针来进行参数传递，规避这种情况的发生
BOOL isStackEmpty(Stack *stack);
BOOL isStackFull(Stack *stack);
int getStackLength(Stack *stack);

ElemType getTop(Stack *stack);
STATUS push(Stack *stack,ElemType element);
ElemType pop(Stack *stack);

STATUS traverseStack(Stack *stack);


//循环顺序队列
typedef struct TagCSQueue{
	ElemType base[SIZE];
	//记录当前队头和队尾位置
	int rear;
	int front;
}*CSQueue;

STATUS initQueue(CSQueue *queue);
BOOL isQueueEmpty(CSQueue queue);
BOOL isQueueFull(CSQueue queue);
int getQueueLength(CSQueue queue);
ElemType getHead(CSQueue queue);
STATUS enQueue(CSQueue queue, ElemType element);
ElemType deQueue(CSQueue queue);
STATUS clearQueue(CSQueue queue);
STATUS destroyQueue(CSQueue queue);