#include "MatricGraph.h"
/*
	malloc申请一个二维数组的三种方式:(3行2列)
		一.用二级指针(推荐这种,增加灵活性)
			1.先申请一个指针数组(形如int *p[3],可写成int **p)
			int **a = (int **)malloc(sizeof(int *) * 3);
			2.对其每一个指针数组元素申请空间
			for(int i = 0;i < 2;i++){
				a[i] = (int *)malloc(sizeof(int) * 2);
			}
		二.用数组指针
			int (*a)[2] = (int (*)[2])malloc(sizeof(int) * 3 * 2);
		三.用一维数组代替二维数组
			int *a = (int *)malloc(sizeof(int) * 3 * 2);
			1.访问的时候需要手动计算换行需要的位移,如a[3][2]的访问:
			*(a + 3 * 2 + 1)
*/
void initMatricGraph(MatricGraph *graph,int vexCount, int arcCount){
	//1.先初始化图
	(*graph) = (MatricGraph)malloc(sizeof(Matric));
	//2.初始化里面的成员
	(*graph)->matric = (ELEM_TYPE **)malloc(sizeof(int *) * vexCount);
	for (int i = 0; i < vexCount; i++)
	{
		(*graph)->matric[i] = (int *)malloc(sizeof(int) * vexCount);
	}
	
	(*graph)->arcCount = arcCount;
	(*graph)->vexCount = vexCount;

	(*graph)->vexs = (ELEM_TYPE *)malloc(sizeof(ELEM_TYPE) * vexCount);
	for(int i = 0;i < (*graph)->vexCount;i++){
		(*graph)->vexs[i] = 0;
	}

	(*graph)->positions = (ELEM_TYPE *)calloc(sizeof(ELEM_TYPE),vexCount);

	for(int i = 0;i < (*graph)->vexCount;i++){
		for(int j = 0;j < (*graph)->vexCount;j++){
			(*graph)->matric[i][j] = MAX_ELEMENT;
		}
	}
}
/*
	graph:邻接矩阵的地址
	vexs:传过来的顶点集
	arcs:边信息集合
	arcInfoLength:每条边信息所占长度
*/
void createMatricGraph(MatricGraph *graph,int *vexs,int (*arcs)[3],int arcInfoLength){
	for(int i = 0;i < (*graph)->vexCount;i++){
		(*graph)->vexs[i] = vexs[i];
	}
	for(int i = 0;i < (*graph)->arcCount;i++){
		int start = arcs[i][0];
		int end = arcs[i][1];
		int weight = arcs[i][2];
		(*graph)->matric[start][end] = weight;
	}
}
void output(MatricGraph graph){
	printf("\n顶点集：\n");
	for(int i = 0;i < graph->vexCount;i++){
		printf("%d ",graph->vexs[i]);
	}
	printf("\n矩阵：\n");
	for(int i = 0;i < graph->vexCount;i++){
		for(int j = 0;j < graph->vexCount;j++){
			printf("%-10d ",graph->matric[i][j]);
		}
		printf("\n");
	}

}