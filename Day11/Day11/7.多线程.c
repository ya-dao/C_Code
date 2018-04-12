#include<Windows.h>
#include<stdlib.h>
/*
	Win32中的多线程创建
*/
DWORD WINAPI myMessage(LPVOID lp) {
	MessageBoxA(0, "对话框", "test", 0);
}
void main() {
	HANDLE handle;
	DWORD threadId = 0;
	for (int i = 0; i < 5; i++)
	{
		handle = CreateThread(
					NULL,//安全属性
					NULL,//堆栈大小
					myMessage,//函数入口点
					NULL,//函数的参数
					0,//立刻执行
					&threadId//线程ID
		);

		//多线程中的同步
		WaitForSingleObject(handle,INFINITE);
	}
	system("pause");
}