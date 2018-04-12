#include<stdio.h>
#include<stdlib.h>
/*
	根据输入的内容列出所有组合,生成一个密码字典
*/
char words[] = "abc";
int count = 0;
void show(char *array) {
	for (char *p = array; *p; p++)
	{
		printf("%c ",*p);
	}
	printf("\n");
}
void swap(char *pA,char *pB) {
	char temp = *pA;
	*pA = *pB;
	*pB = temp;
}
/*
	算法:假设要排列的内容为"a b c"
		1.abc的排列等于a+bc的排列
		2.bc的排列等于b的排列+c的排列
		3.c的排列只有一种
*/
void arrangement(char *array) {
	if (*array == '\0')
	{
		count++;
		printf("%d:%s\n",count,words);
	}
	for (char *p = array; *p != '\0'; p++)
	{
		swap(p,array);
		arrangement(array + 1);
		swap(p,array);
	}
}
void main() {
	arrangement(words);
	system("pause");
}