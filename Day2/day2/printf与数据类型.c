#include<stdio.h>
int main() {
	/*
		不同类型的区别:
		大小不同,解析的方式不同.
		具体大小可以使用sizeof关键字(不是函数)查看类型大小

		printf()函数不会按照类型自动转换
		如果按照%d去打印一个浮点数,那么就会出现错误.
		如果需要将整数按照浮点数打印那么需要打印的时候进行强行类型转换
	*/
	int number = 10;
	//printf("%f\n",number); 错误
	printf("%f\n",(float)number);
	
	float number1 = 10.0f;
	//printf("%d\n", number1);错误
	printf("%d\n", (int)number1);

	getchar();
	return 0;
}