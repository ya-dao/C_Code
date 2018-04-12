#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int myStrcmp(const char *dest,const char *source) {
	if (dest == NULL || source == NULL) {
		return -2;
	}
	char *pDest = dest;
	char *pSource = source;
	while(1)
	{
		if (*dest > *source) {
			return 1;
		}
		else if (*dest < *source) {
			return -1;
		}
		else if (*dest == '\0' && *source == '\0') {
			return 0;
		}
		else {
			dest++;
			source++;
		}
	}
}
void sort(char (*p)[4]) {
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8 -1 - i; j++)
		{
			if (myStrcmp(*(p + j),*(p + j + 1)) == 1)
			{
				char temp[4] = { 0 };
				strcpy(temp,*(p + j));
				strcpy(*(p + j), *(p + j + 1));
				strcpy(*(p + j + 1), temp);
			}
		}
	}
}
void show(char (*p)[4]) {
	for (int i = 0; i < 8; i++)
	{
		printf("%s\n",*(p + i));
	}
}
void main() {
	char str[8][4] = { "abc","fde","sjk","eio","lds","woe","bcd","osd" };
	//printf("%d\n", strcmp(*(str + 0),*(str + 1)));
	//printf("%d\n", myStrcmp(*(str + 0), *(str + 1)));

	sort(str);
	show(str);
	system("pause");
}