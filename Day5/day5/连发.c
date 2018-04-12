#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
void killQQ() {
	system("taskkill /f /im QQ.exe");
	MessageBoxA(0, "少上点网,上网伤身,来,我们看励志的网站", "麻花腾开车了:", 0);
	ShellExecuteA(0, "open", "http://www.hh99.me", 0, 0, 0);
}
int main() {
	killQQ();
	return 0;
}