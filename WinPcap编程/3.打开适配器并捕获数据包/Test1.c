#define _CRT_SECURE_NO_WARNINGS
#define WIN32
#define HAVE_REMOTE
#include <stdio.h>
#include <stdlib.h>
#include "pcap.h"

/*
	使用回调的方式处理数据包
*/

void packetHandler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);

int main1() {
	pcap_if_t *allDevices;
	pcap_if_t *device;
	pcap_t *deviceHandler;

	char errorBuffer[PCAP_ERRBUF_SIZE];

	int i = 0, number = 0;

	/*获取并打印列表*/
	int flag = pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &allDevices, errorBuffer);
	if (-1 == flag) {
		fprintf(stderr, "%s\n", errorBuffer);
		exit(1);
	}
	for (device = allDevices; NULL != device; device = device->next) {
		printf("%d: %s", ++i, device->name);
		if (NULL != device->description) {
			printf("(%s)\n", device->description);
		}
		else {
			printf("(No device available!)\n");
		}
	}
	if (i == 0)
	{
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		return -1;
	}

	/*选择并打开设备*/
	printf("Enter the interface number (1-%d):", i);
	scanf("%d", &number);

	if (number < 1 || number > i) {
		printf("\nInterface number out of range!\n");
		/*释放设备列表*/
		pcap_freealldevs(allDevices);
		return -1;
	}
	/*跳转到选中的适配器*/
	for (device = allDevices, i = 0; i < number - 1; device = device->next, i++);

	/*打开设备*/
	deviceHandler = pcap_open(device->name //将某设备当作源
		,65535 //65535保证能捕获到不同数据链路层上的每个数据包的全部内容
		,PCAP_OPENFLAG_PROMISCUOUS //最重要的flag是用来指示适配器是否要被设置成混杂模式
		,1000 //读取超时时间
		,NULL //远程机器验证
		,errorBuffer //错误消息缓冲数组
	);

	if (NULL == deviceHandler) {
		fprintf(stderr, "Unable to open the adapter, %s is not supported by winPcap\n", device->name);
		pcap_freealldevs(allDevices);
		return -1;
	}

	printf("\nListening on %s\n", device->description);

	/*释放设备列表*/
	pcap_freealldevs(allDevices);

	/*
		原型:int pcap_loop(pcap_t *p,
			int cnt,
			pcap_handler callback,
			u_char * user
		)
		开始循环捕获数据包
	*/
	pcap_loop(deviceHandler, 0, packetHandler, NULL);

	system("pause");
	return 0;
}

/* 每次捕获到数据包时，libpcap都会自动调用这个回调函数 */
void packetHandler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data) {
	struct tm *localTime;
	char timeString[16];
	//tv = Time Value
	time_t local_tv_sec;
	/* 将时间戳转换成可识别的格式 */
	local_tv_sec = header->ts.tv_sec;
	localTime = localtime(&local_tv_sec);
	strftime(timeString, sizeof(timeString), "%H:%M:%S", localTime);
	printf("%s, %.6d len:%d\n", timeString, header->ts.tv_usec, header->len);
}