#include "Child.h"

void ct_init(ChildTree *tree){
	*tree = (ChildTree)malloc(sizeof(struct ChildTreeStruct));
	(*tree)->nodes = (ChildTreeNode)calloc(SIZE,sizeof(struct ChildTreeNodeStruct));
	for (int i = 0; i < SIZE; i++)
	{
		(*tree)->nodes[i].list = (LinkedListNode)calloc(1, sizeof(struct LinkedListNodeStruct));
	}
}
void ct_create(ChildTree tree){
	for (int i = 0; i < SIZE; i++)
	{
		tree->nodes[i].data = i + 1;
	}
	LinkedListNode next = tree->nodes[0].list;
	LinkedListNode newNode = NULL;
	for (int i = 2; i < 4; i++)
	{
		newNode = calloc(1,sizeof(struct LinkedListNodeStruct));
		newNode->child = i;
		newNode->next = next->next;
		next->next = newNode;
	}
	next = tree->nodes[1].list;
	newNode = calloc(1, sizeof(struct LinkedListNodeStruct));
	newNode->child = 4;
	newNode->next = next->next;
	next->next = newNode;

	next = tree->nodes[2].list;
	for (int i = 5; i < 7; i++)
	{
		newNode = calloc(1, sizeof(struct LinkedListNodeStruct));
		newNode->child = i;
		newNode->next = next->next;
		next->next = newNode;
	}

	next = tree->nodes[3].list;
	for (int i = 7; i < 10; i++)
	{
		newNode = calloc(1, sizeof(struct LinkedListNodeStruct));
		newNode->child = i;
		newNode->next = next->next;
		next->next = newNode;
	}

	next = tree->nodes[4].list;
	newNode = calloc(1, sizeof(struct LinkedListNodeStruct));
	newNode->child = 10;
	newNode->next = next->next;
	next->next = newNode;
}
void ct_show(ChildTree tree){
	for (int i = 0; i < SIZE; i++)
	{
		printf("第%d个结点的数值:%d\n", i + 1, tree->nodes[i].data);
		printf("第%d个结点的子结点:\n", i + 1);
		LinkedListNode next = tree->nodes[i].list->next;
		while (next != NULL)
		{
			printf("%d ",next->child);
			next = next->next;
		}
		printf("\n");
	}
}
void ct_queryChild(ChildTree tree){
	int nodeIndex = 0;
	printf("查找第几个结点的子结点:\n");
	scanf("%d",&nodeIndex);
	printf("第%d个结点的子结点:\n", nodeIndex);
	LinkedListNode p = tree->nodes[nodeIndex - 1].list;
	//跳过头结点
	p = p->next;
	while (p != NULL)
	{
		printf("%d ",p->child);
		p = p->next;
	}
	printf("\n");
}
void ct_queryParent(ChildTree tree){
	int nodeIndex = 0;
	printf("查找第几个结点的父结点:\n");
	scanf("%d", &nodeIndex);
	int parent = -1;
	for (int i = 0; i < SIZE; i++)
	{
		LinkedListNode p = tree->nodes[i].list;
		while (p != NULL)
		{
			if (p->child == tree->nodes[nodeIndex - 1].data)
			{
				parent = i;
				break;
			}
			p = p->next;
		}
		if (parent != -1)
		{
			printf("第%d个结点的父结点是%d:\n", nodeIndex, parent + 1);
			break;
		}
	}
}
void ct_destroy(ChildTree tree){
	for (int i = 0; i < SIZE; i++)
	{
		free(tree->nodes[i].list);
	}
	free(tree->nodes);
	free(tree);
}

