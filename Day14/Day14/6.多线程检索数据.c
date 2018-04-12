#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<process.h>

#define N 93

//全局变量,用于线程之间通信,如果有一个线程找到对应数值,则修改其值,其他线程每次判断其值是否发生改变
int isFind = 0;

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
		if ((i + 1) % 10 == 0) {
			printf("\n");
		}
	}
	printf("\n");
}
void work(void *p) {
	SearchInfo *info = (SearchInfo *)p;
	for (int i = 0; i < info->count; i++)
	{
		if (isFind) {
			printf("其他线程已找到,线程%d退出\n",info->threadId);
			return;
		}
		if (*(info->startPoint + i) == info->target)
		{
			printf("线程%d已找到数据%d\n",info->threadId,*(info->startPoint + i));
			isFind = 1;
			return;
		}
	}
}
void main() {
	int array[N];
	init(array);
	show(array);

	int target = 0;
	printf("输入目标数据:\n");
	scanf("%d",&target);

	//最好建立与cpu核心数量成比例的线程数,能提高效率
	SearchInfo info[10];
	for (int i = 0; i < 10; i++)
	{
		int *startIndex = array + 10 * i;
		//这里不该创建一个变量,因为函数那里接受的是指针类型,如果传递这个变量的地址过去,那么每一个线程所使用的参数全部是一样的.
		//SearchInfo info[i];
		info[i].startPoint = startIndex;
		//适用于比较规律的划分,可以除尽的话就不用特殊处理
		info[i].target = target;
		info[i].threadId = i + 1;
		_beginthread(work, 0, &info[i]);
	}

	system("pause");
}