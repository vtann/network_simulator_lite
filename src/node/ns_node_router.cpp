#include "ns_node_router.h"

router::router(int n) : node(n)
{
    //interface_list = NULL;
      
} 

router::~router()
{
    //interface_list = NULL;
}

void router::add_interface(router_interface* interface)
{
    interface_list.push_back(interface);  
}

router_interface* router::get_interface(int if_id) 
{
    int num = num_of_interfaces();
    int index;

    if ((if_id < 0) || (if_id > num))
    {
        return NULL;
    }
    for (index = 0; index < num; index++)
    {
        if (interface_list[index]->get_interface_id() == if_id)
        {
            break;
        }  
    }
    return interface_list[index]; 
}

router_interface* router::get_interface(std::string& mac) 
{
    int num = num_of_interfaces();
    int index;
    int found = 0;

    for (index = 0; index < num; index++)
    {
        if (0 == mac.compare(interface_list[index]->get_interface_address()))
        {
            found = 1;
            break;
        }  
    }
    return ((1 == found) ? interface_list[index] : NULL); 
}

ns_ns::interfaces router::get_all_interfaces() const
{
    return interface_list;
}  

int router::num_of_interfaces() const
{
    return interface_list.size();
}


