#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define ElemType int
#define SIZE 10

typedef struct LinkedListNodeStruct {
	int child;
	struct LinkedListNodeStruct *next;
}*LinkedListNode;

typedef struct ChildTreeNodeStruct {
	//加上即为孩子双亲表示法,方便查找父结点,是孩子表示法的改进
	//int parent;
	ElemType data;
	LinkedListNode list;
}*ChildTreeNode;

typedef struct ChildTreeStruct {
	ChildTreeNode nodes;
}*ChildTree;

void ct_init(ChildTree *tree);
void ct_create(ChildTree tree);
void ct_show(ChildTree tree);
void ct_queryChild(ChildTree tree);
void ct_queryParent(ChildTree tree);
void ct_destroy(ChildTree tree);