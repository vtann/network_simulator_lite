#include <limits.h>
#include "../../../link/ns_node_router_link.h"
#include "gtest/gtest.h"

TEST(test_router_link, router_link_creation)
{
    // router(int nodeID, int numbInterfaces, double xAxis, double yAxis);
    std::shared_ptr<router> router_1 (new router(1, 1, 1.1, 1.1));
    std::shared_ptr<router> router_2 (new router(2, 2, 2.2, 2.2));

    // Check whether nodes are created properly by checking router id
    EXPECT_EQ(1, router_1->get_node_id()); 
    EXPECT_EQ(2, router_2->get_node_id()); 

    // router_interface(int nodeID, int interfaceID, std::string mac, std::string ip, int mask, int interfaceQueue, double interfaceSpeed);
    std::shared_ptr<router_interface> router_if_1 (new router_interface(1, 1, "00:00:00:00:00:01", "192.169.0.0", 24, 10, 100.1));
    std::shared_ptr<router_interface> router_if_2 (new router_interface(1, 2, "00:00:00:00:00:02", "192.169.1.0", 24, 10, 100.1));
    std::shared_ptr<router_interface> router_if_3 (new router_interface(2, 1, "00:00:00:00:00:03", "192.169.3.0", 24, 10, 100.1));

    // Check whether interfaces are created properly by checking interface id
    EXPECT_EQ(1, router_if_1->get_interface_id()); 
    EXPECT_EQ(2, router_if_2->get_interface_id());
    EXPECT_EQ(1, router_if_3->get_interface_id());

    std::string mac_address_1 = "00:00:00:00:00:01";
    std::string mac_address_2 = "00:00:00:00:00:02";
    std::string mac_address_3 = "00:00:00:00:00:03";

    // Configure MAC address for interfaces
    router_if_1->set_interface_address(mac_address_1);
    router_if_2->set_interface_address(mac_address_2);
    router_if_3->set_interface_address(mac_address_3);
   
    // Check whether MAC addresses are configured properly 
    EXPECT_EQ(mac_address_1, router_if_1->get_interface_address()); 
    EXPECT_EQ(mac_address_2, router_if_2->get_interface_address()); 
    EXPECT_EQ(mac_address_3, router_if_3->get_interface_address()); 

    // Add interfaces to router 1
    router_1->add_interface(router_if_1); 
    router_1->add_interface(router_if_2);
    // Add interfaces to router 2
    router_2->add_interface(router_if_3);
     
    // Get created interfaces of router 1 and check interface id
    std::shared_ptr<router_interface> router_if_temp = router_1->get_interface(1); 
    EXPECT_EQ(1, router_if_temp->get_interface_id());
    router_if_temp = router_1->get_interface(2); 
    EXPECT_EQ(2, router_if_temp->get_interface_id());
    
    // Get created interfaces of router 2 and check interface id
    router_if_temp = router_2->get_interface(1); 
    EXPECT_EQ(1, router_if_temp->get_interface_id());

    std::shared_ptr<router_link> router_link_1 (new router_link(1));
    std::shared_ptr<router_link> router_link_2 (new router_link(2));

    // Actually interface not connected 
    EXPECT_EQ(false, router_if_1->get_is_connected_flag());
    EXPECT_EQ(false, router_if_2->get_is_connected_flag());
    EXPECT_EQ(false, router_if_3->get_is_connected_flag());
    
    // create_link(router* src_router, router_interface* src_if, router* dst_router, router_interface* dst_if, double link_delay, double link_weight);
    EXPECT_EQ(0, router_link_1->create_link(router_1, router_if_1, router_2, router_if_3, 100.2, 10.2));    
    EXPECT_EQ(1, router_link_2->create_link(router_1, router_if_3, router_2, router_if_3, 100.2, 10.2));    
   
    // Check link cost is configured properly 
    EXPECT_EQ(10.2, router_link_1->get_link_cost());
    
    // Actually interface connected now 
    EXPECT_EQ(true, router_if_1->get_is_connected_flag());
    EXPECT_EQ(true, router_if_3->get_is_connected_flag());
}
