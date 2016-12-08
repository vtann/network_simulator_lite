#include "ns_packet_sender.h"

extern pthread_mutex_t thread_mutex;

using namespace ns_ns;

void packet_sender(router_network *rn, router* r)
{
    routing_table* rt;
    std::list<routing_entry*> re;
    arp_table *at;
    ethr_pkt pkt;
    packet_buf *send_pkt;
   
    send_pkt = new packet_buf;
    send_pkt->pkt_buf = new unsigned char [DEFAULT_PACKET_SIZE_WITH_FCS];
    send_pkt->timestamp = new struct timeval;    
 
    rt = r->get_routing_table();     
    at = r->get_arp_table();    
    re = rt->get_routing_table(); 
   
    // rt->dump_routing_table_entries(); 
    for (std::list<routing_entry*>::iterator index = re.begin(); index != re.end(); index++)
    {
        std::string dst_mac = at->find_entry((*index)->gateway_ip_address); 
        std::string src_mac = r->get_interface((*index)->outgoing_if_id)->get_interface_address(); 
        std::string src_ip = r->get_interface((*index)->outgoing_if_id)->get_network_address();  
        std::string dst_ip = (*index)->dst_ip_address; 
        int gw_router_id = (*index)->gateway_router_id; 
        int gw_if_id = (*index)->gateway_if_id;
         
        //std::cout << "SRC MAC: " << src_mac 
        //          << " DST MAC: " << dst_mac
        //          << " SRC IP: " << src_ip
        //          << " DST_IP: " << dst_ip
        //          << std::endl;  
        pkt.construct_pkt(send_pkt->pkt_buf, src_mac, dst_mac, src_ip, dst_ip);
        gettimeofday(send_pkt->timestamp, NULL); 
         
        // Lock mutex and put packet in the outgoing interface send buffer. As of now, packet is copied directly to the recv buffer of gateway
        lock_mutex(&thread_mutex);
        rn->get_router(gw_router_id)->get_interface(gw_if_id)->copy_packet_to_recv_ring_buffer(send_pkt);   
        unlock_mutex(&thread_mutex);
    }
}

