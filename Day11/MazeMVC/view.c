#include "view.h"

void display(int maze[N][N]) {
	printf("-------------------------\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%d ",maze[i][j]);
		}

		printf("\n");
	}
}