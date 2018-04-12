#include<stdio.h>
#include<stdlib.h>
/*
	这里接受的是一个一级指针,而传递的也是一个变量的指针,
	如果想通过修改该指针的值来修改的变量的话,应该用二级指针来修改该变量的值.
	向这样改会把指针指向20(十六进制14)这个地址单位,引发访问冲突.
*/
void change(int *p) {
	*p = 20;
}
/*
	正确的修改方式
*/
void correctChange(int **p) {
	**p = 20;
}
void main() {
	int a = 10;
	int b = 20;
	int *p1 = &a;
	int **p2 = &p1;

	//各指针与其内容的指向
	printf("&a:%p\n", &a);
	printf("p1:%p\n", p1);
	printf("&p1:%p\n", &p1);
	printf("p2:%p\n", p2);
	printf("*p2:%p\n", *p2);
	printf("&p2:%p\n", &p2);

	//通过二级指针修改其值
	**p2 = b;
	printf("**p2=%d\n",**p2);


	//change(&p1);
	correctChange(&p1);
	printf("*p1=%d\n", *p1);
	system("pause");
}