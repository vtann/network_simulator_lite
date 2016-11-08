#ifndef __NS_NODE_IF_H__
#define __NS_NODE_IF_H__
#include "ns_node_if.h"
#endif //__NS_NODE_IF_H__

#ifndef __NS_PACKET_ETHR_H__
#define __NS_PACKET_ETHR_H__
#include "../packet/ns_packet_ethr.h"
#endif // __NS_PACKET_ETHR_H__

#ifndef __NS_NAMESPACE_H__
#define __NS_NAMESPACE_H__
#include "../ns_namespace.h"
#endif // __NS_NAMESPACE_H__

#include <iostream>
#include <vector>

class router_interface : public node_interface
{
    public:
    router_interface(int if_id=-1);
    
    ~router_interface(); 
  
    std::string get_interface_address() const;
    
    void set_interface_address(std::string& mac_addr);
   
    int get_queue_size() const;

    void set_queue_size(int q_size);
 
    int get_interface_speed() const;

    void set_interface_speed(int if_speed);
 
    std::vector<std::string> get_network_address() const;
    
    void set_network_address(std::string& ip_addr);
   
    private:
    std::string mac_address;
    int queue_size;
    int interface_speed;
    std::vector<std::string> ip_address;
    ns_ns::packets ethr_packets; 
}; 
