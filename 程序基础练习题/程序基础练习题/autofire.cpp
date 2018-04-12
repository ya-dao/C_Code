#include <iostream>
#include <stdio.h>
#include <Windows.h>

// for key pushing
__declspec(dllexport) BYTE scan_code(DWORD pKey)
{
	const DWORD result = MapVirtualKey(pKey, 0);
	//printf("%ld\n",result);
	return static_cast<BYTE>(result);
}
__declspec(dllexport) void press_key(DWORD pKey)
{
	keybd_event(static_cast<BYTE>(pKey), scan_code(pKey), 0, 0);
}
__declspec(dllexport) void release_key(DWORD pKey)
{
	keybd_event(static_cast<BYTE>(pKey), scan_code(pKey), KEYEVENTF_KEYUP, 0);
}
// for testing
#define PRESS(x) press_key(x);
#define RELEASE(x) release_key(x);
// test
__declspec(dllexport) int go()
{
	for (;;)
	{
		PRESS('W');
		Sleep(10); // hold it for 1/100'th of a second
		RELEASE('W');
		Sleep(1000); // wait for a second
		PRESS('S');
		Sleep(10); // hold it for 1/100'th of a second
		RELEASE('S');
		Sleep(1000); // wait for a second
	}
}
