#ifndef __NS_NETWORK_H__
#define __NS_NETWORK_H__ 
#include "ns_network.h"
#endif // __NS_NETWORK_H__

router_network::router_network()
{
}

router_network::~router_network()
{
}

int router_network::number_of_routers()
{
    return router_list.size(); 
}

int router_network::number_of_links()
{
    return link_list.size(); 
}

void router_network::add_router(router* new_router)
{
    router_list.push_back(new_router);
}

void router_network::add_link(router_link* new_link)
{
    link_list.push_back(new_link);
}

void router_network::calculate_shortest_path()
{
    router* src_router;
    router* dst_router;
    router_interface* src_if;
    router_interface* gw_if;
    int mask; 
    int vertices = router_list.size();
    double cost; 
    std::vector<double> min_distance;
    std::vector<int> previous;
    shortest_path adjacency_list(vertices);
    std::vector<int>path;
    router_link *edge; 
   
    for (std::vector<router_link*>::iterator index = link_list.begin(); index != link_list.end(); index++)
    {
        src_router = (*index)->get_src_router();  
        dst_router = (*index)->get_dst_router();  
        cost = (*index)->get_link_cost();
        adjacency_list.add_edge(src_router, dst_router, cost);  
    }
    for (int index = 0; index < vertices; index++)
    {
        adjacency_list.dijikstra_compute_paths(index, min_distance, previous); 
        for (int inner_index = 0; inner_index < vertices; inner_index++)
        {
            if (inner_index != index)
            {
                path = adjacency_list.dijkstra_get_shortest_path_to(inner_index, previous);
                if (index == path[0])
                {
                    edge = find_link(path[0], path[1])
                    src_if = edge->get_src_if();    
                    gw_if = edge->get_dst_if();   
                    add_routing_table_entry(gw_if->get_network_address, gw_if->get_if_id, dst_if->mask, );
                    add_arp_entry();  
                }    
                delete path;
            }
        }
    }
}




