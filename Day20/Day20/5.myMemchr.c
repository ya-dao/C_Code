#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
void *myMemchr(void *buffer,int val,int maxCount) {
	if (buffer == NULL || maxCount == 0)
	{
		return NULL;
	}
	char *temp = buffer;
	for (int i = 0; i < maxCount; i++)
	{
		if (*temp == val) {
			return temp;
		}
		temp++;
	}
	return NULL;
}
void main() {
	char *p = "abcde";
	//功能:从指定内存区域中查找某一字符,找到返回其地址,找不到返回NULL
	//void *address = memchr(p,'w',6);
	void *address = myMemchr(p, 'b', 6);
	printf("%p,%s\n",address,address);
	system("pause");
}