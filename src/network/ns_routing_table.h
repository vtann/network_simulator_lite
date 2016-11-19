#include <iostream>
#include <list>

typedef struct routing_entry
{
   std::string dst_ip_address;
   int network_mask;
   int outgoing_if_id;
   int gateway_if_id;
   std::string gateway_ip_address;  
}routing_entry;

std::list<routing_entry*> get_routing_table();  

void add_routing_table_entry(std::string dst_address, int mask, int interface, int gw_id, std::string gw_address);
    
int get_num_of_routing_table_entries();
