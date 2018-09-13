#include<stdio.h>
#include<stdlib.h>
#include "StackAndQueue.h"

#define ELEMENT_TYPE int

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
void preorderTraversal(BinaryTree tree);
void inorderTraversal(BinaryTree tree);
void postorderTraversal(BinaryTree tree);
void preorderTraversal_iteration(BinaryTree tree);
void inorderTraversal_iteration(BinaryTree tree);
void postorderTraversal_iteration(BinaryTree tree);
void levelTraversal(BinaryTree tree);
void swapChild(BinaryTree *tree);
void getCountOfNodeWithOneChild(BinaryTree tree,int *count);

//使用迭代的方式进行树的遍历,需要借助栈的实现
void preorderTraversal_iteration(BinaryTree tree);
void inorderTraversal_iteration(BinaryTree tree);
void postorderTraversal_iteration(BinaryTree tree);