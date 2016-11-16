#ifndef __NS_ROUTING_TABLE_H__
#define __NS_ROUTING_TABLE_H__
#include "ns_routing_table.h"
#endif // __NS_ROUTING_TABLE_H__ 

std::list<routing_entry*> list_routing_table;

void add_routing_table_entry(std::string dst_address, int mask, int interface, int gw_id, std::string gw_address)
{
    routing_entry *element = new routing_entry; 
    
    element->dst_ip_address = dst_address;
    element->network_mask = mask;
    element->outgoing_if_id = interface; 
    element->gateway_if_id = gw_id;
    element->gateway_ip_address = gw_address;
    list_routing_table.push_back(element);
}
    
std::list<routing_entry*> get_routing_table()
{
    return list_routing_table;
} 

