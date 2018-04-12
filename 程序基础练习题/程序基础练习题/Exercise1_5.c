//5.请实现马的走路，请用1代表马位置，0代表空地，2代表憋腿。 
//输入1,2,3,4,6,7,8,9分别代表马的8个方向，控制行走，模拟马的运动
#include<stdio.h>
#include<stdlib.h>
#define N 5

void show(int map[N][N]);
void move(int map[N][N], int *rowIndex, int *columnIndex);
int isGameOver(int rowIndex, int columnIndex);

void main() {
	int rowIndex = 0, columnIndex = 0;
	int map[N][N] = {
		1,0,2,0,0,
		0,2,0,2,0,
		0,2,0,0,2,
		0,0,2,0,0,
		0,2,0,2,0
	};

	do {
		show(map);
		move(map, &rowIndex, &columnIndex);
	} while (!isGameOver(rowIndex,columnIndex));
}

void move(int map[N][N],int *rowIndex,int *columnIndex) {
	char direction = getchar();
	getchar();

	switch (direction)
	{
		case '1':
		if ((*rowIndex < N - 2) && (*columnIndex > 0)) {
			if (map[(*rowIndex) + 1][*columnIndex] != 2) {
				map[(*rowIndex) + 2][(*columnIndex) - 1] = map[*rowIndex][*columnIndex];
				map[*rowIndex][*columnIndex] = 0;

				*rowIndex = (*rowIndex) + 2;
				*columnIndex = (*columnIndex) - 1;
			}
		}
		break;
	case '2':
		if ((*rowIndex < N - 2) && (*columnIndex < N - 1)) {
			if (map[(*rowIndex) + 1][*columnIndex] != 2) {
				map[(*rowIndex) + 2][(*columnIndex) + 1] = map[*rowIndex][*columnIndex];
				map[*rowIndex][*columnIndex] = 0;

				*rowIndex = (*rowIndex) + 2;
				*columnIndex = (*columnIndex) + 1;
			}
		}
		break;
	case '3':
		if ((*rowIndex < N - 1) && (*columnIndex < N - 2)) {
			if (map[*rowIndex][(*columnIndex) + 1] != 2) {
				map[(*rowIndex) + 1][(*columnIndex) + 2] = map[*rowIndex][*columnIndex];
				map[*rowIndex][*columnIndex] = 0;

				*rowIndex = (*rowIndex) + 1;
				*columnIndex = (*columnIndex) + 2;
			}
		}
		break;
	case '4':
		if ((*rowIndex > 0) && (*columnIndex < N - 2)) {
			if (map[*rowIndex][(*columnIndex) + 1] != 2) {
				map[(*rowIndex) - 1][(*columnIndex) + 2] = map[*rowIndex][*columnIndex];
				map[*rowIndex][*columnIndex] = 0;

				*rowIndex = (*rowIndex) - 1;
				*columnIndex = (*columnIndex) + 2;
			}
		}
		break;
	case '5':
		if ((*rowIndex > 1) && (*columnIndex < N - 1)) {
			if (map[(*rowIndex) - 1][*columnIndex] != 2) {
				map[(*rowIndex) - 2][(*columnIndex) + 1] = map[*rowIndex][*columnIndex];
				map[*rowIndex][*columnIndex] = 0;

				*rowIndex = (*rowIndex) - 2;
				*columnIndex = (*columnIndex) + 1;
			}
		}
		break;
	case '6':
		if ((*rowIndex > 1) && (*columnIndex > 0)) {
			if (map[(*rowIndex) - 1][*columnIndex] != 2) {
				map[(*rowIndex) - 2][(*columnIndex) - 1] = map[*rowIndex][*columnIndex];
				map[*rowIndex][*columnIndex] = 0;

				*rowIndex = (*rowIndex) - 2;
				*columnIndex = (*columnIndex) - 1;
			}
		}
		break;
	case '7':
		if ((*rowIndex > 0) && (*columnIndex > 1)) {
			if (map[*rowIndex][(*columnIndex) - 1] != 2) {
				map[(*rowIndex) - 1][(*columnIndex) - 2] = map[*rowIndex][*columnIndex];
				map[*rowIndex][*columnIndex] = 0;

				*rowIndex = (*rowIndex) - 1;
				*columnIndex = (*columnIndex) - 2;
			}
		}
		break;
	case '8':
		if ((*rowIndex < N - 1) && (*columnIndex > 1)) {
			if (map[*rowIndex][(*columnIndex) - 1] != 2) {
				map[(*rowIndex) + 1][(*columnIndex) - 2] = map[*rowIndex][*columnIndex];
				map[*rowIndex][*columnIndex] = 0;

				*rowIndex = (*rowIndex) + 1;
				*columnIndex = (*columnIndex) - 2;
			}
		}
		break;
	}
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

int isGameOver(int rowIndex,int columnIndex) {
	if (rowIndex == N - 1 && columnIndex == N - 1) {
		return 1;
	}
	else {
		return 0;
	}
}