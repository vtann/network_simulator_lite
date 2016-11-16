#include <iostream>
#include <list>

typedef struct arp_entry
{
   std::string gateway_ip_address;  
   std::string gateway_mac_address;
}arp_entry;

std::list<arp_entry*> get_arp_table();  

void add_arp_table_entry(std::string gw_network_address, std::string gw_mac_address);
    
