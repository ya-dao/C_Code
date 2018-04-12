#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define DATA 9

/*
运用system函数通过指定的路径打开一个应用程序
*/
void test1() {
	/*
	1.转义字符的处理,"\"需要用两个"\\"来转义,双引号需要用(\")进行转义
	2.如果路径中有空格,则需要将此路径作为一个字符串用双引号括起来
	3.如果路径中带有括号(),则括号前面需要加上空格" "
	*/

	system("\"C:\\Program Files (x86)\\Tencent\\QQ\\Bin\\QQScLauncher.exe\"");
}

/*
	getchar()接收字符后退出的问题
*/
void test2() {
	/*
		1.vs中对scanf有安全性的要求,需要在代码中#define _CRT_SECURE_NO_WARNINGS一个常量来消除该警告,#define _CRT_SECURE_NO_WARNINGS必须放在最前面,如果放在#include后面就会无效
		2.一般的#define不强制要求放最前面
		3.getchar()可做为停顿下来看控制台输出的一种方式,如果前面是scanf()函数,那么输入完成后按下的回车会被getchar()函数接收.
	*/
	int num1 = DATA;
	printf("\n%d",num1);
	int num = DATA;
	scanf("%d",&num);
	getchar();
}

/*
	通过\a转义字符播放声音
*/
void test3() {
	//在C语言里面,真和假的区别是0和非0,并非0和1.
	while (-1) {
		putchar('\a');
	}
}

/*
	通过printf函数向一个文本里面输出文本并使用\r和\n转义字符.
	'\r'是回车，'\n'是换行，前者使光标到行首，后者使光标下移一格，
	通常敲一个回车键，即是回车，又是换行（\r\n）。
	Windows中每行结尾是“<换行><回车>”，即“\n\r”；
*/
void test4() {
	printf("蓝蓝的天上白云飘,\r\n白云下面马儿跑.\n");
}

/*
	转义字符里面的8进制和16进制
	三个重要的ascii码值
		0 48
		A 65
		a 97
*/
void test5() {
	putchar('\101');	// \开头8进制  1 * 8^2 + 0 * 8^1 + 1 * 8^0 = 65
	putchar('\x43');	// \x开头16进制	4 * 16^1 + 3 * 16^0 = 67
}
int main() {
	
	//test1();
	//test2();
	//test3();
	//test4();
	
	test5();

	system("pause");
	return 0;
}
