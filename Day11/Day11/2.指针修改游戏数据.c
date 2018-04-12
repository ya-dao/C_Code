#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <process.h>
//本次植物大战僵尸中阳光的内存地址:1F70E168
_declspec(dllexport) void go() {
	int *p = 0x1F70E168;
	while (1) {
		if (*p < 50) {
			*p = 100;
		}
		Sleep(1000);
	}
}