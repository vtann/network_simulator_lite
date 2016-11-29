#include "ns_node.h"

#include "../ns_namespace.h"

#include "../interface/ns_node_router_if.h"

#ifndef __NS_NODE_ROUTER_H__
#define __NS_NODE_ROUTER_H__

class router : public node 
{
    public:
    router(int n=-1);
    
    ~router();
    
    void add_interface(router_interface* interface);

    router_interface* get_interface(int if_id);
    
    router_interface* get_interface(std::string& mac);
    
    ns_ns::interfaces get_all_interfaces() const;
    
    int num_of_interfaces() const;
    
    private:
    ns_ns::interfaces interface_list;
};

#endif // __NS_NODE_ROUTER_H__
