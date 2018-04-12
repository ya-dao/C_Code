#include<stdio.h>
#include<stdlib.h>

/*
	现有n级台阶,每次只能走一步或者两步,问有多少种走法?
	台阶问题思路:
		这是一个动态规划的问题.
		设有n级台阶,最后一步只能选择从n-1或者n-2走上来,只有两种走法
		如果最后一次走一步,则剩下n-1种走法.
		如果最后一次走两步,则剩下n-2种走法.
		所以所有可能的走法就是f(n) = f(n-1) + f(n-2);
*/

int main() {
	int n = 10;

	//动态规划
	int array[10] = { 0 };
	array[0] = 1;
	array[1] = 2;
	for (int i = 2; i < n; i++)
	{
		array[i] = array[i - 1] + array[i - 2];
	}

	printf("第10级台阶共有%d种走法\n",array[9]);
	printf("第10级台阶共有%d种走法\n", recursive(10));

	system("pause");
}
//递归
int recursive(int n) {
	if (n == 1) {
		return 1;
	}
	else if (n == 2) {
		return 2;
	}
	else {
		return recursive(n - 1) + recursive(n - 2);
	}
}