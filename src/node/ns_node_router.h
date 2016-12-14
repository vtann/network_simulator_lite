#include <memory>

#include "ns_node.h"

#include "../ns_namespace.h"

#include "../interface/ns_node_router_if.h"

#include "../network/ns_routing_table.h"

#include "../network/ns_arp_table.h"

#ifndef __NS_NODE_ROUTER_H__
#define __NS_NODE_ROUTER_H__

/*! 
 *  \brief     This router class inherits node (superclass)
 *  \details   This class creates a router used in the network simulation.
 *  \author    Karthika Krishnamurthy.
 *  \version   1.0
 *  \date      2016
 *  \pre       Needs node class.
 *  \bug       Not all memory is freed when deleting an object of this class.
 *  \warning   Improper use can crash your application
 *  \copyright GNU Public License.
 */
class router : public node 
{
    public:
        // Constructor of router class
        router(int nodeID, int numbInterfaces, double xAxis, double yAxis);

        // Destructor of router class
        ~router();
        
        // Copy constructor
        router(const router &r); 

        // Add interface to the routers 
        void add_interface(std::shared_ptr<router_interface> interface);

        // Get interface with interface id 
        std::shared_ptr<router_interface> get_interface(int if_id);

        // Get interface with MAC address 
        std::shared_ptr<router_interface> get_interface(std::string& mac);

        // Get all interfaces
        ns_ns::interfaces get_all_interfaces() const;

        // Get number of interfaces present in router 
        int get_num_of_interfaces() const;

        // Get x-axis location of router for GUI
        double get_xAxis() const;

        // Get y-axis location of router for GUI
        double get_yAxis() const;
   
        // Get routing table of this router  
        routing_table* get_routing_table();

        // Get ARP table of this router  
        arp_table* get_arp_table();

    private:
        // Number of interfaces
        int num_of_interfaces;
        
        // x-axis and y-axis location of router in GUI
        double xAxis, yAxis;
       
        // Interface list 
        ns_ns::interfaces interface_list;

        // Pointer to routing table
        routing_table* r_table;

        // Pointer to arp table
        arp_table* a_table;
};

#endif // __NS_NODE_ROUTER_H__
