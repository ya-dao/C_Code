#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
void* myMemmove(void *dest,void *src,int size) {
	if (dest == NULL || src == NULL)
	{
		return NULL;
	}
	//先用一段内存保存需要拷贝的数据
	char *temp = malloc(sizeof(char) * size);
	memcpy(temp, src,size);
	//然后用临时内存里面的内容进行赋值
	memcpy(dest, temp, size);
	free(temp);
	return dest;
}
/*
	memcpy和memmove区别:
	memcpy:这是逐字节拷贝,如果目标内存和源内存重合,则该行为未定义
	memmove:这是先将源内存数据拷贝出去然后再进行拷贝,如果有重合情况,则能保证源内存会成功拷贝
*/
void main() {
	char str1[] = "aabbcc";
	printf("The string: %s\n", str1);
	memcpy(str1 + 2, str1, 4);
	printf("New string: %s\n", str1);

	strcpy_s(str1, sizeof(str1), "aabbcc");   // reset string

	printf("The string: %s\n", str1);
	myMemmove(str1 + 2, str1, 4);
	printf("New string: %s\n", str1);

	system("pause");
}