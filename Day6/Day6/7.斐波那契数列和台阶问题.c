#include<stdio.h>
/*
	求解斐波那契数列
*/
void method1(){
	int a = 1;
	int b = 1;
	int c = 0;
	int i = 0;
	printf("第1个月的兔子数:%d\n",1);
	printf("第2个月的兔子数:%d\n",1);
	for(i = 3;i <= 10;i++){
		c = a + b;
		a = b;
		b = c;
		printf("第%d个月的兔子数:%d\n",i,c);
	}
}
int recursive(int month){
	if(month == 1){
		return 1;
	}else if(month == 2){
		return 1;
	}else{
		return recursive(month - 1) + recursive(month - 2);
	}
}
void main(){
	int result = 0;
	int i = 0;
	printf("第1个月的兔子数:%d\n",1);
	printf("第2个月的兔子数:%d\n",1);
	for(i = 3;i <= 4;i++){
		result = recursive(i);
		printf("第%d个月的兔子数:%d\n",i,result);
	}
}