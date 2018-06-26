//该文件存储主要的结构体和方法声明
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Stack.h"
#include "Util.h"

typedef struct FunctionAnalysis {
	//更新,代码行数决定不包含注释和空行,单独保存.
	//所有行数,包括注释和空行
	int codeLineCount;//代码行数
	int commentLineCount;//注释总行数
	int blankLineCount;//空行总行数
	char functionName[NAME_SIZE];
	struct FunctionAnalysis *next;
}FunctionAnalysis;

typedef struct CodeAnalysis {
	char fileName[NAME_SIZE];
	//更新,增加新属性,文件中总的行数.原来的代码总行数不包括注释和空行,记录其数据的方法就不再更改代码,改为代码行数=总行数-空行数-注释行数
	int totalLineCount;//总行数
	int codeLineCount;//代码总行数
	int commentLineCount;//注释总行数
	int blankLineCount;//空行总行数
	FunctionAnalysis *functionAnalysis;
}CodeAnalysis;

//主要逻辑方法
BOOL isEmptyLine(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
BOOL isComment(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
BOOL isFunction(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
void isBlock(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
void handleLineString(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
void increaseCodeCount(CodeAnalysis *codeAnalysis, Stack *signStack);
void increaseEmptyLineCount(CodeAnalysis *codeAnalysis, Stack *signStack);
void increaseCommentLineCount(CodeAnalysis *codeAnalysis, Stack *signStack);
void addFunctionNode(CodeAnalysis *codeAnalysis, char *functionName);
void popMultiply(Stack *signStack, int pushCount);
void updateTotalLineCount(CodeAnalysis *codeAnalysis);