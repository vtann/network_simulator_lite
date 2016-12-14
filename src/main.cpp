#include <iostream>

#include <string>

// Dependency for xml parsing
#include "xml/tinyxml2.h"

#include "xml/ns_xml_parser.h"

#include "network/ns_network.h"

#include "sim/ns_network_tester.h"

#include "util/ns_sim_utils.h"

#include "sim/ns_delay_calculator.h"

#include "gui/ns_gui.h"

#include "ns_namespace.h"

pthread_mutex_t thread_mutex;
pthread_mutex_t result_mutex;

int main(int argc, char* argv[]) 
{
    // Check the number of parameters.
    if (argc < 2) 
    {
        // Tell the user how to run the program.
        std::cerr << "Usage: " << argv[0] << " <FILEPATH/XMLFILENAME.xml>" << std::endl;
        return NOT_OK;
    }
    else
    {
        // Create XML parser class with input XML file argument. 
        XMLparser xml(argv[1]);
   
        // Create a network class object. It is needed to created routing table and arp table.
        std::shared_ptr<router_network> rn(new router_network);
 
        // Load xml using the library.
        xml.load();

        // Process the xml and create the network.
        xml.process(rn);

        // Calculate the shortest path and configure the routing table and ARP table.        
        rn->calculate_shortest_path(UNDIRECTED_GRAPH, LINK_COST);

        // Log routing table of all nodes
        rn->log_dump_of_all_routing_tables();          

        // Log arp table of all nodes
        rn->log_dump_of_all_arp_tables();          

        // Create test class
        network_test *test = new network_test(rn);   

        // Create interface buffer mutex
        if (OK != create_mutex(&thread_mutex))
        {
            std::cerr << "Mutex creation failed" << std::endl; 
            return NOT_OK;        
        }         

        // Create result mutex
        if (OK != create_mutex(&result_mutex))
        {
            std::cerr << "Mutex creation failed" << std::endl; 
            return NOT_OK;        
        }         

        // Start the threads.  
        test->create_features();

        std::cout << "Delay measurement results:" << std::endl;  
        
        dump_delay_test_results();
       
        log_dump_delay_test_results();
       
        ns_gui gui;
        gui.generate_layout(rn);
        gui.create_gui();

        return OK;
    }
}
