#include <limits.h>

#include "gtest/gtest.h"

#include "../../../xml/ns_xml_parser.h"

#include "../../../packet/ns_packet_ethr.h"

#include "../../../network/ns_routing_table.h"

#include "../../../network/ns_network.h"

TEST(test_network_simulator, packet_test)
{
    XMLparser x("../../../../resources/example.xml");
        
    std::shared_ptr<router_network> nw (new router_network);
        
    x.load();

    x.process(nw);

    // Get number of routers
    EXPECT_EQ(3, nw->number_of_routers());      
    
    // Get number of links
    EXPECT_EQ(3, nw->number_of_links());     

    // Get first router
    std::shared_ptr<router> router_1 = nw->get_router(0);

    EXPECT_EQ(2, router_1->get_num_of_interfaces());        
 
    std::shared_ptr<router_interface> router_if_1 = router_1->get_interface(0); 
    EXPECT_EQ("00:00:00:00:00:11", router_if_1->get_interface_address());
    EXPECT_EQ("192.168.0.1", router_if_1->get_network_address());
    std::shared_ptr<router_interface> router_if_2 = router_1->get_interface(1); 
    EXPECT_EQ("00:00:00:00:00:12", router_if_2->get_interface_address());
    EXPECT_EQ("192.168.1.1", router_if_2->get_network_address());
      
    // Get second router
    std::shared_ptr<router> router_2 = nw->get_router(1);

    EXPECT_EQ(3, router_2->get_num_of_interfaces());        
  
    router_if_1 = router_2->get_interface(0); 
    EXPECT_EQ("00:00:00:00:00:21", router_if_1->get_interface_address());
    EXPECT_EQ("192.168.0.2", router_if_1->get_network_address());
    router_if_2 = router_2->get_interface(1); 
    EXPECT_EQ("00:00:00:00:00:22", router_if_2->get_interface_address());
    EXPECT_EQ("192.168.1.2", router_if_2->get_network_address());
    std::shared_ptr<router_interface> router_if_3 = router_2->get_interface(2); 
    EXPECT_EQ("00:00:00:00:00:23", router_if_3->get_interface_address());
    EXPECT_EQ("192.168.2.1", router_if_3->get_network_address());
    
    // Get third router
    std::shared_ptr<router> router_3 = nw->get_router(2);

    EXPECT_EQ(2, router_3->get_num_of_interfaces());        
  
    router_if_1 = router_3->get_interface(0); 
    EXPECT_EQ("00:00:00:00:00:31", router_if_1->get_interface_address());
    EXPECT_EQ("192.168.2.2", router_if_1->get_network_address());
    router_if_2 = router_3->get_interface(1); 
    EXPECT_EQ("00:00:00:00:00:32", router_if_2->get_interface_address());
    EXPECT_EQ("192.168.3.1", router_if_2->get_network_address());

    nw->calculate_shortest_path(UNDIRECTED_GRAPH, LINK_COST);
    EXPECT_EQ(2, router_1->get_routing_table()->get_num_of_routing_table_entries());
    EXPECT_EQ(2, router_2->get_routing_table()->get_num_of_routing_table_entries());
    EXPECT_EQ(2, router_3->get_routing_table()->get_num_of_routing_table_entries());

    router_1->get_routing_table()->dump_routing_table_entries();
    router_2->get_routing_table()->dump_routing_table_entries();
    router_3->get_routing_table()->dump_routing_table_entries();
}
