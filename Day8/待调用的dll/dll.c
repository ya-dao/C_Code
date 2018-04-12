#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
_declspec(dllexport) void go() {
	MessageBoxA(0, "调用成功", "测试", 0);
}

_declspec(dllexport) void run(char* content) {
	MessageBoxA(0, content, "测试", 0);
}