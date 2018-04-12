/*
	将两个非递减的有序链表合并到一个非递增的有序链表.
	要求结果链表仍使用原来两个链表的存储空间,不另外占用其他的存储空间,表中允许有重复的数据.
*/
#include "LinkList.h"
void initialize(LinkList *list,int *elements,int length) {
	initList(list);
	for (int i = 0; i < length; i++)
	{
		insertByIndex(list,-1,*(elements + i));
	}
}
/*
	功能:合并两个非递减链表为一个非递增的链表
	思路:逐个比较,然后将大的插入到前面
	返回:无返回,结果以listA为新的链表头结点
*/
void merge(LinkList *listA,LinkList *listB) {
	LinkList a = (*listA)->next;
	LinkList b = (*listB)->next;
	LinkList tempNode = NULL;
	LinkList newHead = *listA;
	//断开后继的结点
	newHead->next = NULL;
	//释放掉B的表头结点
	free(*listB);

	while (a != NULL && b != NULL) {
		if (a->data <= b->data)
		{
			tempNode = a;
			a = a->next;
		}
		else {
			tempNode = b;
			b = b->next;
		}

		tempNode->next = newHead->next;
		newHead->next = tempNode;
	}

	while (a != NULL) {
		tempNode = a;
		a = a->next;
		tempNode->next = newHead->next;
		newHead->next = tempNode;
	}

	while (b != NULL) {
		tempNode = b;
		b = b->next;
		tempNode->next = newHead->next;
		newHead->next = tempNode;
	}
}
void main() {
	//初始化两个链表
	LinkList listA;
	int arrayA[] = { 2,4,5,6,7 }; 
	initialize(&listA,arrayA,5);

	LinkList listB;
	int arrayB[] = { 1,2,2,8,9 };
	initialize(&listB,arrayB,5);

	show(listA);
	show(listB);

	printf("after merge:\n");
	merge(&listA,&listB);
	show(listA);

	system("pause");
}