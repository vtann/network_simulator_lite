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
  
    double get_link_cost() const;

    void set_link_cost(double cost);

    void set_src_router(int src);
   
    void set_dst_router(int dst);

    void set_src_if(int src);
 
    void set_dst_if(int dst);

    int get_src_router() const;

    int get_dst_router() const;

    int get_src_if() const;

    int get_dst_if() const;

    void create_link(int src_router, int src_if, int dst_router, int dst_if);

    //std::map < std::pair<int, int>, std::pair<int, int> > get_link() const;  
    
    private:
    //std::map < std::pair<int, int>, std::pair<int, int> > link;
    int src_router;
    int dst_router;
    int src_interface;
    int dst_interface;
    double link_cost;
};
