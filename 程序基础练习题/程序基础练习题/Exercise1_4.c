//请实现迷宫，不许使用while
#include<stdio.h>
#include<stdlib.h>
#define N 5

void showMaze(int maze[N][N]);
void move(int maze[N][N], int *rowIndex, int *columnIndex);
int isGameOver(int rowIndex, int columnIndex);
void AIAutoMove(int maze[N][N], int rowIndex, int columnIndex,int *isOver);

void main() {
	int rowIndex = 0, columnIndex = 0;
	int isOver = 0;
	int maze[N][N] = { 
		1,0,2,0,0,
		2,0,2,0,0,
		0,0,0,2,0,
		2,2,0,0,0,
		0,0,2,2,0,
	};

	/*do {
		showMaze(maze);
		move(maze, &rowIndex, &columnIndex);
	} while (!isGameOver(rowIndex,columnIndex));
	printf("逃脱成功,恭喜!!!\n");*/

	AIAutoMove(maze, rowIndex, columnIndex, &isOver);
	if (isOver)
	{
		printf("逃脱成功,恭喜!!!\n");
	}
	else {
		printf("无解!!!\n");
	}

	system("pause");
}

void showMaze(int maze[N][N]) {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%d ",maze[i][j]);
		}
		printf("\n");
	}
	printf("--------------\n");
}

void move(int maze[N][N],int *rowIndex,int *columnIndex) {
	char direction = getchar();
	getchar();

	switch (direction) {
	case 'w':
	case 'W':
		if (*rowIndex > 0 && 
			maze[*rowIndex - 1][*columnIndex] < 2) {
			int temp = maze[*rowIndex][*columnIndex];
			maze[*rowIndex][*columnIndex] = 
				maze[*rowIndex - 1][*columnIndex];
			maze[*rowIndex - 1][*columnIndex] = temp;

			(*rowIndex)--;
		}
		break;
	case 'a':
	case 'A':
		if (*columnIndex > 0 &&
			maze[*rowIndex][*columnIndex - 1] < 2) {
			int temp = maze[*rowIndex][*columnIndex];
			maze[*rowIndex][*columnIndex] =
				maze[*rowIndex][*columnIndex - 1];
			maze[*rowIndex][*columnIndex - 1] = temp;

			(*columnIndex)--;
		}
		break;
	case 's':
	case 'S':
		if (*rowIndex < N - 1 &&
			maze[*rowIndex + 1][*columnIndex] < 2) {
			int temp = maze[*rowIndex][*columnIndex];
			maze[*rowIndex][*columnIndex] =
				maze[*rowIndex + 1][*columnIndex];
			maze[*rowIndex + 1][*columnIndex] = temp;

			(*rowIndex)++;
		}
		break;
	case 'd':
	case 'D':
		if (*columnIndex < N - 1 &&
			maze[*rowIndex][*columnIndex + 1] < 2) {
			int temp = maze[*rowIndex][*columnIndex];
			maze[*rowIndex][*columnIndex] =
				maze[*rowIndex][*columnIndex + 1];
			maze[*rowIndex][*columnIndex + 1] = temp;

			(*columnIndex)++;
		}
		break;
	}
}

int isGameOver(int rowIndex,int columnIndex) {
	if ((rowIndex == N - 1) && (columnIndex == N - 1)) {
		return 1;
	}
	else {
		return 0;
	}
}

void AIAutoMove(int maze[N][N],int rowIndex,int columnIndex,int *isOver) {
	showMaze(maze);

	if (isGameOver(rowIndex,columnIndex)) {
		*isOver = 1;
		return;
	}
	if (1 == *isOver) {
		return;
	}

	if (columnIndex < N - 1 && maze[rowIndex][columnIndex + 1] < 2 && !(*isOver)) {
		int temp = maze[rowIndex][columnIndex];
		maze[rowIndex][columnIndex] =
			maze[rowIndex][columnIndex + 1];
		maze[rowIndex][columnIndex + 1] = temp;

		maze[rowIndex][columnIndex] = 3;

		AIAutoMove(maze, rowIndex, columnIndex + 1,isOver);
	}
	if (rowIndex < N - 1 && maze[rowIndex + 1][columnIndex] < 2 && !(*isOver)) {
		int temp = maze[rowIndex][columnIndex];
		maze[rowIndex][columnIndex] =
			maze[rowIndex + 1][columnIndex];
		maze[rowIndex + 1][columnIndex] = temp;

		maze[rowIndex][columnIndex] = 3;
		AIAutoMove(maze, rowIndex + 1, columnIndex, isOver);
	}
	if (columnIndex > 0 && maze[rowIndex][columnIndex - 1] < 2 && !(*isOver)) {
		int temp = maze[rowIndex][columnIndex];
		maze[rowIndex][columnIndex] =
			maze[rowIndex][columnIndex - 1];
		maze[rowIndex][columnIndex - 1] = temp;

		maze[rowIndex][columnIndex] = 3;
		AIAutoMove(maze, rowIndex, columnIndex - 1, isOver);
	}
	if (rowIndex > 0 && maze[rowIndex - 1][columnIndex] < 2 && !(*isOver)) {
		int temp = maze[rowIndex][columnIndex];
		maze[rowIndex][columnIndex] =
			maze[rowIndex - 1][columnIndex];
		maze[rowIndex - 1][columnIndex] = temp;

		maze[rowIndex][columnIndex] = 3;
		AIAutoMove(maze, rowIndex - 1, columnIndex, isOver);
	}
	maze[rowIndex][columnIndex] = 4;
}