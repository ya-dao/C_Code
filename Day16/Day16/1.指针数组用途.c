#include<stdio.h>
#include<stdlib.h>
void function1(char **p) {
	//1.指针数组作参数时会退化成一个二级指针
	for (int i = 0; i < 2; i++)
	{
		//这里的字符指针数组每一个元素都是一个常量字符的数组,只需要加一层*获取到每个数组指针即可.
		//system(*(*(p + i)));
		system(*(p + i));
	}
}
void function2() {
	/*
		如果需要malloc动态生成一个二维数组,在接收的时候必须手动指定列的大小,不能指定个动态的值.
		这时需要用到指针数组.
	*/
	//int (*p)[num] = malloc(sizeof(int) * 20);
	int (*p)[5] = malloc(sizeof(int) * 20);
	for (int i = 0; i < 20; i++)
	{
		*(*(p + i / 5) + (i % 5)) = i + 1;
		printf("%d ",*(*(p + i / 5) + i % 5));
		if ((i + 1) % 5 == 0)
		{
			printf("\n");
		}
	}
	free(p);
}
void function3() {
	/*
		核心:由于指针数组对应的指针类型是一个二级指针.
		二维数组转换为二级指针:
			1.取出二维数组里面的每一个行指针,将其置于指针数组里面每一个元素
			2.将该指针数组直接赋值给一个二级指针即可.
			3.使用时通过二级指针的++/--,直接将该二级指针所指向的一级指针作为一个行指针,
				再通过行指针++/--取出列
		指针数组的应用:
			通过指针数组用malloc创建一个无需手动指定行列的二维数组,也称为创建动态内存块
		思路:
			malloc动态创建一个指针数组,该数组的每一个元素作为行指针再次动态创建一个数组.
	*/
	//创建包含4个行指针的指针数组
	int **p = malloc(sizeof(int *) * 4);
	for (int i = 0; i < 4; i++)
	{
		//在行指针上创建一个一维数组
		*(p + i) = malloc(sizeof(int) * 5);
		for (int j = 0; j < 5; j++)
		{
			*(*(p + i) + j) = i * 5 + j;
		}
	}
	for (int i = 0; i < 20; i++)
	{
		printf("%d ",*(*(p + i / 5) + i % 5));
		if ((i + 1) % 5 == 0) {
			printf("\n");
		}
	}

}
void main() {
	char *p[] = { "calc","notepad" };
	//function1(p);
	//function2();
	function3();
	system("pause");
}