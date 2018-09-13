#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define ElemType char
#define SIZE 10

typedef struct ChildSiblingStruct {
	int parent;
	ElemType data;
	struct ChildSiblingStruct *firstChild;
	struct ChildSiblingStruct *firstSibling;
}*TreeNode,*CSTree;

void cs_init(CSTree *tree);
void cs_create(TreeNode *tree, char **elements);
void cs_show(CSTree tree);
//void cs_queryChild(CSTree tree);
//void cs_queryParent(CSTree tree);
//void cs_destroy(CSTree tree);