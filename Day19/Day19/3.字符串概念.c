#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void function1() {
	/*
		C语言字符串两种风格
		1.字符串数组
			char str[] = { "abc" };
		2.常量字符串
			char *p = "abc";
	*/
	char str[] = { "abc" };
	char *p = "abc";
	printf("%s\n%s\n",str,p);
}
void function2() {
	/*
	C语言字符串两种风格区别:
	1.字符串数组
		1.数组名是一个常量地址,不能修改
		2.字符串数组里面的内容都是保存到某个具体的地址空间里面的,可以对其进行更改
		3.字符串数组大小由其内存空间大小决定,char str[100]声明100即为100,如果未声明大小则为其实际长度+'\0'
		4.字符串数组长度由其有效内容决定,遇到\0停止
	2.常量字符串
		1.指针是个变量,可以更改使其指向一个新的字符串
		2.常量字符串里面的内容都是存在于代码区内的常量(可读不可写),指针只是该常量字符串的首地址.
		3.常量字符串大小固定为4个字节,因为它是一个指针.
		4.常量字符串长度由其有效内容决定,遇到\0停止
	*/
	char str[100] = { "abc" };
	char *p = "abc";
	/*
		//1.
		str = "bcd";
		p = "bcd";
	*/
	
	
		//2.
		*(str + 1) = 'B';
		*(p + 1) = 'B';//引发中断
		printf("%s\n%s\n", str, p);
	
	
	/*
		//3.
		printf("sizeof(str) = %d\n",sizeof(str));
		printf("sizeof(p) = %d\n", sizeof(p));
	*/

	////4.
	//printf("strlen(str) = %d\n", strlen(str));
	//printf("strlen(p) = %d\n", strlen(p));

}
void function3() {
	/*
		字符串初始化注意事项:
			字符串初始化时必须以\0结尾,否则打印时会出现"烫烫"等乱码情况
			1.char str[] = { 'a','b','c','d' };
			当不指定数组初始化大小时,如果没有手动指定\0,编译器不会自动在结尾添加\0
			2.char str[5] = { 'a','b','c','d' };
			当指定的大小大于实际初始化的内容时,编译器会自动在结尾添加\0
			3.char str[5] = { 'a','b','c','d','e'};
			当指定的长度被内容全部填充(不包括\0)时,全部打印时会出现乱码
		总结:
			如果不是明确长度大于内容长度时,必须手动添加\0在结尾,否则会在打印时出现乱码
	*/
	//char str[] = { 'a','b','c','d' };
	//char str[5] = { 'a','b','c','d' };
	char str[5] = { 'a','b','c','d','e'};
	printf("%d\n", sizeof(str));
	printf("%s\n",str);
}
void function4() {
	/*
		打印字符串
			1.下标法
			2.指针法
			两种都可以根据偏移从某个字符开始打印
			如果采用指针法,则结束条件可以直接设置为*p,原因:
				如果*p遍历到\0位置时,其\0的ascii码值为0,条件为false,不会继续执行
	*/
	char str[5] = { 'a','b','c','d','\0' };
	printf("%s\n",str + 2);
	for (int i = 2; i < 5; i++)
	{
		printf("%c ",str[i]);
	}
	printf("\n");
	for (char *p = str + 2; *p != '\0'; p++)
	{
		printf("%c ", *p);
	}
	printf("\n");
}
void main() {
	//function1();
	function2();
	//function3();
	//function4();
	system("pause");
}