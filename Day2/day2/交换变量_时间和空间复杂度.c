#include<stdio.h>
/*
创建一个中间变量来交换值
	空间复杂度为1(创建了一个中间变量)	
	时间复杂度为3(赋值了3次)
*/
void test1() {
	int a = 5;
	int b = 10;

	int temp = a;
	a = b;
	b = temp;

	printf("a=%d,b=%d\n", a, b);
}
/*
	通过+ - * / 的方式来交换变量的值
		空间复杂度0(没有创建额外的变量)
		时间复杂度6(计算3次,赋值3次)
	缺点:+ - * / 操作容易导致数据越界,最稳当的方式是使用异或操作
*/
void test2() {
	int a = 5;
	int b = 10;

	a = a + b; // a = 15 b = 10
	b = a - b; // a = 50 b = 5
	a = a - b; // a = 10 b = 5

	/*
	a = a * b; // a = 50 b = 10
	b = a / b; // a = 50 b = 5
	a = a / b; // a = 10 b = 5
	*/

	printf("a=%d,b=%d\n", a, b);
}
/*
	使用异或操作来交换变量的值
		空间复杂度0
		时间复杂度6(计算3次,赋值3次)
	异或特点:A与B异或之后的值再与B异或还是会得到原值
*/
void test3() {
	int a = 5;
	int b = 10;

	//5 :0000 0101
	//10:0000 1001
	//12:0000 1100
	a = a ^ b; // a = 12 b = 10
	b = b ^ a; // a = 12 b = 5
	a = a ^ b; // a = 10 b = 5

	printf("a=%d,b=%d\n", a, b);
}
int main() {
	//test1();
	test2();

	getchar();
	return 0;
}
