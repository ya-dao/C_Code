#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<math.h>

#define R 200
#define PI 3.1415926
#define LEFT 1
#define RIGHT 2

void main() {
	
	system("start notepad");
	Sleep(2000);

	HWND window = FindWindowA("Notepad", "无标题 - 记事本");
	if (window != NULL) {
		int x = 900;
		int y = 350;
		int angle = 0;
		int flag = RIGHT;
		/*
			1.由于是要循环转360度,所以我们需要将弧度转化为角度来计算三角函数值,使其转得像个圆.
			2.弧度和角度的关系百度sin90和sin90度的区别
			3.sin(90)是指的弧度,单位被省略
			4.sin(90 * PI / 180)是指的角度
			5.角度 = 弧度 * PI / 180
			*/
		while (1) {
			printf("转\n");
			if (angle == 180 && flag == RIGHT) {
				flag = LEFT;
				angle = 0;
				//修改圆心
				x = 500;
			}
			else if(angle == 0 && flag == LEFT){
				flag = RIGHT;
				angle = 180;
				//修改圆心
				x = 900;
			}

			SetWindowPos(
				window,
				0,
				x + R * cos(angle * PI / 180),
				y - R * sin(angle * PI / 180),
				100,
				100,
				0
			);
			
			angle = ((angle + 1) % 360);
			Sleep(5);
		}
	}
	else {
		printf("窗口不存在\n");
	}
	system("pause");
}
