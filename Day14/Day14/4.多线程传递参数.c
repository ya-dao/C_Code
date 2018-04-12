#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<Windows.h>
void run(void *p) {
	MessageBox(NULL, "一套8万8", "暴走加连发", 0);
}

void runWithParameter(void *p) {
	//将void*转换成int*
	int *p1 = p;
	char str[10] = { 0 };
	//将int数值加入到字符串中
	sprintf(str,"一套%d万8",*p1);
	MessageBox(NULL, str, "暴走加连发", 0);
}
void main() {
	int array[] = { 4,5,6,7,8 };
	for (int i = 0; i < 5; i++)
	{
		//_beginthread(run, 0, NULL);
		//开启多线程并传递参数,注意多线程访问同一变量冲突的问题
		_beginthread(runWithParameter,0,(array + i));
	}
	system("pause");
}