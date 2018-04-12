#include "LinkList.h"

LinkList* initList(){
	LinkList *linkList = (LinkList*)malloc(sizeof(LinkList));
	linkList->data = 0;
	linkList->next = NULL;
	return linkList;
}

STATUS destroyList(LinkList *linkList){
	LNode *p = linkList;
	LNode *q = linkList->next;
	if(linkList == NULL){
		return ERROR;
	}
	while(q != NULL){
		//先将q的下一个保存在p中
		p = q->next;
		//删除当前q指向的那个
		free(q);
		//p中保存了下一个,所以把p给q,轮替删除
		q = p;
	}
	//把头结点的下一个置空
	linkList->data = 0;
	linkList->next = NULL;
	return SUCCESS;
}

STATUS clearList(LinkList *linkList){
	LNode *node = linkList->next;
	if(linkList == NULL){
		return ERROR;
	}
	
	while(node != NULL){
		node->data = 0;
		node = node->next;
	}
	return SUCCESS;
}

STATUS isEmpty(LinkList *linkList){
	LNode *node = linkList->next;
	if(linkList == NULL){
		return ERROR;
	}
	
	if(node == NULL){
		return TRUE;
	}
	return FALSE;
}

int getLength(LinkList *linkList){
	LNode *node = linkList->next;
	int length = 0;
	if(linkList == NULL){
		return ERROR;
	}
	
	while(node != NULL){
		length++;
		node = node->next;
	}
	//将长度存在头结点中
	linkList->data = length;
	return length;
}

ElemType getElement(LinkList *linkList,int index){
	int i = 0;
	LNode *node = linkList->next;
	if(linkList == NULL){
		return ERROR;
	}
	
	while(i < index){
		node = node->next;
		i++;
	}
	return node->data;
}

int locateElement(LinkList *linkList,ElemType target){
	int index = 0;
	LNode *node = linkList->next;
	if(linkList == NULL){
		return ERROR;
	}
	
	while(node != NULL){
		if(node->data == target){
			return index;
		}
		index ++;
		node = node->next;
	}
	return ERROR;
}

ElemType priorElement(LinkList *linkList,ElemType currentElement){
	LNode *node = linkList->next;
	LNode *priorNode = linkList;
	if(linkList == NULL){
		return ERROR;
	}
	
	while(node != NULL){
		if(node->data == currentElement){
			return priorNode->data;
		}
		//轮替两个的位置
		priorNode = node;
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
	LNode *node = linkList->next;
	LNode *perviousNode = linkList;
	//创建并初始化
	LNode *newNode = initList();
	

	if(linkList == NULL){
		return ERROR;
	}
	
	//指定的下标超过长度直接报错
	length = getLength(linkList);
	if (index > length) {
		return ERROR;
	}
	while (TRUE) {
		if (i == index) {
			break;
		}
		else if (index < 0 && node == NULL) {
			break;
		}
		i++;
		perviousNode = node;
		node = node->next;
	}
	
	newNode->data = element;
	//如果指定的位置是在最后一个则用前一个结点赋值,如果还用node会造成空指针
	if (node == NULL)
	{
		newNode->next = perviousNode->next;
	}
	else {
		//如果不是最后一个则把下一个结点连接在该新结点后面
		newNode->next = node->next;
	}
	perviousNode->next = newNode;
	return SUCCESS;
}

STATUS removeByIndex(LinkList *linkList,int index){
	int i = 0;
	LNode *node = linkList->next;
	LNode *tempNode = NULL;
	if(linkList == NULL){
		return ERROR;
	}
	
	while(i != index - 1){
		i++;
		node = node->next;
	}
	
	tempNode = node->next;
	ElemType result = tempNode->data;
	node->next = tempNode->next;
	
	free(tempNode);
	return result;
}

void show(LinkList *linkList){
	LNode *node = linkList->next;
	if(linkList->next == NULL){
		printf("暂无数据！\n");
	}
	
	while(node != NULL){
		printf("%d,",node->data);
		node = node->next;
	}
	printf("\n");
}