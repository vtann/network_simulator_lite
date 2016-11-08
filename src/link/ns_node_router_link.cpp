#include "ns_node_router_link.h"

int router_link::get_link_cost() const
{
    return link_cost;
}

void router_link::set_link_cost(int cost)
{
    link_cost = cost;
}
