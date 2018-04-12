#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<process.h>//使用线程必须要导入该头文件
/*
	使用多线程需要注意的事项:
		1.线程必须是一个函数,函数名不限制,但是参数必须是void*类型
		2.开启线程的方式为_beginthread(函数地址,堆栈大小或 0,参数或NULL);
		3.如果主线程退出,则子线程也会随之挂掉
		
*/
void testThread(void *p) {
	MessageBoxA(0, "测试", "测试", 0);
}
void main() {
	//单线程打开5个对话框
	/*for (int i = 0; i < 5; i++)
	{
		MessageBoxA(0, "测试", "测试", 0);
	}*/
	for (int i = 0; i < 5; i++)
	{
		_beginthread(testThread, 0, NULL);
	}

	system("pause");//保证主线程不死,否则子线程也会跟着死掉
}