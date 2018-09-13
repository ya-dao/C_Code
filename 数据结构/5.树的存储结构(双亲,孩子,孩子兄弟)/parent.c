#include "parent.h"

void pt_init(ParentTree *tree) {
	(*tree) = (struct ParentTreeStruct *)malloc(sizeof(struct ParentTreeStruct));
	(*tree)->nodes = (ParentTreeNode *)malloc(sizeof(ParentTreeNode) * SIZE);
}
void pt_create(ParentTree tree) {
	for (int i = 0; i < SIZE; i++)
	{
		tree->nodes[i].data = i + 1;
		
		/*printf("输入第%d个结点的数值:\n",i + 1);
		scanf("%d",&(tree->nodes[i].data));
		printf("输入第%d个结点的父结点:\n", i + 1);
		scanf("%d", &(tree->nodes[i].parent));*/
	}
	tree->nodes[0].parent = -1;
	tree->nodes[1].parent = 0;
	tree->nodes[2].parent = 0;
	tree->nodes[3].parent = 1;
	tree->nodes[4].parent = 2;
	tree->nodes[5].parent = 2;
	tree->nodes[6].parent = 3;
	tree->nodes[7].parent = 3;
	tree->nodes[8].parent = 3;
	tree->nodes[9].parent = 4;
}
void pt_show(ParentTree tree) {
	for (int i = 0; i < SIZE; i++)
	{
		printf("第%d个结点的数值:%d\n", i + 1,tree->nodes[i].data);
		printf("第%d个结点的父结点:%d\n", i + 1, tree->nodes[i].parent + 1);
	}
}
void pt_queryParent(ParentTree tree) {
	int childNode = 0;
	int parentNode = 0;
	printf("查询第几个结点的父结点:\n");
	scanf("%d",&childNode);
	parentNode = tree->nodes[childNode - 1].parent;
	printf("第%d个结点的父结点为%d\n",childNode,parentNode + 1);
}
void pt_queryChild(ParentTree tree) {
	int *childNode = calloc(SIZE, sizeof(ElemType));
	int parentNode = 0;
	int childCount = 0;
	printf("查询第几个结点的所有子结点:\n");
	scanf("%d", &parentNode);
	int childIndex = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (tree->nodes[i].parent == parentNode - 1) {
			childCount++;
			childNode[childIndex] = tree->nodes[i].data;
			childIndex++;
		}
	}
	printf("第%d个结点的子结点为:\n", parentNode);
	for (int i = 0; i < SIZE && childNode[i] != 0; i++)
	{
		printf("%d ", childNode[i]);
	}
	printf("\n");

}
void pt_destroy(ParentTree tree) {
	free(tree->nodes);
	free(tree);
}