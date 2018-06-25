#include "PeParser.h"
void main() {
	FILE *file = NULL;
	char fileName[100] = { 0 };
	//char fileName[100] = "C:\\Users\\ZhangHao\\Desktop\\PE\\HelloWorld.exe";
	STATUS status = 0;

	while (1) {
		inputFileName(fileName);
		status = openFile(&file,fileName);
		if (status != SUCCESS)
		{
			showString(ERROR_ON_OPEN_FILE);
		}
		else {
			break;
		}
	}
	//解析Dos中有用的两个字段
	IMAGE_DOS_HEADER_STRUCT *dosHeader = (IMAGE_DOS_HEADER_STRUCT *)malloc(sizeof(IMAGE_DOS_HEADER_STRUCT));
	status = parseDosHeaderStruct(dosHeader,file);
	if (status == FAILURE) {
		showString(ERROR_ON_PARSE_DOS);
	}

	//解析PE头
	IMAGE_NT_HEADERS_STRUCT *ntHeaders = (IMAGE_NT_HEADERS_STRUCT *)malloc(sizeof(IMAGE_NT_HEADERS_STRUCT));
	parseNTHeadersStruct(ntHeaders, file);

	//解析段表
	int sectionCount = ntHeaders->fileHeader->numberOfSections;
	IMAGE_SECTION_HEADER_STRUCT *sectionHeader = (IMAGE_SECTION_HEADER_STRUCT *)malloc(sizeof(IMAGE_SECTION_HEADER_STRUCT) * sectionCount);
	for (int i = 0; i < sectionCount; i++)
	{
		status = parseSectionStruct(&(sectionHeader[i]), file, i);
		if (status == FAILURE) {
			showString(ERROR_ON_PARSE_SECTION_HEADER);
		}
	}

	showDosHeader(dosHeader);
	printf("\n");
	showNTHeader(ntHeaders);
	printf("\n");
	showSectionHeader(sectionHeader,sectionCount);

	/*
		通常我们会犯的释放内存问题大概有以下几种：
		1.内存重复释放，出现double free时，通常是由于这种情况所致。
		2.内存泄露，分配的内存忘了释放。
		3.内存越界使用，使用了不该使用的内存。(多数情况)
		4.使用了无效指针。
		5.空指针，对一个空指针进行操作。
	*/
	free(dosHeader);
	free(ntHeaders->fileHeader);
	free(ntHeaders->optionalHeader->dataDirectories);
	free(ntHeaders->optionalHeader);
	free(ntHeaders);
	free(sectionHeader);
	fclose(file);
	system("pause");
}