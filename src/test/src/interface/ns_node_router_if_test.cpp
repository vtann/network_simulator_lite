#include <limits.h>
#include "../../../interface/ns_node_router_if.h"
#include "gtest/gtest.h"

TEST(test_router_interface, router_interface_creation)
{
    router_interface router_if_1(1);
    router_interface router_if_2(2);

    EXPECT_EQ(1, router_if_1.get_interface_id()); 
    EXPECT_EQ(2, router_if_2.get_interface_id()); 
}





