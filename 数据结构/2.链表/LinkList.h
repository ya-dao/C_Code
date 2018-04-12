#include<stdio.h>
#include<stdlib.h>

#define ElemType int
#define STATUS int

#define ERROR -1
#define SUCCESS 1

#define TRUE 1
#define FALSE 0

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,LinkList;

LinkList* initList();
STATUS destroyList(LinkList *linkList);
STATUS clearList(LinkList *linkList);
STATUS isEmpty(LinkList *linkList);
int getLength(LinkList *linkList);
ElemType getElement(LinkList *linkList,int index);
int locateElement(LinkList *linkList,ElemType target);
ElemType priorElement(LinkList *linkList,ElemType currentElement);
STATUS insertByIndex(LinkList *linkList,int index,ElemType element);
STATUS removeByIndex(LinkList *linkList,int index);
void show(LinkList *linkList);