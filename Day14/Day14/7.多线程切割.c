#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<process.h>

#define N 100
#define THREAD_COUNT 8

typedef struct SearchInfo {
	int *startPoint;
	int count;
	int target;
	int threadId;
}SearchInfo;

void init(int *array) {
	time_t t;
	srand(time(&t));
	for (int i = 0; i < N; i++)
	{
		*(array + i) = rand() % 100;
	}
}
void show(int *array) {
	for (int i = 0; i < N; i++)
	{
		printf("%2d ", *(array + i));
		if ((i + 1) % THREAD_COUNT == 0) {
			printf("\n");
		}
	}
	printf("\n");
}
void work(void *p) {
	SearchInfo *info = (SearchInfo *)p;
	//printf("线程%d开始查找数据\n", info->threadId);
	for (int i = 0; i < info->count; i++)
	{
		if (*(info->startPoint + i) == info->target)
		{
			printf("线程%d已找到数据%d\n", info->threadId, *(info->startPoint + i));
			return;
		}
	}
	printf("线程%d结束查找\n", info->threadId);
}
void main() {
	int array[N];
	init(array);
	show(array);

	int target = 0;
	printf("输入目标数据:\n");
	scanf("%d", &target);

	//最好建立与cpu核心数量成比例的线程数,能提高效率
	SearchInfo info[THREAD_COUNT];
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		int *startIndex = array + THREAD_COUNT * i;
		//这里不该创建一个变量,因为函数那里接受的是指针类型,如果传递这个变量的地址过去,那么每一个线程所使用的参数全部是一样的.
		//SearchInfo info;
		info[i].startPoint = startIndex;
		//比较凌乱的划分,93不能除尽,需要特殊处理
		if ((N - THREAD_COUNT * i) % THREAD_COUNT == 0)
		{
			info[i].count = N - THREAD_COUNT * i % THREAD_COUNT;
		}
		else {
			info[i].count = THREAD_COUNT;
		}
		info[i].target = target;
		info[i].threadId = i + 1;
		
		_beginthread(work, 0, &info[i]);
	}

	system("pause");
}