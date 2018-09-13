//参考链接:https://blog.csdn.net/tic_yx/article/details/9718971
/*
	重点如下:
		1.结构体中第一个成员地址始终与结构体变量地址相同
		2、对齐的原则：
		原则1：数据成员对齐规则：结构（struct或联合union）的数据成员，第一个数据成员放在offset为0的地方，以后每个数据成员存储的起始位置要从该成员大小的整数倍开始（比如int在32位机为４字节，则要从4的整数倍地址开始存储）。

		原则2：结构体作为成员：如果一个结构里有某些结构体成员，则结构体成员要从其内部最大元素大小的整数倍地址开始存储。（struct a里存有struct b，b里有char，int，double等元素，那b应该从8的整数倍开始存储。）

		原则3：收尾工作：结构体的总大小，也就是sizeof的结果，必须是其内部最大成员的整数倍，不足的要补齐。

*/
#include<stdio.h>
#include<stdlib.h>

struct A {
	char a;
	char b;
};

struct B {
	int a;
	char b;
};

void main() {
	
	printf("sizeof(A):%d\n", sizeof(struct A));
	printf("sizeof(B):%d\n", sizeof(struct B));

	system("pause");
}