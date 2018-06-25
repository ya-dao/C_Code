//该文件是测试文件,所有内容与实现的具体细节无关
#include "CourseDesign.h"

CodeAnalysis *initCodeAnalysis(char *fileName);
FILE *initFile(char *fileName);
void process(CodeAnalysis *codeAnalysis, Stack *signStack, FILE *file);
void show(CodeAnalysis *codeAnalysis);
void release(FILE *file, Stack *signStack, CodeAnalysis *codeAnalysis);

void main() {
	//char fileName[20] = { 0 };
	//inputFileName(fileName);
	char fileName[100] = FILE_PATH;

	//初始化
	CodeAnalysis *codeAnalysis = initCodeAnalysis(fileName);
	Stack *signStack = (Stack *)malloc(sizeof(Stack));
	initStack(&signStack);
	FILE *file = initFile(fileName);
	if (file == NULL)
	{
		return;
	}
	
	process(codeAnalysis, signStack, file);

	show(codeAnalysis);

	release(file, signStack, codeAnalysis);

	system("pause");
}

/*
	主流程,读一行处理一行
*/
void process(CodeAnalysis *codeAnalysis,Stack *signStack,FILE *file) {
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

		if (buffer[0] == '\t') {
			printf("");
		}

		handleLineString(buffer, codeAnalysis, signStack);

		if (feof(file))
		{
			break;
		}
	}
}

/*
	初始化CodeAnalysis结构体和其成员
*/
CodeAnalysis *initCodeAnalysis(char *fileName) {
	CodeAnalysis *codeAnalysis = (CodeAnalysis *)malloc(sizeof(CodeAnalysis));
	codeAnalysis->codeLineCount = 0;
	codeAnalysis->commentLineCount = 0;
	codeAnalysis->emptyLineCount = 0;
	memset(codeAnalysis->fileName, 0, sizeof(char));
	//拷贝文件名
	int i = 0;
	while (fileName[i] != '\0')
	{
		codeAnalysis->fileName[i] = fileName[i];
		i++;
	}
	codeAnalysis->fileName[i] = '\0';

	//初始化里面的函数结点
	codeAnalysis->functionAnalysis = (FunctionAnalysis *)malloc(sizeof(FunctionAnalysis));
	codeAnalysis->functionAnalysis->codeLineCount = 0;
	memset(codeAnalysis->functionAnalysis->functionName, 0, sizeof(char));

	//函数结点的头结点用于统计函数个数:functionName="函数总数"
	char functionCountString[9] = FUNCTION_COUNT;
	functionCountString[8] = '\0';
	i = 0;
	while (functionCountString[i] != '\0')
	{
		codeAnalysis->functionAnalysis->functionName[i] = functionCountString[i];
		i++;
	}
	codeAnalysis->functionAnalysis->functionName[i] = '\0';
	codeAnalysis->functionAnalysis->next = NULL;

	return codeAnalysis;
}

FILE *initFile(char *fileName) {
	//ANSI编码,注意不要读到UTF-8编码的文本,会乱码
	FILE *file = fopen(fileName, "r");
	if (file == NULL)
	{
		output(OPEN_FILE_ERROR);
		return NULL;
	}
	return file;
}

/*
	输出结果
*/
void show(CodeAnalysis *codeAnalysis) {
	printf("文件名:%s\n", codeAnalysis->fileName);
	printf("代码总行数:%d\n", codeAnalysis->codeLineCount);
	printf("注释总行数:%d\n", codeAnalysis->commentLineCount);
	printf("空行总行数:%d\n", codeAnalysis->emptyLineCount);

	printf("\n");
	FunctionAnalysis *next = codeAnalysis->functionAnalysis;
	printf("%s:%d\n", next->functionName, next->codeLineCount);
	next = next->next;
	printf("\n");

	while (next != NULL)
	{
		printf("函数名:%s\n", next->functionName);
		printf("代码总行数:%d\n", next->codeLineCount);
		printf("\n");
		next = next->next;
	}
}

/*
	释放文件资源和内存
*/
void release(FILE *file, Stack *signStack, CodeAnalysis *codeAnalysis) {
	fclose(file);
	destroyStack(&signStack);
	FunctionAnalysis *next = codeAnalysis->functionAnalysis->next;
	FunctionAnalysis *current = codeAnalysis->functionAnalysis;
	while (next != NULL)
	{
		free(current);
		current = next;
		next = next->next;
	}
	free(current);
	free(codeAnalysis);

	//置空,避免迷途指针
	file = NULL;
	signStack = NULL;
	current = NULL;
	next = NULL;
	codeAnalysis = NULL;
}