#include<stdio.h>
#include<stdlib.h>
#include<iostream>

/*
	typedef相当于基于已有类型重新定义一个类型名称,方便识别
*/

typedef unsigned int l_int;

void main(){
	
	l_int a = 12345678;
	printf("%d\n",a);
}