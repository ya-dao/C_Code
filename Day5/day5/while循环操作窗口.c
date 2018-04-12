#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
/*
	通过Win32Api操作窗口移动
*/
int main() {
	//通过类名和标题获取窗口句柄,如果找不到则返回NULL
	HWND win = FindWindowA("TXGuiFoundation", "QQ");
	//通过句柄操作该窗口是否显示
	ShowWindow(win,SW_SHOW);
	int i = 0;
	while (i <= 1080) {
		//通过句柄设置窗口是否显示,坐标,窗体大小
		SetWindowPos(win, NULL, i * 1920 / 1080, i, 430, 333, 0);
		if (i % 2 == 0) {
			ShowWindow(win, SW_HIDE);
		}
		else {
			ShowWindow(win, SW_SHOW);
		}
		i++;
		Sleep(20);
	}
	return 0;
}