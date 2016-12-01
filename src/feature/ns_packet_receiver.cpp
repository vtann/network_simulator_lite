#include "ns_packet_receiver.h"

class ethr_pkt;

void packet_receiver::receive_packet(unsigned char *pkt)
{
    ethr_pkt rec_pkt;
    
    rec_pkt.parse_pkt(pkt);

    router_interface *rec_interface = rec_router->get_interface(rec_interface_id);
    
    std::string if_mac_addr = rec_interface->get_interface_address();
    std::string pkt_mac_addr = rec_pkt.get_dst_mac_address();
    
    if (0 != pkt_mac_addr.compare(if_mac_addr))
    {
        // Drop the packet and don't update delay
    }
      
    std::string if_ip_addr = rec_interface->get_network_address();
    std::string pkt_ip_addr = rec_pkt.get_dst_ipv4_address();
    
    if (0 == pkt_ip_addr.compare(if_ip_addr))
    {
        // Check ttl  
        // Calculate delay
    }
    else
    {
        std::list<routing_entry*> table = get_routing_table(); 
        // Routing table
        for (std::list<routing_entry*>::iterator index = table.begin(); index != table.end(); index++)
        {
            if (0 == pkt_ip_addr.compare(0, ((*index)->network_mask - 1), (*index)->dst_ip_address))  
            {
                //put it in the respective queue 
                 
            }
        } 
    }
}
 
