#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
	使用管道执行cmd命令获取结果
*/
void main()
{
	FILE* pipe = NULL;
	char buffer[1024] = {0};
	char *result = NULL;
	pipe = _popen("ipconfig","r");
	if(pipe == NULL){
		printf("哦豁!\n");
		return;
	}
	while(!feof(pipe)){
		fgets(buffer,1024,pipe);
		result = strstr(buffer,"IPv4 地址");
		//printf("%s\n",buffer);
		if(result != NULL){
			printf("%s\n",result);

		}
	}
	_pclose(pipe);
	system("pause");
}
