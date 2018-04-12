#include <stdio.h>
#include <Windows.h>

// for key pushing
BYTE scan_code(DWORD pKey)
{
	const DWORD result = MapVirtualKey(pKey, 0);
	printf("%ld\n",result);
	return (BYTE)(result);
}
void press_key(DWORD pKey)
{
	keybd_event((BYTE)(pKey), scan_code(pKey), 0, 0);
}
void release_key(DWORD pKey)
{
	keybd_event((BYTE)(pKey), scan_code(pKey), KEYEVENTF_KEYUP, 0);
}
// for testing
#define PRESS(x) press_key(x);
#define RELEASE(x) release_key(x);
// test
int main()
{
	Sleep(2000);
	for (int i = 0;i < 20;i++)
	{
		PRESS('3');
		Sleep(10); // hold it for 1/100'th of a second
		RELEASE('3');
		Sleep(20); // wait for a second
	}
}