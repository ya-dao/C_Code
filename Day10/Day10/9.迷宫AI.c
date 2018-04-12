#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>

#define N 5

void init(int map[N][N]) {
	time_t* times = NULL;
	srand(time(times));

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if ((rand() % 5) > 3) {
				map[i][j] = 2;
			}
		}
	}
	map[0][0] = 1;
}

void show(int map[N][N]) {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%d ",map[i][j]);
		}
		printf("\n");
	}
	printf("---------------\n");
}

void move(int map[N][N]) {
	char direction = 'a';
	int i = 0, j = 0;
	while (1) {
		int flag = 0;
		
		scanf("%c",&direction);
		getchar();	//吃掉回车键

		switch (direction) {
			case 'a':
			case 'A':
				{
					if (j > 0) {
						int temp = map[i][j];
						map[i][j] = map[i][j - 1];
						map[i][j - 1] = temp;
						j--;
						flag = 1;
					}
					break;
				}
			case 'd':
			case 'D':
				{
					if (j < 8) {
						int temp = map[i][j];
						map[i][j] = map[i][j + 1];
						map[i][j + 1] = temp;
						j++;
						flag = 1;
				}
				break;
			}
			case 'w':
			case 'W':
			{
				if (i > 0) {
					int temp = map[i][j];
					map[i][j] = map[i - 1][j];
					map[i - 1][j] = temp;
					i--;
					flag = 1;
				}
				break;
			}
			case 's':
			case 'S':
			{
				if (i < 8) {
					int temp = map[i][j];
					map[i][j] = map[i + 1][j];
					map[i + 1][j] = temp;
					i++;
					flag = 1;
				}
				break;
			}
		}
		if (map[9][9] == 1) {
			printf("已到达终点,游戏结束!\n");
			break;
		}
		else if(flag == 1){
			show(map);
		}
		else if(flag == 0){
			printf("非法边界操作\n");
		}
	}
}

void autoOutward(int map[N][N],int i,int j) {
	if(i == (N - 1) && j == (N - 1)){
		printf("已到达终点,游戏结束!\n"); 
		return;
	}
	else {
		//走过的路标识为3
		map[i][j] = 3;
		show(map);
		Sleep(1000);
		//向右
		if (j < (N - 1)) {
			if (map[i][j + 1] != 2 && map[i][j + 1] != 3) {
				autoOutward(map, i, ++j);
			}
		}
		//向上
		if (i > 0) {
			if (map[i - 1][j] != 2 && map[i - 1][j] != 3) {
				autoOutward(map, --i, j);
			}
		}
		//向左
		if (j > 0) {
			if (map[i][j - 1] != 2 && map[i][j - 1] != 3) {
				autoOutward(map, i, --j);
			}
		}
		//向下
		if (i < (N - 1)) {
			if (map[i + 1][j] != 2 && map[i + 1][j] != 3) {
				autoOutward(map, ++i, j);
			}
		}
	}
}

void main(){
	int map[N][N] = { 0 };
	init(map);
	//show(map);

	//move(map);

	autoOutward(map,0,0);

	system("pause");
}