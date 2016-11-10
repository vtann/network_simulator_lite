#ifndef __NS_NODE_ROUTER_LINK_H__
#define __NS_NODE_ROUTER_LINK_H__
#include "ns_node_router_link.h"
#endif // __NS_NODE_ROUTER_LINK_H__ 

double router_link::get_link_cost() const
{
    return link_cost;
}

void router_link::set_link_cost(double cost)
{
    link_cost = cost;
}

void router_link::set_src_router(int src)
{
    src_router = src;
}

void router_link::set_dst_router(int dst)
{
    dst_router = dst;
}

void router_link::set_src_if(int src)
{
    src_interface = src;
}

void router_link::set_dst_if(int dst)
{
    dst_interface = dst;
}

int router_link::get_src_router() const
{
    return src_router;
}

int router_link::get_dst_router() const
{
    return dst_router;
}

int router_link::get_src_if() const
{
    return src_interface;
}

int router_link::get_dst_if() const
{
    return dst_interface;
}

void router_link::create_link(int src, int src_if, int dst, int dst_if)
{
    src_router = src;
    dst_router = dst;
    src_interface = src_if;
    dst_interface = dst_if;
}

