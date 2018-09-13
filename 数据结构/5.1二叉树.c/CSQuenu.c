#include "StackAndQueue.h"

/*
	循环队列约定:空出一个结点作为区别队空和队满的条件,队头指针指向头元素,队尾指针指向尾元素的下一个位置
*/
STATUS initQueue(CSQueue *queue){
	//没用二级指针,导致强制转换看起较为复杂
	(*queue) = (CSQueue )malloc(sizeof(struct TagCSQueue));
	for (int i = 0; i < SIZE; i++)
	{
		(*queue)->base[i]= NULL;
	}
	(*queue)->front = 0;
	(*queue)->rear = 0;
	return SUCCESS;
}
BOOL isQueueEmpty(CSQueue queue){
	if (queue == NULL)
	{
		return ERROR;
	}
	if(queue->front == queue->rear){
		return TRUE;
	}else{
		return FALSE;
	}
}
BOOL isQueueFull(CSQueue queue){
	if (queue == NULL)
	{
		return ERROR;
	}
	if((queue->rear + 1) % SIZE == queue->front){
		return TRUE;
	}else{
		return FALSE;
	}
}
int getQueueLength(CSQueue queue){
	if (queue == NULL || queue->base == NULL)
	{
		return 0;
	}
	else{
		//%SIZE为了防止求出的当前长度超过最大长度
		return (queue->rear + SIZE - queue->front) % SIZE;
	}
}

ElemType getHead(CSQueue queue){
	if (queue == NULL)
	{
		return NULL;
	}
	else{
		return queue->base[queue->front];
	}
}
STATUS enQueue(CSQueue queue,ElemType element){
	if (queue == NULL)
	{
		return ERROR;
	}
	if(isQueueFull(queue) == TRUE){
		printf("当前队列已满!\n");
		return ERROR;
	}else{
		queue->base[queue->rear] = element;
		queue->rear = (queue->rear + 1) % SIZE;
		return SUCCESS;
	}
}
ElemType deQueue(CSQueue queue){
	if (queue == NULL)
	{
		return NULL;
	}
	if(isQueueEmpty(queue)){
		printf("当前队列为空!\n");
		return NULL;
	}else{
		ElemType result = queue->base[queue->front];
		queue->front = (queue->front + 1) % SIZE;
		return result;
	}
}

STATUS clearQueue(CSQueue queue){
	if(queue->front == queue->rear){
		return SUCCESS;
	}else{
		queue->front = 0;
		queue->rear = queue->front;
		return SUCCESS;
	}
}
STATUS destroyQueue(CSQueue queue){
	if(queue == NULL){
		return SUCCESS;
	}else{
		free(queue);
		queue = NULL;
		return SUCCESS;
	}

}

