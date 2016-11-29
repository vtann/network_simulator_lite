#include "ns_node_if.h"

#ifndef __NS_PACKET_ETHR_H__
#define __NS_PACKET_ETHR_H__
#include "../packet/ns_packet_ethr.h"
#endif // __NS_PACKET_ETHR_H__

#include "../ns_namespace.h"

#include <vector>

#ifndef __NS_NODE_ROUTER_IF_H__
#define __NS_NODE_ROUTER_IF_H__

class router_interface : public node_interface
{
    public:
    router_interface(int node_id, int if_id=-1);
    
    ~router_interface(); 

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
    int interface_speed;
    std::string ip_address;
    int mask;
    ns_ns::packets ethr_packets;
    bool is_connected_flag;
}; 

#endif // __NS_NODE_ROUTER_IF_H__ 
