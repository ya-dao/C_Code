#include<stdio.h>
#include<Windows.h>
void main() {

	//获取桌面的句柄
	HWND windowHandle = GetDesktopWindow();
	//获取桌面显示的上下文运行环境
	HDC windowDC = GetWindowDC(windowHandle);
	//获取内存中一个位图上下文运行环境
	HDC memoryDC = CreateCompatibleDC(0);
	HBITMAP bitmap = (HBITMAP)LoadImage(windowHandle,TEXT("1.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	SelectObject(memoryDC, bitmap);
	while (1) {
		BitBlt(windowDC, 0, 0, 500, 500, memoryDC, 0, 0, SRCCOPY);
	}
}