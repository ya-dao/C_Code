#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
void* myMemset(void *dest,int val,int size) {
	if (dest == NULL)
	{
		return NULL;
	}
	char *dest_temp = dest;
	for (int i = 0; i < size; i++)
	{
		*(dest_temp + i) = val;
	}
	return dest;
}
void main() {
	char str[] = "test memory";
	//memset(str, '*', 4);
	myMemset(str, '*', 4);
	printf("%s\n",str);
	system("pause");
}