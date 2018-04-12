#include<stdio.h>
#include<stdlib.h>
/*
	大致思路:
		大顶堆:任何一个父结点都必然大于他的子结点
		小顶堆:任何一个父结点都必然小于它的子结点
		构建一个堆,时刻保持数组的堆序性,大顶堆的情况下,最上面的元素必然是最大的.
		排序的时候只需要将最顶端的元素和最后一个元素交换,再次调整其结构,使之满足堆序性即可

*/
#define N 10
void show(int *p) {
	for (int i = 0; i < N; i++)
	{
		printf("%d ",p[i]);
	}
	printf("\n");
}
void swap(int *pA,int *pB) {
	int temp = *pA;
	*pA = *pB;
	*pB = temp;
}
void heap(int *p,int length) {
	/*
		堆可以用于查找最大值
	*/
	for (int i = length; i > 0; i--)
	{
		int parent = i / 2;
		int maxChild = 2 * parent + 1;
		while (maxChild < length) {
			if (maxChild < length - 1 && p[maxChild] < p[maxChild + 1])
			{
				maxChild++;
			}
			if (p[maxChild] > p[parent])
			{
				swap(p + maxChild, p + parent);
			}
			else
			{
				break;
			}
			parent = maxChild;
			maxChild = 2 * parent + 1;
		}
		show(p);
	}
}
void heapSort(int *p,int length) {
	for (int i = 0; i < N; i++)
	{
		heap(p,N - i);
		swap(p,p + N -1 - i);
		show(p);
	}
}
void main() {
	int array[] = { 3,2,5,4,6,7,1,9,8,0};
	//int array[] = { 0,1,2,3,4,};
	//heap(array,N);
	//printf("max:%d\n",array[0]);
	heapSort(array,N);
	show(array);
	system("pause");
}