#ifndef __NS_PACKET_ETHR_H__
#define __NS_PACKET_ETHR_H__
#include "ns_packet_ethr.h"
#endif //__NS_PACKET_ETHR_H__

std::string ethr_pkt::get_src_mac_address() const
{
    return src_mac_address;
}

std::string ethr_pkt::get_dst_mac_address() const
{
    return dst_mac_address;
}

std::string ethr_pkt::get_src_ipv4_address() const
{
    return src_ipv4_address;
}

std::string ethr_pkt::get_dst_ipv4_address() const
{
    return dst_ipv4_address;
}

int ethr_pkt::get_l2_ethertype() const
{
    return l2_ethertype;
}
   
int ethr_pkt::get_dscp_priority() const
{
    return dscp_priority;
}

int ethr_pkt::get_ttl() const
{
    return ttl;
}

std::string ethr_pkt::get_packet() const
{
   return full_packet; 
}   

void ethr_pkt::set_src_mac_address(std::string src_mac_addr)
{
    src_mac_address = src_mac_addr;
}

void ethr_pkt::set_dst_mac_address(std::string dst_mac_addr)
{
    dst_mac_address = dst_mac_addr;
}

void ethr_pkt::set_src_ipv4_address(std::string src_ip_addr)
{
    src_ipv4_address = src_ip_addr;
}

void ethr_pkt::set_dst_ipv4_address(std::string dst_ip_addr)
{
    dst_ipv4_address = dst_ip_addr;
}

void ethr_pkt::set_l2_ethertype(int ethrtype)
{
    l2_ethertype = ethrtype;
}

void ethr_pkt::set_dscp_priority(int priority)
{
    dscp_priority = priority;
}

void ethr_pkt::set_ttl(int value)
{
    ttl = value;
}

void ethr_pkt::set_packet(std::string packet)
{
    full_packet = packet;
} 

