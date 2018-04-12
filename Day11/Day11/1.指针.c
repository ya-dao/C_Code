#include <stdlib.h>
#include <stdio.h>
void main1() {
	/*错误,指针类型存入的地址,不是值.如果将一个值赋值给指针,在对其进行操作的时候会将该值作为地址进行操作,如果该地址是其他程序正在使用的,则会引发中断异常
	int *p = 10;
	*p = 100;
	printf("%d\n",*p);
	getchar();
	*/
}
//一级指针
void main2(){
	int a = 3;
	int *p = &a;
	*p = 10;

	printf("%d\n",a);
	getchar();
}
//二级指针
void main() {
	int a = 3;
	int b = 5;

	//让指针p指向变量a
	int *p = &a;

	/*
		让二级指针p2指向一级指针p,即*p2 = p,**p2 = a
	*/
	int **p2 = &p;
	printf("%p,%p\n%p,%p,%p\n",&a,p,&p,p2,*p2);

	**p2 = 20;

	*p2 = &b;
	*p = 10;
	
	printf("%d,%d\n",a,b);
	getchar();
}