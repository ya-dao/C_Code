#include "Constant.h"
#include "Structs.h"

void inputFileName(char *fileName);
STATUS openFile(FILE **file, char *fileName);

//通用方法
void showString(char *string);
DWORD charToDWORD(char *buffer, int size, int isCharacter);
STATUS seekAndReadFile(FILE *file, int size, int offset, void *result, int isCharacter);

//解析的方法
STATUS parseDosHeaderStruct(IMAGE_DOS_HEADER_STRUCT *dosHeader,FILE *file);
STATUS parseNTHeadersStruct(IMAGE_NT_HEADERS_STRUCT *ntHeader, FILE *file);
STATUS parsePESignature(IMAGE_NT_HEADERS_STRUCT *ntHeaders, FILE *file);
STATUS parseFileHeaderStruct(IMAGE_FILE_HEADER_STRUCT *fileHeaders, FILE *file);
STATUS parseOptionalHeaderStruct(IMAGE_OPTIONAL_HEADER32_STRUCT *optionalHeaders, FILE *file);
STATUS parseDataDirectoryStruct(IMAGE_DATA_DIRECTORY_STRUCT *dataDirectoryHeaders, FILE *file, int directoryIndex);
STATUS parseSectionStruct(IMAGE_SECTION_HEADER_STRUCT *sectionHeader, FILE *file, int index);

void showDosHeader(IMAGE_DOS_HEADER_STRUCT *dosHeader);
void showNTHeader(IMAGE_NT_HEADERS_STRUCT *ntHeader);
void showSectionHeader(IMAGE_SECTION_HEADER_STRUCT *sectionHeader, int sectionCount);