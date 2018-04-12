#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

//pragma comment(linker,"/subsystem:"windows" /entry:"mainCRTStartup"")
//linker连接,将dos编译改成window模式编译,可以去掉Dos窗口,同时dos里面的操作,如输入输出不可用
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

void main() {
	MessageBoxA(0, "去掉Dos界面", "Window模式编译", 0);
	printf("还能看到么?\n");
	int num = 0;
	scanf("%d",&num);
}

//导出接口用于调用
_declspec(dllexport) void go() {

	MessageBoxA(0, "辅助注入成功", "村长提示", 0);

}