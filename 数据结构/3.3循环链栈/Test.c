#include "CSQueue.h"
void main(){
	CSQueue queue;
	init(&queue);
	
	printf("EnQueue:\n");
	for(int i = 0;i < 9;i++){
		enQueue(&queue,i);
		printf("Current insert:%d\n", i);
	}

	printf("isEmpty:%s\n",isEmpty(queue)?"¿Õ":"·Ç¿Õ");

	printf("isFull:%s\n",isFull(queue)?"Âú":"·ÇÂú");

	printf("Length:%d\n",getLength(queue));

	printf("DeQueue:\n");
	while(!isEmpty(queue)){
		ElemType head = deQueue(&queue);
		printf("Current head:%d\n", head);
	}

	printf("isEmpty:%s\n",isEmpty(queue)?"¿Õ":"·Ç¿Õ");

	printf("isFull:%s\n",isFull(queue)?"Âú":"·ÇÂú");

	printf("Length:%d\n",getLength(queue));

	printf("Head:%d\n",getHead(queue));

	printf("EnQueue again:\n");
	for (int i = 0; i < 9; i++) {
		enQueue(&queue, i);
		printf("Current insert:%d\n", i);
	}

	printf("Clear:\n");
	clear(&queue);
	printf("isEmpty:%s\n", isEmpty(queue) ? "¿Õ" : "·Ç¿Õ");

	printf("isFull:%s\n", isFull(queue) ? "Âú" : "·ÇÂú");

	printf("Length:%d\n", getLength(queue));

	printf("Head:%d\n", getHead(queue));

	printf("Destroy:\n");
	destroy(&queue);
	printf("isEmpty:%s\n", isEmpty(queue) ? "¿Õ" : "·Ç¿Õ");

	printf("isFull:%s\n", isFull(queue) ? "Âú" : "·ÇÂú");

	printf("Length:%d\n", getLength(queue));

	printf("Head:%d\n", getHead(queue));

	system("pause");
}