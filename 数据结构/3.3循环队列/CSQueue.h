#include<stdio.h>
#include<stdlib.h>
#define ElemType int
#define STATUS int
#define BOOL int
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define SUCCESS -2
#define MAXSIZE 10

//循环顺序队列
typedef struct {
	ElemType *base;
	//记录当前队头和队尾位置
	int rear;
	int front;
}CSQueue;

STATUS init(CSQueue *queue);
BOOL isEmpty(CSQueue queue);
BOOL isFull(CSQueue queue);
int getLength(CSQueue queue);
ElemType getHead(CSQueue queue);
STATUS enQueue(CSQueue *queue,ElemType element);
ElemType deQueue(CSQueue *queue);
STATUS clear(CSQueue *queue);
STATUS destroy(CSQueue *queue);