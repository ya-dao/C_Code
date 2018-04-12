#include "view.h"
#include "model.h"

int move(int maze[N][N], int i, int j);
int left(int maze[N][N], int* i, int* j);
int right(int maze[N][N], int* i, int* j);
int up(int maze[N][N], int* i, int* j);
int down(int maze[N][N], int* i, int* j);

void AIFindPath(int maze[N][N],int i,int j,int* flag);