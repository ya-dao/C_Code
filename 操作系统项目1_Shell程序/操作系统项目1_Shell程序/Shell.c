#include "shell.h"

/*
	获取显示当前工作目录的上一级目录,并返回截止到'\0'的长度
*/
int getDirectory(char *directory) {
	char *p = _getcwd(directory, DIRECTORY_SIZE);
	if (p != NULL)
	{
		directory[0] -= 32;
		return strlen(directory);
	}

	return -1;
}
/*
	获取目录,并返回接收的命令
*/
void getCommand(char *command) {
	memset(command, 0, COMMAND_SIZE);
	char directory[DIRECTORY_SIZE] = { 0 };
	int length = getDirectory(directory);

	char *p = directory;

	p[length++] = '>';
	p[length++] = '\0';

	printf("%s", directory);
	gets_s(command,COMMAND_SIZE);
}

/*
	根据输入的命令作出不同的操作响应
*/
void analyzeCommand(char *command) {
	char buffer[DIRECTORY_SIZE] = { 0 };
	int flag = UNRELATED;
	if (strcmp(command, EXIT) == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(command, CLS) == 0) {
		system("cls");
	}
	else if (strcmp(command, PAUSE) == 0) {
		system("pause");
	}
	else if (strcmp(command, DIR) == 0) {
		char directory[DIRECTORY_SIZE] = { 0 };
		getDirectory(directory);
		
		FileInfomation fileInfo;
		intptr_t fileHandle = _findfirst(strcat(directory,"*"),&fileInfo);
		if (fileHandle == -1)
		{
			printf("There is no file!\n");
		}
		else{
			int i = 0;
			char timeString[30] = { 0 };
			do {
				__time64_t time = fileInfo.time_create;
				struct tm localTime;
				errno_t errorCode = _localtime64_s(&localTime,&time);
				if (errorCode == 0)
				{
					int year = localTime.tm_year + 1900;
					int month = localTime.tm_mon + 1;
					int day = localTime.tm_mday;
					int hour = localTime.tm_hour;
					int minute = localTime.tm_min;
					sprintf(timeString, "%04d/%02d/%02d %0d:%0d", year, month, day, hour, minute);
				}
				int isDir = FALSE;
				int size = fileInfo.size;
				if (size == 0) {
					isDir = TRUE;
				}
				char *fileName = fileInfo.name;
				printf("%-s  %-5s  %-10d %-30s\n", timeString, isDir ? "<DIR>" : "", size, fileName);
				i++;
			} while (_findnext(fileHandle,&fileInfo) == 0);
		}
	}
	else if ((flag = isCdOperate(command, buffer)) != UNRELATED)
	{
		if (flag == CD_CURRENT)
		{
			char directory[DIRECTORY_SIZE] = { 0 };
			getDirectory(directory);
			printf("%s\n", directory);
		}
		else if (flag == CD_OTHERS) {
			int result = _chdir(buffer);
			if (result == -1)
			{
				printf("Failed to change directory!\n");
			}
		}

	}
	else if ((flag = isEchoOperate(command, buffer)) != UNRELATED) {
		printf("%s\n", buffer);
	}
	else if (command == HELP)
	{
		system(command);
	}
	printf("\n");
}

int isCdOperate(char *command, char *path) {
	int flag = UNRELATED;
	if (command == NULL || path == NULL || strlen(command) < 2)
	{
		return flag;
	}

	char *p = command;
	if (p[0] != 'c' || p[1] != 'd')
	{
		return flag;
	}
	if (p[2] == '\0')
	{
		flag = CD_CURRENT;
		return flag;
	}
	else if(p[2] == ' ')
	{
		flag = CD_CURRENT;
		p += 3;
		while (*p != '\0')
		{
			if (*p != ' ')
			{
				flag = CD_OTHERS;
				break;
			}
			p++;
		}
		if (flag == CD_OTHERS)
		{
			char *q = path;
			while (*p != '\0')
			{
				*q = *p;
				q++;
				p++;
			}
		}
	}
	return flag;
}

int isEchoOperate(char *command, char *comment) {
	int flag = UNRELATED;
	if (command == NULL || comment == NULL || strlen(command) < 6)
	{
		return flag;
	}

	char *p = command;
	if (p[0] != 'e' || p[1] != 'c' || p[2] != 'h' || p[3] != 'o')
	{
		return flag;
	}

	if (p[4] != ' ')
	{
		return flag;
	}
	else
	{
		p += 5;
		while (*p != '\0')
		{
			if (*p != ' ')
			{
				flag = ECHO;
				break;
			}
			p++;
		}
		if (flag == ECHO)
		{
			char *q = comment;
			while (*p != '\0')
			{
				*q = *p;
				if (*p == ' ')
				{
					while (*p == ' ' && *p != '\0')
					{
						p++;
					}
					//下面还要加1,所以先退一步
					p--;
				}
				q++;
				p++;
			}
		}
	}
	return flag;
}
