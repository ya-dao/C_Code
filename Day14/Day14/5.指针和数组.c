#include<stdio.h>
#include<stdlib.h>
/*
	1.指针和数组名
	a相当于一个类型是int *的指针,指向一个数组首元素,但不是一个真的指针,使用a时相当于是&a[0],以一个元素为单位,其+1相当于往前移一个元素.
	&a是一个数组指针int *[5],指向的是一个数组的开始地址,以整个数组为单位,+1相当于跨过一个数组.
	sizeof(*a)等价于int类型元素的大小
	sizeof(*&a)等价于sizeof(*(&a)),由前面说的&a是一个数组指针,所以其大小等于数组的大小
	sizeof(a)等价于sizeof(*(&a)),同上.*号可以取出类型大小
*/
void function1() {
	int a[] = { 1,2,3,4,5 };
	printf("a = %p,a + 1 = %p\n", a, a + 1);
	printf("&a = %p,&a + 1 = %p\n", &a, &a + 1);

	printf("sizeof(a) = %d\n", sizeof(a));
	printf("sizeof(*a) = %d\n", sizeof(*a));
	printf("sizeof(*&a) = %d\n", sizeof(*&a));
}
/*
	实战1:反转数组
*/
void reverse(int *p,int length) {
	int *head = p;
	int *tail = p + (length - 1);
	while(head < tail)
	{
		int temp = *head;
		*head = *tail;
		*tail = temp;
		head++;
		tail--;
	}
}
/*
	实战2:实现strcopy
*/
void* strcopy(char *source,char *destination,int length) {
	if (*source == NULL || *destination == NULL) {
		return source;
	}
	for (int i = 0; i < length; i++) {
		*(source + i) = *(destination + i);
	}
	return source;
}
void show(int *p) {
	for (int i = 0; i < 5; i++)
	{
		printf("%d ",*(p + i));
	}
	printf("\n");
}
void main() {
	//function1();
	int a[] = { 1, 2, 3, 4, 5 };
	reverse(a,5);
	show(a);
	char ch[50] = {"cunzhang is great!"};
	/*
		这里传递的需要被修改的source不能是字符串常量指针,如下:
		char *p = "xxxx";必须是char a[N]这种.
		因为*p = "xxx"的内容是代码区的常量,只能读不能修改
	*/
	char *p = strcopy(ch, "expert", 6);
	printf("%s\n",p);
	system("pause");
}