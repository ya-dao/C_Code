#include<stdio.h>
#include<stdlib.h>
/*
	区别一个数组名的指针类型,核心一点是+1.
		因为+1会加上其类型的步长,然后根据步长的不同来进行类型的区分
*/
void function1() {
	/*
		一维数组名a:
			a指向一个元素,类型为int指针int *,步长为一个元素
			&a指向一个数组,类型为数组指针int (*p)[],步长为整个数组
			*a:a指向数组首元素,*a为取出该地址对应的值
	*/
	int a[] = { 1,2,3 };
	printf("a = %p,&a = %p,*a = %p\n", a, &a, *a);
	printf("a+1 = %p,&a+1 = %p,*a+1 = %p\n", a + 1, &a + 1, *a + 1);
}
void function2() {
	/*
		二维数组b:
		b为一个行指针,指向数组中的一行,类型为int (*)[5]
		&b为一个指向该二维数组的指针,类型为int (*)[3][5]
		*b为一个列指针,指向数组的一个元素,类型为int *
	*/
	int b[3][5] = { 1 ,2 ,3 };
	printf("%d\n",*(*b + 1));
	printf("b = %p,&b = %p,*b = %p\n", b, &b, *b);
	printf("b+1 = %p,&b+1 = %p,*b+1 = %p\n", b + 1, &b + 1, *b + 1);
}
void main() {
	//function1();
	function2();
	system("pause");
}