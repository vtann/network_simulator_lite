#include "ns_node.h"

#include "../ns_namespace.h"

#include "../interface/ns_node_router_if.h"

#include "../network/ns_routing_table.h"

#include "../network/ns_arp_table.h"

#ifndef __NS_NODE_ROUTER_H__
#define __NS_NODE_ROUTER_H__

class router : public node 
{
    public:
        router(int nodeID,int numbInterfaces, double xAxis, double yAxis);

        ~router();
        
        router(const router &r); //Copy constructor

        void add_interface(router_interface* interface);

        router_interface* get_interface(int if_id);

        router_interface* get_interface(std::string& mac);

        ns_ns::interfaces get_all_interfaces() const;

        int get_num_of_interfaces() const;

        double get_xAxis() const;

        double get_yAxis() const;
    
        routing_table* get_routing_table();

        arp_table* get_arp_table();

    private:
        int num_of_interfaces;
        double xAxis,yAxis;
        ns_ns::interfaces interface_list;
        routing_table *r_table;
        arp_table *a_table;
};

#endif // __NS_NODE_ROUTER_H__
