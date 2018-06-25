#include "courseDesign.h"

void main() {
	CodeAnalysis *codeAnalysis = (CodeAnalysis *)malloc(sizeof(CodeAnalysis));
	codeAnalysis->codeLineCount = 0;
	codeAnalysis->commentLineCount = 0;
	codeAnalysis->emptyLineCount = 0;
	memset(codeAnalysis->fileName,0,sizeof(char));
	codeAnalysis->functionAnalysis = (FunctionAnalysis *)malloc(sizeof(FunctionAnalysis));
	codeAnalysis->functionAnalysis->codeLineCount = 0;
	memset(codeAnalysis->functionAnalysis->functionName, 0, sizeof(char));
	
	char functionCountString[9] = FUNCTION_COUNT;
	functionCountString[8] = '\0';
	{
		int i = 0;
		while (functionCountString[i] != '\0')
		{
			codeAnalysis->functionAnalysis->functionName[i] = functionCountString[i];
			i++;
		}
		codeAnalysis->functionAnalysis->functionName[i] = '\0';
	}
	codeAnalysis->functionAnalysis->next = NULL;
	
	Stack *signStack = (Stack *)malloc(sizeof(Stack));
	initStack(&signStack);
	
	//char fileName[20] = { 0 };
	//inputFileName(fileName);
	char fileName[100] = FILE_PATH;
	FILE *file = NULL;
	//ANSI编码,注意不要读到UTF-8编码的文本,会乱码
	file = fopen(fileName,"r");
	if (file == NULL)
	{
		output(OPEN_FILE_ERROR);
		return;
	}
	
	/*
	这种判断是否到了文件尾的方式在存在错误的，因为fgets函数是遇到回车‘\r'符返回的，所以在读到最后一行时，
	它的文件指针并没有指向文件尾，而是指向’\r'处，，feof 依然返回0（文件还没结束 ），所以这时operations还是会执行
	while (!feof(fp))
	{
		fgets(temp, 100, fp);
		Operation(temp);
	}
	应该修改为下面这种形式:
	*/
	char buffer[BUFFER_SIZE] = { 0 };
	while (1) {
		fgets(buffer, BUFFER_SIZE, file);
		//处理开始
		//output(buffer);

		if (buffer[0] == '\t') {
			printf("");
		}
		handleLineString(buffer, codeAnalysis, signStack);
		
		if (feof(file))
		{
			break;
		}
	}

	printf("文件名:%s\n",codeAnalysis->fileName);
	printf("代码总行数:%d\n",codeAnalysis->codeLineCount);
	printf("注释总行数:%d\n", codeAnalysis->commentLineCount);
	printf("空行总行数:%d\n", codeAnalysis->emptyLineCount);
	
	printf("\n");
	FunctionAnalysis *next = codeAnalysis->functionAnalysis;
	printf("%s:%d\n", next->functionName,next->codeLineCount);
	next = next->next;
	printf("\n");
	
	while (next != NULL)
	{
		printf("函数名:%s\n",next->functionName);
		printf("代码总行数:%d\n", next->codeLineCount);
		printf("\n");
		next = next->next;
	}

	fclose(file);
	destroyStack(&signStack);
	next = codeAnalysis->functionAnalysis->next;
	FunctionAnalysis *current = codeAnalysis->functionAnalysis;
	while (next != NULL)
	{
		free(current);
		current = next;
		next = next->next;
	}
	free(current);
	current = NULL;
	next = NULL;
	free(codeAnalysis);
	system("pause");
}