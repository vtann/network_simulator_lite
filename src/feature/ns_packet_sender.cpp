#include "ns_packet_sender.h"

using namespace ns_ns;

void packet_sender(router_network *rn, router* r)
{
    routing_table* rt;
    std::list<routing_entry*> re;
    arp_table *at;
    ethr_pkt pkt;
    unsigned char *s_pkt = new unsigned char [DEFAULT_PACKET_SIZE_WITH_FCS];
    
    rt = r->get_routing_table();     
    at = r->get_arp_table();    
    re = rt->get_routing_table(); 
   
    rt->dump_routing_table_entries(); 
    for (std::list<routing_entry*>::iterator index = re.begin(); index != re.end(); index++)
    {
        std::string dst_mac = at->find_entry((*index)->gateway_ip_address); 
        std::string src_mac = r->get_interface((*index)->outgoing_if_id)->get_interface_address(); 
        std::string src_ip = r->get_interface((*index)->outgoing_if_id)->get_network_address();  
        std::string dst_ip = (*index)->dst_ip_address; 
        int gw_router_id = (*index)->gateway_router_id; 
        int gw_if_id = (*index)->gateway_if_id; 
        pkt.construct_pkt(s_pkt, src_mac, dst_mac, src_ip, dst_ip);
        
        // Lock mutex and put packet in the outgoing interface send buffer. As of now, packet is copied directly to the recv buffer of gateway
        rn->get_router(gw_router_id)->get_interface(gw_if_id)->copy_packet_to_recv_ring_buffer(s_pkt);   
        std::cout << rn->get_router(gw_router_id)->get_interface(gw_if_id)->get_num_pkts_in_recv_buffer() << std::endl;  
    }
}

