#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
/*
	需求:
		自动打开浏览器,完成自动输入搜索内容,然后打开预先选定项
*/

/*
	1.通过浏览器打开指定网站
*/
void open(char* url) {
	ShellExecuteA(0, "open", url, "", "", 1);
}

/*
	输入搜索内容
	keybd_event注意:
		1.硬件编码不是虚拟按键值,所以不用填,填了反而打不了汉字
		2.第三个参数除了松开事件之外,填0即可,否则使用组合键会有问题
		3.第四个参数就不用填了,一般都不用
*/
void input() {
	//1.输入英文
	keybd_event('S', 0x53, 0, 0);
	keybd_event('S', 0x53, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('U', 0x55, 0, 0);
	keybd_event('U', 0x55, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('P', 0x50, 0, 0);
	keybd_event('P', 0x50, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('A', 0x41, 0, 0);
	keybd_event('A', 0x41, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('R', 0x52, 0, 0);
	keybd_event('R', 0x52, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('C', 0x43, 0, 0);
	keybd_event('C', 0x43, KEYEVENTF_KEYUP, 0);
	//2.切换输入法
	keybd_event(VK_LCONTROL, 0, 0, 0);
	Sleep(40);
	keybd_event(VK_SPACE, 0, 0, 0);
	Sleep(40);
	keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
	Sleep(50);
	keybd_event(VK_LCONTROL, 0, KEYEVENTF_KEYUP, 0);
	Sleep(50);
	//3.输入汉字
	keybd_event('C', 0, 0, 0);
	keybd_event('C', 0, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('F', 0, 0, 0);
	keybd_event('F', 0, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('H', 0, 0, 0);
	keybd_event('H', 0, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('K', 0, 0, 0);
	keybd_event('K', 0, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event(VK_SPACE, 0, 0, 0);
	keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('G', 0, 0, 0);
	keybd_event('G', 0, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('U', 0, 0, 0);
	keybd_event('U', 0, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('C', 0, 0, 0);
	keybd_event('C', 0, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('K', 0, 0, 0);
	keybd_event('K', 0, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event(VK_SPACE, 0, 0, 0);
	keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event(VK_RETURN, 0, 0, 0);
	keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
}

/*
	模拟鼠标操作,打开第一个链接
	1.如果不设置MOUSEEVENTF_ABSOLUTE,则鼠标的移动是相对于当前位置.设置之后,整个屏幕会被分割成65536 * 65535,所以移动的像素需要通过公式计算
	2.第二和第三个参数如果不是鼠标移动事件就不用填,如果是就填
	3.第四和第五个不填
*/
void moveMouse() {
	Sleep(1000);
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, 250 * 65535 / 1920, 220 * 65535 / 1080, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
/*
	通过cmd命令关闭浏览器进程
*/
void close() {
	system("taskkill /f /im chrome.exe");
}
int main() {
	char* url = "http://www.baidu.com";
	
	open(url);
	Sleep(1500);
	input();
	Sleep(100);
	moveMouse();
	Sleep(5000);
	close();
	return 0;
}
