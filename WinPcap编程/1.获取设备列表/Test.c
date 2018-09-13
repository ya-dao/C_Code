#define WIN32
/*
	pcap_findalldevs_ex函数是属性该头文件中的,文档中忘了添加该头文件.
	#include <remote-ext.h>
	但是该头文件中已经指明不能直接导入该头文件,只需要声明 HAVE_REMOTE 常量,并导入pcap.h即可
*/
#define HAVE_REMOTE
#include <stdio.h>
#include <stdlib.h>
#include "pcap.h"

int main() {
	pcap_if_t *allDevices;
	pcap_if_t *device;
	char errorBuffer[PCAP_ERRBUF_SIZE];

	int i = 0;
	/* 获取本地机器设备列表 */
	int flag = pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &allDevices, errorBuffer);
	if (flag == -1) {
		fprintf(stdout, "%s" ,errorBuffer);
		exit(1);
	}

	/*打印列表*/
	for (device = allDevices; device != NULL; device = device->next)
	{
		printf("%d: %s", ++i, device->name);
		if (device->description != NULL) {
			printf("(%s)\n", device->description);
		}
		else {
			printf("(No device available!)\n");
		}
	}

	if (i == 0) {
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
	}

	pcap_freealldevs(allDevices);
	system("pause");
	return 0;
}