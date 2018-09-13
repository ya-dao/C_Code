#include "BinaryTree.h"

void main() {
	BinaryTree tree = NULL;
	int elements[9] = { 1,2,-1,3,-1,-1,4,-1,-1 };
	int *p = elements;
	initBinaryTree(&tree);
	printf("是否为空树:%s\n",isBinaryTreeEmpty(tree)?"空":"非空");
	createBinaryTree(&tree, &p);
	printf("是否为空树:%s\n", isBinaryTreeEmpty(tree) ? "空" : "非空");
	
	//测试新功能
	//swapChild(&tree);

	int count = 0;
	getCountOfNodeWithOneChild(tree, &count);
	printf("\n度为1的结点:%d\n",count);

	printf("\n前序遍历:\n");
	preorderTraversal(tree);
	printf("\n前序迭代遍历:\n");
	preorderTraversal_iteration(tree);

	printf("\n中序遍历:\n");
	inorderTraversal(tree);

	printf("\n中序迭代遍历:\n");
	inorderTraversal_iteration(tree);

	printf("\n后序遍历:\n");
	postorderTraversal(tree);

	printf("\n后序迭代遍历:\n");
	postorderTraversal_iteration(tree);

	printf("\n层序遍历:\n");
	levelTraversal(tree);

	printf("\n深度:%d\n",getBinaryTreeDepth(tree));

	BTNode *node = malloc(sizeof(BTNode));
	node->data = 4;
	assignValue(&tree, node, 5);
	printf("\n修改结点4之后:\n");
	preorderTraversal(tree);

	printf("\nroot:%d\n", getRoot(tree));
	
	node->data = 3;
	printf("\n结点3的父结点:%d\n", getParent(tree,node));

	node->data = 1;
	printf("\n结点1的左子结点:%d\n", getLeftChild(tree, node));

	node->data = 1;
	printf("\n结点1的右子结点:%d\n", getRightChild(tree, node));

	int elements2[9] = { 1,2,-1,3,-1,-1,-1 };
	int *pp = elements2;
	BinaryTree tree2 = NULL;
	initBinaryTree(&tree2);
	createBinaryTree(&tree2, &pp);

	node->data = 2;
	insertChild(&tree,node,1,&tree2);
	printf("\n插入结点之后:\n");
	preorderTraversal(tree);

	deleteChild(&tree,node,1);
	printf("\n删除结点之后:\n");
	preorderTraversal(tree);

	system("pause");
}

void visit(BinaryTree pTree, Stack *stack) {
	while (pTree != NULL)
	{
		push(stack, pTree->rightChild);
		push(stack, pTree->leftChild);
		pTree = getTop(stack);
	}
}
void postorderTraversal_iteration1(BinaryTree tree) {
	Stack *stack = NULL;
	initStack(&stack);
	BTNode *pTree = tree;
	if (pTree != NULL)
	{
		push(stack, pTree);
	}
	while (TRUE)
	{
		BTNode *top = getTop(stack);
		if (top != NULL && top->leftChild != pTree && top->rightChild != pTree)
		{
			visit(top, stack);
		}
		if (isStackEmpty(stack) == TRUE)
		{
			break;
		}
		pTree = pop(stack);
		if (pTree != NULL)
		{
			printf("%d ", pTree->data);
		}
	}
}