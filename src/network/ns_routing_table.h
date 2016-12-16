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
   int gateway_router_id;
   int gateway_if_id;
   std::string gateway_ip_address;  
}routing_entry;

/*! 
 *  \brief     This router class has routing table related functions)
 *  \details   This class updates the routing table which are used for packet routing.
 *  \author    Karthika Krishnamurthy.
 *  \version   1.0
 *  \date      2016
 *  \pre       Used by router_network class.
 *  \bug       Not all memory is freed when deleting an object of this class.
 *  \warning   Improper use can crash your application
 *  \copyright GNU Public License.
 */
class routing_table 
{
    public:

    // Get routing table
    void add_routing_table_entry(std::string dst_address, int mask, int interface, int gw_router_id, int gw_id, std::string gw_address);
    
    // Get routing table entrues
    int get_num_of_routing_table_entries();

    // Dump routing table entries
    void dump_routing_table_entries();

    // Dump routing table entries
    void dump_routing_table_entries(std::ostream& routing_file);

    // Get routing table
    std::list<routing_entry*> get_routing_table();  

    private:
    std::list<routing_entry*> list_routing_table;
};

#endif // __NS_ROUTING_TABLE_H__ 

