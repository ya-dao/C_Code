/*众数问题
	问题描述:给定含有N个元素的多重集合S,每个元素在S中出现的次数称为该元素的重数.
			多重集S中重数最大的元素称为众数
	算法设计:对于给定的由N个自然数组成的多重集S,计算S的众数及重数
	数据输入:输入数据由文件名为input.txt的文本文件提供.文件的第一行为多重集中元素个数n
			在接下来的n行中,每行有一个自然数
	结果输出:将计算结果输出到文件output.txt.输出文件有两行,第1行是众数,第2行是重数
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>

int writeInputData(FILE** inputFile, char* inputPath);
int solveProblem(FILE** inputFile, char* inputPath, int* max, int* count);
int writeOutputResult(FILE** output, char* outputPath, int max, int count);
void showDialog(char *inputPath);
void showArr(int *arr, int n);

void main() {
	char* inputPath = "C:\\Users\\Administrator\\Desktop\\input.txt";
	char* outputPath = "C:\\Users\\Administrator\\Desktop\\output.txt";
	
	FILE* inputFile = NULL;
	FILE* outputFile = NULL;
	
	int max = 0;
	int count = 0;

	int flag = writeInputData(&inputFile, inputPath);
	if (!flag)
	{
		showDialog(inputPath);
	}
	else {
		fclose(inputFile);
	}

	flag = solveProblem(&inputFile,inputPath,&max,&count);
	if (!flag)
	{
		showDialog(inputPath);
	}
	else {
		fclose(inputFile);
	}

	flag = writeOutputResult(&outputFile, outputPath, max, count);
	if (!flag)
	{
		showDialog(outputPath);
	}
	else {
		fclose(outputFile);
	}
	system("pause");
}

int writeInputData(FILE** inputFile,char* inputPath) {
	//w模式如果文件不存在则会自动创建对应文件并命名
	if ((*inputFile = fopen(inputPath, "w")) != NULL)
	{
		char* buffer = "6\n1\n2\n2\n2\n3\n5\n";
		/*
		sizeof关键字求的是char指针的大小,指针都是4字节
		strlen函数求的是里面内容的大小,不包括'\0'
		*/
		fwrite(buffer, strlen(buffer), 1, *inputFile);
		return 1;
	}
	else
	{
		return 0;
	}
}
/*
	max:最大数
	count:出现的最大次数
*/
int solveProblem(FILE** inputFile,char* inputPath,int* max,int* count) {
	if ((*inputFile = fopen(inputPath,"r")) != NULL)
	{
		char length[10] = { 0 };
		fgets(length, 10, *inputFile);
		int N = 0;
		sscanf(length,"%d",&N);
		int* data = (int*)(malloc(sizeof(int) * N));
		char c = 0;
		for(int i = 0;(c = fgetc(*inputFile)) != EOF;)
		{
			if (c != '\n') {
				data[i] = c - 48;
				i++;
			}
		}
		//第一个元素是数据个数,无需统计
		int* statistical = (int*)(malloc(sizeof(int) * (N - 1)));
		for (int i = 1; i < N; i++)
		{
			int count = 0;
			for (int j = 1; j < N; j++)
			{
				if (data[i] == data[j])
				{
					count++;
				}
			}
			statistical[i - 1] = count;
		}
		int maxIndex = 0;
		for (int i = 0; i < N - 1; i++)
		{
			if (statistical[i] >= *count)
			{
				*count = statistical[i];
				maxIndex = i;
			}
		}
		//由于statistical比data数组少一个元素个数,所以需要加1
		*max = data[maxIndex + 1];
		
		free(data);
		free(statistical);
	}
	else {
		return 0;
	}

	return 1;
}

int writeOutputResult(FILE** output,char* outputPath,int max,int count) {
	if ((*output = fopen(outputPath,"w")) != NULL)
	{
		char result[10] = { 0 };
		sprintf(result,"%d\n%d\n",max,count);
		fwrite(result,strlen(result),1,*output);
	}
	else {
		return 0;
	}
	return 1;
}

void showDialog(char *inputPath) {
	char tip[100] = { 0 };
	sprintf(tip, "Can't open or write on the path:%s", inputPath);
	printf("%s\n", tip);
	MessageBoxA(0, tip, "Tip", 0);
}

void showArr(int *arr,int n) {
	for (int i = 0; i < n; i++)
	{
		printf("%d ",*(arr + i));
	}
	putchar(10);
}