#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include <GlobalTypes.h>
#include <IP_Address.h>
#include <Packet.h>

using namespace std;

/* 4 bytes IP address */
typedef struct ip_v6_address {
	//u_char byte1[16];
	uint8_t u6_addr8[16];
}ip_v6_address;



/* 4 bytes IP address */
typedef struct ip_address {
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
}ip_address;



/* IPv4 header */
typedef struct ip_v4_header {
	u_char  ihl : 4;
	u_char  ver : 4;        // Version (4 bits) + Internet header length (4 bits)
	u_char  tos;            // Type of service 
	u_short tlen;           // Total length 
	u_short identification; // Identification
	u_short flags_fo;       // Flags (3 bits) + Fragment offset (13 bits)
	u_char  ttl;            // Time to live
	u_char  proto;          // Protocol
	u_short crc;            // Header checksum
	ip_address  saddr;      // Source address
	ip_address  daddr;      // Destination address
	u_int   op_pad;         // Option + Padding
};



/* IPv4 header */
typedef struct ip_v6_header {
	uint32_t ver_tc_label;
	uint16_t len;
	uint8_t hop_limit;
	uint8_t next_header;

//	ip_v6_address  saddr;      // Source address
//	ip_v6_address  daddr;      // Destination address

}ip_v6_header;



typedef struct tcp_header {
	u_short sport;  /* source port */
	u_short dport;  /* destination port */
	u_long th_seq;   /* sequence number */
	u_long th_ack;   /* acknowledgement number */
	u_char th_off : 4; /* data offset */
	u_char th_x2 : 4;


	u_char th_flags : 6;

/*
#define TH_FIN 0x01
#define TH_SYN 0x02
#define TH_RST 0x04
#define TH_PUSH 0x08
#define TH_ACK 0x10
#define TH_URG 0x20
#define TH_ECE 0x40
#define TH_CWR 0x80
*/
//#define TH_FLAGS (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)

	u_short th_win;   /* window */
	u_short th_sum;   /* checksum */
	u_short th_urp;   /* urgent pointer */
}tcp_header;


typedef struct udp_header {
	u_short sport;          // Source port
	u_short dport;          // Destination port
	u_short len;            // Datagram length
	u_short crc;            // Checksum
}udp_header;



//Primary fields of the ICMP header
typedef struct icmp_header {
	unsigned char   i_type;
	unsigned char   i_code;
}icmp_header;


typedef struct ipv4_flag
{
	Int32 reserved : 1;
	Int32 fragmented : 1;
	Int32 location : 1;
};


class IPPacket
{

public:

	Int32 version;
	Int32 HeaderLength;
	Int32 TOS;
	int TTL;
	int Protocol;
	string Source;
	string Destination;
	ipv4_flag Flags;
	int SourcePort;
	int DestinationPort;
};



class IP
{

private:

public:
	static Packet* CreatePacket(const u_char *Data);

};