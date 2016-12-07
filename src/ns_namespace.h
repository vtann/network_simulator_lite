#include <iostream>
#include <vector>

#ifndef __NS_NAMESPACE_H__
#define __NS_NAMESPACE_H__

class router;
class router_interface;
class router_link;
class ethr_pkt;

namespace ns_ns
{
    const int ipv4_header_size = 20;  
    const int ipv6_header_size = 40;  
    const int raw_eth_header_size = 14;  
    const int RAW_ETHR_L2_ETHERTYPE = 2048;
    const int DEFAULT_TTL_VALUE = 64; 
    const int RAW_ETHR_L3_ETHERTYPE = 255;
    const int DEFAULT_IPV4_HEADER_SIZE = 20;
    const int DEFAULT_IPV4_PACKET_SIZE = 64;
    const int DEFAULT_PACKET_SIZE_WITH_FCS = 68;  
    const int dst_mac_address_offset = 0;  
    const int src_mac_address_offset = 6;  
    const int l2_ethertype_offset = 12;  
    const int ip_header_offset = 14;  
    const int ip_dscp_offset = 15;  
    const int ip_total_length_offset = 16;
    const int ip_identifier_offset = 18;
    const int ip_fragment_offset = 20;
    const int ip_ttl_offset = 22;  
    const int ip_protocol_offset = 23;  
    const int ip_header_checksum_offset = 24;  
    const int src_network_address_offset = 26;  
    const int dst_network_address_offset = 30;  
    typedef std::vector<router*> routers;
    typedef std::vector<router_interface*> interfaces;
    typedef std::vector<router_link*> links;
    typedef std::vector<ethr_pkt*> packets; 
    enum graph_type
    {
        DIRECTED_GRAPH   = 0, 
        UNDIRECTED_GRAPH
    };
    
    enum return_type
    {
        OK     = 0,
        NOT_OK
    };

    enum packet_ip_type
    {
        PACKET_IPv4 = 0,
        PACKET_IPv6
    };
   
    enum packet_param_type
    {
        SRC_MAC_ADDRESS = 0, 
        DST_MAC_ADDRESS, 
        SRC_IP_ADDRESS,
        DST_IP_ADDRESS
    }; 

    enum shortest_path_param
    {
        LINK_COST = 0,
        LINK_DELAY
    }; 
}

#endif // __NS_NAMESPACE_H__
