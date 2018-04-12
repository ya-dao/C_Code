#include<stdio.h>
#include<stdlib.h>
void function1() {
	/*
		malloc申请的空间不会初始化
	*/
	int *p = malloc(sizeof(int) * 10);
	printf("%p\n",p);
	for (int i = 0; i < 10; i++)
	{
		*(p + i) = i + 1;
	}
	printf("%p\n", p);
	free(p);
}
void function2() {
	/*
	calloc申请的空间时默认会把所有类型都会初始化为0
	*/
	double *p = calloc(10,sizeof(double));
	printf("%p\n", p);
	for (int i = 0; i < 10; i++)
	{
		*(p + i) = i + 1.0;
	}
	printf("%p\n", p);
	free(p);
}
void function3() {
	/*
		realloc可以在已申请的空间基础上扩展新的空间
		原型:extern void *realloc(void *mem_address, unsigned int newsize);
		扩展有两种情况:
			1.如果再次扩展的空间不大,即小于原本空间后面相邻的空闲内存
				那么会在原起始地址上多扩展出那些空间
			2.如果再次扩展的空间较大,即大于原本空间后面相邻的空闲内存
				那么会重新分配一个新的地址,并且会把原来的值拷贝过去并释放原空间
		总结:
		1. realloc失败的时候，返回NULL
		2. realloc失败的时候，原来的内存不改变，不会释放也不会移动
		3. 假如原来的内存后面还有足够多剩余内存的话，realloc的内存=原来的内存+剩余内存,realloc还是返回原来内存的地址; 假如原来的内存后面没有足够多剩余内存的话，realloc将申请新的内存，然后把原来的内存数据拷贝到新内存里，原来的内存将被free掉,realloc返回新内存的地址
		4. 如果size为0，效果等同于free()。这里需要注意的是只对指针本身进行释放，例如对二维指针**a，对a调用realloc时只会释放一维，使用时谨防内存泄露。
		5. 传递给realloc的指针必须是先前通过malloc(), calloc(), 或realloc()分配的
		6.传递给realloc的指针可以为空，等同于malloc。
	*/
	int *p = malloc(sizeof(int) * 10);
	for (int i = 0; i < 10; i++)
	{
		*(p + i) = i + 1;
	}
	printf("%p\n", p);
	int *newP = realloc(p,500 * sizeof(int));
	for (int i = 0; i < 520; i++)
	{
		*(newP + i) = i + 1 + 10;
	}
	printf("%p\n", newP);
	free(p);
	free(newP);
}
void function4() {
	/*
		_recalloc与realloc基本类似,只是前者会初始化.
	*/
	int *p = (int *)calloc(10,sizeof(int));
	for (int i = 0; i < 10; i++)
	{
		*(p + i) = i + 1;
	}
	printf("%p\n", p);
	int *newP = (int *)_recalloc(p,200,sizeof(int));
	printf("%p\n", newP);
}
void main() {
	//function1();
	//function2();
	//function3();
	function4();
	system("pause");
}