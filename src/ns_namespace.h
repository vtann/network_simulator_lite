#include <iostream>
#include <vector>

//class router;
class router_interface;
class router_link;
class ethr_pkt;

namespace ns_ns
{
    const int ipv4_header_size = 20;  
    const int ipv6_header_size = 40;  
    const int raw_eth_header_size = 14;  
    const int l2_ethertype = 0x0800;
    const int dst_mac_address_offset = 0;  
    const int src_mac_address_offset = 6;  
    const int l2_ethertype_offset = 12;  
    const int ip_header_offset = 14;  
    const int ip_dscp_offset = 15;  
    const int ip_total_length_offset = 16;
    const int ip_ttl_offset = 18;  
    const int ip_protocol_offset = 19;  
    const int ip_header_checksum_offset = 20;  
    const int src_network_address_offset = 22;  
    const int dst_network_address_offset = 26;  
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
}
