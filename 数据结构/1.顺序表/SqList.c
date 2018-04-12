//检查其为空
#include "SqList.h"
int isLegal(SqList *sqList){
	if(sqList->list == NULL){
		return FALSE;
	}else if(sqList->size <= 0){
		return FALSE;
	}

	return TRUE;
}

//判断内容是否已满
int isFull(SqList *sqList){
	if(sqList->length >= sqList->size){
		return TRUE;
	}
	return FALSE;
}

//创建一个指定大小的线性表,并初始化其所有内容为0,返回值为传入进来的线性表,选择性的接受返回结果
SqList* init(SqList *sqList,int size){
	sqList->list = (ElemType *)calloc(size,sizeof(ElemType));
	sqList->length = 0;
	sqList->size = size;
	return sqList;
}

//清空里面的元素并重置大小
SqList* clear(SqList *sqList){
	int i = 0;
	for(;i < sqList->length;i++){
		*(sqList->list + i) = 0;
	}
	sqList->length = 0;
	return sqList;
}

//销毁表,返回其地址,通过判断是否为NULL,为NULL成功销毁
SqList* destroy(SqList *sqList){
	free(sqList->list);
	sqList->list = NULL;
	sqList->length = 0;
	sqList->size = 0;
	free(sqList);
	sqList = NULL;
	return sqList;
}

//在指定的下标,插入指定的值,默认插到最后,操作失败返回-1,成功返回其下标
int insert(SqList *sqList,int index,ElemType element){
	//合法性检查
	if(!isLegal(sqList)){
		return ERROR;
	}
	if(isFull(sqList)){
		return ERROR;
	}

	if(index >= 0 && index < sqList->length){
		int i = sqList->length - 1;
		for(;i >= index;i--){
			*(sqList->list + i + 1) = *(sqList->list + i);
		}
		*(sqList->list + index) = element;
		sqList->length++;
		return index;
	}else{
		*(sqList->list + sqList->length) = element;
		sqList->length++;
		return sqList->length - 1;
	}
}

//删除指定区间内的数据,失败返回-1
int deleteByRange(SqList *sqList,int lowIndex,int highIndex){
	//合法性判断
	if(lowIndex < 0 || lowIndex > sqList->length || highIndex < 0 || highIndex > sqList->length){
		return FALSE;
	}
	if(!isLegal(sqList)){
		return FALSE;
	}
	while(highIndex < sqList->length){
		*(sqList->list + lowIndex) = *(sqList->list + highIndex);
		lowIndex++;
		highIndex++;
	}
	sqList->length -= highIndex - lowIndex;
	return TRUE;
}
//删除表中指定元素的值
int deleteByValue(SqList *sqList,ElemType element){
	int i = 0;
	int j = i + 1;
	int count = 0;
	if(!isLegal(sqList)){
		return ERROR;
	}
	for(i = 0;i < sqList->length;i++){
		if(*(sqList->list + i) == element){
			for(j = i + 1;j < sqList->length - 1;j++){
				*(sqList->list + j - 1) = *(sqList->list + j);
			}
			count++;
		}
	}
	sqList->length -= count;
	return TRUE;
}

//查找指定元素下标,未找到返回-1
int getIndex(SqList *sqList,ElemType element){
	int i = 0;
	if(!isLegal(sqList)){
		return FALSE;
	}
	
	for(i = 0;i < sqList->length;i++){
		if(*(sqList->list + i) == element){
			return i;
		}
	}
	return -1;
}
//通过给定下标获取元素值,找不到返回-1
int getElement(SqList *sqList,int index){
	if(!isLegal(sqList)){
		return FALSE;
	}
	if(index < 0){
		return FALSE;
	}
	return *(sqList->list + index);
}
//返回表的长度
int getLength(SqList *sqList){
	if(!isLegal(sqList)){
		return FALSE;
	}
	return sqList->length;
}

//修改指定元素的值,失败返回-1,成功返回其原来的值
int alterElement(SqList *sqList,int oldElement,ElemType newElement){
	if(!isLegal(sqList)){
		return FALSE;
	}

	for (int i = 0; i < sqList->length; i++)
	{
		if (*(sqList->list + i) == oldElement) {
			*(sqList->list + i) = newElement;
		}
	}
	return oldElement;
}

void display(SqList *sqList){
	int i = 0;
	printf("当前表的长度:%d\n",getLength(sqList));
	printf("当前表中状态:\n");
	for(i = 0; i < sqList->length;i++){
		printf("%d,",*(sqList->list + i));
	}
	printf("\n");
}