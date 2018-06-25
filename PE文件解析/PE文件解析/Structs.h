#include <WINDEF.H>

typedef struct IMAGE_DOS_HEADER_STRUCT {
	WORD e_magic;//MZ签名
	DWORD e_lfanew;//PE文件头偏移,指定了PE文件头的位置
}IMAGE_DOS_HEADER_STRUCT;

typedef struct IMAGE_FILE_HEADER_STRUCT {
	WORD machine;//运行平台
	WORD numberOfSections;//PE中的节数
	WORD sizeOfOptionalHeader;//扩展头的大小
	WORD characteristics;//文件属性
}IMAGE_FILE_HEADER_STRUCT;

typedef struct IMAGE_DATA_DIRECTORY_STRUCT {
	int id;//当前表序号
	DWORD virtualAddress;//数据的起始RVA
	DWORD iSize;//数据块的长度
}IMAGE_DATA_DIRECTORY_STRUCT;

typedef struct IMAGE_OPTIONAL_HEADER32_STRUCT {
	WORD magic;//标志字,普通可执行文件为(0x010BH)
	DWORD sizeOfCode;//所有含代码的节的总大小
	DWORD addressOfEntryPoint;//程序执行入口RVA
	DWORD baseOfCode;//代码的节的起始RVA
	DWORD baseOfData;//数据的节的起始RVA
	DWORD imageBase;//程序建议装载地址(EXE通常为40000H)
	DWORD sectionAlignment;//内存中的区块对齐粒度(通常为0x1000H)
	DWORD fileAlignment;//文件中的区块对齐粒度(通常为0x20000H)
	DWORD sizeOfImage;//内存中整个PE文件的映像尺寸
	DWORD sizeOfHeaders;//所有头+节表的大小
	WORD subsystem;//文件的子系统(Windows图形程序通常为0x0002)
	DWORD numberOfRvaAndSizes;//DataDirectory项目数量,通常为16个
	IMAGE_DATA_DIRECTORY_STRUCT *dataDirectories;//数据目录数组,通常只关心第2个元素(导入目录)和第13个目录(导入函数地址目录)
}IMAGE_OPTIONAL_HEADER32_STRUCT;

typedef struct IMAGE_NT_HEADERS_STRUCT {
	DWORD signature;//PE文件标识
	IMAGE_FILE_HEADER_STRUCT *fileHeader;//文件头结构
	IMAGE_OPTIONAL_HEADER32_STRUCT *optionalHeader;//扩展头结构
}IMAGE_NT_HEADERS_STRUCT;

//个数由FILE_HEADER中的NumberOfSection + 1个空的结束符段表决定
typedef struct IMAGE_SECTION_HEADER_STRUCT {
	BYTE    Name[IMAGE_SIZEOF_SHORT_NAME];
	union {
		DWORD   PhysicalAddress;
		DWORD   VirtualSize;
	} Misc;
	DWORD   VirtualAddress;
	DWORD   SizeOfRawData;
	DWORD   PointerToRawData;
	DWORD   Characteristics;
}IMAGE_SECTION_HEADER_STRUCT;

