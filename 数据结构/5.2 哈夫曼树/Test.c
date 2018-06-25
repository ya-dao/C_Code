#include "Huffman.h"
void main() {
	int weights[N] = { 5,29,7,8,14,23,3,11 };
	HuffmanTree tree = NULL;
	initTree(&tree,weights);
	createTree(&tree);
	for (int i = 0; i < 2 * N - 1; i++)
	{
		if ((tree + i)->parent == 0)
		{
			prefix(tree + i);
		}
		//printf("%d:weight=%d,parent=%d\n",i + 1,(tree + i)->weight, (tree + i)->parent);
	}
	char **codes = NULL;
	codes = malloc(sizeof(char *) * N);
	for (int i = 0; i < N; i++)
	{
		//由于有'\0'的存在,需要多来一个
		codes[i] = malloc(sizeof(char) * (N + 1));
		//由于使用的calloc,所以不用初始化这个N了
		for (int j = 0; j < N + 1; j++)
		{
			codes[i][j] = '\0';
		}
		encodeRecursive(tree,tree + i,codes[i] + N);
	}
	for (int i = 0; i < N; i++)
	{
		printf("%d:", (tree + i)->weight);
		for (int j = 0; j < N + 1; j++)
		{
			//不要试图用%c打印0('\0'),不可显示字符打印结果随环境和cmd编码不同而不同,中文编码的cmd下会出现'a'
			if (codes[i][j] != '\0') {
				printf("%c ",codes[i][j]);
			}
		}
		printf("\n");
	}
	system("pause");
}