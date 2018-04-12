#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<Windows.h>
#include<time.h>
void setTitle(void *p) {
	int seconds = 1;
	char title[100] = { 0 };
	while (1) {
		sprintf(title, "title µ±Ç°µÚ%dÃë", seconds);
		system(title);
		seconds++;
		Sleep(1000);
	}
}
void setColor(void *p) {
	srand(time(NULL));
	char color[100] = { 0 };
	int frontColor = 0;
	int bgColor = 0;
	while (1) {
		frontColor = rand() % 16;
		bgColor = rand() % 16;
		sprintf(color, "color %x%x", frontColor, bgColor);
		system(color);
		Sleep(1000);
	}
}
void main() {
	_beginthread(setTitle, 0, 0);
	_beginthread(setColor, 0, 0);
	system("pause");
}