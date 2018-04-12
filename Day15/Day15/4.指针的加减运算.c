#include<stdio.h>
#include<stdlib.h>
void function1(int *p) {
	//*(p + i)等价于p[i]
	printf("*(p + 3)=%d\n",*(p + 3));
	printf("p[3]=%d\n", p[3]);
}
void function2(int *p) {
	//等价于p=p+3,前进3个单位,指向第4个元素
	p += 3;
	//*(p++)等价于*(p);p++;先取当前p的值,p再自增,结果为4
	printf("*(p++)=%d\n", *(p++));
	//*p由于上一步p已自增,结果为5
	printf("*p=%d\n", *p);
	//*(++p)等价于p++;*(p + 1);p先自增,再取p的值,结果为6
	printf("*(++p)=%d\n", *(++p));
}
void function3(int *p) {
	/*
		定义的变量存储在栈区,存储方向是从高地址往低地址存.
		栈的出口向上.底下是高地址,上面是低地址.
	*/
	int a = 1, b = 2, c = 3;
	printf("%p\n", &a);
	printf("%p\n", &b);
}
void main() {
	int array[] = { 1,2,3,4,5,6,7,8,9,0 };
	//function1(array);
	//function2(array);
	function3(array);
	system("pause");
}