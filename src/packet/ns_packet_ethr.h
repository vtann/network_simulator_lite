#ifndef __NS_PACKET_H__
#define __NS_PACKET_H__
#include "ns_packet.h"
#endif //__NS_PACKET_H__

class ethr_pkt : public packet
{
    public:
    std::string get_src_mac_address() const;
   
    std::string get_dst_mac_address() const;
   
    std::string get_src_ipv4_address() const;
   
    std::string get_dst_ipv4_address() const;

    int get_l2_ethertype() const;
   
    int get_dscp_priority() const;

    int get_ttl() const;
  
    std::string get_packet() const;
   
    void set_src_mac_address(std::string src_mac_addr);

    void set_dst_mac_address(std::string dst_mac_addr);

    void set_src_ipv4_address(std::string src_ip_addr);

    void set_dst_ipv4_address(std::string dst_ip_addr);

    void set_l2_ethertype(int ethrtype);

    void set_dscp_priority(int priority);

    void set_ttl(int value);

    void set_packet(std::string packet);

    private:
    std::string src_mac_address; 
    std::string dst_mac_address; 
    std::string src_ipv4_address; 
    std::string dst_ipv4_address;
    int l2_ethertype;
    int dscp_priority;
    int ttl;
    std::string full_packet; 
};
