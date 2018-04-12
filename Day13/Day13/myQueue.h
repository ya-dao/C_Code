#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#define N 10

struct MyQueue
{
	int queue[N];
	int head;
	int tail;
};

typedef struct MyQueue myQueue;

void init(myQueue *queue);
int isEmpty(myQueue *queue);
int isFull(myQueue *queue);
void enQueue(myQueue *queue,int object);
int deQueue(myQueue *queue);
int getTop(myQueue *queue);
void clear(myQueue *queue);
void show(myQueue *queue);