#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
void main() {
	char url[100] = "https://www.bilibili.com/video/av6538245/?p=\n";
	char buffer[100] = { 0 };
	printf("输入需要生成的链接,最后的变量删去,例:\n");
	printf("");
	gets(url);

	int start = 0,end = 0;
	printf("起始值:\n");
	scanf("%d",&start);

	printf("结束值:\n");
	scanf("%d", &end);

	for (int i = start; i <= end; i++)
	{
		sprintf(buffer,"%s%d",url,i);
		printf("%s\n",buffer);
	}

	system("pause");
}