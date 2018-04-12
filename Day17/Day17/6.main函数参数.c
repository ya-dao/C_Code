#include<stdio.h>
#include<stdlib.h>
/*
	argc:参数个数
	args:输入的参数
	void main(int argc,char **args) {
		for (int i = 0; i < argc; i++)
		{
			printf("%s\n",*(args + i));
		}
		system("pause");
	}
*/
void main(int argc,char **args,char **envp) {
	/*
		循环终止条件是字符串(*(envp + i))为NULL
	*/
	for (int i = 0; *(envp + i) != NULL; i++)
	{
		printf("%s\n",*(envp + i));
	}
	system("pause");
}