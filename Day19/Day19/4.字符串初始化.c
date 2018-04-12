#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
void main() {
	/*
		接收输入的内容初始化字符串
		1.字符串数组
			1.1	输入的内容会从字符串开始地址将输入的内容逐个写入到内存中,直到遇到\0.
				非常不安全,会更改到后面其他的内存空间中的数据,引发不可预测的结果
			1.2 整体输出该字符串时,会从该地址一直输出,直到遇到\0(无视长度)
		2.字符串常量
			2.1 如果需要根据输入更改字符串内容,则需要让指针指向一片开辟的内存空间.如:
				(1)指向一个字符串数组
				(2)malloc开辟一片空的内存
	*/
	char str[3];
	char *p = NULL;
	scanf("%s",str);
	printf("%s\n", str);
	printf("%s\n", str);
	//2.1(1)
	//p = str;
	
	//2.1(1)
	//p = malloc(sizeof(char) * 5);
	scanf("%s", p);
	printf("%s\n", p);

	system("pause");
}