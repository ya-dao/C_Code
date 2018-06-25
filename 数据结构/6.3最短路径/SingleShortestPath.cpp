#define VEX_COUNT 6
#define ARC_COUNT 8
#include "MatricGraph.h"
#include "Stack.h"
void show(int *array,int length){
	for(int i = 0;i < length;i++){
		printf("%d ",array[i]);
	}
	printf("\n");
}
void debug(MatricGraph graph,int *paths,int *distances) {
	printf("%s\n", "-----------debug-------------");
	show(graph->positions, graph->vexCount);
	show(paths, graph->vexCount);
	show(distances, graph->vexCount);
}
void getPathAndDistance(int *paths,int *distances,int startVertex) {
	Stack *stack = NULL;
	initStack(&stack);
	for (int i = 0; i < VEX_COUNT; i++)
	{
		if (i != startVertex) {
			printf("%d->%d:\n", startVertex,i);
			printf("路径长度:%d\n",distances[i]); 
			int parent = paths[i];
			if (parent != -1) {
				clearStack(&stack);
				push(stack, i);
			}
			while (parent != -1) {
				push(stack,parent);
				parent = paths[parent];
			}
			printf("路径:");
			while (isStackEmpty(stack) != 1) {
				if (getLength(stack) == 1) {
					printf("%d\n",pop(stack));
				}
				else {
					printf("%d->",pop(stack));
				}
			}
			printf("\n");
		}
	}
	destroyStack(&stack);
}
void shortestPath(MatricGraph graph,int startVertex){
	//中间经过的点
	int *paths = (int *)calloc(sizeof(int),graph->vexCount);
	//最短的距离值
	int *distances = (int *)calloc(sizeof(int),graph->vexCount);
	//1.划分顶点集
	for(int i = 0;i < graph->vexCount;i++){
		graph->positions[i] = RIGHT;
		distances[i] = graph->matric[startVertex][i];
		if(distances[i] != MAX_ELEMENT){
			paths[i] = startVertex;
		}else{
			paths[i] = -1;
		}
	}
	graph->positions[startVertex] = LEFT;
	
	//debug(graph,paths,distances);
	
	//3.选择距离最小的点
	for(int i = 1;i < graph->vexCount;i++){
		//printf("\n%d阶段:",i);
		//逐个扫描获取最小值的点,并记录其下标
		int min = MAX_ELEMENT;
		int vertexIndex = 0;
		for(int j = 0;j < graph->vexCount;j++){
			//前提条件是两个点分别在两边
			if(graph->positions[j] == RIGHT && distances[j] < min){
				vertexIndex = j;
				min = distances[j];
			}
		}
		graph->positions[vertexIndex] = LEFT;

		//debug(graph, paths, distances);
		
		//4.更新distance的值
		for(int j = 0;j < graph->vexCount;j++){
			if(graph->positions[j] == RIGHT &&
				distances[j] > distances[vertexIndex] + graph->matric[vertexIndex][j]){
				//更新当前最短距离值
				distances[j] = distances[vertexIndex] + graph->matric[vertexIndex][j];
				//上一个路径上的点
				paths[j] = vertexIndex;
			}
		}
		//debug(graph, paths, distances);
	}
	for (int i = 0; i < graph->vexCount; i++)
	{
		if (graph->positions[i] == RIGHT) {
			graph->positions[i] = LEFT;
		}
	}
	//debug(graph, paths, distances);
	getPathAndDistance(paths,distances,startVertex);
}

void main(){
	MatricGraph graph = NULL;
	int vexs[] = {1,2,3,4,5,6};
	//原始数组,但是从0开始,所以-1
	int arcs[][3] = { { 0,2,10 },{ 0,4,30},{ 0,5,100},{ 1,2,5},{ 2,3,50 },{ 3,5,10 },{ 4,3,20 }	,{ 4,5,60 }	};

	initMatricGraph(&graph,VEX_COUNT, ARC_COUNT);
	createMatricGraph(&graph,vexs,arcs,3);
	output(graph);
	shortestPath(graph,0);
	system("pause");
}