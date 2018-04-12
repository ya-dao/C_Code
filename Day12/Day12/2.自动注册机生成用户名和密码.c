#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<locale.h>

#define N 6
/*
	自动注册机随机生成一个用户名和密码
*/
void generateUsername() {
	wchar_t username[N] = { L'号', L'康', L'伟', L'超', L'文', L'奎'};
	for (int i = 0; i < 2; i++)
	{
		wprintf(L"%c",username[rand() % 6]);
	}
	printf("\n");
}
void generatePassword() {
	char password[N] = { 's', 'a', 'd', 'w', 'g', 'h' };
	for (int i = 0; i < 6; i++)
	{
		putchar(password[rand() % 6]);
	}
	printf("\n");
}
void main() {
	setlocale(LC_ALL, "zh-CN");
	srand(time(NULL));
	generateUsername();
	generatePassword();

	system("pause");
}