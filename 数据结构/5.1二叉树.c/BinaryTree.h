#include<stdio.h>
#include<stdlib.h>
#define ELEMENT_TYPE int
#define STATUS int
#define SUCCESS 1
#define ERROR -1

typedef struct Tree {
	ELEMENT_TYPE data;
	struct Tree *leftChild;
	struct Tree *rightChild;
}BTNode,*BinaryTree;

STATUS initBinaryTree(BinaryTree *tree);
STATUS destroyBinaryTree(BinaryTree *tree);
STATUS createBinaryTree(BinaryTree *tree,int **elements);
STATUS clearBinaryTree(BinaryTree *tree);
int isBinaryTreeEmpty(BinaryTree tree);
int getBinaryTreeDepth(BinaryTree tree);
STATUS assignValue(BinaryTree *tree,BTNode *node,ELEMENT_TYPE value);
ELEMENT_TYPE getRoot(BinaryTree tree);
ELEMENT_TYPE getParent(BinaryTree tree,BTNode *node);
ELEMENT_TYPE getLeftChild(BinaryTree tree,BTNode *node);
ELEMENT_TYPE getRightChild(BinaryTree tree,BTNode *node);
ELEMENT_TYPE getLeftSibling(BinaryTree tree,BTNode *node);
ELEMENT_TYPE getRightSibling(BinaryTree tree,BTNode *node);
STATUS insertChild(BinaryTree *tree,BTNode *parentNode,int isLeftChild, BinaryTree *newChild);
STATUS deleteChild(BinaryTree *tree,BTNode *parentNode,int isLeftChild);
void prefixTraverse(BinaryTree tree);
void infixTraverse(BinaryTree tree);
void postfixTraverse(BinaryTree tree);
void levelTraverse(BinaryTree tree);
void swapChild(BinaryTree *tree);
void getCountOfNodeWithOneChild(BinaryTree tree,int *count);