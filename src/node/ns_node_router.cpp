#include "ns_node_router.h"

/*! \fn router(int node_id, int num_interfaces, double x_axis, double y_axis) 
 *  \brief A constructor function which creates a router object.
 *  \param node_id, unique identifier for router.
 *  \param num_interfaces, number of interfaces present in the router.
 *  \param x_axis, x co-ordinate for router position in GUI.
 *  \param y_axis, y co-ordinate for router position in GUI.
 *  \exception std::out_of_range parameter is out of range.
 *  \return None.
 */
router::router(int node_id, int num_interfaces, double x_axis, double y_axis) : node(node_id)
{
    this->num_of_interfaces = num_interfaces;
    this->xAxis = x_axis;
    this->yAxis = y_axis;

    // Allocate memory for routing table class
    r_table = new routing_table;
    
    // Allocate memory for arp table class
    a_table = new arp_table;
} 

router::~router()
{
}

/*! \fn add_interface(router_interface* interface)
 *  \brief Function to add interface to a router
 *  \param interface, pointer to a router_interface class
 *  \return Nothing.
 */ 
void router::add_interface(std::shared_ptr<router_interface> interface)
{
    interface_list.push_back(interface);  
}

/*! \fn get_interface(router_interface* interface)
 *  \brief Function to add interface to a router
 *  \param if_id, interface id.
 *  \return pointer to a router_interface class.
 */ 
std::shared_ptr<router_interface> router::get_interface(int if_id) 
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

/*! \fn get_interface(router_interface* interface)
 *  \brief Function to add interface to a router
 *  \param mac, interface MAC address.
 *  \return pointer to a router_interface class.
 */ 
std::shared_ptr<router_interface> router::get_interface(std::string& mac) 
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

/*! \fn get_all_interfaces()
 *  \brief Function to get all interfaces of a router
 *  \param None.
 *  \return pointer to a list of router_interface class objects.
 */ 
ns_ns::interfaces router::get_all_interfaces() const
{
    return interface_list;
}  

/*! \fn get_num_all_interfaces()
 *  \brief Function to get all interfaces of a router
 *  \param None.
 *  \return pointer to a list of router_interface class objects.
 */
int router::get_num_of_interfaces() const
{
    return interface_list.size();
}

/*! \fn get_xAxis()
 *  \brief Function to get x co-ordinate of a router in GUI
 *  \param None.
 *  \return x-axis value.
 */
double router::get_xAxis() const
{
    return this->xAxis;
}

/*! \fn get_yAxis()
 *  \brief Function to get y co-ordinate of a router in GUI
 *  \param None.
 *  \return y-axis value.
 */
double router::get_yAxis() const
{
    return this->yAxis;
}

/*! \fn router(int nodeID, int numbInterfaces, double xAxis, double yAxis) 
 *  \brief A constructor function which creates a router object.
 *  \param r, pointer to router class object.
 *  \return None.
 */
router::router(const router &r) : node(r.get_node_id()) 
{
    this->num_of_interfaces=r.get_num_of_interfaces();
    this->xAxis=r.get_xAxis();
    this->yAxis=r.get_yAxis();
}

/*! \fn get_routing_table()
 *  \brief Function to get routing table of the router
 *  \param None.
 *  \return Pointer to routing table class object.
 */
routing_table* router::get_routing_table()
{
    return r_table;
}

/*! \fn get_arp_table()
 *  \brief Function to get arp table of the router
 *  \param None.
 *  \return Pointer to arp table class object.
 */
arp_table* router::get_arp_table()
{
    return a_table;
}
