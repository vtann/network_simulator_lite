#include "ns_node_if.h"

#include "../packet/ns_packet_ethr.h"

#include "../ns_namespace.h"

#include <vector>

#include <algorithm>

#ifndef __NS_NODE_ROUTER_IF_H__
#define __NS_NODE_ROUTER_IF_H__

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
   
    private:
    int router_id;
    std::string mac_address;
    int queue_size;
    double interface_speed;
    std::string ip_address;
    int mask;
    ns_ns::packets ethr_packets;
    bool is_connected_flag;
    unsigned char **if_send_buf;
    unsigned char **if_recv_buf;
}; 

#endif // __NS_NODE_ROUTER_IF_H__ 
