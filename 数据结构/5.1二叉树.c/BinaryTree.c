#include "BinaryTree.h"

/*初始化传入的二叉树*/
STATUS initBinaryTree(BinaryTree *tree){
	(*tree) = (BinaryTree)malloc(sizeof(BTNode));
	(*tree)->data = -1;
	(*tree)->leftChild = NULL;
	(*tree)->rightChild = NULL;
	return SUCCESS;
}
/*
	销毁当前二叉树
	猜测当前只能用后序遍历的方式逐个删除结点空间，其他两种可能会导致先删掉根结点，后面的结点回不来
*/
STATUS destroyBinaryTree(BinaryTree *tree){
	if((*tree)->leftChild != NULL || (*tree)->rightChild != NULL){
		destroyBinaryTree(&(*tree)->leftChild);
		destroyBinaryTree(&(*tree)->rightChild);
		free(*tree);
		return SUCCESS;
	}else{
		return SUCCESS;
	}
}
/*
	根据给定的元素（以-1号结束）按先序创建二叉树，使用X序都可以创建
*/
STATUS createBinaryTree(BinaryTree *tree,int **elements){
	if(**elements == -1){
		(*tree) = NULL;
	}else{
		(*tree) = malloc(sizeof(BTNode));
		(*tree)->data = **elements;
		*elements = *elements + 1;
		createBinaryTree(&(*tree)->leftChild,elements);
		*elements = *elements + 1;
		createBinaryTree(&(*tree)->rightChild, elements);
	}
	return SUCCESS;
}
/*
	将其置为一个空二叉树
*/
STATUS clearBinaryTree(BinaryTree *tree){
	destroyBinaryTree(tree);
	initBinaryTree(tree);
	return SUCCESS;
}
/*
	判断其是否为一个空树
*/
int isBinaryTreeEmpty(BinaryTree tree){
	if(tree->leftChild != NULL || tree->rightChild != NULL){
		return 0;
	}else{
		return 1;
	}
}
/*
	获取树的深度
*/
int getBinaryTreeDepth(BinaryTree tree){
	if(tree == NULL){
		return 0;
	}else{
		int leftDepth = getBinaryTreeDepth(tree->leftChild);
		int rightDepth = getBinaryTreeDepth(tree->rightChild);
		if(leftDepth > rightDepth){
			return leftDepth + 1;
		}else{
			return rightDepth + 1;
		}
	}
}
STATUS assignValue(BinaryTree *tree,BTNode *node,ELEMENT_TYPE value){
	if (*tree == NULL)
	{
		return ERROR;
	}
	else {
		if ((*tree)->data == node->data)
		{
			(*tree)->data = value;
			return SUCCESS;
		}
		int leftFlag = assignValue(&(*tree)->leftChild, node, value);
		if (leftFlag == 1)
		{
			return leftFlag;
		}
		int rightFlag = assignValue(&(*tree)->rightChild, node, value);
		return rightFlag;
	}
}
ELEMENT_TYPE getRoot(BinaryTree tree) {
	if (tree == NULL)
	{
		return -1;
	}
	else {
		return tree->data;
	}
}
ELEMENT_TYPE getParent(BinaryTree tree, BTNode *node) {
	if (tree == NULL)
	{
		return ERROR;
	}
	else {
		//如果根结点等于给定的值,返回-1
		if (tree->data == node->data)
		{
			return -1;
		}
		if (tree->leftChild != NULL)
		{
			if (tree->leftChild->data != node->data)
			{
				return tree->leftChild->data;
			}
		}
		if (tree->rightChild != NULL)
		{
			if (tree->rightChild->data != node->data)
			{
				return tree->rightChild->data;
			}
		}
		int left = getParent(tree->leftChild, node);
		if (left != 0)
		{
			return left;
		}
		int right = getParent(tree->rightChild, node);
		return right;
	}
}
ELEMENT_TYPE getLeftChild(BinaryTree tree, BTNode *node) {
	if (tree == NULL)
	{
		return ERROR;
	}
	else {
		if (tree->data == node->data)
		{
			if (tree->leftChild != NULL)
			{
				return tree->leftChild->data;
			}
		}
		ELEMENT_TYPE left = getLeftChild(tree->leftChild, node);
		if (left != ERROR)
		{
			return left;
		}
		ELEMENT_TYPE right = getLeftChild(tree->rightChild,node);
		return right;
	}
}
ELEMENT_TYPE getRightChild(BinaryTree tree, BTNode *node) {
	if (tree == NULL)
	{
		return ERROR;
	}
	else {
		if (tree->data == node->data)
		{
			if (tree->rightChild != NULL)
			{
				return tree->rightChild->data;
			}
		}
		ELEMENT_TYPE left = getRightChild(tree->leftChild, node);
		if (left != ERROR)
		{
			return left;
		}
		ELEMENT_TYPE right = getRightChild(tree->rightChild, node);
		return right;
	}
}
/*
	从根结点开始遍历某个的子结点,如果其子结点等于指定结点
		判断当前结点是否为左子结点,则指定结点没有左兄弟
		判断当前结点是否为右子结点,则返回其父结点的左子结点
*/
ELEMENT_TYPE getLeftSibling(BinaryTree tree, BTNode *node) {
	if (tree == NULL)
	{
		return ERROR;
	}
	else {
		if (tree->leftChild->data == node->data)
		{
			return ERROR;
		}
		if (tree->rightChild->data == node->data)
		{
			return tree->leftChild->data;
		}

		int left = getLeftSibling(tree->leftChild, node);
		if (left != ERROR)
		{
			return left;
		}
		int right = getLeftSibling(tree->rightChild, node);
		return right;
	}

	return ERROR;
}
ELEMENT_TYPE getRightSibling(BinaryTree tree, BTNode *node) {
	if (tree == NULL)
	{
		return ERROR;
	}
	else {
		if (tree->leftChild->data == node->data)
		{
			return ERROR;
		}
		if (tree->rightChild->data == node->data)
		{
			return tree->leftChild->data;
		}

		int left = getLeftSibling(tree->leftChild, node);
		if (left != ERROR)
		{
			return left;
		}
		int right = getLeftSibling(tree->rightChild, node);
		return right;
	}

	return ERROR;
}
/*
	parentNode指向原树tree中某一结点
	isLeftChild表明插入parentNode的左子结点还是右子结点
	newChild为待插入的新子结点且右子结点非空
	将newChild插入对应的结点,parent原有的左子结点或右子结点成为newChild的右子结点
*/
STATUS insertChild(BinaryTree *tree, BTNode *parentNode, int isLeftChild, BinaryTree *newChild) {
	if (*tree == NULL)
	{
		return ERROR;
	}
	else {
		if ((*tree)->data == parentNode->data)
		{
			if (isLeftChild == 1)
			{
				(*newChild)->rightChild = (*tree)->leftChild;
				(*tree)->leftChild = *newChild;
			}else if (isLeftChild == 0)
			{
				(*newChild)->rightChild = (*tree)->rightChild;
				(*tree)->rightChild = *newChild;
			}
			return SUCCESS;
		}
		STATUS left = insertChild(&(*tree)->leftChild, parentNode, isLeftChild, newChild);
		if (left == SUCCESS)
		{
			return left;
		}
		STATUS right = insertChild(&(*tree)->rightChild, parentNode, isLeftChild, newChild);
		return right;
	}
}
STATUS deleteChild(BinaryTree *tree, BTNode *parentNode, int isLeftChild) {
	if (*tree == NULL)
	{
		return ERROR;
	}
	else {
		if ((*tree)->data == parentNode->data)
		{
			if (isLeftChild == 1)
			{
				(*tree)->leftChild = NULL;
				return SUCCESS;
			}
			else if (isLeftChild == 0)
			{
				(*tree)->rightChild = NULL;
				return SUCCESS;
			}
		}
		int left = deleteChild(&(*tree)->leftChild, parentNode, isLeftChild);
		if (left != ERROR)
		{
			return left;
		}
		int right = deleteChild(&(*tree)->rightChild, parentNode, isLeftChild);
		return right;
	}
}
void prefixTraverse(BinaryTree tree){
	if(tree == NULL){
		return;
	}else{
		printf("%d ",tree->data);
		prefixTraverse(tree->leftChild);
		prefixTraverse(tree->rightChild);
	}
}
void infixTraverse(BinaryTree tree) {
	if (tree == NULL) {
		return;
	}
	else {
		infixTraverse(tree->leftChild);
		printf("%d ", tree->data);
		infixTraverse(tree->rightChild);
	}
}
void postfixTraverse(BinaryTree tree) {
	if (tree == NULL) {
		return;
	}
	else {
		postfixTraverse(tree->leftChild);
		postfixTraverse(tree->rightChild);
		printf("%d ", tree->data);
	}
}
void levelTraverse(BinaryTree tree) {
	if (tree == NULL)
	{
		return;
	}
	else {
		printf("%d ",tree->data);

	}
}
/*
	1、设计算法交换二叉树中每个结点的左右儿子。
	思路:跟遍历差不多,直接使用前序遍历进行操作
		由于是链表,所以交换儿子结点会把后面的结点一起交换了
*/
void swapChild(BinaryTree *tree) {
	if (NULL == (*tree))
	{
		return;
	}
	else 
	{
		//读取其右儿子,由于只是交换两个的值,所以只需要取一任意一个临时保存即可
		BTNode *rightChild = (*tree)->rightChild;
		(*tree)->rightChild = (*tree)->leftChild;
		(*tree)->leftChild = rightChild;
		//递归操作其左儿子和右儿子
		swapChild(&(*tree)->leftChild);
		swapChild(&(*tree)->rightChild);
	}
}
/*
	遍历该树,同时对只有一个子结点的情况进行计数
	递归中为了避免反复创建变量计数,直接传计数变量的指针即可
*/
void getCountOfNodeWithOneChild(BinaryTree tree,int *count) {
	if (NULL == tree)
	{
		return;
	}
	else 
	{
		if ((NULL != tree->leftChild && NULL == tree->rightChild) ||
			(NULL == tree->leftChild && NULL != tree->rightChild))
		{
			*count = *count + 1;
		}
		//遍历子结点
		getCountOfNodeWithOneChild(tree->leftChild, count);
		getCountOfNodeWithOneChild(tree->rightChild, count);
	}
}