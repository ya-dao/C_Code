#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<Windows.h>
void run1(void *p) {
	MessageBoxA(NULL, "1", "1", 0);
}
void run2(void *p) {
	MessageBoxA(NULL, "2", "2", 0);
}
void run3(void *p) {
	MessageBoxA(NULL, "3", "3", 0);
}
void function1(HANDLE *pp) {
	void (*p[])(void *) = { run1,run2,run3 };
	for (int i = 0; i < 3; i++)
	{
		//(*(p + i))(NULL);
		//第二个参数传递0,将默认的栈大小复制过去
		*(pp + i) = _beginthread((*(p + i)),0,NULL);
		//异步中的同步处理
		//第一个参数传递句柄
		//第二个参数传递等待时间
		//WaitForSingleObject(*(pp + i),INFINITE);
	}
}
void main() {
	//栈上的Handle数组
	HANDLE handles[3];
	//堆上的Handle数组
	HANDLE *p = malloc(sizeof(void *) * 3);
	function1(handles);
	//WaitForSingle/MultipleObject可用于主线程设置退出条件
	//WaitForSingleObject(handles[0],INFINITE);
	//等待的句柄一旦结束,主线程随即退出,false,等待一个,适合只需要找出一个最快的结果的场合
	//如果为true,需要等待全部.适合等待最慢的那个结果的场合
	WaitForMultipleObjects(3,handles,FALSE,INFINITE);
	//system("pause");
}