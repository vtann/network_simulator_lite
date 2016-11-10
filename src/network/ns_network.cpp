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

void router_network::calculate_shortest_path()
{
    int src_router;
    int dst_router;
    int vertices = router_list.size();
    double cost; 
    std::vector<double> min_distance;
    std::vector<int> previous;
    shortest_path adjacency_list(vertices);
   
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
                std::list<int> path = adjacency_list.dijkstra_get_shortest_path_to(inner_index, previous);
            }
        }
    } 
}
