#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<math.h>
int myMemicmp(const void *buffer1, const void *buffer2,int size) {
	char *buffer_1 = buffer1;
	char *buffer_2 = buffer2;

	for (int i = 0; i < size; i++)
	{
		//因为要忽略大小写,先判断是否为字符串
		if ((*(buffer_1 + i) >='a' && *(buffer_1 + i) <= 'z') ||
			(*(buffer_1 + i) >= 'A' && *(buffer_1 + i) <= 'Z')) {
			if (*(buffer_2 + i) >= 'a' && *(buffer_2 + i) <= 'z' ||
				(*(buffer_2 + i) >= 'A' && *(buffer_2 + i) <= 'Z')) {
				//如果两个相减相差0或者32,则说明是同一个字符或者大小写
				int difference = abs(*(buffer_1 + i) - *(buffer_2 + i));
				if (difference == 0 || difference == 32)
				{
					//同一字符直接跳过,继续下一个,不同则直接在下面判断大小
					continue;
				}
			}
		}
		if (*(buffer_1 + i) > *(buffer_2 + i)) {
			return 1;
		}
		else if (*(buffer_1 + i) < *(buffer_2 + i)) {
			return -1;
		}
	}
	return 0;
}
void main() {
	//_memicmp:比较两组字符的前N个字节是否相同(忽略大小写)
	char *a = "abcd";
	char *b = "ABCD";
	//int result = _memicmp(a, b, 4);
	int result = myMemicmp(a, b, 4);
	printf("%d\n",result);
	int c[] = { 1,2,5,4 };
	int d[] = { 1,2,5,3 };
	//它的比法也是一个字节一个字节的比较,经过测试两个低字节完全相同的两个不同的数得到该结论
	//result = _memicmp(c, d, 9);
	result = myMemicmp(c, d, 12);
	printf("%d\n", result);
	system("pause");
}