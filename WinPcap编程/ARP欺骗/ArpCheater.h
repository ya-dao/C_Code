#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define WIN32
#define HAVE_REMOTE

#define TRUE 1
#define FALSE 0
#define HOST_NUMBER "hostNumber"
#define ATTACK_COUNT "attackCount"
#define INDICATOR_IP 1
#define INDICATOR_MAC 2

#include "direct.h"
#include <stdio.h>
#include <stdlib.h>
#include "pcap.h"
#include <packet32.h>
#include <ntddndis.h>
#include <process.h>

//字节对齐必须是1 
#pragma pack (1) 
typedef struct ArpDatagramHeader {
	unsigned short hardwareType; //硬件类型：表示硬件地址的类型，值为1表示以太网地址
	unsigned short protocolType; //协议类型：表示要映射的协议地址类型。它的值为0x0800表示IP地址类型
	unsigned char hardwareAddressLength; //硬件地址长度和协议地址长度以字节为单位，对于以太网上的IP地址的ARP请求或应答来说，他们的值分别为6和4；
	unsigned char protocolAddressLength;
	unsigned short operationType; //操作类型（op）:1表示ARP请求，2表示ARP应答
	unsigned char senderMac[6]; //发送端MAC地址：发送方设备的硬件地址；
	unsigned long senderIP; //发送端IP地址：发送方设备的IP地址；
	unsigned char receiverMac[6]; //目标MAC地址：接收方设备的硬件地址。
	unsigned long receiverIP; //目标IP地址：接收方设备的IP地址。
	//发包的时为了保证以太网帧的最小帧长为64 bytes，会在报文里添加一个padding字段，用来填充数据包大小。
	//以太网的数据部分大小必须是在46 - 1500之间，而ARP包只有28个字节，所以需要填充18个字节才能满足要求。
	unsigned char padding[18]; 
}ArpDatagramHeader;

typedef struct EthnetFrameHander {
	unsigned char destinationMac[6];
	unsigned char sourceMAC[6];
	//帧类型:ARP:0X806 RARP:0X8035
	unsigned short frameType;
}EthnetFrameHander;

/*完整的ARP包*/
typedef struct ArpDatagram {
	EthnetFrameHander ethnetFrame;
	ArpDatagramHeader arpDatagram;
}ArpDatagram;

/*封装主机参数*/
typedef struct AttackHost {
	unsigned long ip; //要伪装成的IP地址列表
	unsigned char *mac; //网关MAC
}AttackHost;

/*
	加载配置文件
*/
void loadConfig();

/*向局域网中所有主机发送请求包*/
void sendPacketToAllHost(int hostSize, unsigned long net);
/*分别向目标主机和路由发送ARP应答包使其断网*/
void sendAttackPacket(void *p);

/*
	获取本机MAC
*/
unsigned char* getLocalMac(char* deviceName);

/*
	封装ARP协议请求包
	@param sourceMac 源MAC
	@param sourceIP 源IP
	@param destinationIP 目标IP
	@return  ARP协议请求包
*/
unsigned char* buildArpRequestDatagram(unsigned char* sourceMac, unsigned long sourceIP,
	unsigned long destinationIP);

/*
	封装ARP协议应答包
	@param packet 需要构造的应答包
	@param sourceMac 源MAC
	@param sourceIP 源IP
	@param destinationIP 目标IP
*/
void buildArpReplyDatagram(ArpDatagram *packet, unsigned char* sourceMac, unsigned long sourceIP,
	unsigned long destinationIP, unsigned char* destinationMac);

/*
	判断当前行是否为空行,fgets读取空行会返回'\n',所以判断方法如下:
	1.如果以'\n'开始,则是空行
	2.如果遇到'\n'之前的所有字符都为' '空格,也是空行
*/
int isSpaceLine(char *buffer);

/*
	初始化变量
*/
void init();

/*
	读取IP或MAC
*/
int loadIPOrMac(char *buffer, int contentIndicator, unsigned long *ip, unsigned char *mac, int hostId);

/*
	显示读取到的网关和主机的IP和MAC
*/
void showConfig();

/*
显示结果
*/
void showResult(int sendResult, unsigned long *IPs, unsigned char **Macs, int i, int j);