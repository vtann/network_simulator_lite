#include <limits.h>
#include "../../../network/ns_network.h"
#include "gtest/gtest.h"

TEST(test_network, network_creation)
{
    router router_1(1);
    router router_2(2);
    router router_3(3);

    EXPECT_EQ(1, router_1.get_node_id()); 
    EXPECT_EQ(2, router_2.get_node_id()); 
    EXPECT_EQ(3, router_3.get_node_id()); 

    router_interface router_if_1_1(1, 1);
    router_interface router_if_1_2(1, 2);
    router_interface router_if_2_1(2, 1);
    router_interface router_if_2_2(2, 2);
    router_interface router_if_3_1(3, 1);
    router_interface router_if_3_2(3, 2);

    EXPECT_EQ(1, router_if_1_1.get_interface_id()); 
    EXPECT_EQ(2, router_if_1_2.get_interface_id());
    EXPECT_EQ(1, router_if_2_1.get_interface_id()); 
    EXPECT_EQ(2, router_if_2_2.get_interface_id());
    EXPECT_EQ(1, router_if_3_1.get_interface_id()); 
    EXPECT_EQ(2, router_if_3_2.get_interface_id());

    std::string mac_address[] = {"00:00:00:00:00:01", "00:00:00:00:00:02", "00:00:00:00:00:03",
                                 "00:00:00:00:00:04", "00:00:00:00:00:05", "00:00:00:00:00:06"};

    router_if_1_1.set_interface_address(mac_address[0]);
    router_if_1_2.set_interface_address(mac_address[1]);
    router_if_2_1.set_interface_address(mac_address[2]);
    router_if_2_2.set_interface_address(mac_address[3]);
    router_if_3_1.set_interface_address(mac_address[4]);
    router_if_3_2.set_interface_address(mac_address[5]);
   
    EXPECT_EQ(mac_address[0], router_if_1_1.get_interface_address()); 
    EXPECT_EQ(mac_address[1], router_if_1_2.get_interface_address()); 
    EXPECT_EQ(mac_address[2], router_if_2_1.get_interface_address()); 
    EXPECT_EQ(mac_address[3], router_if_2_2.get_interface_address()); 
    EXPECT_EQ(mac_address[4], router_if_3_1.get_interface_address()); 
    EXPECT_EQ(mac_address[5], router_if_3_2.get_interface_address()); 

    router_1.add_interface(&router_if_1_1); 
    router_1.add_interface(&router_if_1_2);
    router_1.add_interface(&router_if_2_1); 
    router_1.add_interface(&router_if_2_2);
    router_1.add_interface(&router_if_3_1); 
    router_1.add_interface(&router_if_3_2);
     
    router_link router_link_1(1);
    router_link router_link_2;
    router_link router_link_3;

    EXPECT_EQ(1, router_link_1.get_link_cost());
    EXPECT_EQ(1, router_link_2.get_link_cost());
    EXPECT_EQ(1, router_link_3.get_link_cost());
    
    EXPECT_EQ(0, router_link_1.create_link(&router_1, &router_if_1_1, &router_2, &router_if_2_1));    
    EXPECT_EQ(1, router_link_1.create_link(&router_1, &router_if_1_2, &router_1, &router_if_1_2));    
    EXPECT_EQ(1, router_link_1.create_link(&router_1, &router_if_1_1, &router_2, &router_if_2_1));   
    EXPECT_EQ(0, router_link_2.create_link(&router_2, &router_if_2_2, &router_3, &router_if_3_1));    
    EXPECT_EQ(0, router_link_3.create_link(&router_3, &router_if_3_2, &router_1, &router_if_1_2));   

    router_network network;

    network.add_router(&router_1);
    network.add_router(&router_2);
    network.add_router(&router_3);
     
    EXPECT_EQ(3, network.number_of_routers()); 
    
    network.add_link(&router_link_1);
    network.add_link(&router_link_2);
    network.add_link(&router_link_3);
     
    EXPECT_EQ(3, network.number_of_links()); 
}





