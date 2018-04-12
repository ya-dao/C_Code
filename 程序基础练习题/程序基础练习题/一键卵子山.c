#include<Windows.h>

void onInit();
void onDestroy();
void luanzishan_1p();
void luanzishan_2p();
int getScanCode(int code);
void registerQuickPower();

int WINAPI WinMain(HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow) {

	onInit();

	MSG msg;
	while (GetMessage(&msg,NULL,0,0))
	{
		if (msg.message == WM_HOTKEY)
		{
			if (msg.wParam == 0x1)
			{
				MessageBoxA(NULL,"开启成功","提示",0);
				registerQuickPower();
			}

			if (msg.wParam == 0x3)
			{
				luanzishan_1p();
			}

			if (msg.wParam == 0x4)
			{
				luanzishan_2p();
			}

			if (msg.wParam == 0x2)
			{
				MessageBoxA(NULL, "关闭成功", "提示", 0);
				onDestroy();
			}
		}
	}
}

void onInit() {
	//注册开启一键卵子山热键
	RegisterHotKey(NULL, 0x1, 0, VK_HOME);

	//注册退出热键
	RegisterHotKey(NULL, 0x2, 0, VK_END);

	MessageBoxA(NULL, "卵子山天下第一!", "提示", 0);
}

void onDestroy() {
	//解除一键卵子山热键
	UnregisterHotKey(NULL, 0x1);

	//解除退出热键
	UnregisterHotKey(NULL, 0x2);

	//解除卵子山热键
	UnregisterHotKey(NULL, 0x3);
	UnregisterHotKey(NULL, 0x4);

	exit(0);
}

void registerQuickPower() {
	//注册一键卵子山热键
	RegisterHotKey(NULL, 0x3, 0, 'Y');
	RegisterHotKey(NULL, 0x4, 0, 'O');
}

//一键卵子山(1P)
//164636d+D
//通过comoboMaker观察得出,第一个斜方向必须停留2帧以上,4268四个方向可以只有1帧
//kw模拟器中一帧至少在40以上
void luanzishan_1p() {
	////1
	//keybd_event('A', getScanCode('A'), 0, 0);
	//keybd_event('S', getScanCode('S'), 0, 0);
	//Sleep(70);
	//keybd_event('A', getScanCode('A'), 2, 0);
	//keybd_event('S', getScanCode('S'), 2, 0);

	////6
	//keybd_event('D', getScanCode('D'), 0, 0);
	//Sleep(40);
	//keybd_event('D', getScanCode('D'), 2, 0);
	//
	////4
	//keybd_event('A', getScanCode('A'), 0, 0);
	//Sleep(40);
	//keybd_event('A', getScanCode('A'), 2, 0);
	//
	////6
	//keybd_event('D', getScanCode('D'), 0, 0);
	//Sleep(40);
	//keybd_event('D', getScanCode('D'), 2, 0);
	////3
	//keybd_event('S', getScanCode('S'), 0, 0);
	//keybd_event('D', getScanCode('D'), 0, 0);
	//Sleep(70);
	//keybd_event('S', getScanCode('S'), 2, 0);
	//keybd_event('D', getScanCode('D'), 2, 0);

	////6
	//keybd_event('D', getScanCode('D'), 0, 0);
	//Sleep(40);
	//keybd_event('D', getScanCode('D'), 2, 0);

	//keybd_event('I', getScanCode('I'), 0, 0);
	//Sleep(40);
	//keybd_event('I', getScanCode('I'), 2, 0);
}

//一键卵子山(2P)
//346414+D
void luanzishan_2p() {
	//3
	keybd_event('D', getScanCode('D'), 0, 0);
	keybd_event('S', getScanCode('S'), 0, 0);
	Sleep(70);
	keybd_event('D', getScanCode('D'), 2, 0);
	keybd_event('S', getScanCode('S'), 2, 0);

	//4
	keybd_event('A', getScanCode('A'), 0, 0);
	Sleep(40);
	keybd_event('A', getScanCode('A'), 2, 0);

	//6
	keybd_event('D', getScanCode('D'), 0, 0);
	Sleep(40);
	keybd_event('D', getScanCode('D'), 2, 0);

	//4
	keybd_event('A', getScanCode('A'), 0, 0);
	Sleep(40);
	keybd_event('A', getScanCode('A'), 2, 0);
	//1
	keybd_event('S', getScanCode('S'), 0, 0);
	keybd_event('A', getScanCode('A'), 0, 0);
	Sleep(70);
	keybd_event('S', getScanCode('S'), 2, 0);
	keybd_event('A', getScanCode('A'), 2, 0);

	//4
	keybd_event('A', getScanCode('A'), 0, 0);
	Sleep(40);
	keybd_event('A', getScanCode('A'), 2, 0);

	keybd_event('I', getScanCode('I'), 0, 0);
	Sleep(40);
	keybd_event('I', getScanCode('I'), 2, 0);
}

/*
	八神左边跑抓
*/
void loriLeftGrip() {
	keybd_event('D', getScanCode('D'), 2, 0);
	keybd_event('A', getScanCode('A'), 0, 0);
	Sleep(17);
	keybd_event('S', getScanCode('S'), 0, 0);
	Sleep(17);
	keybd_event('A', getScanCode('A'), 2, 0);
	Sleep(17);
	keybd_event('S', getScanCode('S'), 2, 0);

	Sleep(17);
	keybd_event('D', getScanCode('D'), 0, 0);
	Sleep(17);
	keybd_event('I', getScanCode('I'), 0, 0);
	Sleep(17);
	keybd_event('D', getScanCode('D'), 2, 0);
	Sleep(17);
	keybd_event('I', getScanCode('I'), 2, 0);
}

int getScanCode(int code) {
	return MapVirtualKey(code,MAPVK_VK_TO_VSC);
}