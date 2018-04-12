//3¸öÊıÅÅĞò
#include<stdio.h>
#include<stdlib.h>
void init(int *a,int *b,int *c){
	*a = 3;
	*b = 2;
	*c = 1;
}
void swap(int *a,int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
void process(int *a,int *b,int *c){
	if(*a > *b){
		swap(a,b);
	}
	if(*b > *c){
		swap(b,c);
	}
	if(*a > *b){
		swap(a,b);
	}
}
void show(int *a,int *b,int *c){
	printf("a = %d\n",*a);
	printf("b = %d\n",*b);
	printf("c = %d\n",*c);
}
void main(){
	int a = 0;
	int b = 0;
	int c = 0;
	
	init(&a,&b,&c);
	process(&a,&b,&c);
	show(&a,&b,&c);

	system("pause");
}