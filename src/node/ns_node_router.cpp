#ifndef __NS_NODE_ROUTER_H__
#define __NS_NODE_ROUTER_H__
#include "ns_node_router.h"
#endif // __NS_NODE_ROUTER_H__

router::router(int n) : node(n)
{
} 

router::~router()
{
}

router_interface* router::get_interface(int if_id) const
{
    return interface_list[if_id]; 
}

ns_ns::interfaces router::get_all_interfaces() const
{
    return interface_list;
}  

