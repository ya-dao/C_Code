#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>

#define TRUE 1
#define FALSE 0
#define HOST_NUMBER "hostNumber"
#define ATTACK_COUNT "attackCount"
#define INDICATOR_IP 1
#define INDICATOR_MAC 2

int hostNumber;//需要攻击的主机数量
int attackCount;//需要攻击的次数
unsigned long gatewayIP; //网关IP
unsigned char gatewayMac[6]; //网关MAC
unsigned long *fakeIps; //要伪装成的IP地址列表
//需要攻击的主机MAC地址列表,其数量未知,暂时用数组指针表示
unsigned char(*attackHostMacs)[6];

void loadConfig();
int isSpaceLine(char *buffer);
void init();
int loadIPOrMac(char *buffer, int contentIndicator, unsigned long *ip, unsigned char *mac, int hostId);

int main() {
	loadConfig();
	system("pause");
	return 0;
}
/*
加载配置文件并初始化其内容
功能 : 获得当前工作目录.
char* _getcwd(char *buffer, int maxlen);
*/
void loadConfig() {
	char buffer[300] = { 0 };

	FILE *config = fopen("./config.txt", "r");
	if (config == NULL)
	{
		fprintf(stderr, "当前路径中不存在config.txt配置文件,请检查!\n");
		free(config);
		config = NULL;
		exit(-1);
	}
	//指明有内容的行是存放的IP还是MAC,1表示IP,2表示MAC
	int contentIndicator = 0;
	//当前读取的主机序号
	int hostId = 0;
	int i = 0;
	while (!feof(config))
	{
		fgets(buffer, 300, config);

		if (buffer[0] == '#')
		{
			continue;
		}
		else if (TRUE == isSpaceLine(buffer)) {
			//在空行时,重置其为IP
			contentIndicator = INDICATOR_IP;
			continue;
		}
		else if (strstr(buffer, HOST_NUMBER) != NULL)
		{
			sscanf(buffer, "hostNumber=%d", &hostNumber);
			//读取到主机数量就可以开始初始化了
			init();
		}
		else if (strstr(buffer, ATTACK_COUNT) != NULL)
		{
			//读取攻击次数
			sscanf(buffer, "attackCount=%d", &attackCount);
		}
		else
		{
			//读取网关的IP和MAC
			if (hostId == 0)
			{
				hostId = loadIPOrMac(buffer, contentIndicator, &gatewayIP, gatewayMac, hostId);
			}
			else {
				hostId = loadIPOrMac(buffer, contentIndicator, &fakeIps[hostId - 1], attackHostMacs[hostId - 1], hostId);
			}
			contentIndicator++;
		}
	}

	fclose(config);
	config = NULL;
}

/*
初始化变量
*/
void init() {
	fakeIps = (unsigned long *)calloc(hostNumber, sizeof(unsigned long));
	attackHostMacs = (unsigned char(*)[6])calloc(hostNumber, sizeof(char) * 6);
}

/*
读取IP或MAC
*/
int loadIPOrMac(char *buffer, int contentIndicator, unsigned long *ip, unsigned char *mac, int hostId) {
	if (contentIndicator == INDICATOR_IP)
	{
		(*ip) = inet_addr(buffer);
	}
	else if (contentIndicator == INDICATOR_MAC) {
		sscanf(buffer, "%hhX-%hhX-%hhX-%hhX-%hhX-%hhX",
			&mac[0], &mac[1], &mac[2],
			&mac[3], &mac[4], &mac[5]);
		//读取完MAC之后该主机所有内容才算读取完毕
		hostId++;
	}
	return hostId;
}

/*
判断当前行是否为空行,fgets读取空行会返回'\n',所以判断方法如下:
1.如果以'\n'开始,则是空行
2.如果遇到'\n'之前的所有字符都为' '空格,也是空行
*/
int isSpaceLine(char *buffer) {
	if (buffer == NULL)
	{
		return TRUE;
	}
	if (buffer[0] == '\n') {
		return TRUE;
	}
	for (int i = 0; buffer[i] != '\n'; i++)
	{
		if (buffer[i] != ' ')
		{
			return FALSE;
		}
	}
	return TRUE;
}