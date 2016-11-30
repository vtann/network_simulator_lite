#include "ns_node_router_if.h"

using namespace ns_ns;

router_interface::router_interface(int nodeID,int interfaceID,std::string mac,std::string ip, int mask, int interfaceQueue, int interfaceSpeed) : node_interface(interfaceID)
{
   this->router_id = nodeID;
   set_interface_address(mac);
   set_network_address(ip);
   set_mask(mask);
   set_queue_size(interfaceQueue);
   set_interface_speed(interfaceSpeed);
   
   is_connected_flag = false;
}

router_interface::~router_interface()
{
}

int router_interface::get_router_id() const
{
    return router_id;
}

void router_interface::set_router_id(int id)
{
    router_id = id;
}
  
std::string router_interface::get_interface_address() const
{
    return mac_address;
}

void router_interface::set_interface_address(std::string& mac_addr)
{
    mac_address = mac_addr;
}

std::string router_interface::get_network_address() const
{
    return ip_address;
}

void router_interface::set_network_address(std::string& ip_addr)
{
    ip_address = ip_addr;
}

int router_interface::get_queue_size() const
{
    return queue_size;
}

void router_interface::set_queue_size(int q_size)
{
    queue_size = q_size;
}

bool router_interface::get_is_connected_flag() const
{
    return is_connected_flag;
}

void router_interface::set_is_connected_flag(bool flag)
{
    is_connected_flag = flag;
}

void router_interface::set_mask(int ip_mask) 
{
    mask = ip_mask;
}

int router_interface::get_interface_speed() const
{
    return interface_speed;
}

int router_interface::get_mask() const
{
    return mask;
}

void router_interface::set_interface_speed(int if_speed)
{
    interface_speed = if_speed;
}

router_interface::router_interface(const router_interface &r_i):node_interface(r_i.get_interface_id()){
    this->router_id=r_i.router_id;
    this->mac_address=r_i.mac_address;
    this->queue_size=r_i.queue_size;
    this->interface_speed=r_i.interface_speed;
    this->ip_address=r_i.ip_address;
    this->mask=r_i.mask;
    this->ethr_packets=r_i.ethr_packets;
    this->is_connected_flag=r_i.is_connected_flag; 
}

