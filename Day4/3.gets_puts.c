#include<stdio.h>
#include<stdlib.h>
int main(){
	//puts和gets可用于从文件中重定向和重定向至文件中
	char str[100] = {0};
	gets(str);
	system(str);
	puts(str);
	char ch = getchar();
	putchar(ch);
	return 0;
}