#include<stdlib.h>
#include<stdio.h>
#include<Windows.h>
void main() {
	HWND win = FindWindowA("#32770", "MFCApplication1");
	if (win == NULL) {
		printf("该窗体不存在\n");
	}
	else {
		//设置窗口标题
		//SetWindowText(win, "表情包");
		//Sleep(5000);
		//显示/隐藏窗口
		//ShowWindow(win, 0);
		//Sleep(5000);
		//ShowWindow(win, 1);
		//寻找子窗口
		HWND child = FindWindowExA(win, 0, "Button", "Button1");
			//禁用窗口
			//EnableWindow(child, 0);
			//Sleep(5000);
			//EnableWindow(child, 1);
		//模拟操作系统窗体程序发送各种消息
		//发送关闭消息
		//SendMessageA(child,WM_CLOSE,0,0);
		//发送点击消息,如果目标窗口没有获得焦点,需要发送两次点击消息,第一个消息是获取焦点
		//SendMessageA(child,BM_CLICK,0,0);
		//SendMessageA(child, BM_CLICK, 0, 0);

		//找到编辑框的句柄,向其发送字符,如果是发送字符,第一个是发送的字符,第二个是数量
		HWND edit = FindWindowExA(win, 0, "Edit", "");
		SendMessageA(edit, WM_CHAR, 65, 2);
		SendMessageA(edit, WM_GETTEXT, 0, 0);
	}
}