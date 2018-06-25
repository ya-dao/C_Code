//该文件存储主要的方法实现细节
#include "CourseDesign.h"

/*
	主要的判断逻辑
*/
void handleLineString(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack) {
	//判断顺序:空行->注释->函数->四不像
	if (isEmptyLine(lineString, codeAnalysis, signStack) == FALSE) {
		if (isComment(lineString, codeAnalysis, signStack) == FALSE) {
			if (isFunction(lineString, codeAnalysis, signStack) == FALSE) {
				isBlock(lineString, codeAnalysis, signStack);
			}
		}
	}
}

BOOL isEmptyLine(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack) {
	int index = skipSpace(lineString,0);
	if (lineString[index] == '\n') {
		//对总行数和空行数进行计数
		(codeAnalysis->emptyLineCount)++;
		increaseCodeCount(codeAnalysis, signStack);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL isComment(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack) {
	int index = skipSpace(lineString,0);
	//判断单行注释和多行注释起始
	if (lineString[index] == '/') {
		if (lineString[index + 1] == '/' || lineString[index + 1] == '*') {
			(codeAnalysis->commentLineCount)++;
			increaseCodeCount(codeAnalysis, signStack);
			if (lineString[index + 1] == '*')
			{
				//将当前注释块起始符压栈
				push(signStack, SIGN_MULTIPLE_COMMENT);
			}
		}
		return TRUE;
	}
	//判断多行注释结束
	else if (lineString[index] == '*') {
		if (lineString[index + 1] == '/')
		{
			//对代码行数的修改要放在出栈前,避免函数的括号出栈完了还没修改,造成函数里内的代码行数被漏加
			increaseCodeCount(codeAnalysis, signStack);
			(codeAnalysis->commentLineCount)++;
			
			pop(signStack);
		}
		return TRUE;
	}
	return FALSE;
}
/*
	函数签名应该满足的条件([]表示可选):
	[XX] YY([ZZ]){
	或者
	[XX] YY([ZZ])
	{
	重点判断'YY(){',其他鸡肋部分还是要考虑下,虽然不是必要条件
*/
BOOL isFunction(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack) {
	int index = skipSpace(lineString,0);
	char buffer[NAME_SIZE] = { 0 };
	char functionName[NAME_SIZE] = { 0 };
	//将返回类型存入buffer中
	if (copyAndCheckIdentifier(buffer, lineString, &index) == FALSE) {
		return FALSE;
	}

	index = skipSpace(lineString,index);

	//如果不是'(',则说明还有函数名,之前的是返回类型
	if (lineString[index] != '\n' && lineString[index] != '(') {
		//将函数名存入buffer中
		if (copyAndCheckIdentifier(buffer, lineString, &index) == FALSE) {
			return FALSE;
		}
		else
		{
			strcpy(functionName, buffer);
		}
	}
	//跳过空格应该来到'('了
	index = skipSpace(lineString,index);

	//如果下一个是'(',则后面是参数
	if (lineString[index] == '(')
	{
		//跳过'('及' ',检查下一个是不是')',如果不是则有参数,主要检查一个参数的情况,避免跟if/while混淆
		index++;
		index = skipSpace(lineString,index);
		while (lineString[index] != '\n' && lineString[index] != ')')
		{
			//循环遍历,以便处理const这种情况
			while (lineString[index] != ',' && lineString[index] != '\n' && lineString[index] != ')') {
				//跳过空格,检查
				if (copyAndCheckIdentifier(buffer, lineString, &index) == FALSE) {
					return FALSE;
				}
				index = skipSpace(lineString,index);
			}
			if (lineString[index] == ',')
			{
				index++;
			}
			index = skipSpace(lineString, index);
		}
	}
	else
	{
		return FALSE;
	}
	/*
		经过上面的处理之后,
		要么是处于函数参数的括号处,
		判断大括号,存在就入栈
		没有就算了,但是要判断是否存在';',区别函数声明头
	*/
	if (lineString[index] == ')')
	{
		index++;
		//如果')'到这行结束中间出现其他字符就可以认为格式不对了
		while (lineString[index] != '\n')
		{
			if (lineString[index] == '{')
			{
				push(signStack, '{');
				break;
			}
			if (lineString[index] == ';')
			{
				return FALSE;
			}
			index++;
		}
		//添加一个函数的结点
		addFunctionNode(codeAnalysis,functionName);
		//修改代码行数
		increaseCodeCount(codeAnalysis,signStack);
		return TRUE;
	}
	return FALSE;
}

/*
	增加一个新的函数统计结点到CodeAnalysis里面
*/
void addFunctionNode(CodeAnalysis *codeAnalysis,char *functionName) {
	FunctionAnalysis *function = (FunctionAnalysis *)malloc(sizeof(FunctionAnalysis));
	function->codeLineCount = 0;
	strcpy(function->functionName, functionName);
	//用头插法将其插入到第一个位置
	function->next = codeAnalysis->functionAnalysis->next;
	codeAnalysis->functionAnalysis->next = function;
	//头结点统计函数个数
	codeAnalysis->functionAnalysis->codeLineCount++;
}

/*
	其他情况,括号的入栈和出栈,其他统一算代码
*/
void isBlock(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack) {
	int index = skipSpace(lineString,0);
	//if和while等的的'{'为下一行第一个非空白字符的情况
	if (lineString[index] == '{')
	{
		push(signStack, '{');
		increaseCodeCount(codeAnalysis, signStack);
		return;
	}
	//跳过该行末尾,方便下面判断该行末尾字符的操作
	while (lineString[index] != '\n' && lineString[index] != '\0')
	{
		index++;
	}
	//清除换行符'\n'前面所有空白字符,即将指针移到倒数第一个非空白符,最后一行可能没得'\n',只有一个'\0'
	while (index >= 0 && (lineString[index] == ' ' || lineString[index] == '\t'
		|| lineString[index] == '\n' || lineString[index] == '\0')){
		index--;
	}
	//if和while等的的'{'为同一行末尾的情况,必须是位于'\n'前的唯一元素
	if (lineString[index] == '{') {
		push(signStack, SIGN_BLOCK);
		increaseCodeCount(codeAnalysis, signStack);
		return;
	}
	//结束的'}'必须是位于'\n'前的唯一元素,避免跟数组混淆,即不带分号';'
	if (lineString[index] == '}') {
		increaseCodeCount(codeAnalysis, signStack);
		pop(signStack);
		return;
	}
	increaseCodeCount(codeAnalysis, signStack);
}

/*
	对相应部分的代码行数进行增加
*/
void increaseCodeCount(CodeAnalysis *codeAnalysis, Stack *signStack) {
	(codeAnalysis->codeLineCount)++;
	//栈里有括号的时候才可能是函数里的代码,否则就是# 和 函数/变量声明 这些东西了
	if (isStackEmpty(signStack) == FALSE)
	{
		(codeAnalysis->functionAnalysis->next->codeLineCount)++;
	}
}
