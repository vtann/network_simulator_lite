#include <iostream>
#include <vector>
#include <list>

#ifndef __NS_NODE_ROUTER_H__
#define __NS_NODE_ROUTER_H__
#include "../node/ns_node_router.h"
#endif // __NS_NODE_ROUTER_H__ 

#ifndef __NS_NODE_ROUTER_LINK_H__
#define __NS_NODE_ROUTER_LINK_H__
#include "../link/ns_node_router_link.h"
#endif // __NS_NODE_ROUTER_LINK_H__ 

#ifndef __NS_SHORTEST_PATH_H__
#define __NS_SHORTEST_PATH_H__
#include "ns_shortest_path.h"
#endif // __NS_SHORTEST_PATH_H__ 

class router_network
{
    public:
    router_network();
     
    ~router_network();

    void add_router(router* new_router);

    void add_link(router_link* new_link);

    int number_of_routers();
    
    int number_of_links();
    
    void calculate_shortest_path();
    
    void set_routing_algorithm_param();      
    
    //router_link 
 
    private:
    std::vector<router*> router_list;
    std::vector<router_link*> link_list; 
};
