#include <limits.h>
#include "../../../network/ns_network.h"
#include "../../../network/ns_timer.h"
#include "../../../feature/ns_packet_sender.h"
#include "../../../packet/ns_packet_ethr.h"
#include "gtest/gtest.h"
#include <memory>

pthread_mutex_t thread_mutex;

using namespace ns_ns;

TEST(test_network, network_creation)
{
    // router(int nodeID, int numbInterfaces, double xAxis, double yAxis);
    std::shared_ptr<router> router_1 (new router(0, 2, 1.1, 1.1));
    std::shared_ptr<router> router_2 (new router(1, 2, 2.2, 2.2));
    std::shared_ptr<router> router_3 (new router(2, 2, 3.3, 3.3));

    EXPECT_EQ(0, router_1->get_node_id()); 
    EXPECT_EQ(1, router_2->get_node_id()); 
    EXPECT_EQ(2, router_3->get_node_id());

    // router_interface(int nodeID, int interfaceID, std::string mac, std::string ip, int mask, int interfaceQueue, double interfaceSpeed);
    std::shared_ptr<router_interface> router_if_1_1 (new router_interface(0, 0, "00:00:00:00:00:01", "192.168.0.1", 24, 10, 100.1));
    std::shared_ptr<router_interface> router_if_1_2 (new router_interface(0, 1, "00:00:00:00:00:02", "192.168.2.1", 24, 10, 100.1));
    std::shared_ptr<router_interface> router_if_1_3 (new router_interface(0, 2, "00:00:00:00:00:07", "192.168.3.1", 24, 10, 100));
    std::shared_ptr<router_interface> router_if_2_1 (new router_interface(1, 0, "00:00:00:00:00:03", "192.168.0.2", 24, 10, 100.1));
    std::shared_ptr<router_interface> router_if_2_2 (new router_interface(1, 1, "00:00:00:00:00:04", "192.168.1.1", 24, 10, 100.1));
    std::shared_ptr<router_interface> router_if_3_1 (new router_interface(2, 0, "00:00:00:00:00:05", "192.168.1.2", 24, 10, 100.1));
    std::shared_ptr<router_interface> router_if_3_2 (new router_interface(2, 1, "00:00:00:00:00:06", "192.168.2.2", 24, 10, 100.1));
    std::shared_ptr<router_interface> router_if_3_3 (new router_interface(2, 2, "00:00:00:00:00:08", "192.168.3.2", 24, 10, 100));

    EXPECT_EQ(0, router_if_1_1->get_interface_id()); 
    EXPECT_EQ(1, router_if_1_2->get_interface_id());
    EXPECT_EQ(2, router_if_1_3->get_interface_id());
    EXPECT_EQ(0, router_if_2_1->get_interface_id()); 
    EXPECT_EQ(1, router_if_2_2->get_interface_id());
    EXPECT_EQ(0, router_if_3_1->get_interface_id()); 
    EXPECT_EQ(1, router_if_3_2->get_interface_id());
    EXPECT_EQ(2, router_if_3_3->get_interface_id());

    std::string mac_address[] = {"00:00:00:00:00:01", "00:00:00:00:00:02", "00:00:00:00:00:03",
                                 "00:00:00:00:00:04", "00:00:00:00:00:05", "00:00:00:00:00:06"};

    router_if_1_1->set_interface_address(mac_address[0]);
    router_if_1_2->set_interface_address(mac_address[1]);
    router_if_2_1->set_interface_address(mac_address[2]);
    router_if_2_2->set_interface_address(mac_address[3]);
    router_if_3_1->set_interface_address(mac_address[4]);
    router_if_3_2->set_interface_address(mac_address[5]);
   
    EXPECT_EQ(mac_address[0], router_if_1_1->get_interface_address()); 
    EXPECT_EQ(mac_address[1], router_if_1_2->get_interface_address()); 
    EXPECT_EQ(mac_address[2], router_if_2_1->get_interface_address()); 
    EXPECT_EQ(mac_address[3], router_if_2_2->get_interface_address()); 
    EXPECT_EQ(mac_address[4], router_if_3_1->get_interface_address()); 
    EXPECT_EQ(mac_address[5], router_if_3_2->get_interface_address()); 

    router_1->add_interface(router_if_1_1); 
    router_1->add_interface(router_if_1_2);
    router_1->add_interface(router_if_1_3);
    router_2->add_interface(router_if_2_1); 
    router_2->add_interface(router_if_2_2);
    router_3->add_interface(router_if_3_1); 
    router_3->add_interface(router_if_3_2);
    router_3->add_interface(router_if_3_3);
   
    std::shared_ptr<router_link> router_link_1 (new router_link(0));
    std::shared_ptr<router_link> router_link_2 (new router_link(1));
    std::shared_ptr<router_link> router_link_3 (new router_link(2));
    std::shared_ptr<router_link> router_link_4 (new router_link(3));

    // create_link(router* src_router, router_interface* src_if, router* dst_router, router_interface* dst_if, double link_delay, double link_weight);
    EXPECT_EQ(0, router_link_1->create_link(router_1, router_if_1_1, router_2, router_if_2_1, 100.2, 10.2));    
    EXPECT_EQ(1, router_link_1->create_link(router_1, router_if_1_2, router_1, router_if_1_2, 100.2, 10.2));    
    EXPECT_EQ(1, router_link_1->create_link(router_1, router_if_1_1, router_2, router_if_2_1, 100.2, 10.2));   
    EXPECT_EQ(0, router_link_2->create_link(router_2, router_if_2_2, router_3, router_if_3_1, 100.2, 10.2));    
    EXPECT_EQ(0, router_link_3->create_link(router_3, router_if_3_2, router_1, router_if_1_2, 100, 10));    
    EXPECT_EQ(0, router_link_4->create_link(router_1, router_if_1_3, router_3, router_if_3_3, 1000, 100));   

    EXPECT_EQ(10.2, router_link_1->get_link_cost());
    EXPECT_EQ(10.2, router_link_2->get_link_cost());
    EXPECT_EQ(10, router_link_3->get_link_cost());
    EXPECT_EQ(100, router_link_4->get_link_cost());
    
    std::shared_ptr<router_network> network (new router_network);

    network->add_router(router_1);
    network->add_router(router_2);
    network->add_router(router_3);
   
    std::shared_ptr<router> r_temp = network->get_router(0);
    EXPECT_EQ(0, r_temp->get_node_id());
    r_temp = network->get_router(1);
    EXPECT_EQ(1, r_temp->get_node_id());
    r_temp = network->get_router(2);
    EXPECT_EQ(2, r_temp->get_node_id());
    //r_temp = network->get_router(3);
    //EXPECT_EQ(NULL, r_temp);
    
    EXPECT_EQ(3, network->number_of_routers()); 
    
    network->add_link(router_link_1);
    network->add_link(router_link_2);
    network->add_link(router_link_3);
    network->add_link(router_link_4);
     
    EXPECT_EQ(4, network->number_of_links());
    
    std::shared_ptr<router_link> temp = network->find_link(router_1->get_node_id(), router_2->get_node_id());
    EXPECT_EQ("00:00:00:00:00:01", temp->get_src_if()->get_interface_address()); 
    network->calculate_shortest_path(UNDIRECTED_GRAPH, LINK_DELAY);
    r_temp = network->get_router(0);
    EXPECT_EQ(2, r_temp->get_routing_table()->get_num_of_routing_table_entries()); 
    r_temp = network->get_router(1);
    EXPECT_EQ(2, r_temp->get_routing_table()->get_num_of_routing_table_entries()); 
    r_temp = network->get_router(2);
    EXPECT_EQ(2, r_temp->get_routing_table()->get_num_of_routing_table_entries());

    packet_send send;
    send.packet_sender(network, network->get_router(0));      
    send.packet_sender(network, network->get_router(0));      
    send.packet_sender(network, network->get_router(0));      
    send.packet_sender(network, network->get_router(0));      
    send.packet_sender(network, network->get_router(0));      
    send.packet_sender(network, network->get_router(0));      
    send.packet_sender(network, network->get_router(0));      
    send.packet_sender(network, network->get_router(0));      
    send.packet_sender(network, network->get_router(0));      
    send.packet_sender(network, network->get_router(0));      
    send.packet_sender(network, network->get_router(0));     
    EXPECT_EQ(10, network->get_router(1)->get_interface(0)->get_num_pkts_in_recv_buffer()); 
    EXPECT_EQ(0, network->get_router(1)->get_interface(1)->get_num_pkts_in_recv_buffer()); 
}
















