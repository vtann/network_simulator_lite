#ifndef __NS_NODE_ROUTER_IF_H__
#define __NS_NODE_ROUTER_IF_H__
#include "ns_node_router_if.h"
#endif //__NS_NODE_ROUTER_IF_H__

router_interface::router_interface(int if_id) : node_interface(if_id)
{
    
}

router_interface::~router_interface()
{
}

std::string router_interface::get_interface_address() const
{
    return mac_address;
}

void router_interface::set_interface_address(std::string& mac_addr)
{
    mac_address = mac_addr;
}

std::vector<std::string> router_interface::get_network_address() const
{
    return ip_address;
}

void router_interface::set_network_address(std::string& ip_addr)
{
    ip_address.push_back(ip_addr);
}

int router_interface::get_queue_size() const
{
    return queue_size;
}

void router_interface::set_queue_size(int q_size)
{
    queue_size = q_size;
}

int router_interface::get_interface_speed() const
{
    return interface_speed;
}

void router_interface::set_interface_speed(int if_speed)
{
    interface_speed = if_speed;
}

