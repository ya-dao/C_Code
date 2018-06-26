//该文件存储主要的结构体和方法声明
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Stack.h"
#include "Util.h"

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

//主要逻辑方法
BOOL isEmptyLine(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
BOOL isComment(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
BOOL isFunction(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
void isBlock(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
void handleLineString(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
void increaseCodeCount(CodeAnalysis *codeAnalysis, Stack *signStack);
void addFunctionNode(CodeAnalysis *codeAnalysis, char *functionName);
void popMultiply(Stack *signStack, int pushCount);