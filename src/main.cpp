#include <iostream>

#include <string>

// Dependency for xml parsing
#include "xml/tinyxml2.h"

#include "xml/ns_xml_parser.h"

#include "network/ns_network.h"

#include "sim/ns_network_tester.h"

#include "util/ns_sim_utils.h"

#include "sim/ns_delay_calculator.h"

#include "ns_namespace.h"

pthread_mutex_t thread_mutex;

src_dst *delay_result = NULL;

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
        XMLparser x(argv[1]);
   
        router_network *rn;

        // Create a network class object. It is needed to created routing table and arp table.
        rn = new router_network;
 
        // Load xml using the library.
        x.load();

        // Process the xml and create the network.
        x.process(rn);

        // Calculate the shortest path and configure the routing table and ARP table.        
        rn->calculate_shortest_path(UNDIRECTED_GRAPH, LINK_COST);

        // Create test class
        network_test *test = new network_test(rn);   

        // Create mutex
        if (OK != create_mutex(&thread_mutex))
        {
            std::cerr << "Mutex creation failed" << std::endl; 
            return NOT_OK;        
        }         

        // Start the threads.  
        //test->create_features();
  
        return OK;
    }
}
