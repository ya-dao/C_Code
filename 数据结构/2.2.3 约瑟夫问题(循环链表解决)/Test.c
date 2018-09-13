#include "CyclicLinkedList.h"
/*
	问题描述:此处n=8,k=3时,最后剩下7
	n个人围成一个圈，然后从1依次报数，报到k的那个人退出圈，后面一个人继续从1开始报数，直到剩下最后一个人，求最后剩下的人的编号
	解析:
		1.用数组
		每个元素增加一个标志位,每出局一个就将其flag位置为0,遍历时跳过那些已经出局的元素,循环下去就ok
		2.用循环链表
		找到一个删除一个,注意要跳过头结点
*/

//number of person
#define NUMBER 8
//the interval of numbering each round
#define INTERVAL 3
#define EXIST 1
#define NOT_EXIST 0

typedef struct TagPerson {
	CyclicLinkedListNode *next;
	int index;
	int isExist;
}Person;

void useArray();

void print(CyclicLinkedListNode *node) {
	Person *person = (Person *)node;
	printf("%d ", person->index);
}

int comparator(CyclicLinkedListNode *currentValue, CyclicLinkedListNode *targetValue) {
	Person *current = (Person *)currentValue;
	Person *target = (Person *)targetValue;

	if (current->index == target->index)
	{
		return CYCLIC_LINKED_LIST_TRUE;
	}
	else
	{
		return CYCLIC_LINKED_LIST_FALSE;
	}
}

int main() {

	CyclicLinkedList list = create_CyclicLinkedList();

	for (int i = 0; i < NUMBER; i++)
	{
		Person *person = (Person *)malloc(sizeof(Person));
		person->index = i + 1;
		insert_CyclicLinkedList(list, i, (CyclicLinkedListNode *)person);
	}

	printf("插入完毕:\n");
	traverse_CyclicLinkedList(list, print);

	int interval = 1;
	int i = 0;
	CyclicLinkedListNode *p = list->node->next;
	CyclicLinkedListNode *pTemp = NULL;

	while (getSize_CyclicLinkedList(list) > 1)
	{
		if (interval == INTERVAL)
		{
			interval = 1;
			i++;
			printf("第%d次出列:%d\n", i, ((Person *)p)->index);

			pTemp = p;
			p = p->next;
			removeByValue_CyclicLinkedLIst(list,pTemp,comparator);

			//跳过头结点
			if (p == list->node)
			{
				p = p->next;
			}
		}
		else
		{
			p = p->next;
			//跳过头结点
			if (p == list->node)
			{
				p = p->next;
			}
			interval++;
		}
	}

	printf("幸运儿是:%d\n", ((Person *)p)->index);

	system("pause");
	return 0;
}

void useArray() {
	Person persons[NUMBER] = { NULL };


	for (int i = 0; i < NUMBER; i++)
	{
		persons[i].index = i + 1;
		persons[i].isExist = EXIST;
	}

	int currentInterval = 1;
	int size = NUMBER;

	for (int i = 0, j = 0; size != 1; i = (i + 1) % NUMBER)
	{
		if (persons[i].isExist == EXIST)
		{
			if (currentInterval == INTERVAL)
			{
				printf("第%d次出列:%d\n", j, persons[i].index);
				persons[i].isExist = NOT_EXIST;
				currentInterval = 0;
				j++;
				size--;
			}
			currentInterval++;
		}

	}

	for (int i = 0; i < NUMBER; i++)
	{
		if (persons[i].isExist == EXIST)
		{
			printf("幸运儿是:%d\n", persons[i].index);
		}
	}
}