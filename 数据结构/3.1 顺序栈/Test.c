#include "Stack.h"
#include <time.h>
void main(){
	Stack *stack = NULL;
	int i = 0;
	initStack(&stack);

	srand(time(NULL));

	printf("入栈操作:\n");
	for(i = 0;i < stack->maxSize;i++){
		push(stack,rand() % 100 + 1);

		stackTraverse(stack);
	}

	printf("栈内元素是否为空:%s\n",isStackEmpty(stack)?"空":"非空");

	printf("栈内元素长度:%d\n",getLength(stack));

	printf("当前栈内top元素:%d\n",getTop(stack));


	printf("\n出栈操作:\n");
	while(stack->top != stack->base){
		printf("当前出栈元素:%d\n",pop(stack));
		stackTraverse(stack);
		printf("\n");
	}

	printf("栈内元素是否为空:%s\n",isStackEmpty(stack)?"空":"非空");
	printf("栈内元素长度:%d\n",getLength(stack));

	printf("\n再次进行入栈操作:\n");
	for(i = 0;i < stack->maxSize;i++){
		push(stack,rand() % 100 + 1);

		stackTraverse(stack);
	}

	printf("\n栈清空操作:\n");
	clearStack(&stack);
	printf("栈内元素长度:%d\n",getLength(stack));
	stackTraverse(stack);

	printf("\n再次进行入栈操作:\n");
	for(i = 0;i < stack->maxSize;i++){
		push(stack,rand() % 100 + 1);

		stackTraverse(stack);
	}
	printf("启动栈销毁\n");
	destroyStack(&stack);
	printf("栈内元素长度:%d\n",getLength(stack));

	system("pause");
}
