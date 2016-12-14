#include <iostream>
#include <map>
#include <memory>

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

    double get_link_delay() const;

    void set_link_delay(double cost);

    void set_src_router(std::shared_ptr<router> src);
   
    void set_dst_router(std::shared_ptr<router> dst);

    void set_src_if(std::shared_ptr<router_interface> src);
 
    void set_dst_if(std::shared_ptr<router_interface> dst);

    std::shared_ptr<router> get_src_router();

    std::shared_ptr<router> get_dst_router();

    std::shared_ptr<router_interface> get_src_if();

    std::shared_ptr<router_interface> get_dst_if();

    int create_link(std::shared_ptr<router> src_router, std::shared_ptr<router_interface> src_if, std::shared_ptr<router> dst_router, std::shared_ptr<router_interface> dst_if, double link_delay, double link_weight);

    private:
    int link_id;
    std::shared_ptr<router> src_router;
    std::shared_ptr<router> dst_router;
    std::shared_ptr<router_interface> src_interface;
    std::shared_ptr<router_interface> dst_interface; 
    double link_delay;
    double link_cost;
};

#endif // __NS_NODE_ROUTER_LINK_H__ 
