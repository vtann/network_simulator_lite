#include "ns_network.h"

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

std::vector<router*> router_network::get_all_routers()
{
    return router_list; 
}

std::vector<router_link*> router_network::get_all_links()
{
    return link_list; 
}

router* router_network::get_router(int node_id)
{
    for (unsigned int index = 0; index < router_list.size(); index++)
    {
        if (node_id == router_list[index]->get_node_id())
        {
            return router_list[index]; 
        } 
    }
    return NULL;
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
 
router_link* router_network::find_link(std::string& src_mac, std::string& dst_mac)
{
    unsigned int index;

    for (index = 0; index < link_list.size(); index++)
    {
        if (0 == src_mac.compare(link_list[index]->get_src_if()->get_interface_address()))
        {
            if (0 == dst_mac.compare(link_list[index]->get_dst_if()->get_interface_address()))
            {
                return link_list[index];   
            }
        }
    }
    return NULL;
}

void router_network::calculate_shortest_path(ns_ns::graph_type graph, ns_ns::shortest_path_param param)
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
    std::ofstream shortpath_file;

    shortpath_file.open("logs/ns_traceroute_logs.txt");
    shortpath_file << "Shortest path for all nodes are below:" << std::endl;   
   
    for (std::vector<router_link*>::iterator index = link_list.begin(); index != link_list.end(); index++)
    {
        src_router = (*index)->get_src_router();  
        dst_router = (*index)->get_dst_router(); 
        if (param == LINK_COST)
        { 
            cost = (*index)->get_link_cost();
        }
        else 
        {
            cost = (*index)->get_link_delay();
        } 
        if (false == adjacency_list.check_remove_dup_edge(graph, src_router->get_node_id(), dst_router->get_node_id(), cost))
        {
            adjacency_list.add_edge(graph, src_router->get_node_id(), dst_router->get_node_id(), cost);  
        } 
    }

    // Print edges for debugging purposes
    // adjacency_list.print_edges();    

    for (int index = 0; index < vertices; index++)
    {
        router *r = router_list[index]; 
        routing_table *r_t = r->get_routing_table();    
        arp_table *a_t = r->get_arp_table();    
        adjacency_list.dijikstra_compute_paths(index, min_distance, previous);
         
        // Below code is used for logging puposes
        adjacency_list.log_dijkstra_paths(index, previous, shortpath_file);           
 
        for (int inner_index = 0; inner_index < vertices; inner_index++)
        {
            if (inner_index != index)
            {
                //std::cout << "index: " << index << std::endl;  
                //std::cout << "inner_index: " << inner_index << std::endl;  
                adjacency_list.dijkstra_get_shortest_path_to(path, inner_index, previous);
                int num = path.size();
 
                start_edge = find_link(path[num - 2], path[num - 1]);
                if ((NULL == start_edge))
                {
                    start_edge = find_link(path[num - 1], path[num - 2]);
                    if ((NULL != start_edge))
                    {
                        src_if = start_edge->get_src_if();    
                        gw_if = start_edge->get_dst_if();   
                    } 
                    else
                    {
                        return;
                    }
                }
                else
                {
                    gw_if = start_edge->get_src_if();    
                    src_if = start_edge->get_dst_if();   
                } 
                end_edge = find_link(path[0], path[1]);
                if ((NULL == end_edge))
                {
                    end_edge = find_link(path[1], path[0]);
                    if ((NULL != end_edge))
                    {
                        dst_if = end_edge->get_dst_if();   
                    } 
                    else
                    {
                        return;
                    }
                }
                else
                {
                    dst_if = end_edge->get_src_if();   
                } 
                r_t->add_routing_table_entry(dst_if->get_network_address(), dst_if->get_mask(), src_if->get_interface_id(), gw_if->get_router_id(), gw_if->get_interface_id(), gw_if->get_network_address());
                a_t->add_arp_table_entry(gw_if->get_network_address(), gw_if->get_interface_address());  
            }
            path.clear();
        }
        path.clear();
    }
    shortpath_file.close();
}

void router_network::log_dump_of_all_routing_tables()
{
    std::ofstream routing_file;

    routing_file.open("logs/ns_routing_table_logs.txt");
    routing_file << "Routing table of all nodes are below:" << std::endl;  
    
    for (auto index = router_list.begin(); index != router_list.end(); index++)
    {
        routing_file << "=====================================================================================================================" << std::endl;
        routing_file << "Node: " << (*index)->get_node_id() << std::endl;  
        routing_file << "-----------------------------------------------------------------------------------------------------------------" << std::endl;
        (*index)->get_routing_table()->dump_routing_table_entries(routing_file); 
        routing_file << "-----------------------------------------------------------------------------------------------------------------" << std::endl;
        routing_file << "=====================================================================================================================" << std::endl;
    } 
    routing_file.close();
}

void router_network::log_dump_of_all_arp_tables()
{
    std::ofstream arp_file;

    arp_file.open("logs/ns_arp_table_logs.txt");
    arp_file << "ARP table of all nodes are below:" << std::endl;  
    
    for (auto index = router_list.begin(); index != router_list.end(); index++)
    {
        arp_file << "=====================================================================================================================" << std::endl;
        arp_file << "Node: " << (*index)->get_node_id() << std::endl;  
        arp_file << "-----------------------------------------------------------------------------------------------------------------" << std::endl;
        (*index)->get_arp_table()->dump_arp_table_entries(arp_file); 
        arp_file << "-----------------------------------------------------------------------------------------------------------------" << std::endl;
        arp_file << "=====================================================================================================================" << std::endl;
    } 
    arp_file.close();
}


