#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
/*
	通过播放一段音频和更换桌面来达到恐怖效果
*/
void main() {
	//20:修改桌面
	//0:默认参数0
	// : 图片路径
	//3:即刻生效
	SystemParametersInfo(20, 0, "E:\\程序设计\\C++\\C语言视频\\20150409C语言4月份\\20150409C语言\\资源\\4.jpg", 3);
	ShellExecuteA(0, "open", "E:\\程序设计\\C++\\C语言视频\\20150409C语言4月份\\20150409C语言\\资源\\1.mp3", 0, 0, 0);
}