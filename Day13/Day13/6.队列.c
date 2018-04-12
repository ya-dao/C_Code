#include "myQueue.h"

int main() {
	myQueue queue;
	init(&queue);
	for (int i = 88; i < 88 + N; i++)
	{
		enQueue(&queue, i);
		show(&queue);
	}
	printf("出队\n");
	for (int i = 0; i < N; i++)
	{
		deQueue(&queue);
		show(&queue);
	}
	system("pause");
}

void init(myQueue *queue) {
	memset((void *)queue->queue,0,sizeof(int) * N);
	queue->head = 0;
	queue->tail = 0;
}
int isEmpty(myQueue *queue) {
	if (queue->head == queue->tail) {
		return 1;
	}
	else {
		return 0;
	}
}
int isFull(myQueue *queue) {
	if (queue->tail == N) {
		return 1;
	}
	else {
		return 0;
	}
}
void enQueue(myQueue *queue, int object) {
	//插入的时候先把数据往后移,由于tail-1必须大于等于0,所以不加empty这个条件了
	for (int i = queue->tail - 1; i >= 0; i--)
	{
		queue->queue[i + 1] = queue->queue[i];
	}

	if (!isFull(queue)) {
		queue->queue[queue->head] = object;
		queue->tail++;
	}
}
int deQueue(myQueue *queue) {
	if (!isEmpty(queue)) {
		int top = queue->queue[queue->tail];
		queue->tail--;
		return top;
	}
	else {
		return -1;
	}
}
int getTop(myQueue *queue) {
	if (!isEmpty(queue))
	{
		return queue->queue[queue->tail];
	}
	else {
		return -1;
	}
}
void clear(myQueue *queue) {
	queue->tail = queue->head;
}

void show(myQueue *queue) {
	for (int i = 0; i < queue->tail; i++)
	{
		printf("%2d ",queue->queue[i]);
	}
	printf("\n");
}