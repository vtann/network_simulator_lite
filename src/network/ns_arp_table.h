#include <iostream>

#include <list>

#include <algorithm>

#include <iomanip>

#ifndef __NS_ARP_TABLE_H__
#define __NS_ARP_TABLE_H__

typedef struct arp_entry
{
   std::string gateway_ip_address;  
   std::string gateway_mac_address;
}arp_entry;

/*! 
 *  \brief     This router class has ARP related functions)
 *  \details   This class updates the ARP table which are used for packet routing.
 *  \author    Karthika Krishnamurthy.
 *  \version   1.0
 *  \date      2016
 *  \pre       Used by router_network class.
 *  \bug       Not all memory is freed when deleting an object of this class.
 *  \warning   Improper use can crash your application
 *  \copyright GNU Public License.
 */
class arp_table 
{
    public:
 
    // Get ARP table
    std::list<arp_entry*> get_arp_table();  

    // Add ARP entry
    void add_arp_table_entry(std::string gw_network_address, std::string gw_mac_address);
    
    // Get ARP table entries
    int get_num_of_arp_table_entries();
  
    // Find entry with Gateway IP address. 
    std::string find_entry(std::string gw_ip_address);

    // Dump ARP entries
    void dump_arp_table_entries(std::ostream& arp_file);

    // Check whether ARP entry is already present. 
    bool is_arp_present(std::string gw_ip_address);
 
    private:
    std::list<arp_entry*> list_arp_table;
};

#endif // __NS_ARP_TABLE_H__ 

