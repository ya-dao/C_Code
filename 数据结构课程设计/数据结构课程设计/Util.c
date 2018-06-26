//该文件存储一些常用的工具方法,凡是不直接涉及到修改程序关键数据的方法都放在这里面
#include "CourseDesign.h"

void inputFilePath(char *fileName) {
	printf("注意:只支持C语言,其他类型勿扰,Dos下不支持中文路径,谢谢合作!\n");
	printf("提示:建议手动党不要挑战极限,最好直接到文件夹里找到对应文件拖进来\n\n");
	printf("例:C:\\Users\\ZhangHao\\Desktop\\test.c\n");
	printf("文件的全路径:\n");
	scanf("%s", fileName);
}
/*
	从路径中分割出文件名
*/
void getFileName(char *fileName, char *filePath){
	int startIndex = 0, endIndex = 0;
	//1.移动指针到尾部
	while (filePath[endIndex] != '\0') {
		endIndex++;
	}
	//2.移动指针到最后一个'\'处
	while (filePath[endIndex] != '\\') {
		endIndex--;
	}
	endIndex++;
	//3.复制文件名
	while (filePath[endIndex] != '\0') {
		fileName[startIndex++] = filePath[endIndex++];
	}
	fileName[startIndex++] = '\0';
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

void output(char *content) {
	printf("%s\n", content);
}

/*
跳过所有空字符,找到第一个不为' '的位置
*/
int skipSpace(char *lineString, int index) {
	while (lineString[index] != '\n' && (lineString[index] == ' ' || lineString[index] == '\t'))
	{
		index++;
	}
	return index;
}
/*
判断标识符
规则:只能用数字,字母,下划线组成且数字不打头
*/
BOOL isLegalIdentifier(char *identifier) {
	int startIndex = 0;
	int endIndex = 0;
	//过滤前面的空格
	while (identifier[startIndex] != '\0' && (identifier[startIndex] == ' ' || identifier[startIndex] == '\t'))
	{
		startIndex++;
		//同时把结尾指针往后移
		endIndex++;
	}
	//考虑指针的情况 [int] *p
	if (identifier[startIndex] != '\0')
	{
		if (identifier[startIndex] == '*' || identifier[startIndex] == '&')
		{
			startIndex++;
		}
	}
	//过滤后面的空格再考虑指针的问题 int* 
	while (identifier[startIndex] != '\0' && (identifier[startIndex] == ' ' || identifier[startIndex] == '\t'))
	{
		endIndex++;
	}
	if (identifier[endIndex] != '\0')
	{
		if (identifier[startIndex] == '*' || identifier[startIndex] == '&')
		{
			endIndex--;
		}
	}
	//标识符判断规则:不能数字开头,即除了下划线和字母,都算错
	if (isLegalFirstCharacter(identifier[startIndex]) != TRUE)
	{
		return FALSE;
	}
	startIndex++;
	while (startIndex < endIndex)
	{
		if (isLegalCharacter(identifier[startIndex]) != TRUE)
		{
			return FALSE;
		}
		startIndex++;
	}
	return TRUE;
}

//判断标识符中第一个字符是否合法
BOOL isLegalFirstCharacter(char character) {
	if ((character >= 'a' && character <= 'z')
		|| (character >= 'A' || character <= 'Z')
		|| (character == '_'))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//判断标识符中除第一个以外的每个字符是否合法
BOOL isLegalCharacter(char character) {
	if ((character >= 'a' && character <= 'z')
		|| (character >= 'A' && character <= 'Z')
		|| (character >= '0' && character <= '9')
		|| (character == '_'))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//判断逻辑运算符
BOOL isOperator(char character) {
	if (character == '&' || character == '|' || character == '^'
		|| character == '!' || character == '='
		|| character == '<' || character == '>')
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL copyAndCheckIdentifier(char *buffer, char *source, int *sourceIndex) {
	int bufferIndex = 0;
	while (source[*sourceIndex] != '\n' && source[*sourceIndex] != '\0' && (source[*sourceIndex] != '\t' && source[*sourceIndex] != ' ' && source[*sourceIndex] != '(') && source[*sourceIndex] != ')' && source[*sourceIndex] != ',')
	{
		//同时考虑有数组作为参数的情况
		if (source[*sourceIndex] != '[') {
			if (isLegalCharacter(source[*sourceIndex]) == TRUE)
			{
				buffer[bufferIndex] = source[*sourceIndex];
				bufferIndex++;
			}
			//如果字符不合法且为运算符,那就GG
			else
			{
				if (isOperator(source[*sourceIndex]) == TRUE) {
					return FALSE;
				}
			}
			(*sourceIndex)++;
		}
		//只要出现数组'[',就一直往后寻找']'
		else
		{
			while (source[*sourceIndex] != '\n' && source[*sourceIndex] != ']')
			{
				(*sourceIndex)++;
			}
			break;
		}
	}
	buffer[bufferIndex] = '\0';
	if (isLegalIdentifier(buffer) != TRUE)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}