#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
//用于操作工作目录的库函数
#include<direct.h>
//操作文件目录的库函数,_finddata_t用于描述一个文件的各种信息的结构体
#include<io.h>
//用于转换时间的库函数
#include<time.h>

typedef struct _finddata_t FileInfomation;

#define TRUE 1
#define FALSE 0

#define COMMAND_SIZE 100
#define DIRECTORY_SIZE 200

#define UNRELATED 0
#define ECHO 1

#define CD_CURRENT 1
#define CD_OTHERS 2

#define DIR "dir"
#define EXIT "exit"
#define CLS "cls"
#define PAUSE "pause"
#define HELP "help"

int getDirectory(char *directory);
void getCommand(char *command);
void analyzeCommand(char *command);
int isCdOperate(char *command, char *path);
int isEchoOperate(char *command, char *comment);