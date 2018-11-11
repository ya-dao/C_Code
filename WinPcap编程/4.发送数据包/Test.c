#define _CRT_SECURE_NO_WARNINGS
#define WIN32
#define HAVE_REMOTE
#include <stdio.h>
#include <stdlib.h>
#include "pcap.h"

int main() {

	pcap_if_t *allDevices;
	pcap_if_t *device;
	char errorBuffer[PCAP_ERRBUF_SIZE];
	int i = 0, number = 0;

	pcap_t *deviceHandler;

	u_char packet[100];

	int flag = pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &allDevices, errorBuffer);

	if (-1 == flag) {
		fprintf(stderr, "%s\n", errorBuffer);
		exit(1);
	}

	for (device = allDevices; NULL != device; device = device->next) {
		printf("%d: %s\n", ++i, device->name);
		if (NULL != device->description)
		{
			printf("(%s)\n",device->description);
		}
		else {
			printf("No device available!\n");
		}
	}

	if (0 == i)
	{
		printf("No interfaces found!Make sure WinPcap is installed!");
		return -1;
	}

	printf("Enter the interface number(1 - %d):\n", i);
	scanf("%d", &number);

	if (number > i || number < 1) {
		printf("Interface number out of range!");
		pcap_freealldevs(allDevices);
		return -1;
	}

	for (device = allDevices, i = 0; i < number - 1; device = device->next, i++);

	deviceHandler = pcap_open(device->name, 100, PCAP_OPENFLAG_PROMISCUOUS, 1000, NULL, errorBuffer);

	if (NULL == deviceHandler)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", device->name);
		return -1;
	}

	/*发包,假设在以太网上，设置MAC的目的地址为:1:1:1:1:1:1*/
	packet[0] = 1;
	packet[1] = 1;
	packet[2] = 1;
	packet[3] = 1;
	packet[4] = 1;
	packet[5] = 1;
	/*源MAC地址为本机:D0-53-49-F3-7A-27,每组为一个字节,转换成十进制*/
	packet[6] = 208;
	packet[7] = 83; 
	packet[8] = 73;
	packet[9] = 243;
	packet[10] = 122;
	packet[11] = 39;

	/*随便填充后面的内容*/
	for (i = 12; i<100; i++)
	{
		packet[i] = i % 256;
	}

	/*发送数据包*/
	int result = pcap_sendpacket(deviceHandler,packet, 100);
	if (0 != result) {
		fprintf(stderr, "\nError sending the packet:%s\n", pcap_geterr(deviceHandler));
		return -1;
	}
	else {
		printf("Success sending the packet!\n");
	}

	system("pause");
	return 0;
}