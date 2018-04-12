//正常的从下往上大小顺序的汉诺塔,打印出5层的搬法,要求打印出每一步移动的盘子编号
#include<stdio.h>
#include<stdlib.h>

void tower(int layers, char from, char temp, char to);
void showMove(int layer, char from, char to);

int stepCount = 0;
void main() {
	int layers = 5;
	tower(layers, 'A', 'B', 'C');
	system("pause");
}
/*
	layers:塔的总层数
	from:起始的柱子
	temp:中转的柱子
	to:目标柱子
	要求:若有3个柱子,有2个盘子需要从A柱搬到C柱,且搬过去后顺序不能变
	思路:
		1.先将(n - 1)个盘子从A搬到B
		2.再将第n个盘子从A搬到C
		3.再将(n - 1)个盘子从B搬到C
*/
void tower(int layers,char from,char temp,char to) {
	if (layers > 0) {
		tower(layers - 1, from, to, temp);
		showMove(layers,from,to);
		tower(layers - 1, temp, from, to);
	}
}
/*
	显示每一个步移动的盘子编号和移动的方向
*/
void showMove(int layer,char from,char to) {
	printf("第%02d步:%d号盘子%c--->%c\n",++stepCount,layer,from,to);
}