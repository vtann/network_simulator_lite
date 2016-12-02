#include "ns_node_router_link.h"

using namespace ns_ns;

router_link::router_link(int link_id)
{
    this->link_id = link_id;
}

router_link::~router_link()
{
}

double router_link::get_link_cost() const
{
    return link_cost;
}

void router_link::set_link_cost(double cost)
{
    link_cost = cost;
}

void router_link::set_src_router(router* src)
{
    src_router = src;
}

void router_link::set_dst_router(router* dst)
{
    dst_router = dst;
}

void router_link::set_src_if(router_interface* src)
{
    src_interface = src;
}

void router_link::set_dst_if(router_interface* dst)
{
    dst_interface = dst;
}

router* router_link::get_src_router() 
{
    return src_router;
}

router* router_link::get_dst_router() 
{
    return dst_router;
}

router_interface* router_link::get_src_if() 
{
    return src_interface;
}

router_interface* router_link::get_dst_if() 
{
    return dst_interface;
}

int router_link::create_link(router* src, router_interface* src_if, router* dst, router_interface* dst_if,double link_speed,double link_weight)
{
    if ((dst_if->get_router_id() == src_if->get_router_id()) && (dst->get_node_id() == src->get_node_id()))
    {
        return NOT_OK;
    }

    if ((true == src_if->get_is_connected_flag()) || (true == dst_if->get_is_connected_flag()))     
    {
        return NOT_OK;
    }

    if ((src->get_node_id() != src_if->get_router_id()) || (dst->get_node_id() != dst_if->get_router_id()))
    {
        return NOT_OK;
    }
    src_router = src;
    dst_router = dst;
    src_interface = src_if;
    dst_interface = dst_if;
    src_interface->set_is_connected_flag(true);
    dst_interface->set_is_connected_flag(true);
    this->link_speed = link_speed;
    this->link_cost = link_weight;
 
    return OK; 
}

