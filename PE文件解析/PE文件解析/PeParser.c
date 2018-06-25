#include "PeParser.h"

void inputFileName(char *fileName) {
	showString(TIPS_INPUT_FILE_PATH);
	gets(fileName);
}

STATUS openFile(FILE **file,char *fileName) {
	*file = fopen(fileName,"r");
	if (*file != NULL)
	{
		return SUCCESS;
	}
	else {
		return FAILURE;
	}
}

STATUS parseDosHeaderStruct(IMAGE_DOS_HEADER_STRUCT *dosHeader,FILE *file) {
	if (dosHeader == NULL) {
		return FAILURE;
	}

	char buffer[5] = { 0 };
	int size = fread(buffer, sizeof(WORD), 1, file);
	if (size != 0)
	{
		//showString(buffer);
		dosHeader->e_magic = (WORD)charToDWORD(buffer, sizeof(WORD), CHARACTER);
		fseek(file, 0 - sizeof(WORD), SEEK_CUR);

		int result = seekAndReadFile(file, sizeof(DWORD), OFFSET_ELFANEW, &(dosHeader->e_lfanew), NOT_CHARACTER);
		if (result == FSEEK_ERROR)
		{
			return FAILURE;
		}
		else
		{
			return SUCCESS;
		}
	}
	else {
		return FAILURE;
	}
}

STATUS parseNTHeadersStruct(IMAGE_NT_HEADERS_STRUCT *ntHeaders, FILE *file) {
	//1.PE文件标识
	STATUS status = parsePESignature(ntHeaders, file);
	if (status == FAILURE) {
		showString(ERROR_ON_PARSE_PE_SIGNATURE);
		return FAILURE;
	}

	//2.文件头
	ntHeaders->fileHeader = (IMAGE_FILE_HEADER_STRUCT *)malloc(sizeof(IMAGE_FILE_HEADER_STRUCT));
	status = parseFileHeaderStruct(ntHeaders->fileHeader, file);
	if (status == FAILURE) {
		showString(ERROR_ON_PARSE_FILE_HEADER);
		return FAILURE;
	}

	//3.可选头
	ntHeaders->optionalHeader = (IMAGE_OPTIONAL_HEADER32_STRUCT *)malloc(sizeof(IMAGE_OPTIONAL_HEADER32_STRUCT));
	status = parseOptionalHeaderStruct(ntHeaders->optionalHeader, file);
	if (status == FAILURE) {
		showString(ERROR_ON_PARSE_OTPIONAL_HEADER);
		return FAILURE;
	}
	return SUCCESS;
}

STATUS parsePESignature(IMAGE_NT_HEADERS_STRUCT *ntHeader, FILE *file) {
	if (file == NULL || ntHeader == NULL) {
		return FAILURE;
	}
	int result = seekAndReadFile(file, sizeof(DWORD), OFFSET_NT_HEADERS, &(ntHeader->signature), CHARACTER);
	if (result == FSEEK_ERROR)
	{
		return FAILURE;
	}
	return SUCCESS;
}

