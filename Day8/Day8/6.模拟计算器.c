#include<stdio.h>
#include<stdlib.h>
/*
	使用位运算实现加减乘除取模
	加法即两个数进行异或运算,然后通过与运算判断有无进位的情况,如果有直接左移一位即可
*/
int add(int a,int b){
	int sum = 0;
	sum = a ^ b;
	if(a & b != 0){
		sum += ((a & b) << 1);
	}
	return sum;
}
/*
	5 - 3 = 2
	5的补码:
		0000 0101
	
	3的原码
	先将其转换成负数
		0000 0011 ==>  1111 1100
	再求其反码
		1000 0011 ==>  1111 1100
	再+1得到补码
		1111 1100 ==>  1111 1101
	再进行加法
*/
void substract(int a,int b){
	int mask = 4294967295;
	int minus = 0;
	//先异或得到反码
	b ^= mask;
	//加1得到补码
	b += 1;
	minus = add(a,b);
	printf("%d\n",minus);
}
/*
	乘法即是多个加法
*/
void times(int a,int b){
	int i = 0;
	int sum = a;
	
	for(;i < b - 1;i++){
		sum = sum ^ a;
		if((a & a) != 0){
			sum += ((a & a) << 1);
		}
	}
	printf("%d\n",sum);
}
/*
	除法:将被除数取反+1得到其对应的负数的补码.
		 然后根据除数大于被除数的条件进行循环相加最后再加1
*/
void divide(int a,int b){
	int result = 1;
	int mask = 4294967295;
	int sum = 0;
	int c = b;
	while(a > c){
		b = c;

		b ^= mask;
		b += 1;
		 
		sum = a ^ b;
		
		//必须打括号,!=的优先大于&与运算
		if((a & b) != 0){
			sum += ((a & b) << 1);
		}
		a = sum;
		result++;
	}

	printf("%d\n",result);
}

/*
	取余就是进行除法,将最后小于被除数的除数做为负数
*/
void remainder(int a,int b){
	int c = b;
	int mask = 4294967295;
	int sum = 0;
	while(a >= c){
		b = c;
		b  = b ^ mask;
		
		sum = b ^ 1;
		if((b & 1) != 0){
			sum += ((b & 1) << 1);
		}
		
		b = sum;

		sum = a ^ b;
		if((a & b) != 0){
			sum += ((a & b) << 1);
		}
		
		a = sum;
	}
	printf("%d\n",a);
}

void main(){
	//add(3,5);
	//substract(5,3);
	times(12,2);
	//divide(35,5);
	//remainder(33,5);
	system("pause");
}