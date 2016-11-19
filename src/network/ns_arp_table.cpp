#ifndef __NS_ARP_TABLE_H__
#define __NS_ARP_TABLE_H__
#include "ns_arp_table.h"
#endif // __NS_ARP_TABLE_H__ 

std::list<arp_entry*> list_arp_table;

void add_arp_table_entry(std::string gw_nw_addr, std::string gw_mac_addr)
{
    arp_entry *element = new arp_entry; 
    
    element->gateway_ip_address = gw_nw_addr;
    element->gateway_mac_address = gw_mac_addr;
    list_arp_table.push_back(element);
}
    
std::list<arp_entry*> get_arp_table()
{
    return list_arp_table;
} 

int get_num_of_arp_table_entries()
{
   return list_arp_table.size();
}
