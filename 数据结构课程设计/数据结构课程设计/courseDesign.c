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
		increaseEmptyLineCount(codeAnalysis, signStack);
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
			increaseCommentLineCount(codeAnalysis, signStack);

			if (lineString[index + 1] == '*')
			{
				//将当前注释块起始符压栈
				push(signStack, SIGN_MULTIPLE_COMMENT);
			}
		}
		return TRUE;
	}
	//判断多行注释结束(多行注释在下一行开始的情况
	else if (lineString[index] == '*') {
		if (lineString[index + 1] == '/')
		{
			//对代码行数的修改要放在出栈前,避免函数的括号出栈完了还没修改,造成函数里内的代码行数被漏加
			increaseCommentLineCount(codeAnalysis, signStack);
			
			pop(signStack);
			return TRUE;
		}
	}
	
	//如果栈顶是多行注释起始符,则需要随时判断结束标志符
	if (getTop(signStack) == '*')
	{
		//跳到该行末尾,方便下面判断该行末尾字符的操作(处理多行注释结束符在这一行末尾的情况)
		while (lineString[index] != '\n' && lineString[index] != '\0')
		{
			index++;
		}
		//清除换行符'\n'前面所有空白字符,即将指针移到倒数第一个非空白符,最后一行可能没得'\n',只有一个'\0'
		while (index >= 0 && (lineString[index] == ' ' || lineString[index] == '\t'
			|| lineString[index] == '\n' || lineString[index] == '\0')) {
			index--;
		}
		//多行注释结束符
		if (lineString[index] == '/')
		{
			if (lineString[index - 1] == '*')
			{
				//对代码行数的修改要放在出栈前,避免函数的括号出栈完了还没修改,造成函数里内的代码行数被漏加
				increaseCommentLineCount(codeAnalysis, signStack);

				//多行注释出栈
				pop(signStack);
				return TRUE;
			}
		}
		//如果多行注释仍未结束,直接计数即可
		else
		{
			increaseCommentLineCount(codeAnalysis, signStack);
			return TRUE;
		}
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
	//有可能一个while等条件语句里面有多个'('被入栈,而函数中检测到逻辑运算符后,函数立即返回,导致栈不平衡.
	//所以这里需要记录本次入栈次数,退出时全部出栈
	int pushCount = 0;
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
		/*
			入栈'('并跳过'('及' ',检查下一个是不是')',如果不是则有参数,主要检查一个参数的情况,避免跟if/while混淆
			入栈和出栈'('的原因是避免参数里面的(表达式),如int (*p)[3]或者while((a + b) > 3)
			这里不想只通过while/if/for等关键字来确定是不是函数,因为关键字可能有遗漏,找出差异是最好的
		*/
		push(signStack,SIGN_PARENTHESES);
		pushCount++;
		index++;
		index = skipSpace(lineString,index);
		//循环的条件不再是lineString[index] != ')',而是符号栈顶不是'(',这才代表参数列表已经读取完毕了
		while (lineString[index] != '\n' && getTop(signStack) == '(' )
		{
			//循环遍历获取参数列表的标识符,以便处理const这种情况
			while (lineString[index] != ',' && lineString[index] != '\n' && getTop(signStack) == '(') {
				//跳过空格,检查
		  		if (copyAndCheckIdentifier(buffer, lineString, &index) == FALSE) {
					popMultiply(signStack, pushCount);
					return FALSE;
				}
				//再碰到'('就继续入栈并跳过
				if (lineString[index] == '(')
				{
					push(signStack, SIGN_PARENTHESES);
					pushCount++;
					index++;
					index = skipSpace(lineString, index);
				}
				//碰到')'就继续出栈并跳过
				if (lineString[index] == ')')
				{
					pop(signStack);
					pushCount--;
					//后面需要根据参数列表结束的那个')'来判断后面的是不是'{',所以最后一个')'不跳过
					if (getTop(signStack) == '(')
					{
						index++;
					}
					index = skipSpace(lineString, index);
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
		popMultiply(signStack, pushCount);
		return FALSE;
	}
	/*
		经过上面的处理之后,
		如果是处于函数参数结束的括号处,就判断大括号,存在就入栈
		没有就算了,但是要判断末尾是否存在';',区别函数声明头
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
				popMultiply(signStack, pushCount);
				return FALSE;
			}
			index++;
		}
		//添加一个函数的结点
		addFunctionNode(codeAnalysis,functionName);
		//前面'{'已经入栈,修改文件和函数中代码行数,更新,函数代码行数只统计里面纯代码行
		//increaseCodeCount(codeAnalysis,signStack);

		//前面'{'已经入栈, 只修改文件里面的行数记录,不能调用上面的方法,否则会对函数内部进行计数
		(codeAnalysis->totalLineCount)++;
		updateTotalLineCount(codeAnalysis);

		popMultiply(signStack, pushCount);
		return TRUE;
	}
	popMultiply(signStack, pushCount);
	return FALSE;
}

/*
	根据指定的push次数进行pop
*/
void popMultiply(Stack *signStack,int pushCount) {
	while (pushCount > 0)
	{
		pop(signStack);
		pushCount--;
	}
}

/*
	增加一个新的函数统计结点到CodeAnalysis里面
*/
void addFunctionNode(CodeAnalysis *codeAnalysis,char *functionName) {
	FunctionAnalysis *function = (FunctionAnalysis *)malloc(sizeof(FunctionAnalysis));
	function->blankLineCount = 0;
	function->commentLineCount = 0;
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
		//函数定义的开头不算在代码里面,这里是处理函数定义的'{'在下一行的情况
		increaseCodeCount(codeAnalysis, signStack);
		push(signStack, '{');
		return;
	}
	//跳到该行末尾,方便下面判断该行末尾字符的操作
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
		//这里是判断函数的最后一个'}',所以要先出栈,然后看栈是否为空,为空说明刚才是函数里的最后一个'}',不计数
		pop(signStack);
		//函数定义的结束符不算在代码里面
		increaseCodeCount(codeAnalysis, signStack);
		return;
	}
	increaseCodeCount(codeAnalysis, signStack);
}

/*
	对相应部分的代码行数进行增加
*/
void increaseCodeCount(CodeAnalysis *codeAnalysis, Stack *signStack) {
	//对总行数进行计数
	(codeAnalysis->totalLineCount)++;
	//栈里有大括号的时候才可能是函数里的代码,否则就是# 和 函数/变量声明 这些东西了
	if (getBottom(signStack) == SIGN_BLOCK) {
		(codeAnalysis->functionAnalysis->next->codeLineCount)++;
	}
	//更新新加入的字段
	updateTotalLineCount(codeAnalysis);
}

/*
	对空行数进行计数
*/
void increaseEmptyLineCount(CodeAnalysis *codeAnalysis, Stack *signStack) {
	//对总行数和空行数进行计数
	(codeAnalysis->blankLineCount)++;
	(codeAnalysis->totalLineCount)++;
	//如果当前在函数里面就分别计数,不计入函数总行数
	if (getBottom(signStack) == SIGN_BLOCK) {
		(codeAnalysis->functionAnalysis->next->blankLineCount)++;
	}
	//更新新加入的字段
	updateTotalLineCount(codeAnalysis);
}

/*
	对注释行数进行计数
*/
void increaseCommentLineCount(CodeAnalysis *codeAnalysis, Stack *signStack) {
	//对总行数和注释行数进行计数
	(codeAnalysis->commentLineCount)++;
	(codeAnalysis->totalLineCount)++;
	//如果当前在函数里面就分别计数,不计入函数总行数
	if (getBottom(signStack) == SIGN_BLOCK) {
		(codeAnalysis->functionAnalysis->next->commentLineCount)++;
	}
	//更新新加入的字段
	updateTotalLineCount(codeAnalysis);
}
/*
	修改文件中的代码行数=总行数-空行数-注释行数
*/
void updateTotalLineCount(CodeAnalysis *codeAnalysis) {
	int totalLineCount = codeAnalysis->totalLineCount;
	int emptyLineCount = codeAnalysis->blankLineCount;
	int commentLineCount = codeAnalysis->commentLineCount;
	codeAnalysis->codeLineCount = totalLineCount - emptyLineCount - commentLineCount;
}