#include "LinkStack.h"
void main() {
	//尽管init方法也是将其置为NULL,但是还是在创建的时候将其置NULL,避免野指针的情况.
	LinkStack stack = NULL;
	init(&stack);
	int flag = 0;
	for (int i = 0; i < 5; i++)
	{
		flag = push(&stack, i);
		if (flag == SUCCESS)
		{
			printf("push %d succeeded!\n",i);
		}
		flag = getTop(stack);
		if (flag >= 0)
		{
			printf("current top element is %d !\n", flag);
		}
	}
	//长度只求一次,避免边操作边遍历的不同步现象
	int length = getLength(stack);
	for (int i = 0; i < length; i++)
	{
		ElemType element = pop(&stack);
		printf("pop %d succeeded!\n", element);
	}

	printf("\npush elements again!\n");
	for (int i = 10; i < 15; i++)
	{
		flag = push(&stack, i);
		if (flag == SUCCESS)
		{
			printf("push %d succeeded!\n", i);
		}
		flag = getTop(stack);
		if (flag >= 0)
		{
			printf("current top element is %d !\n", flag);
		}
	}

	printf("destroy operation:\n");
	//通过断点debug查看内存变化观察其过程
	destroy(&stack);
	printf("current size after destroy:%d\n",getLength(stack));
	
	system("pause");
}