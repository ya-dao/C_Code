#include<stdio.h>
#include<stdlib.h>

#define ElemType int
#define STATUS int

#define ERROR -1
#define SUCCESS 1

#define TRUE 1
#define FALSE 0
/*
	假设以带头结点的循环链表表示队列,并且只设一个指针指向队尾元素结点
	试编写相应的置空队列,判断队列是否为空,入队和出队算法
*/

typedef struct {
	ElemType data;
	struct LNode *next;
}QNode,*QueuePtr;
typedef struct {
	QueuePtr front;
	QueuePtr rear;
}Queue,*LinkQueue;

STATUS init(LinkQueue *queue);
STATUS enQueue(LinkQueue *queue,ElemType element);
ElemType deQueue(LinkQueue *queue);
ElemType getHead(LinkQueue queue);


