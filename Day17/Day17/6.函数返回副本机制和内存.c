#include<stdio.h>
#include<stdlib.h>
char* function1() {
	/*
		错误示例:str在栈中
			函数不能返回指向栈区的内存,当栈的生命周期结束之后该内存区域会被回收
		正确做法:
			如果需要返回一段内存,应该在堆中创建并将数据保存至该处并返回其地址
			或者返回代码区的常量字符
	*/
	char str[] = { "china no.1" };
	return str;
}
char* function2() {
	//正确做法1:指向字符常量返回地址
	//char *str = "china no.1";
	//正确做法2:在堆中创建内存并返回地址
	char *str = (char *)malloc(sizeof(char) * 11);
	str[0] = 'c';
	str[1] = 'h';
	str[2] = 'i';
	str[3] = 'n';
	str[4] = 'a';
	str[5] = ' ';
	str[6] = 'n';
	str[7] = 'o';
	str[8] = '.';
	str[9] = '1';
	str[10] = '\0';
	return str;
}
int function3() {
	/*
		函数的副本机制
			函数的返回值不在内存,而是在cpu的缓存中,不能对其取地址
	*/
	int a = 5;
	return a;
}
void main() {
	//char *p = function1();
	/*{
		char *p = function2();
		printf("%s\n", p);
		free(p);
	}*/
	{
		int a = function3();
		printf("%d\n",a);
	}
	system("pause");
}