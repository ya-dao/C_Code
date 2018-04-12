/*
	对缓冲溢出进行分析,并讨论缓冲区溢出攻击的原理和方法,下面是一段示例代码:
	分析程序完成的功能,在什么情况下会出现缓冲溢出问题?
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void fun(char *str) {
	char buf[8];
	strcpy(buf,str);
	printf("%s\n",buf);
}

void main(int argc,char *argv[]) {
	/*
	for (int i = 0; i < argc; i++)
	{
		printf("%s\n",argv[i]);
	}
	*/
	if (argc > 0) {
		fun(argv[1]);
	}
}