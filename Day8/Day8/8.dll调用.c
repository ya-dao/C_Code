#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
/*
	了解dll正常调用的流程和方法
	总结:
		1.先将dll复制到对应项目下根目录
		2.通过window.h中的loadLibraryA("dllName")获取该dll模块
		3.如果该dll载入成功,则可以通过getProcAddress("moduleName","functionName")获取对应的接口函数,然后将其转换成对应的函数指针类型
		4.直接调用该函数即可,按照有参或者无参的方式
		5.用完之后通过freeLibrary("mudouleName")释放该dll模块
*/
//函数指针,该函数名void p(参数列表)改为void (*指针名)(参数列表)
//函数指针类型原型为:void (*)(参数列表)
void (*p)();
void(*p1)(char *content);
void main() {
	HMODULE module = LoadLibraryA("待调用的dll.dll");
	if (module != NULL) {
		p = (void (*)())GetProcAddress(module, "go");
		if (p != NULL) {
			p();
		}
		else {
			MessageBoxA(0, "load function error", "error", 0);
		}
		
		p1 = (void(*)(char* content))GetProcAddress(module, "run");
		if (p1 != NULL)
		{
			p1("调用dll中有参函数成功");
		}
		else {
			MessageBoxA(0, "load function error", "error", 0);
		}
	}
	else {
		MessageBoxA(0, "load module error!", "error", 0);
	}
	FreeLibrary(module);
}