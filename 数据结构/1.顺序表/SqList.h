#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0 
#define ERROR -1

typedef int ElemType;
struct List{
	ElemType *list;
	//表中当前内容的长度
	int length;
	//表的总长度
	int size;
};
typedef struct List SqList;


int isLegal(SqList *sqList);
int isFull(SqList *sqList);
SqList* init(SqList *sqList,int size);
SqList* clear(SqList *sqList);
SqList* destroy(SqList *sqList);
int insert(SqList *sqList,int index,ElemType element);
int deleteByRange(SqList *sqList,int lowIndex,int highIndex);
int deleteByValue(SqList *sqList,ElemType element);
int getIndex(SqList *sqList,ElemType element);
int getElement(SqList *sqList,int index);
int getLength(SqList *sqList);
int alterElement(SqList *sqList,int oldElement,ElemType newElement);
void display(SqList *sqList);
