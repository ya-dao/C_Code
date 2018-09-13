#include "CyclicLinkedList.h"

typedef struct TagPerson {
	CyclicLinkedListNode *next;
	char name[100];
	int age;
}Person;

void print(CyclicLinkedListNode *node);
int comparator(CyclicLinkedListNode *currentValue, CyclicLinkedListNode *targetValue);

void main() {
	Person *expert = (Person*)malloc(sizeof(Person));
	expert->age = 23;
	expert->next = NULL;
	strcpy(expert->name,"expert");

	Person *erWa = (Person*)malloc(sizeof(Person));
	erWa->age = 23;
	erWa->next = NULL;
	strcpy(erWa->name, "¶þÍÞ");

	CyclicLinkedList list = create_CyclicLinkedList();
	insert_CyclicLinkedList(list,0,(CyclicLinkedListNode *)expert);
	insert_CyclicLinkedList(list, 1, (CyclicLinkedListNode *)erWa);

	int size = getSize_CyclicLinkedList(list);
	printf("The size of linked list = %d\n",size);

	CyclicLinkedListNode *p = getNodeByPosition_CyclicLinkedList(list,2);
	printf("get node by position of 2:\n");
	print(p);

	p = getNodeByValue_CyclicLinkedList(list,(CyclicLinkedListNode *)expert,comparator);
	printf("get node by name of expert:\n");
	print(p);

	p = getFirstNode_CyclicLinkedList(list);
	printf("get first node:\n");
	print(p);

	printf("traverse:\n");
	traverse_CyclicLinkedList(list,print);

	printf("remove node by position of 1:\n");
	removeByPosition_CyclicLinkedList(list, 1);
	traverse_CyclicLinkedList(list, print);

	printf("remove node by name of erWa:\n");
	removeByPosition_CyclicLinkedList(list, 1);
	traverse_CyclicLinkedList(list, print);

	releaseMemory(list);

	system("pause");
}
int comparator(CyclicLinkedListNode *currentValue, CyclicLinkedListNode *targetValue) {
	Person *p = (Person *)currentValue;
	Person *q = (Person *)targetValue;
	if (strcmp(p->name,q->name) == 0)
	{
		return CYCLIC_LINKED_LIST_TRUE;
	}
	else
	{
		return CYCLIC_LINKED_LIST_FALSE;
	}
}

void print(CyclicLinkedListNode *node) {
	Person *p = (Person *)node;
	printf("name:%s\n",p->name);
	printf("age:%d\n", p->age);
	printf("-----------------------------\n");
}
