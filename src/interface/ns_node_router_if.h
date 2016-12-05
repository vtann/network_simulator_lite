#include <vector>
#include <algorithm>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "ns_node_if.h"

#include "../packet/ns_packet_ethr.h"

#include "../ns_namespace.h"

#ifndef __NS_NODE_ROUTER_IF_H__
#define __NS_NODE_ROUTER_IF_H__

typedef struct packet_buf
{
    unsigned char *pkt_buf;
    struct timeval *timestamp;
}packet_buf;

class router_interface : public node_interface
{
    public:
    router_interface(int nodeID, int interfaceID, std::string mac, std::string ip, int mask, int interfaceQueue, double interfaceSpeed);
    
    ~router_interface(); 
    
    router_interface(const router_interface &r_i);//Copy constructor

    int get_router_id() const;

    void set_router_id(int id);
  
    std::string get_interface_address() const;
    
    void set_interface_address(std::string& mac_addr);
   
    int get_queue_size() const;

    void set_queue_size(int q_size);
 
    bool get_is_connected_flag() const;

    void set_is_connected_flag(bool flag);

    int get_interface_speed() const;
    
    void set_mask(int ip_mask);
    
    int get_mask() const;

    void set_interface_speed(int if_speed);
 
    std::string get_network_address() const;
    
    void set_network_address(std::string& ip_addr);
   
    void copy_packet_to_send_ring_buffer(unsigned char *pkt);
    
    void copy_packet_to_recv_ring_buffer(unsigned char *pkt);

    void remove_packet_from_send_ring_buffer(packet_buf *pkt);
    
    void remove_packet_from_recv_ring_buffer(packet_buf *pkt);

    private:
    int router_id;
    std::string mac_address;
    int queue_size;
    double interface_speed;
    std::string ip_address;
    int mask;
    ns_ns::packets ethr_packets;
    bool is_connected_flag;
    packet_buf **if_send_buf;
    packet_buf **if_recv_buf;
    int start_recv_buf_idx;
    int end_recv_buf_idx;
    int start_send_buf_idx;
    int end_send_buf_idx;
    int pkts_in_send_buf;
    int pkts_in_recv_buf;
}; 

#endif // __NS_NODE_ROUTER_IF_H__ 
