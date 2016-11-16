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

router_link* router_network::find_link(int src_vertex, int dst_vertex)
{
    for (unsigned int index = 0; index < link_list.size(); index++)
    {
       if (link_list[index]->get_src_router()->get_node_id() == src_vertex)
       {
            if (link_list[index]->get_dst_router()->get_node_id() == dst_vertex)
            {
                return link_list[index];
            }
       }   
    }
    return NULL;
}
 
void router_network::calculate_shortest_path()
{
    router* src_router;
    router* dst_router;
    router_interface* src_if;
    router_interface* gw_if;
    router_interface* dst_if;
    int vertices = router_list.size();
    double cost; 
    std::vector<double> min_distance;
    std::vector<int> previous;
    shortest_path adjacency_list(vertices);
    router_link *start_edge; 
    router_link *end_edge; 
    std::vector<int> path; 
   
    for (std::vector<router_link*>::iterator index = link_list.begin(); index != link_list.end(); index++)
    {
        src_router = (*index)->get_src_router();  
        dst_router = (*index)->get_dst_router();  
        cost = (*index)->get_link_cost();
        adjacency_list.add_edge(src_router->get_node_id(), dst_router->get_node_id(), cost);  
    }
    for (int index = 0; index < vertices; index++)
    {
        adjacency_list.dijikstra_compute_paths(index, min_distance, previous); 
        for (int inner_index = 0; inner_index < vertices; inner_index++)
        {
            if (inner_index != index)
            {
                std::cout << "index: " << index << std::endl;  
                std::cout << "inner_index: " << inner_index << std::endl;  
                adjacency_list.dijkstra_get_shortest_path_to(path, inner_index, previous);
                if (index == path[0])
                {
                    int num = path.size();
                    start_edge = find_link(path[0], path[1]);
                    end_edge = find_link(path[num - 2], path[num - 1]);
                    src_if = start_edge->get_src_if();    
                    gw_if = start_edge->get_dst_if();   
                    dst_if = end_edge->get_dst_if();   
                    add_routing_table_entry(dst_if->get_network_address(), dst_if->get_mask(), src_if->get_interface_id(), gw_if->get_interface_id(), dst_if->get_network_address());
                    //add_arp_entry();  
                } 
            }
        }
    }
}




