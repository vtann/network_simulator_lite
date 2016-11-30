#include <iostream>
#include <map>

#include "ns_node_link.h"

#include "../node/ns_node_router.h"

#include "../interface/ns_node_router_if.h"

#ifndef __NS_NODE_ROUTER_LINK_H__
#define __NS_NODE_ROUTER_LINK_H__

class router_link : public node_link
{
    public:
    router_link(int link_id);
    
    ~router_link(); 
  
    double get_link_cost() const;

    void set_link_cost(double cost);

    void set_src_router(router* src);
   
    void set_dst_router(router* dst);

    void set_src_if(router_interface* src);
 
    void set_dst_if(router_interface* dst);

    router* get_src_router();

    router* get_dst_router();

    router_interface* get_src_if();

    router_interface* get_dst_if();

    int create_link(router* src_router, router_interface* src_if, router* dst_router, router_interface* dst_if,int link_speed,double link_weight);

    private:
    int link_id;
    router* src_router;
    router* dst_router;
    router_interface* src_interface;
    router_interface* dst_interface; 
    int link_speed;
    double link_cost;
};

#endif // __NS_NODE_ROUTER_LINK_H__ 
