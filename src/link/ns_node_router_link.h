#include <iostream>
#include <map>

#ifndef __NS_NODE_LINK_H__
#define __NS_NODE_LINK_H__
#include "ns_node_link.h"
#endif //__NS_NODE_LINK_H__

#ifndef __NS_NODE_ROUTER_H__
#define __NS_NODE_ROUTER_H__
#include "../node/ns_node_router.h"
#endif // __NS_NODE_ROUTER_H__ 

#ifndef __NS_NODE_ROUTER_IF_H__
#define __NS_NODE_ROUTER_IF_H__
#include "../interface/ns_node_router_if.h"
#endif // __NS_NODE_ROUTER_IF_H__ 

class router_link : public node_link
{
    public:
    router_link(int weight=1);
    
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

    int create_link(router* src_router, router_interface* src_if, router* dst_router, router_interface* dst_if);

    private:
    router* src_router;
    router* dst_router;
    router_interface* src_interface;
    router_interface* dst_interface; 
    double link_cost;
};
