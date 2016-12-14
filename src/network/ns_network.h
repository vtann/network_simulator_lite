#include <iostream>

#include <vector>

#include <list>

#include <fstream>

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

    void add_router(std::shared_ptr<router> new_router);

    void add_link(std::shared_ptr<router_link> new_link);

    int number_of_routers();
    
    int number_of_links();
   
    std::vector<std::shared_ptr<router> > get_all_routers();

    std::vector<std::shared_ptr<router_link> > get_all_links();

    std::shared_ptr<router> get_router(int node_id);
    
    void calculate_shortest_path(ns_ns::graph_type graph, shortest_path_param param);
    
    void set_routing_algorithm_param();      
    
    std::shared_ptr<router_link> find_link(int src_vertex, int dst_vertex);
 
    std::shared_ptr<router_link> find_link(std::string& src_mac, std::string& dst_mac);
 
    void log_dump_of_all_routing_tables();

    void log_dump_of_all_arp_tables();

    private:
    ns_ns::routers router_list;
    ns_ns::links link_list; 
};

#endif // __NS_NETWORK_H__
