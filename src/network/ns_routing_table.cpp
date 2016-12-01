#include "ns_routing_table.h"

void routing_table::add_routing_table_entry(std::string dst_address, int mask, int out_if, int gw_id, std::string gw_address)
{
    routing_entry *element = new routing_entry; 
    
    element->dst_ip_address = dst_address;
    element->network_mask = mask;
    element->outgoing_if_id = out_if; 
    element->gateway_if_id = gw_id;
    element->gateway_ip_address = gw_address;
    list_routing_table.push_back(element);
}
    
std::list<routing_entry*> routing_table::get_routing_table()
{
    return list_routing_table;
} 

int routing_table::get_num_of_routing_table_entries()
{
    return list_routing_table.size();
}

void routing_table::dump_routing_table_entries()
{
    std::cout << std::left << std::setw(15) << "Dest IP Address "
              << std::left << std::setw(12) << "Network Mask "
              << std::left << std::setw(21) << "Outgoing Interface ID "
              << std::left << std::setw(20) << "Gateway Interface ID "
              << std::left << std::setw(18) << "Gateway IP Address"
              << std::endl;

    for (std::list<routing_entry*>::iterator index = list_routing_table.begin(); index != list_routing_table.end(); index++)
    {
        std::cout << std::left << std::setw(15) << (*index)->dst_ip_address
                  << std::left << std::setw(12) << (*index)->network_mask
                  << std::left << std::setw(21) << (*index)->outgoing_if_id
                  << std::left << std::setw(20) << (*index)->gateway_if_id
                  << std::left << std::setw(18) << (*index)->gateway_ip_address
                  << std::endl;
    }
}
