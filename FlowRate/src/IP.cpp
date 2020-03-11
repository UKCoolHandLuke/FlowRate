#pragma once

#include <IP.h>
#include <Ethernet.h>
#include <Protocol.h>
#include <time.h>
#include <system.h>


Packet* IP::CreatePacket(const u_char *Data)
{
	Packet *NewPacket = new Packet();
	stringstream ss;

	//Lets check the contents of the ethernet header
	//Ethernet_Header *E_Header = (Ethernet_Header *)Data;

	//unsigned short original_type = E_Header->type;

	//Convert the Type to the correct format
	//E_Header->type = ToLittleEndian(E_Header->type);
	
	//if (E_Header->type > ETHERNET_FRAME_LENGTH_BOUNDARY)
	//{
		//We don't need this for every frame - but its nice to be complete
	//	string srcmac = DecimalToMacAddress(E_Header->smac);
	//	string dstmac = DecimalToMacAddress(E_Header->dmac);
	//	string Type = DecimalToHex(E_Header->type);

		//if (E_Header->type == ETHERNET_IPV4)
		//{

			tcp_header *tcp = NULL;
			udp_header *udp = NULL;
			icmp_header *icmp = NULL;

			ip_v4_header *ih;
			ih = (ip_v4_header *)(Data); //length of ethernet header
			u_int ip_len = ih->ihl * 4;
			u_short sport = 0, dport = 0;

			char IPv4Address_SRC[16] = { 0 };
			char IPv4Address_DST[16] = { 0 };
			sprintf_s(IPv4Address_SRC, "%d.%d.%d.%d", ih->saddr.byte1, ih->saddr.byte2, ih->saddr.byte3, ih->saddr.byte4);
			sprintf_s(IPv4Address_DST, "%d.%d.%d.%d", ih->daddr.byte1, ih->daddr.byte2, ih->daddr.byte3, ih->daddr.byte4);

			NewPacket->Source.Set(IPv4Address_SRC);
			NewPacket->Destination.Set(IPv4Address_DST);

			NewPacket->Protocol.ProtocolNumber = ih->proto;

			/*
			P->version = 4;
			P->HeaderLength = ih->ihl;
			P->Protocol = ih->proto;
			P->TTL = ih->ttl;
			P->TOS = ih->tos;
			P->Source = IPv4Address_SRC;
			P->Destination = IPv4Address_DST;
			*/

			if (NewPacket->Protocol.ProtocolNumber == Protocol::TCP)
			{
				tcp = (tcp_header *)((u_char*)ih + ip_len);
				sport = ntohs(tcp->sport);
				dport = ntohs(tcp->dport);


				//Check for flags
				if (tcp->th_flags & Protocol::TCP_FLAGS::FLAG_FIN)
					NewPacket->Protocol.Properties.Add("TCP.FLAG_FIN", 1);
				if (tcp->th_flags & Protocol::TCP_FLAGS::FLAG_SYN)
					NewPacket->Protocol.Properties.Add("TCP.FLAG_SYN", 1);
				if (tcp->th_flags & Protocol::TCP_FLAGS::FLAG_RST)
					NewPacket->Protocol.Properties.Add("TCP.FLAG_RST", 1);
				if (tcp->th_flags & Protocol::TCP_FLAGS::FLAG_ACK)
					NewPacket->Protocol.Properties.Add("TCP.FLAG_ACK", 1);
				if (tcp->th_flags & Protocol::TCP_FLAGS::FLAG_URG)
					NewPacket->Protocol.Properties.Add("TCP.FLAG_URG", 1);
				if (tcp->th_flags & Protocol::TCP_FLAGS::FLAG_ECE)
					NewPacket->Protocol.Properties.Add("TCP.FLAG_ECE", 1);
				if (tcp->th_flags & Protocol::TCP_FLAGS::FLAG_CWR)
					NewPacket->Protocol.Properties.Add("TCP.FLAG_CWR", 1);


					NewPacket->Protocol.Properties.Add("SOURCE.PORT", sport);
					NewPacket->Protocol.Properties.Add("DESTINATION.PORT", dport);
			}
			else if (NewPacket->Protocol.ProtocolNumber == Protocol::UDP)
			{
				udp = (udp_header *)((u_char*)ih + ip_len);
				sport = ntohs(udp->sport);
				dport = ntohs(udp->dport);

				NewPacket->Protocol.Properties.Add("SOURCE.PORT", sport);
				NewPacket->Protocol.Properties.Add("DESTINATION.PORT", dport);
			}

			if (NewPacket->Protocol.ProtocolNumber == Protocol::ICMP)
			{
				icmp = (icmp_header *)((u_char*)ih + ip_len);

				NewPacket->Protocol.Properties.Add("TYPE", icmp->i_type);
				NewPacket->Protocol.Properties.Add("CODE", icmp->i_code);
			}

			return(NewPacket);
		//}
		/*
		else if (E_Header->type == ETHERNET_ARP)
		{
			ss.str("");
			ss << "(ARP): " << Type << " src:" << srcmac << " dst:" << dstmac;
			System::Logging.Writeln(ss.str(),LogLevel::LOG_DEBUG);
		}
		*/

		//else if (E_Header->type == ETHERNET_IPV6)
		//{
		//	ip_v6_header *ipv6h;
			/*
			ipv6h = (ip_v6_header *)(Data + 14); //length of ethernet header
			P->version = 6;
			P->HeaderLength = ipv6h->len;
			P->Protocol = ih->proto;
			*/
		//	ss.str("");
		//	ss << "(IPV6): " << Type << " src:" << srcmac << " dst:" << dstmac;
		//	System::Logging.Writeln(ss.str(), LogLevel::LOG_DEBUG);
		//}


		//Unknown Frame type - just ignore
		//else
		//{
			//ss.str("");
			//ss << "Unknown frame type: " << Type << " src:" << srcmac << " dst:" << dstmac;
			//System::Logging.Writeln(ss.str(), LogLevel::LOG_DEBUG);
		//}
		

	//}

delete NewPacket;
return(NULL);
}
