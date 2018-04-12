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
	struct LNode *previous;
}LNode,*LinkList;

//修改定义时的LinkList为指针类型
//修改创建和初始化时需要返回参数
void createListWithHead(LinkList *list,int n);
void initList(LinkList *list);
STATUS destroyList(LinkList *linkList);
STATUS clearList(LinkList *linkList);
STATUS isEmpty(LinkList linkList);
int getLength(LinkList linkList);
ElemType getElement(LinkList linkList,int index);
int locateElement(LinkList linkList,ElemType target);
//双向链表中用不到这玩意了
//ElemType priorElement(LinkList linkList,ElemType currentElement);

STATUS insertByIndex(LinkList *linkList,int index,ElemType element);
STATUS removeByIndex(LinkList *linkList,int index);
void show(LinkList linkList);