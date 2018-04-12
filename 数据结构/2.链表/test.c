#include "LinkList.h"
void main(){
	LinkList *list_A;
	LinkList *list_B;
	int i = 0;

	list_A = initList();
	for(i = 1;i <= 7;i += 2){
		insertByIndex(list_A,-1,i);
	}
	show(list_A);

	int empty = isEmpty(list_A);
	printf("isEmpty = %d\n", empty);

	int length = getLength(list_A);
	printf("length = %d\n", length);

	ElemType element = getElement(list_A, 1);
	printf("elment = %d\n", element);

	int position = locateElement(list_A, 3);
	printf("position = %d\n", position);

	ElemType prior = priorElement(list_A,5);
	printf("priorElement = %d\n", prior);

	ElemType removedElement = removeByIndex(list_A,2);
	printf("removedElement = %d\n", removedElement);
	show(list_A);

	clearList(list_A);
	printf("清零后:\n");
	show(list_A);

	destroyList(list_A);
	printf("销毁后:\n");
	show(list_A);

	system("pause");
}