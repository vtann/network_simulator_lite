#include <iostream>
#include <vector>
#include <list>

#include "../node/ns_node_router.h"

#include "../link/ns_node_router_link.h"

#include "ns_shortest_path.h"

#include "ns_routing_table.h"

#include "ns_arp_table.h"

#ifndef __NS_NETWORK_H__
#define __NS_NETWORK_H__ 

class router_network
{
    public:
    router_network();
     
    ~router_network();

    void add_router(router* new_router);

    void add_link(router_link* new_link);

    int number_of_routers();
    
    int number_of_links();
   
    router* get_router(int node_id);
    
    void calculate_shortest_path(ns_ns::graph_type graph);
    
    void set_routing_algorithm_param();      
    
    router_link* find_link(int src_vertex, int dst_vertex);
 
    private:
    std::vector<router*> router_list;
    std::vector<router_link*> link_list; 
};

#endif // __NS_NETWORK_H__
