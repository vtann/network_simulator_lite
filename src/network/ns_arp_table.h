#include <iostream>
#include <list>

#ifndef __NS_ARP_TABLE_H__
#define __NS_ARP_TABLE_H__

typedef struct arp_entry
{
   std::string gateway_ip_address;  
   std::string gateway_mac_address;
}arp_entry;

class arp_table 
{
    public:
    std::list<arp_entry*> get_arp_table();  

    void add_arp_table_entry(std::string gw_network_address, std::string gw_mac_address);
    
    int get_num_of_arp_table_entries();
   
    private:
    std::list<arp_entry*> list_arp_table;
};

#endif // __NS_ARP_TABLE_H__ 
