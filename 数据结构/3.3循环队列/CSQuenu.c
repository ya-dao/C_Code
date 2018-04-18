#include "CSQueue.h"

/*
	循环队列约定:空出一个结点作为区别队空和队满的条件,队头指针指向头元素,队尾指针指向尾元素的下一个位置
*/
STATUS init(CSQueue *queue){
	//没用二级指针,导致强制转换看起较为复杂
	(*queue) = *((CSQueue *)malloc(sizeof(CSQueue)));
	queue->base = (ElemType *)malloc(sizeof(ElemType) * MAXSIZE);
	queue->front = 0;
	queue->rear = 0;
	return SUCCESS;
}
BOOL isEmpty(CSQueue queue){
	if(queue.base == NULL || queue.front == queue.rear){
		return TRUE;
	}else{
		return FALSE;
	}
}
BOOL isFull(CSQueue queue){
	if(queue.base != NULL && 
		(queue.rear + 1) % MAXSIZE == queue.front){
		return TRUE;
	}else{
		return FALSE;
	}
}
int getLength(CSQueue queue){
	if(isEmpty(queue)){
		return 0;
	}else{
		//%MAXSIZE为了防止求出的当前长度超过最大长度
		return (queue.rear + MAXSIZE - queue.front) % MAXSIZE;
	}
}

ElemType getHead(CSQueue queue){
	if(isEmpty(queue)){
		return ERROR;
	}else{
		return *(queue.base + queue.front);
	}
}
STATUS enQueue(CSQueue *queue,ElemType element){
	if(isFull(*queue)){
		printf("当前队列已满!\n");
		return ERROR;
	}else{
		*(queue->base + queue->rear) = element;
		queue->rear = (queue->rear + 1) % MAXSIZE;
		return SUCCESS;
	}
}
ElemType deQueue(CSQueue *queue){
	if(isEmpty(*queue)){
		printf("当前队列为空!\n");
		return ERROR;
	}else{
		ElemType result = *(queue->base + queue->front);
		queue->front = (queue->front + 1) % MAXSIZE;
		return result;
	}
}

STATUS clear(CSQueue *queue){
	if(queue->base == NULL || queue->front == queue->rear){
		return SUCCESS;
	}else{
		queue->front = 0;
		queue->rear = queue->front;
		return SUCCESS;
	}
}
STATUS destroy(CSQueue *queue){
	if(queue->base == NULL || queue->front == queue->rear){
		return SUCCESS;
	}else{
		free(queue->base);
		free(queue);
		return SUCCESS;
	}

}

