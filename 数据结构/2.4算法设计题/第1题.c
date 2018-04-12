/*
	将两个递增的有序链表合并为一个递增的有序链表.
	要求结果链表仍使用原来两个链表的存储空间,不另占用其他存储空间,表中不允许存在重复元素
*/
#include "LinkList.h"
//Initialize the link list with the specified elements
void init(LinkList *listA, LinkList *listB) {
	int elementsA[6] = { 0,1,2,3,4,9 };
	int elementsB[6] = { 0,4,5,7,8,10 };

	initList(listA);
	initList(listB);
	//fill the link list with specified elements
	for (int i = 0; i < 6; i++)
	{
		insertByIndex(listA, -1, elementsA[i]);
		insertByIndex(listB, -1, elementsB[i]);
	}
}
//Algorithm implement:merging the two ordered list into a list which is also ordered and its elements are unique
//思路:插入排序,将B中的每个元素放到A中找到合适的插入位置
//原理:两个都是有序的list,下一次插入的位置必然在本次之后,如果A中没找到合适位置,则说明剩下的全部比A中大,直接连接即可
LinkList mergeOrderedLists(LinkList listA, LinkList listB) {
	//inspect the list whether it is NULL point or not
	if (listA == NULL || listB == NULL) {
		return NULL;
	}
	LNode *previousA = listA;
	LNode *nodeA = listA->next;
	LNode *nodeB = listB->next;
	LNode *tempNode = NULL;

	while (nodeA != NULL && nodeB != NULL)
	{
		if (nodeB->data < nodeA->data)
		{
			tempNode = nodeB;
			nodeB = nodeB->next;
			tempNode->next = nodeA;
			previousA->next = tempNode;
			//一旦有元素插入,则把前一个元素置为新插入的元素,并且暂停A向后移,因为有可能B中的值都小于A中当前元素
			previousA = tempNode;
		}
		else if(nodeB->data == nodeA->data){
			//跳过相同元素
			nodeB = nodeB->next;
		}
		else {
			//只有没找到合适位置插入的时候A才后移
			previousA = nodeA;
			nodeA = nodeA->next;
		}
		show(listA);
	}
	if (nodeB != NULL)
	{
		//把剩余元素直接接到最后即可
		previousA->next = nodeB;
		show(listA);
	}
	return listA;
}
void main() {
	LinkList listA = NULL;
	LinkList listB = NULL;
	
	init(&listA,&listB);
	
	show(listA);
	show(listB);

	putchar(10);
	LinkList listC = mergeOrderedLists(listA,listB);
	putchar(10);
	show(listC);

	system("pause");
}