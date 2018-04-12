#include<stdio.h>
#include<stdlib.h>
//sprintf()向字符串中传入值
void test1(){
	char input[100] = {0};
	char command[100] = {0};
	scanf("%s",input);
	
	//sprintf()用于向字符串中插入可变值
	//通过将.s截取字符串应用于sprintf()来填充字符串
	sprintf(command,"color %.2s",input);
	system(command);
}
/*
	printf格式控制输出格式
	-:printf默认是右对齐,如果加上-号,则表示左对齐,右边补0或空格
	0:表示多余的空格用0填充
	m:输出字符的宽度限制,如果实际宽度大于给定宽度,则按实际宽度显示,如果实际宽度小于给定宽度,则补齐空格或者0
	.n:如果是实数,则表示后面打印的小数位数,如果是字符串,则表示截取的长度
	l:表示长整数.如lf/ld
*/
void test2(){
	printf("%10d\n",1340);
	printf("%010d\n",234);
	printf("%-010d\n",1242);
	printf("%.2f\n",1234.235432);
	printf("%.3s\n","sldfjio");
}
/*
	通过格式化字符来拼接字符串(C语言不支持java字符串的直接相加)
*/
void test3(){
	char command1[100] = "task";
	char command2[100] = "123list";//只能从左边开始截取,'-'号只能表示左对齐,不能表示从右边开始截取
	char command[100] = {0};
	sprintf(command,"%s%.4s",command1,command2+3);
	system(command);
}
/*
	短整数的输出:hd/hu
	长整数的输出:ld/lu
	long long整数的输出:lld/llu
*/
void test4(){
	unsigned short int number1 = 65535;
	short int number2 = 65535;

	//32及以上的系统中,long等价于int
	long number3 = 234124;
	int number4 = 234124;

	//如果是qq号/手机号这些,需要用到long long,不使用字符串,便于排序
	//long long telphone = 18523482416;


	printf("%hu,%hd\n",number1+1,number2);//hu的范围是2的16次方,u是int的范围2的32次方,如果超过就会发生数据溢出.
	printf("%u,%d\n",number1+1,number2);

	
	printf("%ld\n",number3);

	
	//printf("%lld\n",telphone);

}
/*
	打印进制标识符:#
	可以在打印八进制或者十六进制的时候添加0或者0x的标识符
*/
void test5(){
	int number1 = 0123;
	int number2 = 0x123;
	printf("%#o\n",number1);
	
	printf("%#x\n",number2);
}
/*
	格式控制符大小写的问题
	如果输出的内容可以带上字符的一般可以大写,除了%o
*/
void test6(){
	printf("%o\n",0123);
	printf("%O\n",0123);
	printf("%#X\n",0x123);
	printf("%E\n",123.0);//指数形式表示小数,这里不能传整数,printf不会进行类型转换.

	//显示转义字符
	printf("\"%d\"\n",123);
	//两个%%表示一个%%号,且多个%的时候不会重复合并,%%%%%%会表示成3个,不会一直合并成1个
	printf("%d%%\n",12);
	//printf("%d\%\n",12); %不能通过转义表示
}
/*
	printf格式控制符和参数个数对应的问题
	1.如果格式控制符的个数小于实际参数的时候,多余的参数不予输出
	2.如果格式控制符的个数多于实际参数的时候,其他的值不定,可能是垃圾值,也可能是0
*/
void test7(){
	printf("%d,%d\n",1,2,3,4);
	printf("%d,%d,%d,%d\n",1,2);
	
}
/*
	printf宽度和小数点位数的可变值

*/
void test8(){
	int i = 1;
	char str[100] = "120938sjdfoa;u3wqj4023ujsoifadj";
	
	for(;i <= 20;i++){
	//	printf("%*d\n",i,i);
	}

	for(i = 1;i <= 20;i++){
		printf("%.*s\n",i,str);
	}
}
int main(){
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	//test7();
	test8();
	return 0;
}