#include<stdio.h>
#include<limits.h>	//极限头文件

int main() {
	int max = INT_MAX;	//int类型最大最小值的宏定义
	int min = INT_MIN;

	/*
		每个类型的存储方式都有一定的极限,如果数据越界,就会导致结果出问题
		比如:一个字节最大的数+1会为0
			1111 1111
			+		1
		   10000 0000(舍弃越界的1)
		    =		0
	*/

	printf("%d,%d\n",max,min);
	getchar();
	return 0;
}