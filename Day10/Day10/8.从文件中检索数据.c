#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
	根据C语言提供的文件操作Api来读取文件中的数据并筛选
*/
void main() {
	char loadPath[100] = { "C:\\Users\\Administrator\\Desktop\\传说中的大数据.txt" };
	char savePath[100] = { 0 };

	char buffer[1024] = { 0 };
	char target[10] = { 0 };

	scanf("%s",target);
	
	sprintf(savePath, "C:\\Users\\Administrator\\Desktop\\%s.txt", target);

	FILE* file = fopen(loadPath, "r");
	FILE* saveFile = fopen(savePath, "w");
	
	int i = 0;
	for (;!feof(file);i++)
	{
		//这个函数不能自动读取一行,需要手动设置读取长度
		//fread(buffer, sizeof(char), 400, file);
		fgets(buffer, 1024, file);
		char* p = strstr(buffer, target);

		if (p != NULL || i == 0)
		{
			printf("%s\n", buffer);
			fputs(buffer, saveFile);
		}
	}
	//一定要记得关闭文件
	fclose(file);
	fclose(saveFile);
	printf("共计%d人\n",i);
	system("pause");
}