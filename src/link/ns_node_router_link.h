#include <iostream>
#include <map>

#ifndef __NS_NODE_LINK_H__
#define __NS_NODE_LINK_H__
#include "ns_node_link.h"
#endif //__NS_NODE_LINK_H__

#ifndef __NS_NODE_ROUTER_IF_H__
#define __NS_NODE_ROUTER_IF_H__
#include "../interface/ns_node_router_if.h"
#endif // __NS_NODE_ROUTER_IF_H__ 

class router_link : public node_link
{
    public:
    router_link() { };
    
    ~router_link(); 
  
    int get_link_cost() const;

    void set_link_cost(int cost);
    
    private:
    int link_cost;
    std::map<router_interface*, router_interface*> link; 
};
