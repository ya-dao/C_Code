/*
	函数劫持即将原函数名所指向的地址进行修改,达到劫持的目的.
	目前可以使用detours express3.0工具进行任何函数的劫持
*/
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

void show() {
	MessageBoxA(0,"劫持前","test",0);
}

void hijack() {
	MessageBoxA(0,"劫持后","test",0);
}

void main() {
	void (*p)() = show;
	p();
	p = hijack;
	p();
}