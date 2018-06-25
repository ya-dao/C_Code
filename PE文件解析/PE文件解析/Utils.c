#include "PeParser.h"

void showString(char *string) {
	printf("%s\n", string);
}

/*
	将读取到的内容转换成性对应的WORD/DWORD格式
	int isCharacter:是否为标志性字符,如:"MZ"/"PE"
	由于涉及到大小端存储问题,如果不是字符则需要将高地址的内容转换为高字节
*/
DWORD charToDWORD(char *buffer, int size, int isCharacter) {
	if (buffer == NULL) {
		return FAILURE;
	}
	DWORD result = 0;
	if (size == sizeof(WORD))
	{
		//WORD MAKEWORD(BYTE bLow,	BYTE bHigh);
		//0x4D5A
		if (isCharacter == CHARACTER) {
			result = MAKEWORD(buffer[1], buffer[0]);
		}
		else
		{
			result = MAKEWORD(buffer[0], buffer[1]);
		}
	}
	else if (size == sizeof(DWORD)) {
		//DWORD MAKELONG( WORD wLow, WORD wHigh );
		if (isCharacter == CHARACTER)
		{
			WORD low = MAKEWORD(buffer[1], buffer[0]);
			WORD high = MAKEWORD(buffer[3], buffer[2]);
			result = MAKELONG(high, low);
		}
		else
		{
			WORD low = MAKEWORD(buffer[0], buffer[1]);
			WORD high = MAKEWORD(buffer[2], buffer[3]);
			result = MAKELONG(low, high);
		}
	}
	else {
		return FAILURE;
	}
	return result;
}

//读取某个字段的通用方法
STATUS seekAndReadFile(FILE *file, int size, int offset, void *result, int isCharacter) {
	//2.基于PE头,再跳到对应字段的偏移
	int flag = fseek(file, offset, SEEK_CUR);
	if (flag == FSEEK_ERROR)
	{
		return FAILURE;
	}

	char buffer[5] = { 0 };
	flag = fread(buffer, size, 1, file);
	if (flag == FREAD_ERROR)
	{
		return FAILURE;
	}

	//用完将地址偏移回来,包括刚才读取的长度
	fseek(file, 0 - (offset + size), SEEK_CUR);

	if (size == sizeof(WORD))
	{
		*((WORD *)result) = (WORD)charToDWORD(buffer, size, isCharacter);
	}
	else
	{
		*((DWORD *)result) = charToDWORD(buffer, size, isCharacter);
	}
	return SUCCESS;
}