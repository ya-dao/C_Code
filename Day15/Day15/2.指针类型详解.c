#include<stdio.h>
#include<stdlib.h>
/*
	指针的类型和指针所指向的类型必须一一对应,不然会造成解析失败.
	指针类型的不同,解析的方式也不同
*/
void main1() {
	int number = 10;
	int *p = &number;
	float *fp = &number;
	double *dp = &number;
	printf("%d\n%f\n%lf\n",*p,*fp,*dp);
	system("pause");
}
/*
	同类型之间的赋值:
		同类型之间的赋值如果指向的是同一个地址,那么这个地址的值如果发生变化.
		将会启动连锁反应.
*/
void main2() {
	int a = 10;
	int *p = &a;
	int *p2 = p;
	printf("三个变量所指向的地址:%p,%p,%p\n",&a,p,p2);
	*p2 = 5;
	printf("修改之后三个变量所指向的地址的值:%d,%d,%d\n", a, *p, *p2);
	system("pause");
}

/*
	printf类型转换的问题
		1.printf不会自动转换类型,当输出的内容的类型不匹配时,比如:
			float用%d输出,或者int用%f输出,就会出现解析失败.
		不同的类型对应着不同的解析方式.
		2.如果需要输出不同的类型,则需要强制类型转换.比如float用%d输出前,先强制转换(int)b;
		3.赋值号'='除了指针以外,都会进行自动类型转换.
			比如int a = 10.9;会被转换为10;
			对于指针,只会完成地址的赋值,不会自动类型转换
*/
void main() {
	int a = 10.9;
	float b = 10.9;
	printf("a=%d\n", a);
	printf("b=%d\n",b);
	printf("b=%d\n", (int)b);
	system("pause");
}