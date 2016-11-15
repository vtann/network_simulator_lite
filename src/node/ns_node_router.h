#ifndef __NS_NODE_H__
#define __NS_NODE_H__
#include "ns_node.h"
#endif //  __NS_NODE_H__

#ifndef __NS_NAMESPACE_H__
#define __NS_NAMESPACE_H__
#include "../ns_namespace.h"
#endif // __NS_NAMESPACE_H__

#ifndef __NS_NODE_ROUTER_IF_H__
#define __NS_NODE_ROUTER_IF_H__
#include "../interface/ns_node_router_if.h"
#endif // __NS_NODE_ROUTER_IF_H__ 

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

