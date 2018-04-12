#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
void showDialog() {
	MessageBoxA(NULL,"函数指针调用函数","函数指针用途",0);
}
int add(int a, int b) {
	return a + b;
}
int sub(int a, int b) {
	return a - b;
}
void operate(int(*p)(int, int), int a, int b) {
	/*
		作为一个接口,对外接收一个函数指针.
		不限制具体是哪个函数,提升扩展性
	*/
	printf("%d\n",p(a,b));
}
void function1() {
	/*
		函数指针的声明:把函数名换成(*指针名)
			int (*)(int,int)=add
			存储一个函数的地址.
			错误写法:
				int (*)(int,int) = add(1,2);
				add(1,2)是一个函数调用,它会把函数的返回值作为地址赋值给函数指针,造成访问冲突
		作用:
			1.通过函数指针调用一个函数:函数指针(参数);
			2.通过dll注射非法调用另一个进程的函数
			3.将函数指针作为一个函数参数传递给其他函数(实现一个接口的功能)
	*/
	void (*p)() = showDialog;
	p();
}
void function2() {
	/*
		&showDialog,showDialog,*showDialog:
			这三个完全等价
		&showDialog = showDialog
		*showDialog = *(&showDialog) = showDialog
		对于代码区来说,函数指针有类型,但没有类型,*showDialog,&showDialog都没有多大意义
	*/
	printf("%p,%p,%p\n", &showDialog, showDialog, *showDialog);
	//报错,这3个都不允许加减运算,代码区不允许修改(仅限于应用层)
	//printf("%p,%p,%p\n", &showDialog + 1, showDialog + 1, *showDialog+1);
}
void function3() {
	/*
		作用3:将函数指针作为一个函数参数传递给其他函数
	*/
	//operate(add,10,7);
	operate(sub, 10, 7);
}
/*
	函数指针作为返回值
		 int (*ff(int))(int *, int);
		我们用上面介绍的方法分析一下，ff首先与后面的“()”结合，即：
		int (*(ff(int)))(int *, int); // 用括号将ff(int)再括起来也就意味着，ff是一个函数。
		接着与前面的“*”结合，说明ff函数的返回值是一个指针。
		然后再与后面的“()”结合，也就是说，该指针指向的是一个函数。
		这种写法确实让人非常难懂，以至于一些初学者产生误解，认为写出别人看不懂的代码才能显示自己水平高。
		而事实上恰好相反，能否写出通俗易懂的代码是衡量程序员是否优秀的标准。
		一般来说，用typedef关键字会使该声明更简单易懂。在前面我们已经见过：
		int (*PF)(int *, int);
		也就是说，PF是一个函数指针“变量”。
		当使用typedef声明后，则PF就成为了一个函数指针“类型”，即：
			 typedef int (*PF)(int *, int);
		这样就定义了返回值的类型。然后，再用PF作为返回值来声明函数:
			PF ff(int);
*/
int (*function4(int a, int b))(int, int) {
	return add;
}
/*
	使用typedef简化返回值为函数指针的定义
*/
typedef int (*p)(int, int);
p function5() {
	return sub;
}
void main() {
	//function1();
	//function2();
	//function3();
	//printf("function4=%d\n", function4(3, 4)(1, 2));
	printf("function5=%d\n", function5()(3, 2));
	system("pause");
}