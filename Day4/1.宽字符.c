#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<locale.h>
void test1() {
	char ch = '我';
	printf("%c\n", ch);
	printf("%d\n", sizeof(ch));
	printf("%d\n", sizeof(L'我'));
	//wchar_t宽字符用于将汉字当做字符输出等处理,一个占2个字节
	wchar_t wch = L'我';
	printf("%d\n", sizeof(wch));
	//输出宽字符中文必须设置本地语言
	setlocale(LC_ALL, "zh-CN");
	putwchar(wch);
}
/*
	宽字符的输入输出应该用wscanf/wprintf
	且输出的时候需要引入locale.h头文件,并在输入输出前使用setLocale()方法设置本地语言
*/
void test2() {
	wchar_t wch[100] = { '0' };
	setlocale(LC_ALL, "zh-CN");
	wscanf(L"%ls",wch);
	wprintf(L"%ls\n", wch);
}
/*
	wprintf()输出宽字符
	printf()输出窄字符
	两者不能搞反
*/
void test3() {
	printf("%s\n",L"个狗东西");	//不匹配
	setlocale(LC_ALL, "zh-CN");
	wprintf(L"%s\n", "个狗东西");	//不匹配
}
int main() {
	//MessageBox输出的字符编码与设置有关,如果是unicode则是宽字符,如果是多字节字符集则是窄字符
	//MessageBox(0, L"这是文本", L"这是标题", 0);
	//MessageBoxA是输出窄字符的
	//MessageBoxA(0, "这是文本", "这是标题", 0);
	//MessageBoxA是输出宽字符的,输出宽字符需要加上L
	//MessageBoxW(0, L"这是文本", L"这是标题", 0);
	//也可以使用TEXT()函数自动转换宽窄字符类型
	//MessageBox(0, TEXT("这是文本"), TEXT("这是标题"), 0);
	//test1();
	//test2();
	test3();
	system("pause");
	return 0;
}