STATUS parseFileHeaderStruct(IMAGE_FILE_HEADER_STRUCT *fileHeaders, FILE *file) {
	if (file == NULL || fileHeaders == NULL) {
		return FAILURE;
	}
	//1.先从文件起始地址跳到PE头的位置
	int flag = fseek(file, OFFSET_NT_HEADERS, SEEK_SET);
	if (flag == FSEEK_ERROR)
	{
		return FAILURE;
	}

	//2.基于PE头,读取Machine字段
	flag = seekAndReadFile(file, sizeof(WORD), OFFSET_MACHINE, &(fileHeaders->machine), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}

	//3.基于PE头,读取NumberOfSections字段
	flag = seekAndReadFile(file, sizeof(WORD), OFFSET_NUMBER_OF_SECTIONS, &(fileHeaders->numberOfSections), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}

	//4.基于PE头,读取SizeOfOptionalHeader字段
	flag = seekAndReadFile(file, sizeof(WORD), OFFSET_SIZE_OF_OPTIONAL_HEADER, &(fileHeaders->sizeOfOptionalHeader), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	
	//5.基于PE头,读取Characteristics字段
	flag = seekAndReadFile(file, sizeof(WORD), OFFSET_CHARACTERISTICS, &(fileHeaders->characteristics), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}

	//6.解析完,将指针先偏移回文件起始地址
	fseek(file, 0 - OFFSET_NT_HEADERS, SEEK_CUR);
	return SUCCESS;
}
STATUS parseOptionalHeaderStruct(IMAGE_OPTIONAL_HEADER32_STRUCT *optionalHeaders, FILE *file) {
	if (file == NULL || optionalHeaders == NULL) {
		return FAILURE;
	}
	//1.将指针偏移到PE头处
	int flag = fseek(file, OFFSET_NT_HEADERS, SEEK_SET);
	if (flag == FSEEK_ERROR)
	{
		return FAILURE;
	}
	//2.基于PE头,读取Magic字段
	flag = seekAndReadFile(file, sizeof(WORD), OFFSET_MAGIC, &(optionalHeaders->magic), CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//3.基于PE头,读取SizeOfCode字段
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_MAGIC, &(optionalHeaders->sizeOfCode), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//4.基于PE头,读取AddressOfEntryPoint字段
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_ADDRESS_OF_ENTRY_POINT, &(optionalHeaders->addressOfEntryPoint), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//5.基于PE头,读取BaseOfCode字段
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_BASE_OF_CODE, &(optionalHeaders->baseOfCode), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//6.基于PE头,读取BaseOfData字段
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_BASE_OF_DATA, &(optionalHeaders->baseOfData), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//7.基于PE头,读取ImageBase字段
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_IMAGE_BASE, &(optionalHeaders->imageBase), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//8.基于PE头,读取SectionAlignment字段
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_SECTION_ALIGNMENT, &(optionalHeaders->sectionAlignment), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//9.基于PE头,读取FileAlignment字段
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_FILE_ALIGNMENT, &(optionalHeaders->fileAlignment), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//10.基于PE头,读取SizeOfImage字段
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_SIZE_OF_IMAGE, &(optionalHeaders->sizeOfImage), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//11.基于PE头,读取SizeOfHeader字段
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_SIZE_OF_HEADERS, &(optionalHeaders->sizeOfHeaders), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//12.基于PE头,读取Subsystem字段
	flag = seekAndReadFile(file, sizeof(WORD), OFFSET_SUBSYSTEM, &(optionalHeaders->subsystem), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//13.基于PE头,读取numberOfRvaAndSizes字段
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_NUMBER_OF_RVA_AND_SIZE, &(optionalHeaders->numberOfRvaAndSizes), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}

	//14.读取数组目录第2个和第13个元素(下标从0起)
	optionalHeaders->dataDirectories = (IMAGE_DATA_DIRECTORY_STRUCT *)malloc((sizeof(DWORD) * 2 + sizeof(int)) * 2);
	//1.解析第2个元素
	optionalHeaders->dataDirectories[0].id = 2;
	parseDataDirectoryStruct(&(optionalHeaders->dataDirectories[0]), file, 1);
	//2.解析第13个元素
	optionalHeaders->dataDirectories[1].id = 13;
	parseDataDirectoryStruct(&(optionalHeaders->dataDirectories[1]), file, 12);
	//回退指针
	fseek(file, 0 - OFFSET_NT_HEADERS, SEEK_CUR);
	return SUCCESS;
}
STATUS parseDataDirectoryStruct(IMAGE_DATA_DIRECTORY_STRUCT *dataDirectoryHeaders, FILE *file, int directoryIndex) {
	if (file == NULL || dataDirectoryHeaders == NULL) {
		return FAILURE;
	}
	//基于NT_HEADER,偏移到数据目录
	int flag = fseek(file, OFFSET_DATA_DIRECTORY, SEEK_CUR);
	if (flag == FSEEK_ERROR)
	{
		return FAILURE;
	}
	
	//读取第directoryIndex个DATA_DIRECTORY,单个DATA_DIRECTORY大小为sizeof(DWORD) * 2
	//1.读取VIRTUAL_ADDRESS
	flag = seekAndReadFile(file, sizeof(DWORD), (sizeof(DWORD) * 2) * directoryIndex, &(dataDirectoryHeaders->virtualAddress), NOT_CHARACTER);
	if (flag == FSEEK_ERROR)
	{
		return FAILURE;
	}

	//2.读取iSize
	flag = seekAndReadFile(file, sizeof(DWORD), (sizeof(DWORD) * 2) * directoryIndex + sizeof(DWORD), &(dataDirectoryHeaders->iSize), NOT_CHARACTER);
	if (flag == FSEEK_ERROR)
	{
		return FAILURE;
	}

	//回退到NT_HEADER
	fseek(file, 0 - OFFSET_DATA_DIRECTORY, SEEK_CUR);
	return SUCCESS;
}

/*
	解析指定的某个Section_Header
*/
STATUS parseSectionStruct(IMAGE_SECTION_HEADER_STRUCT *sectionHeader, FILE *file ,int index) {
	if (file == NULL || sectionHeader == NULL) {
		return FAILURE;
	}
	//偏移到节表位置
	int flag = fseek(file, OFFSET_IMAGE_SECTION_HEADER, SEEK_SET);
	if (flag == FSEEK_ERROR)
	{
		return FAILURE;
	}

	//1.手动解析段名
	flag = fseek(file, SIZE_OF_SECTION * index, SEEK_CUR);
	if (flag == FSEEK_ERROR)
	{
		return FAILURE;
	}
	flag = fread(sectionHeader->Name, IMAGE_SIZEOF_SHORT_NAME, 1, file);
	if (flag == FREAD_ERROR)
	{
		return FAILURE;
	}
	flag = fseek(file, 0 - (SIZE_OF_SECTION * index + IMAGE_SIZEOF_SHORT_NAME), SEEK_CUR);
	if (flag == FSEEK_ERROR)
	{
		return FAILURE;
	}

	//2.解析Union中的VirtualSize
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_UNION_MISC + SIZE_OF_SECTION * index, &(sectionHeader->Misc.VirtualSize), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//3.解析VirtualAddress
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_VIRTUAL_ADDRESS + SIZE_OF_SECTION * index, &(sectionHeader->VirtualAddress), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//4.解析SIZE_OF_RAW_DATA
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_SIZE_OF_RAW_DATA + SIZE_OF_SECTION * index, &(sectionHeader->SizeOfRawData), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//4.解析POINT_TO_RAW_DATA
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_POINT_TO_RAW_DATA + SIZE_OF_SECTION * index, &(sectionHeader->PointerToRawData), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//5.解析characteristics
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_SECTION_CHARACTERISTICS + SIZE_OF_SECTION * index, &(sectionHeader->Characteristics), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}

	fseek(file, 0 - OFFSET_IMAGE_SECTION_HEADER, SEEK_CUR);
	return SUCCESS;
}