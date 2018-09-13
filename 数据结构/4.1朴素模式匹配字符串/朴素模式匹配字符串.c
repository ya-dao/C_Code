#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int bool;

void plainMatch();
void plainMatchEnhance();

void main() {
	
	plainMatch();
	plainMatchEnhance();

	system("pause");
}

/*
	凭感觉写的,用了两个循环
*/
void plainMatch() {
	char str1[] = "goodgoogle";
	char str2[] = "google";

	for (int i = 0; str1[i] != '\0'; i++)
	{
		bool flag = TRUE;
		for (int j = 0, k = i; str2[j] != '\0'; j++, k++)
		{
			if (str1[k] == '\0' || str2[j] != str1[k])
			{
				flag = FALSE;
				break;
			}
		}
		if (flag == TRUE)
		{
			printf("查找成功!,主串中起始下标为%d\n",i);
			return;
		}
	}
	printf("查找失败!\n");
}

/*
	书上的思路只用了一个循环,主要是用i=i-j+1/2来简化了主串的赋值问题
*/
void plainMatchEnhance() {
	char str1[] = "goodgoogle";
	char str2[] = "google";

	int i = 0;//主串的起始下标
	int j = 0;//子串的起始下标

	while (str1[i] != '\0' && str2[j] != '\0')
	{
		if (str1[i] == str2[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}

		if (str2[j] == '\0')
		{
			printf("查找成功!,主串中起始下标为%d\n", i - j);
		}
		else {
			printf("查找失败!\n");
		}
}