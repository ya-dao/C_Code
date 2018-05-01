/*
	已知两个链表A和B分别表示两个集合,其元素递增排列.设计算法,用于求出A和B的交集,并放在A链表中
*/
#include "LinkList.h"
#define N 5
void merge(LinkList *listA, LinkList *listB) {
	LinkList listC = (*listA)->next;
	initList(listA);
	while (listC != NULL) {
		LNode *nodeB = (*listB)->next;
		while (nodeB != NULL) {
			if (listC->data == nodeB->data)
			{
				insertByIndex(listA, -1, nodeB->data);
				(*listB) = nodeB;
				break;
			}
			else if (nodeB->data > listC->data) {//因为是递增,只要下一个大于A中的元素即可跳出该次寻找
				break;
			}
			nodeB = nodeB->next;
		}
		listC = listC->next;
	}
}
void main() {
	LinkList listA = NULL;
	initList(&listA);
	for (int i = 0; i < N; i++)
	{
		int element = i + 1;
		insertByIndex(&listA,-1,element);
	}
	show(listA);

	LinkList listB = NULL;
	initList(&listB);
	for (int i = 0; i < N; i++)
	{
		int element = i + 2;
		insertByIndex(&listB, -1, element);
	}
	show(listB);

	merge(&listA, &listB);
	show(listA);

	system("pause");
}