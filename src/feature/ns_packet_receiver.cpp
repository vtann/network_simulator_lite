#include "ns_packet_receiver.h"

extern pthread_mutex_t thread_mutex;

class ethr_pkt;

void packet_receiver::packet_poller(std::shared_ptr<router_network> r_n, std::shared_ptr<router> r)
{
    timer r_timer;
    
    r_timer.start_timer();

    std::vector<std::shared_ptr<router_interface> > interfaces = r->get_all_interfaces(); 
    while (1)
    {
        for (unsigned int index = 0; index < interfaces.size(); index++)
        {
            if (0 != (interfaces[index]->get_num_pkts_in_recv_buffer()))
            {
                lock_mutex(&thread_mutex);
                packet_buf *pkt = new packet_buf;
                pkt->pkt_buf = new unsigned char [DEFAULT_PACKET_SIZE_WITH_FCS];
                pkt->timestamp = new struct timeval;
                interfaces[index]->remove_packet_from_recv_ring_buffer(pkt);
                received_packet(r_n, r, index, pkt); 
  
                unlock_mutex(&thread_mutex);
            }     
        }
        if (2 < r_timer.get_elapsed_time_in_sec())
        {
            break;
        }
    }
    r_timer.stop_timer();
}

void packet_receiver::received_packet(std::shared_ptr<router_network> r_n, std::shared_ptr<router> r, int rec_interface_id, packet_buf *pkt)
{
    double delay;
    std::shared_ptr<router_link> link = NULL;
    ethr_pkt rec_pkt;
    
    rec_pkt.parse_pkt(pkt->pkt_buf);

    std::shared_ptr<router_interface> rec_interface = r->get_interface(rec_interface_id);
    
    std::string if_mac_addr = rec_interface->get_interface_address();
    std::string pkt_dst_mac_addr = rec_pkt.get_dst_mac_address();
    std::string pkt_src_mac_addr = rec_pkt.get_src_mac_address();
   
    if (0 != pkt_dst_mac_addr.compare(if_mac_addr))
    {
        // Drop the packet and don't update delay
    }
      
    std::string if_ip_addr = rec_interface->get_network_address();
    std::string pkt_dst_ip_addr = rec_pkt.get_dst_ipv4_address();
    std::string pkt_src_ip_addr = rec_pkt.get_src_ipv4_address();
   
    link = r_n->find_link(pkt_src_mac_addr, pkt_dst_mac_addr);
    if (NULL == link)
    {
        link = r_n->find_link(pkt_dst_mac_addr, pkt_src_mac_addr);
        delay = link->get_link_delay();
    } 
    else
    {
        delay = link->get_link_delay();
    }

    if (0 == pkt_dst_ip_addr.compare(if_ip_addr))
    {
        // std::cout << "REC IF MAC: " << if_mac_addr
        //          << " REC PKT DST MAC: " << pkt_dst_mac_addr 
        //          << " REC PKT SRC IP: " << pkt_src_ip_addr
        //          << " REC PKT DST IP: " << pkt_dst_ip_addr
        //          << std::endl;
  
        // Check ttl  
        // Calculate delay
        struct timeval end_time;
 
        gettimeofday(&end_time, NULL);
        double f_secs = calculate_delay(pkt->timestamp, &end_time);  
        //accumulate_delay(pkt_src_ip_addr, pkt_dst_ip_addr, (delay + (f_secs/1000)));
        accumulate_total_delay(pkt_src_ip_addr, pkt_dst_ip_addr, rec_interface->get_router_id(), (delay + (f_secs/1000)));
    }
    else
    {
        routing_table *rt = r->get_routing_table();
        arp_table *at = r->get_arp_table();
        std::list<routing_entry*> table = rt->get_routing_table(); 
        
        // Routing table
        for (std::list<routing_entry*>::iterator index = table.begin(); index != table.end(); index++)
        {
            if (0 == pkt_dst_ip_addr.compare(0, ((*index)->network_mask - 1), (*index)->dst_ip_address))  
            {
                std::string dst_mac = at->find_entry((*index)->gateway_ip_address); 
                std::string src_mac = r->get_interface((*index)->outgoing_if_id)->get_interface_address(); 
                int gw_router_id = (*index)->gateway_router_id; 
                int gw_if_id = (*index)->gateway_if_id;
                int ttl = rec_pkt.get_ttl();       
                
                rec_pkt.set_src_mac_address(pkt->pkt_buf, src_mac);   
                rec_pkt.set_dst_mac_address(pkt->pkt_buf, dst_mac);   
                rec_pkt.set_ttl(pkt->pkt_buf, ttl);
                
                //accumulate_delay(pkt_src_ip_addr, pkt_dst_ip_addr, delay);
                accumulate_total_delay(pkt_src_ip_addr, pkt_dst_ip_addr, 0, delay);

                // Put it in the respective queue 
                r_n->get_router(gw_router_id)->get_interface(gw_if_id)->copy_packet_to_recv_ring_buffer(pkt);  
                break; 
            }
        }
    }
}
 
