//该文件是测试文件,所有内容与实现的具体细节无关
#include "CourseDesign.h"

CodeAnalysis *initCodeAnalysis(char *fileName);
FILE *initFile(char *fileName);
void process(CodeAnalysis *codeAnalysis, Stack *signStack, FILE *file);
void showEnglish(CodeAnalysis *codeAnalysis);
void showChinese(CodeAnalysis *codeAnalysis);
void release(FILE *file, Stack *signStack, CodeAnalysis *codeAnalysis);
int calculate(int divide, int divided);
float calculateAverage(CodeAnalysis *codeAnalysis);
char evaluateCodeStyle(int codeLine, char *evaluate);
char evaluateCommentStyle(int commentRate, char *evaluate);
char evaluateEmptyLineStyle(int emptyLineRate,char *evaluate);

void main() {
	//初始化
	system("color F2");
	char fileName[BUFFER_SIZE] = { 0 };
	FILE *file = NULL;
	while (file == NULL)
	{
		//inputFileName(fileName);
		sprintf(fileName, "%s", FILE_PATH);
		file = initFile(fileName);
	}

	CodeAnalysis *codeAnalysis = initCodeAnalysis(fileName);
	Stack *signStack = (Stack *)malloc(sizeof(Stack));
	initStack(&signStack);
	
	process(codeAnalysis, signStack, file);

	showEnglish(codeAnalysis);

	printf("\n\n以下中文版分析结果!\n\n");

	showChinese(codeAnalysis);

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
	计算结果
	divide:除数
	divided:被除数
*/
int calculate(int divide,int divided) {
	return (int)(divide * 1.0 / divided * 100);
}

/*
	输入能看懂的人话
*/
void showChinese(CodeAnalysis *codeAnalysis) {
	printf("\n");
	printf("\"%s\"文件的分析结果如下:\n", codeAnalysis->fileName);
	printf("\n");
	printf("\t%-8s:%d\n", "代码行数", codeAnalysis->codeLineCount);
	printf("\t%-8s:%d\n", "注释行数", codeAnalysis->commentLineCount);
	printf("\t%-8s:%d\n", "空行数 ", codeAnalysis->emptyLineCount);
	printf("\t\n");
	printf("\t%s  %s  %s\n", "代码比率", "注释比率", "空行比率");
	printf("\t%s  %s  %s\n", "========", "======== ", "========");
	int pureCodeLine = codeAnalysis->codeLineCount - codeAnalysis->commentLineCount - codeAnalysis->emptyLineCount;
	int emptyLineRate = calculate(codeAnalysis->emptyLineCount, codeAnalysis->codeLineCount);
	int commentRate = calculate(codeAnalysis->commentLineCount, codeAnalysis->codeLineCount);

	printf("\t%-2d%%        %-2d%%       %-2d%%\n\n", calculate(pureCodeLine, codeAnalysis->codeLineCount),
		commentRate, emptyLineRate);

	printf("具体分析结果如下:\n\n");
	FunctionAnalysis *next = codeAnalysis->functionAnalysis;
	printf("\t%s:%d\n", next->functionName, next->codeLineCount);
	next = next->next;
	printf("\n");

	while (next != NULL)
	{
	printf("\t函数名:%s\n", next->functionName);
	printf("\t代码总行数:%d\n", next->codeLineCount);
	printf("\n");
	next = next->next;
	}
}

/*
	输出书上示例的结果
*/
void showEnglish(CodeAnalysis *codeAnalysis) {
	printf("\n");
	printf("The results of analysing program file \"%s\":\n", codeAnalysis->fileName);
	printf("\n");
	printf("\t%-18s:%d\n","Lines of code",codeAnalysis->codeLineCount);
	printf("\t%-18s:%d\n", "Lines of comments",codeAnalysis->commentLineCount);
	printf("\t%-18s:%d\n", "Blank lines",codeAnalysis->emptyLineCount);
	printf("\t\n");
	printf("\t%s  %s  %s\n", "Code", "Comment", "Space");
	printf("\t%s  %s  %s\n", "====", "=======", "=====");
	
	int pureCodeLine = codeAnalysis->codeLineCount - codeAnalysis->commentLineCount - codeAnalysis->emptyLineCount;
	int emptyLineRate = calculate(codeAnalysis->emptyLineCount, codeAnalysis->codeLineCount);
	int commentRate = calculate(codeAnalysis->commentLineCount, codeAnalysis->codeLineCount);
	
	printf("\t%-2d%%   %-2d%%      %-2d%%\n", calculate(pureCodeLine, codeAnalysis->codeLineCount),
		commentRate, emptyLineRate);
	printf("\n");
	printf("\tThe program includes %d functions.\n", codeAnalysis->functionAnalysis->codeLineCount);

	printf("\tThe average lengths of a section of code is %.1f lines.\n", calculateAverage(codeAnalysis));
	printf("\n");

	char evaluate[10] = { 0 };
	char grade = evaluateCodeStyle(pureCodeLine,evaluate);
	printf("\tGrade %C: %s routine size style.\n", grade, evaluate);
	
	memset(evaluate, 0, sizeof(char));
	grade = evaluateCommentStyle(commentRate, evaluate);
	printf("\tGrade %C: %s commenting style.\n", grade, evaluate);
	
	memset(evaluate, 0, sizeof(char));
	grade = evaluateEmptyLineStyle(emptyLineRate, evaluate);
	printf("\tGrade %C: %s empty line style.\n", grade, evaluate);
	printf("\n");
}

/*
	计算所有函数的平均长度
*/
float calculateAverage(CodeAnalysis *codeAnalysis){
	int functioncount = codeAnalysis->functionAnalysis->codeLineCount;
	int sumOfCodeLine = 0;
	FunctionAnalysis *next = codeAnalysis->functionAnalysis->next;
	while (next != NULL)
	{
		sumOfCodeLine += next->codeLineCount;
		next = next->next;
	}
	return (float)(sumOfCodeLine * 1.0 / functioncount);
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

char evaluateCodeStyle(int codeLine, char *evaluate) {
	if (codeLine >= 10 && codeLine <= 15)
	{
		sprintf(evaluate,"%s",EVALUATE_EXCELLENT);
		return 'A';
	}
	else if ((codeLine >= 8 && codeLine <= 9) || (codeLine >= 16 && codeLine <= 20))
	{
		sprintf(evaluate, "%s", EVALUATE_AWSOME);
		return 'B';
	}
	else if ((codeLine >= 5 && codeLine <= 7) || (codeLine >= 21 && codeLine <= 24))
	{
		sprintf(evaluate, "%s", EVALUATE_GREATE);
		return 'C';
	}
	else if (codeLine < 5 || codeLine > 24)
	{
		sprintf(evaluate, "%s", EVALUATE_GOOD);
		return 'D';
	}
	else
	{
		//特殊情况其实就是D,但是还是要把书上的条件写出来
		sprintf(evaluate, "%s", EVALUATE_GOOD);
		return 'D';
	}
}
char evaluateCommentStyle(int commentRate, char *evaluate) {
	if (commentRate >= 15 && commentRate <= 25)
	{
		sprintf(evaluate, "%s", EVALUATE_EXCELLENT);
		return 'A';
	}
	else if ((commentRate >= 10 && commentRate <= 14) || (commentRate >= 26 && commentRate <= 30))
	{
		sprintf(evaluate, "%s", EVALUATE_AWSOME);
		return 'B';
	}
	else if ((commentRate >= 5 && commentRate <= 9) || (commentRate >= 31 && commentRate <=	35))
	{
		sprintf(evaluate, "%s", EVALUATE_GREATE);
		return 'C';
	}
	else if (commentRate < 5 || commentRate > 35)
	{
		sprintf(evaluate, "%s", EVALUATE_GOOD);
		return 'D';
	}
	else
	{
		//特殊情况其实就是D,但是还是要把书上的条件写出来
		sprintf(evaluate, "%s", EVALUATE_GOOD);
		return 'D';
	}
}
char evaluateEmptyLineStyle(int emptyLineRate, char *evaluate) {
	if (emptyLineRate >= 15 && emptyLineRate <= 25)
	{
		sprintf(evaluate, "%s", EVALUATE_EXCELLENT);
		return 'A';
	}
	else if ((emptyLineRate >= 10 && emptyLineRate <= 14) || (emptyLineRate >= 26 && emptyLineRate <= 30))
	{
		sprintf(evaluate, "%s", EVALUATE_AWSOME);
		return 'B';
	}
	else if ((emptyLineRate >= 5 && emptyLineRate <= 9) || (emptyLineRate >= 31 && emptyLineRate <=	35))
	{
		sprintf(evaluate, "%s", EVALUATE_GREATE);
		return 'C';
	}
	else if (emptyLineRate < 5 || emptyLineRate > 35)
	{
		sprintf(evaluate, "%s", EVALUATE_GOOD);
		return 'D';
	}
	else
	{
		//特殊情况其实就是D,但是还是要把书上的条件写出来
		sprintf(evaluate, "%s", EVALUATE_GOOD);
		return 'D';
	}
}