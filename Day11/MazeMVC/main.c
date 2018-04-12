/*
	需求:按照MVC的结构设计迷宫
		M:model数据层
		V:view显示层
		C:controller控制层
*/
#include "controller.h"
#include "model.h"
#include "view.h"

void main() {
	int i = 0, j = 0;
	int flag = 0;
	
	display(maze);

	//flag = move(maze, i, j);
	AIFindPath(maze, i, j, &flag);

	if (flag) {
		printf("恭喜走出来\n");
	}

	system("pause");
}