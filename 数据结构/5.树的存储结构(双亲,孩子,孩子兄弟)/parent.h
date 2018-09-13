#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define ElemType int
#define SIZE 10

typedef struct ParentTreeNodeStruct {
	ElemType data;
	int parent;
}ParentTreeNode;

typedef struct ParentTreeStruct {
	ParentTreeNode *nodes;
}*ParentTree;

void pt_init(ParentTree *tree);
void pt_create(ParentTree tree);
void pt_show(ParentTree tree);
void pt_queryChild(ParentTree tree);
void pt_queryParent(ParentTree tree);
void pt_destroy(ParentTree tree);