#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
void main() {
	printf("Content-type:text/html\n\n");
	char str[100] = { 0 };
	scanf("%s",str);
	printf("ÄãÊäÈëµÄÊÇ%s/br",str);
}