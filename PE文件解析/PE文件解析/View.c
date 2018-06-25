#include "PeParser.h"
void showDosHeader(IMAGE_DOS_HEADER_STRUCT *dosHeader) {
	printf("IMAGE_DOS_HEADER_STRUCT:\n");
	printf("\t-e_magic:%X\n",dosHeader->e_magic);
	printf("\t-e_lfanew:%X\n", dosHeader->e_lfanew);
}
void showNTHeader(IMAGE_NT_HEADERS_STRUCT *ntHeader) {
	printf("IMAGE_NT_HEADER_STRUCT:\n");
	printf("\t-signature:%X\n", ntHeader->signature);
	//FileHeader
	printf("\t-FileHeader:\n");
	printf("\t\t-machine:%X\n", ntHeader->fileHeader->machine);
	printf("\t\t-numberOfSections:%X\n", ntHeader->fileHeader->numberOfSections);
	printf("\t\t-sizeOfOptionalHeader:%X\n", ntHeader->fileHeader->sizeOfOptionalHeader);
	//OptionalHeader
	printf("\t-OptionalHeader:\n");
	printf("\t\t-magic:%X\n", ntHeader->optionalHeader->magic);
	printf("\t\t-sizeOfCode:%X\n", ntHeader->optionalHeader->sizeOfCode);
	printf("\t\t-addressOfEntryPoint:%X\n", ntHeader->optionalHeader->addressOfEntryPoint);
	printf("\t\t-baseOfCode:%X\n", ntHeader->optionalHeader->baseOfCode);
	printf("\t\t-baseOfData:%X\n", ntHeader->optionalHeader->baseOfData);
	printf("\t\t-imageBase:%X\n", ntHeader->optionalHeader->imageBase);
	printf("\t\t-sectionAlignment:%X\n", ntHeader->optionalHeader->sectionAlignment);
	printf("\t\t-fileAlignment:%X\n", ntHeader->optionalHeader->fileAlignment);
	printf("\t\t-sizeOfImage:%X\n", ntHeader->optionalHeader->sizeOfImage);
	printf("\t\t-sizeOfHeaders:%X\n", ntHeader->optionalHeader->sizeOfHeaders);
	printf("\t\t-subsystem:%X\n", ntHeader->optionalHeader->subsystem);
	printf("\t\t-numberOfRvaAndSizes:%X\n", ntHeader->optionalHeader->numberOfRvaAndSizes);
	//DataDirectory
	printf("\t-DataDirectory:\n");
	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			printf("\t\t-%s:\n", "Import Table");
		}
		else
		{
			printf("\t\t-%s:\n", "Import Address Table");
		}
		printf("\t\t-virtualAddress:%X\n", ntHeader->optionalHeader->dataDirectories[i].virtualAddress);
		printf("\t\t-iSize:%X\n", ntHeader->optionalHeader->dataDirectories[i].iSize);
	}
}

void showSectionHeader(IMAGE_SECTION_HEADER_STRUCT *sectionHeader, int sectionCount) {
	printf("IMAGE_SECTION_HEADER:\n");
	for (int i = 0; i < sectionCount; i++)
	{
		printf("\t-e_magic:%s\n", sectionHeader[i].Name);
		printf("\t-VirtualSize:%X\n", sectionHeader[i].Misc.VirtualSize);
		printf("\t-VirtualAddress:%X\n", sectionHeader[i].VirtualAddress);
		printf("\t-SizeOfRawData:%X\n", sectionHeader[i].SizeOfRawData);
		printf("\t-PointerToRawData:%X\n", sectionHeader[i].PointerToRawData);
		printf("\t-Characteristics:%X\n", sectionHeader[i].Characteristics);
		printf("\n");
	}
}
