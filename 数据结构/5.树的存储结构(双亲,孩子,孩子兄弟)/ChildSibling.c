#include "ChildSibling.h"

void cs_init(CSTree *tree) {
	*tree = NULL;
}
void cs_create(TreeNode *treeNode,char **elements) {
	if (**elements == '#')
	{
		(*treeNode) = NULL;
	}
	else
	{
		(*treeNode) = calloc(1,sizeof(struct ChildSiblingStruct));
		(*treeNode)->data = **elements;
		*elements = (*elements) + 1;
		cs_create(&(*treeNode)->firstChild, elements);
		*elements = (*elements) + 1;
		cs_create(&(*treeNode)->firstSibling, elements);
	}
}
void cs_show(CSTree tree) {
	if (tree == NULL)
	{
		return;
	}
	else
	{
		printf("%c",tree->data);
		cs_show(tree->firstChild);
		cs_show(tree->firstSibling);
	}
}
