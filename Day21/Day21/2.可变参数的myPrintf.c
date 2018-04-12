#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
/*
	printf()函数可接受可变参数,需要用到stdarg.h头文件.
	通过在使用var系列函数来获取并操作传递进来的可变参数
*/
/*
	java中的可变参数是..
	C语言中的可变参数是...
*/
void myPrintf(char *format,...) {
	//存放可变参数中的所有参数的字符指针
	va_list ap = NULL;
	//初始化让其指向可变参数列表中的第一个参数,第一个是list本身,第二个是可变参数前一个参数的地址
	//一定是...前面一个
	va_start(ap,format);
	//参数个数是无法通过函数获取的,有两种方法获取
	//1.通过参数指定可变参数个数
	//2.自己通过每个条件统计,这里由于前面有格式控制符,我们可以通过遍历格式控制符直到\0
	//3.va_arg会通过第二个参数(指定的参数类型)返回一个对应类型的值
	int integer = 0;
	char *str = NULL;
	float real = 0.0f;
	while (1) {
		char c = *(format++);
		if (c == '%')
		{
			c = *(format++);
			switch (c)
			{
			case 'd':
				integer = va_arg(ap,int);
				putchar('0' + integer);
				break;
			case 's':
				str = va_arg(ap, char*);
				puts(str);
				break;
			case 'f':
				real = va_arg(ap,double);
				//调用之前的ftoa打印小数
				printf("%f",real);
				break;
			default:
				break;
			}
		}
		else
		{
			putchar(c);
			if (c == '\0') {
				va_end(ap);
				break;
			}
		}
	}
}
void main() {
	int a = 1;
	char *b = "just a test!";
	double c = 3.14;
	printf("a=%d,b=%s,c=%f\n",a,b,c);
	myPrintf("a=%d,b=%s,c=%f\n", a, b, c);
	system("pause");
}