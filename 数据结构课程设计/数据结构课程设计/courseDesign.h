#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Stack.h"

#define BUFFER_SIZE 150

#define FILE_PATH "C:\\Users\\ZhangHao\\Desktop\\test.c"
//#define FILE_PATH "F:\\Code_Sets\\C_Code\\程序基础练习题\\程序基础练习题"
#define OPEN_FILE_ERROR "文件打开失败!"
#define FUNCTION_COUNT "函数总数"

#define BOOL int
#define SIGN_MULTIPLE_COMMENT '*'
#define SIGN_BLOCK '{'
#define NAME_SIZE 80

typedef struct FunctionAnalysis {
	char functionName[NAME_SIZE];
	int codeLineCount;//所有行数,包括注释和空行
	struct FunctionAnalysis *next;
}FunctionAnalysis;

typedef struct CodeAnalysis {
	char fileName[NAME_SIZE];
	int codeLineCount;//代码总行数
	int commentLineCount;//注释总行数
	int emptyLineCount;//空行总行数
	FunctionAnalysis *functionAnalysis;
}CodeAnalysis;

void inputFileName(char *fileName);
void output(char *content);
BOOL isEmptyLine(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
BOOL isComment(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
BOOL isFunction(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
void isBlock(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
void handleLineString(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);

int skipSpace(char *lineString, int index);
BOOL isLegalIdentifier(char *identifier);
BOOL isLegalFirstCharacter(char character);
BOOL isLegalCharacter(char character);
BOOL copyAndCheckIdentifier(char *buffer,char *source,int *sourceIndex);
BOOL isOperator(char character);
void increaseCodeCount(CodeAnalysis *codeAnalysis, Stack *signStack);