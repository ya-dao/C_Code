#include<stdio.h>
#include<stdlib.h>
/*
	结论:指针的++/--地址偏移的长度取决于它的类型,int为4等等
*/
void main() {
	int intArr[] = { 0,1,2,3,4 };
	char charArr[] = { 'A','B','C','D' };
	float floatArr[] = { 1.0f,2.0f,3.0f,4.0f };
	double doubleArr[] = { 1.0,2.0,3.0,4.0 };
	//初始化指针
	int *pInt = intArr;
	int *pInt1 = &intArr[3];
	char *pChar = charArr;
	float *pFloat = floatArr;
	double *pDouble = doubleArr;

	//进行指针减法运算,实际上就是求中间间隔的元素个数:(地址-地址)/sizeof(类型)
	printf("指针减法:%d\n",pInt1 - pInt);

	//进行指针运算
	*pInt++;
	printf("int指针++:%d\n",*pInt);

	*pChar++;
	printf("char指针++:%c\n", *pChar);

	*pFloat++;
	printf("float指针++:%f\n", *pFloat);

	*pDouble++;
	printf("double指针++:%lf\n", *pDouble);

	system("pause");
}