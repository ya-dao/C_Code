//2．输入一个字符，判断它如果是小写字母输出其对应大写字母；如果是大写字母输出其对应小写字母；如果是数字输出数字本身；如果是空格，输出“space”；如果不是上述情况，输出“other”。
#include<stdio.h>
#include<stdlib.h>

int main() {
	char ch = getchar();
	if (ch >= 65 && ch <= 90) {
		printf("%c\n",ch + 32);
	}
	else if (ch >= 97 && ch <= 122) {
		printf("%c\n", ch - 32);
	}
	else if (ch >= 48 && ch <= 57) {
		printf("%c\n", ch);
	}
	else if (ch == 32) {
		printf("%s\n", "space");
	}
	else {
		printf("%s\n", "other");
	}
	system("pause");
	return 0;
}