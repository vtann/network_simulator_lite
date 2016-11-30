#include "ns_node_router.h"

router::router(int nodeID,int numbInterfaces, double xAxis, double yAxis) : node(nodeID)
{
    this->num_of_interfaces=numbInterfaces;
    this->xAxis=xAxis;
    this->yAxis=yAxis;
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
    int num = get_num_of_interfaces();
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
    int num = get_num_of_interfaces();
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

int router::get_num_of_interfaces() const
{
    return interface_list.size();
}

double router::get_xAxis() const
{
    return this->xAxis;
}

double router::get_yAxis() const
{
    return this->yAxis;
}


router::router(const router &r):node(r.get_node_id()) {
    this->num_of_interfaces=r.get_num_of_interfaces();
    this->xAxis=r.get_xAxis();
    this->yAxis=r.get_yAxis();
}


