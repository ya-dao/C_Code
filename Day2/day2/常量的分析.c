#include<stdio.h>
/*
	使用const关键字创建常量并尝试修改其值
	结论:const关键字修饰的变量不能通过赋值的方式修改值,但是可以通过修改内存地址的值的方式来进行修改.
*/
void test1() {
	const int number = 10;
	//number = 11;	//const修饰的变量不可通过赋值的方式修改

	//方式一:通过调试工具直接修改内存地址里面的值
	printf("%p\n",&number);

	//方式二:通过指针操作内存来修改变量的值
	int *p = (int*)&number;	//将number的地址赋值给指针p
	*(p) = 20;				//修改指针p的值为20
	printf("number = %d\n",number);
}

/*
	使用define定义常量并试图修改
	结论:define定义的常量不能通过修改内存地址的值来修改值,因为它的值是由寄存器里产生而不是在内存中,所以对其取不了地址.C语言没有办法修改寄存器里的值.只能通过汇编来修改它的值.
*/
#define data 20
void test2() {
	//define定义的不是变量,所以不能对其进行取地址操作
	//printf("%p\n",&data);
	printf("%d\n",data);
}
/*
	C语言和汇编的区别:
		C语言只能操作内存,不能操作修改寄存器.
		汇编都可以进行操作.
*/
int main() {
	//test1();
	test2();

	getchar();
	return 0;
}