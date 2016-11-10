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

class routing_table
{
    routing_table();

    ~routing_table();
   
    int add_routing_table_entries(std::string dst_address, int mask, int interface);
    
    std::list<routing_entry*> get_routing_table();  

    private:
    std::list<routing_entry*> list_routing_table;
};

