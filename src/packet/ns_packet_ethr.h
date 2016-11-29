#include <list>
#include <sstream>
#include <stdint.h>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <iomanip>

#include "ns_packet.h"

#include "../ns_namespace.h"

#ifndef __NS_PACKET_ETHR_H__
#define __NS_PACKET_ETHR_H__

using namespace ns_ns;

class ethr_pkt : public packet
{
    public:
    std::string get_src_mac_address() const;
   
    std::string get_dst_mac_address() const;
   
    std::string get_src_ipv4_address() const;
   
    std::string get_dst_ipv4_address() const;

    int get_l2_ethertype() const;
   
    int get_ip_version_type() const;

    int get_ip_header_length() const;

    int get_dscp_priority() const;

    int get_ip_total_length() const;

    int get_packet_identifier() const;

    int get_more_frag_flag() const;

    int get_dont_frag_flag() const;

    int get_packet_offset() const;

    int get_ttl() const;
  
    int get_protocol() const;

    int get_ip_header_checksum() const;

    void set_src_mac_address(unsigned char* pkt, std::string src_mac_addr);

    void set_dst_mac_address(unsigned char* pkt, std::string dst_mac_addr);

    void set_src_ipv4_address(unsigned char* pkt, std::string src_ip_addr);

    void set_dst_ipv4_address(unsigned char* pkt, std::string dst_ip_addr);

    void set_l2_ethertype(unsigned char* pkt, int ethrtype);

    void set_ip_version_type(unsigned char* pkt, int type);

    void set_ip_header_length(unsigned char* pkt, int length);

    void set_dscp_priority(unsigned char* pkt, int priority);

    void set_ip_total_length(unsigned char* pkt, int length);

    void set_packet_identifier(unsigned char* pkt, int id);

    void set_fragment_flags(unsigned char* pkt, bool dont_frag, bool more_frag, int frag_offset);

    void set_ttl(unsigned char* pkt, int value);

    void set_protocol(unsigned char* pkt, int value);

    void set_ip_header_checksum(unsigned char* pkt, int checksum);

    void parse_src_mac_address(unsigned char* pkt);

    void parse_dst_mac_address(unsigned char* pkt);

    void parse_src_ipv4_address(unsigned char* pkt);

    void parse_dst_ipv4_address(unsigned char* pkt);

    void parse_l2_ethertype(unsigned char* pkt);

    void parse_ip_version_type(unsigned char* pkt);

    void parse_ip_header_length(unsigned char* pkt);

    void parse_dscp_priority(unsigned char* pkt);

    void parse_ip_total_length(unsigned char* pkt);

    void parse_packet_identifier(unsigned char* pkt);

    void parse_fragment_flags(unsigned char* pkt);

    void parse_ttl(unsigned char* pkt);

    void parse_protocol(unsigned char* pkt);

    void parse_ip_header_checksum(unsigned char* pkt);

    int int_string_to_int(std::string ip_addr_seg);

    int hex_string_to_int(std::string mac_addr_seg);

    std::string int_to_string(int x);

    int hex_to_int(std::string hex_string);

    void string_to_substring(unsigned char* pkt, std::string str, std::string delim, ns_ns::packet_param_type param);

    void construct_pkt(unsigned char* packet, std::string src_mac_addr, std::string dst_mac_addr,
                             std::string src_ip_addr, std::string dst_ip_addr);

    void parse_pkt(unsigned char* packet);

    private:
    std::string src_mac_address; 
    std::string dst_mac_address; 
    std::string src_ipv4_address; 
    std::string dst_ipv4_address;
    int l2_ethertype;
    int ip_version_type;
    int ip_header_length;
    int dscp_priority;
    int ip_total_length;
    int packet_identifier; 
    bool more_frag_flag;
    bool dont_frag_flag;
    int frag_offset_identifier;
    int ttl;
    int l3_protocol_type;
    int ip_header_checksum;
};

#endif //__NS_PACKET_ETHR_H__
