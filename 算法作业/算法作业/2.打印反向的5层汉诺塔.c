//反向的从上往下大小顺序的汉诺塔,打印出5层的搬法,要求打印出每一步移动的盘子编号
#include<stdio.h>
#include<stdlib.h>

void reverseTower(int layers, char from, char temp, char to);
void tower(int layers, char from, char temp, char to);
void showMove(int layer, char from, char to);

int stepCount = 0;
void main() {
	int layers = 5;

	printf("按原顺序的搬法:\n");
	tower(layers, 'A', 'B', 'C');

	stepCount = 0;

	printf("颠倒顺序的搬法:\n");
	reverseTower(layers, 'A', 'B', 'C');

	system("pause");
}

/*
	将反向的汉诺塔顺序颠倒过来(开始是从上面是最大的,搬过去上面是最小的)
	要求:若有3个柱子,有2个盘子需要从A柱搬到C柱,且搬过去后上面是最小的
	思路:
		1.先将第(n-1)个从A搬到C
		2.再将第n个从A搬到B
*/
void reverseTower(int layers,char from,char temp,char to) {
	if (layers > 0) {
		reverseTower(layers - 1, from, temp, to);
		showMove(layers, from, to);
	}
}

/*
	反向的汉诺塔(开始是从上面是最大的,搬过去上面还是最大的)
	要求:若有3个柱子,有2个盘子需要从A柱搬到C柱,且搬过去后顺序不变
	思路:
		1.将第(n - 1)从A搬到B
		2.将第n个从A搬到C
		3.将第(n - 1)个从B搬到C
*/
void tower(int layers,char from,char temp,char to) {
	if (layers > 0) {
		tower(layers - 1, from, to, temp);
		showMove(layers, from, to);
		tower(layers - 1, temp, from,to);
	}
}
/*
显示每一个步移动的盘子编号和移动的方向
*/
void showMove(int layer, char from, char to) {
	printf("第%02d步:%d号盘子%c--->%c\n", ++stepCount, layer, from, to);
}