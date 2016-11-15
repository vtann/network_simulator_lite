#include <limits.h>
#include "gtest/gtest.h"
#include "../../../node/ns_node_router.h"

TEST(test_router, router_creation)
{
    router router_1(1);
    router router_2(2);

    EXPECT_EQ(1, router_1.get_node_id()); 
    EXPECT_EQ(2, router_2.get_node_id()); 
}

TEST(test_router, router_if_list_creation)
{
    router router_1(1);
    router router_2(2);

    EXPECT_EQ(1, router_1.get_node_id()); 
    EXPECT_EQ(2, router_2.get_node_id()); 

    router_interface router_if_1(1);
    router_interface router_if_2(2);

    EXPECT_EQ(1, router_if_1.get_interface_id()); 
    EXPECT_EQ(2, router_if_2.get_interface_id());

    std::string mac_address_1 = "00:00:00:00:00:01";
    std::string mac_address_2 = "00:00:00:00:00:02";

    router_if_1.set_interface_address(mac_address_1);
    router_if_2.set_interface_address(mac_address_2);
   
    EXPECT_EQ(mac_address_1, router_if_1.get_interface_address()); 
    EXPECT_EQ(mac_address_2, router_if_2.get_interface_address()); 

    router_1.add_interface(&router_if_1); 
    router_1.add_interface(&router_if_2);

    router_interface *router_if_3 = router_1.get_interface(1); 
    EXPECT_EQ(1, router_if_3->get_interface_id());
    router_interface *router_if_4 = router_1.get_interface(2); 
    EXPECT_EQ(2, router_if_4->get_interface_id());
    router_interface *router_if_5 = router_2.get_interface(1); 
    EXPECT_EQ(NULL, router_if_5);
    router_if_3 = router_1.get_interface(mac_address_1); 
    EXPECT_EQ(mac_address_1, router_if_3->get_interface_address());
    router_if_3 = router_2.get_interface(mac_address_1); 
    EXPECT_EQ(NULL, router_if_3);
}




