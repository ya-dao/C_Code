#include "LinkList.h"

void createListWithHead(LinkList *list,int n){
	//创建并初始化头结点
	(*list) = (LinkList)malloc(sizeof(LNode));
	(*list)->data = 0;
	(*list)->next = (*list);
	(*list)->previous = (*list);
	//表示当前元素,用于引用next和previous元素,便于在两个结点之间插入元素
	LNode *p = (*list);
	//每次插入的临时结点
	LNode *tempNode = NULL;
	for (int i = 0; i < n; i++)
	{
		//先搞定新元素的前驱和后继
		tempNode = malloc(sizeof(LNode));
		tempNode->data = i;
		tempNode->next = p->next;
		tempNode->previous = p;
		//搞定p->next->previous
		p->next->previous = tempNode;
		//最后搞定p->next,确保之前的引用关系不出错
		p->next = tempNode;
		p = tempNode;
	}
}

void initList(LinkList *list){
	(*list) = (LinkList)malloc(sizeof(LNode));
	(*list)->data = 0;
	(*list)->next = (*list);
	(*list)->previous = (*list);
}

STATUS destroyList(LinkList *linkList){
	LNode *p = (*linkList);
	LNode *q = (*linkList)->next;
	if((*linkList) == NULL){
		return ERROR;
	}
	while(q != (*linkList)){
		//先将q的下一个保存在p中
		p = q->next;
		//删除当前q指向的那个
		free(q);
		//p中保存了下一个,所以把p给q,轮替删除
		q = p;
	}
	//把头结点的下一个置为头结点
	(*linkList)->data = 0;
	(*linkList)->next = (*linkList);
	return SUCCESS;
}

STATUS clearList(LinkList *linkList){
	LNode *node = (*linkList)->next;
	if((*linkList) == NULL){
		return ERROR;
	}
	
	while(node != (*linkList)){
		node->data = 0;
		node = node->next;
	}
	return SUCCESS;
}

STATUS isEmpty(LinkList linkList){
	LNode *node = linkList->next;
	if(linkList == NULL){
		return ERROR;
	}
	
	if(node == linkList){
		return TRUE;
	}
	return FALSE;
}

int getLength(LinkList linkList){
	LNode *node = linkList->next;
	int length = 0;
	if(linkList == NULL){
		return ERROR;
	}
	
	while(node != linkList){
		length++;
		node = node->next;
	}
	//将长度存在头结点中
	linkList->data = length;
	return length;
}

ElemType getElement(LinkList linkList,int index){
	int i = 0;
	LNode *node = linkList->next;
	if(linkList == NULL){
		return ERROR;
	}
	
	while(i < index && node != linkList){
		node = node->next;
		i++;
	}
	return node->data;
}

int locateElement(LinkList linkList,ElemType target){
	int index = 0;
	LNode *node = linkList->next;
	if(linkList == NULL){
		return ERROR;
	}
	
	while(node != linkList){
		if(node->data == target){
			return index;
		}
		index ++;
		node = node->next;
	}
	return ERROR;
}

/*
	尾部插入，指定下标时插入到指定下标的后面，指定下标（-1）时则在链表最后一个位置插入
*/
STATUS insertByIndex(LinkList *linkList,int index,ElemType element){
	int i = 0;
	int length = 0;
	LNode *node = (*linkList)->next;
	LNode *previousNode = (*linkList);
	//创建并初始化
	LNode *newNode = NULL;
	initList(&newNode);
	

	if((*linkList) == NULL){
		return ERROR;
	}
	
	//指定的下标超过长度直接报错
	length = getLength((*linkList));
	if (index > length) {
		return ERROR;
	}
	while (TRUE) {
		if (i == index) {
			break;
		}
		else if (index < 0 && node == (*linkList)) {
			break;
		}
		i++;
		previousNode = node;
		node = node->next;
	}
	
	newNode->data = element;
	//如果指定的位置是在最后一个则用前一个结点赋值,如果还用node会造成空指针
	if (node == (*linkList))
	{
		newNode->next = previousNode->next;
		newNode->previous = previousNode;
	}
	else {
		//如果不是最后一个则把下一个结点连接在该新结点后面
		newNode->next = node->next;
		newNode->previous = node;
	}
	previousNode->next->previous = newNode;
	previousNode->next = newNode;
	return SUCCESS;
}

STATUS removeByIndex(LinkList *linkList,int index){
	int i = 0;
	LNode *node = (*linkList)->next;
	LNode *tempNode = NULL;
	if(linkList == NULL){
		return ERROR;
	}
	
	while(i != index - 1){
		i++;
		node = node->next;
	}
	
	tempNode = node->next;
	tempNode->next->previous = node;
	ElemType result = tempNode->data;
	node->next = tempNode->next;
	
	free(tempNode);
	return result;
}

void show(LinkList linkList){
	LNode *node = linkList->next;
	if(linkList->next == NULL){
		printf("暂无数据！\n");
	}
	
	while(node != linkList){
		printf("%d,",node->data);
		node = node->next;
	}
	printf("\n");
}