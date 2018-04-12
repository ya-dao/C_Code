#include<stdio.h>
#include<stdlib.h>
void function1(int *p,int length) {
	/*
		一维数组作为参数
			形参可用一级指针或者一个一维数组
		实例:反转一个数组里面的数
	*/
	for (int *tail = p + length - 1; p != tail; p++,tail--)
	{
		int temp = *p;
		*p = *tail;
		*tail = temp;
	}
}
void show1(int *p,int length) {
	for (int i = 0; i < length; i++)
	{
		printf("%d ",*(p + i));
	}
	printf("\n");
}
void function2(int (*p)[4],int rows,int n) {
	/*
		二维数组作为参数
			形参可用二维数组或者数组指针,还可以将其行地址统一存放在一个指针数组里面
			第三种有一个好处就是可以动态指定行列,示例操作:
				void function2(int **p,int row,int column);
				int a[3][4] = {0};
				int *p[3] = {NULL};
				for(int i = 0;i < row;i++){
					p[i] = a + i;
				}
				function2(p,3,4);
			实例:计算3个学生,各4个成绩,求总平均分以及第n个人的成绩
	*/
	int scoreOfEachStudent = 0;
	float totalAverage = 0;
	for (int i = 0; i < rows; i++)
	{
		if (n == i) {
			printf("第%d个学生成绩:",n);
		}
		scoreOfEachStudent = 0;
		for (int j = 0; j < 4; j++)
		{
			if (n == i) {
				printf("%d ",*(*(p + i) + j));
			}
			scoreOfEachStudent += *(*(p + i) + j);
		}
		if (n == i) {
			printf("\n");
		}
		totalAverage += (scoreOfEachStudent / 4.0f);
	}
	printf("总平均分:%.1f\n", totalAverage / 3.0f);
}
void main() {
	int a[] = { 1,2,3,4,5 };
	//function1(a, 5);
	//show1(a, 5);
	int score[3][4] = {89,78,65,71,82,94,93,70,100,98,99,91};
	function2(score, 3, 2);
	system("pause");
}