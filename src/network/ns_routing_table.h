#include <iostream>

#include <list>

#include <iomanip>

#ifndef __NS_ROUTING_TABLE_H__
#define __NS_ROUTING_TABLE_H__

typedef struct routing_entry
{
   std::string dst_ip_address;
   int network_mask;
   int outgoing_if_id;
   int gateway_if_id;
   std::string gateway_ip_address;  
}routing_entry;

class routing_table 
{
    public:
    void add_routing_table_entry(std::string dst_address, int mask, int interface, int gw_id, std::string gw_address);
    
    int get_num_of_routing_table_entries();

    void dump_routing_table_entries();

    std::list<routing_entry*> get_routing_table();  

    private:
    std::list<routing_entry*> list_routing_table;
};

#endif // __NS_ROUTING_TABLE_H__ 
