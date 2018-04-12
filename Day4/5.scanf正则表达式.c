#include<stdio.h>
#include<stdlib.h>
/*
	scanf的正则表达式没有数量词,没有代表字母和数字的符号,比如\\d,\\w这些是没得的
	而且它是一但出现跟正则表达式不匹配的字符就停止输入了.
*/
void test1(){
	char str[100] = {0};
	scanf("%[^0-9]",str);
	printf("%s\n",str);
}

void test2(){
	
}
int main(){
	test1();
	return 0;
}