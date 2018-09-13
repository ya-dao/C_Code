#include "shell.h"

int main() {

	/*char p[] = "ab";
	printf("%d\n",strlen(p));*/

	char command[COMMAND_SIZE] = { 0 };
	char directory[DIRECTORY_SIZE] = { 0 };
	
	while (1)
	{
		getCommand(command);
		analyzeCommand(command);
	}


	system("pause");
	return 0;
}