#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

#define 风姐要求的高 180
#define 风姐要求的富 10000
#define 风姐要求的帅 95

#define 春哥要求的高 180
#define 春哥要求的富 1000000
#define 春哥要求的帅 95
/*
	3.实现文件输入输出，三目运算符，关系运算符  用凤姐找出符合条件，春哥找出条件
	173  10000000   96
	173  10000000   96
	173  10000000   96
	重定向符
		< 从文件输入
		> 向文件输出
*/
int main() {
	int height = 0;
	int handsome = 0;
	int wealthy = 0;

	for (int i = 0; i < 3; i++) {
		scanf("%d,%d,%d", &height, &wealthy,&handsome);
		printf("%d,%d,%d\n", height, handsome, wealthy);
		if (height >= 风姐要求的高 && handsome >= 风姐要求的帅 && wealthy >= 风姐要求的富) {
			printf("风姐觉得你还可以!\n");
		}
		else {
			printf("爬开些\n");
		}

		if (height >= 春哥要求的高 || handsome >= 春哥要求的帅 || wealthy >= 春哥要求的富) {
			printf("春哥表示看上你了!\n");
		}
		else {
			printf("一边玩蛋去\n");
		}
	}
	return 0;
}