#include<stdio.h>

/*
	scanf格式控制符:
		*号:表示读取输入内容的时候跳过这一个项
		m:指定输入所占宽度
	scanf输入的格式控制符和输入的参数必须完全匹配,如果%d,%d 则输入的时候也必须1,2这样输入,逗号不能省略

	scanf的空白符可以由空格/回车/tab键组成

	scanf的返回值是代表成功读取到多少个输入的数据
	printf的返回值是代表打印多少个字符
*/
void test1(){
	int a = 0,b = 0,c = 0;
	scanf("%d%*d%d",&a,&c);//表示跳过第二个输入数据
	printf("%d,%d,%d\n",a,b,c);
}

/*
	1.scanf函数在输入的时候可以指定输入的数据所占的字符个数,scanf自动按照指示截取所需长度的数据
	2.%*表示读取的这个数据被忽略,不被赋值给其他变量
	3.输入的实数不能指定精度
	4.scanf函数必须使用变量的地址,否则它会把变量的值当作地址,从而引起访问地址冲突
	5.使用scanf输入字符时,空格和转义字符都会被当成一个有效字符输入
	6.scanf函数在以下情况会认为解析出一个数据
		1.遇到非字符型数据,如空白字符
		2.有指定宽度的话,读到指定宽度即认为这个整数输入完毕
*/
void test2(){
	int number = 0;
	//1.scanf("%3d",&number);
	//2.scanf("%*3d",&number);
	//printf("%d\n",number);
	double number2 = 0.0;
	//3.
	scanf("%5lf",&number2);
	printf("%lf\n",number2);
}
/*
	统计输入的字符
	%n会统计前面输入的有效字符数
*/
void test3(){
	char str[100] = {0};
	int n = 0;
	int number = 0;
	scanf("%d%s%n",&number,str,&n);
	printf("%s,%d,%d\n",str,n,number);
}
int main(){
	//test1();
	//test2();
	test3();
	return 0;
}
