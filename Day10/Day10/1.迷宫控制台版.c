#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROW 9
#define COL 9
void show(int map[ROW][COL]) {
	printf("---------------\n");
	for (int i = 0; i < ROW;i++) {
		for (int j = 0; j < COL;j++) {
			printf("%d ",map[i][j]);
		}
		printf("\n");
	}
}
void initData(int map[ROW][COL]) {
	for (int i = 0; i < ROW;i++) {
		for (int j = 0; j < COL; j++)
		{
			map[i][j] = 0;
		}
	}
}
void initObstacle(int map[ROW][COL]) {
	srand(time(NULL));
	for (int i = 0; i < ROW;i++) {
		int index = rand() % COL;
		map[i][index] = 2;
	}
}
void move(int map[ROW][COL]) {
	int x = 0, y = 0;
	char direction = 0;
	while (1) {
		direction = getchar();
		getchar();//接收输入完成后的那个回车

		switch (direction) {
			case 'A':
			case 'a': 
				{
					if (y - 1 >= 0 && map[x][y - 1] != 2) {
						int temp = map[x][y];
						map[x][y] = map[x][y - 1];
						map[x][y - 1] = temp;

						y--;
					}
					break;
				}
			case 'S':
			case 's':
			{
				if (x + 1 < 9 && map[x + 1][y] != 2) {
					int temp = map[x][y];
					map[x][y] = map[x + 1][y];
					map[x + 1][y] = temp;

					x++;
				}
				break;
			}
			case 'D':
			case 'd':
			{
				if (y + 1 < 9 && map[x][y + 1] != 2) {
					int temp = map[x][y];
					map[x][y] = map[x][y + 1];
					map[x][y + 1] = temp;
					
					y++;
				}
				break;
			}
			case 'W':
			case 'w':
			{
				if (x - 1 >= 0 && map[x - 1][y] != 2) {
					int temp = map[x - 1][y];
					map[x - 1][y] = map[x][y];
					map[x][y] = temp;

					x--;
				}
				break;
			}
		}
		show(map);
		if (x == ROW - 1 && y == COL - 1) {
			printf("YOU WIN!");
			break;
		}
	}
}

void main() {
	int map[ROW][COL] = { 0 };
	//initData(map);

	int x = 0;
	int y = 0;
	map[x][y] = 1;
	show(map);

	initObstacle(map);
	show(map);

	move(map);

	system("pause");
}