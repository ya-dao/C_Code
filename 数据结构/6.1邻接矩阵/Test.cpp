#include "MatricGraph.h"
#define VEX_COUNT 6
#define ARC_COUNT 8
void main(){
	MatricGraph graph = NULL;
	int vexs[] = {1,2,3,4,5,6};
	//原始数组,但是从0开始,所以-1
	//int arcs[][3] = {{1,2,5},{1,4,7},{2,3,4},{3,6,9},{4,3,5},{4,6,6},{5,4,5},{6,5,1}};
	int arcs[][3] = { { 0,1,5 },{ 0,3,7 },{ 1,2,4 },{ 2,5,9 },{ 3,2,5 },{ 3,5,6 },{ 4,3,5 },{ 5,4,1 } };
	initMatricGraph(&graph,VEX_COUNT, ARC_COUNT);
	createMatricGraph(&graph,vexs,arcs,3);
	output(graph);

	system("pause");
}