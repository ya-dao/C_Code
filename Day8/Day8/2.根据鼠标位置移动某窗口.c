#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
/*
	通过getCursorPos获取当前鼠标位置并保存至Point结构体中.
	然后通过setWindowPosition()来设置窗口位置
*/
void main() {
	POINT point;
	
	HWND win = FindWindowA("TXGuiFoundation", "QQ");
	if (win == NULL) {
		printf("该窗口不存在\n");
	}else{
		while (1) {
			GetCursorPos(&point);
			SetWindowPos(win, 0, point.x + 200, point.y + 200, 300, 300, 1);
		}
	}
	system("pause");
}