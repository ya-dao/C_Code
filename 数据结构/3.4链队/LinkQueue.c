#include "LinkQueue.h"

STATUS init(LinkQueue *queue) {
	QNode *node = (QNode *)malloc(sizeof(QNode));
	node->next = NULL;
	(*queue) = (LinkQueue)malloc(sizeof(Queue));
	(*queue)->front = (*queue)->rear = node;
	return SUCCESS;
}
STATUS enQueue(LinkQueue *queue, ElemType element) {
	QNode *node = (QNode *)malloc(sizeof(QNode));
	node->data = element;
	node->next = NULL;
	(*queue)->rear->next = node;
	(*queue)->rear = node;
	return SUCCESS;
}
ElemType deQueue(LinkQueue *queue) {
	//判断队列是否为空
	if ((*queue)->front == (*queue)->rear)
	{
		return ERROR;
	}
	QNode *node = (*queue)->front;
	(*queue)->front = node->next;
	//如果当前出队的元素是最后一个元素,则将尾指针指向头结点
	if ((*queue)->rear == node)
	{
		(*queue)->rear = (*queue)->front;
	}
	ElemType result = node->data;
	free(node);
	return result;

}
ElemType getHead(LinkQueue queue) {
	//判断是否为空
	if (queue->front == queue->rear)
	{
		return ERROR;
	}
	return queue->front->data;
}