#include<stdio.h>
#include<stdlib.h>
#define ELEM_TYPE int
#define MAX_ELEMENT INT_MAX
typedef struct Matric{
	ELEM_TYPE *vexs;	//顶点信息
	ELEM_TYPE **matric;	//邻接矩阵,必定是一个方阵
	int vexCount,arcCount;	//当前顶点数和边数
}*MatricGraph;
void initMatricGraph(MatricGraph *graph,int vexCount, int arcCount);
void createMatricGraph(MatricGraph *graph,int *vexs,int (*arcs)[3],int arcInfoLength);
void output(MatricGraph graph);