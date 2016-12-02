#include <limits.h>
#include "../../../interface/ns_node_router_if.h"
#include "gtest/gtest.h"

TEST(test_router_interface, router_interface_creation)
{
    //router_interface(int nodeID,int interfaceID,std::string mac,std::string ip, int mask, int interfaceQueue, double interfaceSpeed);
    router_interface router_if_1(1, 1,"00:00:00:00:00:01","192.169.0.0",24,10,100.1);
    router_interface router_if_2(1, 2,"00:00:00:00:00:02","192.169.1.0",24,10,100.1);

    EXPECT_EQ(1, router_if_1.get_interface_id()); 
    EXPECT_EQ(2, router_if_2.get_interface_id()); 
}





