#include<stdio.h>
#include<stdlib.h>
#include<Windows.h> //detours.h里有windows.h中的内容,需要先包括它
#include "detours.h"
#include "detver.h"

#pragma comment(lib,"detours.lib")

int (WINAPI *oldMessageBoxA)(
	HWND hWnd,
	LPCSTR lpText,
	LPCSTR lpCaption,
	UINT uType) = MessageBoxA;

int WINAPI newMessageBoxA(
	HWND hWnd,
	LPCSTR lpText,
	LPCSTR lpCaption,
	UINT uType) {
		printf("%s\n",lpText);
}

void hook() {
	//恢复原始的地址映射表,避免反复拦截
	DetourRestoreAfterWith();
	//开始一个新的事务，用于附加或取消拦截
	DetourTransactionBegin();
	//在当前事务中获取一个线程用于修改函数名所指向的地址
	DetourUpdateThread(GetCurrentThread());
	//使第二个参数上的函数拦截第一个参数上的函数
	DetourAttach((void**)&oldMessageBoxA, newMessageBoxA);
	//提交拦截事务
	DetourTransactionCommit();
}

void main() {
	MessageBoxA(0, "劫持前", "劫持", 0);

	hook();

	MessageBoxA(0, "劫持后", "劫持", 0);

	system("pause");
}
