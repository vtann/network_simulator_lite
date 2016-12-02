#include <limits.h>
#include "../../../link/ns_node_router_link.h"
#include "gtest/gtest.h"

TEST(test_router_link, router_link_creation)
{
    //router(int nodeID,int numbInterfaces, double xAxis, double yAxis);
    router router_1(1,1,1.1,1.1);
    router router_2(2,2,2.2,2.2);

    EXPECT_EQ(1, router_1.get_node_id()); 
    EXPECT_EQ(2, router_2.get_node_id()); 

    //router_interface(int nodeID,int interfaceID,std::string mac,std::string ip, int mask, int interfaceQueue, double interfaceSpeed);
    router_interface router_if_1(1, 1,"00:00:00:00:00:01","192.169.0.0",24,10,100.1);
    router_interface router_if_2(1, 2,"00:00:00:00:00:02","192.169.1.0",24,10,100.1);
    router_interface router_if_3(2, 1,"00:00:00:00:00:03","192.169.3.0",24,10,100.1);

    EXPECT_EQ(1, router_if_1.get_interface_id()); 
    EXPECT_EQ(2, router_if_2.get_interface_id());
    EXPECT_EQ(1, router_if_3.get_interface_id());

    std::string mac_address_1 = "00:00:00:00:00:01";
    std::string mac_address_2 = "00:00:00:00:00:02";
    std::string mac_address_3 = "00:00:00:00:00:03";

    router_if_1.set_interface_address(mac_address_1);
    router_if_2.set_interface_address(mac_address_2);
    router_if_3.set_interface_address(mac_address_3);
   
    EXPECT_EQ(mac_address_1, router_if_1.get_interface_address()); 
    EXPECT_EQ(mac_address_2, router_if_2.get_interface_address()); 
    EXPECT_EQ(mac_address_3, router_if_3.get_interface_address()); 

    router_1.add_interface(&router_if_1); 
    router_1.add_interface(&router_if_2);
    router_2.add_interface(&router_if_3);
     
    router_interface *router_if_temp = router_1.get_interface(1); 
    EXPECT_EQ(1, router_if_temp->get_interface_id());
    router_if_temp = router_1.get_interface(2); 
    EXPECT_EQ(2, router_if_temp->get_interface_id());
    router_if_temp = router_2.get_interface(1); 
    EXPECT_EQ(1, router_if_temp->get_interface_id());

    router_link router_link_1(1);
    router_link router_link_2(2);

    EXPECT_EQ(1, router_link_1.get_link_cost());
    EXPECT_EQ(1, router_link_2.get_link_cost());
    
    EXPECT_EQ(false, router_if_1.get_is_connected_flag());
    EXPECT_EQ(false, router_if_2.get_is_connected_flag());
    EXPECT_EQ(false, router_if_3.get_is_connected_flag());
    
    //int create_link(router* src_router, router_interface* src_if, router* dst_router, router_interface* dst_if,double link_speed,double link_weight);
    EXPECT_EQ(0, router_link_1.create_link(&router_1, &router_if_1, &router_2, &router_if_3,100.2,10.2));    
    EXPECT_EQ(1, router_link_1.create_link(&router_1, &router_if_3, &router_2, &router_if_3,100.2,10.2));    
    
    EXPECT_EQ(true, router_if_1.get_is_connected_flag());
    EXPECT_EQ(true, router_if_3.get_is_connected_flag());
    
}