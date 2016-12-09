#include "ns_arp_table.h"

void arp_table::add_arp_table_entry(std::string gw_nw_addr, std::string gw_mac_addr)
{
    arp_entry *element = new arp_entry; 
    
    element->gateway_ip_address = gw_nw_addr;
    element->gateway_mac_address = gw_mac_addr;
    list_arp_table.push_back(element);
}
    
std::list<arp_entry*> arp_table::get_arp_table()
{
    return list_arp_table;
} 

int arp_table::get_num_of_arp_table_entries()
{
   return list_arp_table.size();
}

std::string arp_table::find_entry(std::string gw_ip_address) 
{
    for (std::list<arp_entry*>::iterator index = list_arp_table.begin(); index != list_arp_table.end(); index++)
    {
        if (0 == gw_ip_address.compare((*index)->gateway_ip_address))
        {
            return (*index)->gateway_mac_address;  
        }
    } 
    return NULL;
}

void arp_table::dump_arp_table_entries(std::ostream& arp_file)
{
    arp_file << std::left << std::setw(20) << "Gateway IP Address "
              << std::left << std::setw(20) << "Gateway MAC Address"
              << std::endl;

    for (std::list<arp_entry*>::iterator index = list_arp_table.begin(); index != list_arp_table.end(); index++)
    {
        arp_file << std::left << std::setw(20) << (*index)->gateway_ip_address
                  << std::left << std::setw(20) << (*index)->gateway_mac_address
                  << std::endl;
    }
}

