#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CYCLIC_LINKED_LIST_TRUE 1
#define CYCLIC_LINKED_LIST_FALSE 0

/*
	前提:
		根据结构体对齐原则,作为链表结点的next必须放在第一个成员变量的位置,防止在结构体指针之间强转发生数据解析的错乱.
		原因:结构体第一个成员变量的位置与其结构体变量相等.
			在链表中的next与用户定义的结构体类型node都放在第一个成员变量的位置上,在结构体类型强转的情况下,确保每次操作的都是同一内存地址
			即Person即便强转为了CyclicLinkedListNode,只要操作next,无论此时结构体类型是什么,他们都是在操作同一块内存.

	改进的关键在于以下两点:
		1.链表结构本身改为软编码,具体内容由用户自己定义,只提供一个指针.与之前将结构体内容写死相比,这种写法更加灵活.增加了类似于多态的特性
			在这种情况下next指针具体是什么类型已经无所谓了,用户只需要自己创建一个结构体,包含一个CyclicLinkedListNode结构体的成员变量在里面即可,在具体使用的时候大量使用类型强转:
			(1).进行增删等动作时,将类型强转为CyclicLinkedListNode,直接将其链入链表即可
			(2).一旦涉及元素的读取时,由用户将其强转为自定义的类型,通过其具体实现的函数来完成操作,我们只需要获取该函数指针即可
		2.增加了函数指针的使用,在用户具体类型不确定的情况下,使用函数指针由用户自己实现具体的函数功能,更加灵活
*/
typedef struct TagCyclicLinkedListNode {//可以加上一个Tag来区别临时名字和typedef的变量名
	/*
		一个结构体里面不能又引用结构体本身变量,这样的行为属于嵌套定义了,只能用指针.
		原理:该结构体尚未定义完成,编译器不知道为其分配多大的内存,而指针的大小是已知且固定的(4Byte)
	*/
	struct TagCyclicLinkedListNode *next;
}CyclicLinkedListNode;

typedef struct TagCyclicLinkedList {
	//尽管这里使用一个变量更为方便,在malloc该List时也会对node进行分配内存,避免再次手动malloc.但是结构体所占的内存肯定比一个指针大,所以还是不要偷懒,老老实实的用指针
	CyclicLinkedListNode *node;
	int size;
}*CyclicLinkedList;

//比较器的函数指针,具体的比较规则由用户自行定义
typedef int(*COMPARATOR)(CyclicLinkedListNode *currentValue,CyclicLinkedListNode *targetValue);

//打印结点内容的函数指针,具体的打印规则由用户自行定义
typedef void(*PRINT)(CyclicLinkedListNode *node);

CyclicLinkedList create_CyclicLinkedList();

void insert_CyclicLinkedList(CyclicLinkedList list, int position, CyclicLinkedListNode *node);

void removeByPosition_CyclicLinkedList(CyclicLinkedList list, int position);

//由于这里需要比较用户指定的值和我们遍历到的元素值,但是我们又不知道用户具体使用的数据类型,所以需要用户传入一个自定义的比较函数指针(类似于java的比较器(comparator))
void removeByValue_CyclicLinkedLIst(CyclicLinkedList list, CyclicLinkedListNode *targetValue,COMPARATOR comparator);

CyclicLinkedListNode* getNodeByPosition_CyclicLinkedList(CyclicLinkedList list, int position);

CyclicLinkedListNode* getNodeByValue_CyclicLinkedList(CyclicLinkedList list, CyclicLinkedListNode *targetValue,COMPARATOR comparator);

CyclicLinkedListNode* getFirstNode_CyclicLinkedList(CyclicLinkedList list);

int getSize_CyclicLinkedList(CyclicLinkedList list);

//由于不知道具体类型,打印操作也只能由用户自行定义,传入一个函数指针给我们调用即可
void traverse_CyclicLinkedList(CyclicLinkedList list,PRINT print);

void releaseMemory(CyclicLinkedList list);