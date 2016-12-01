#include <iostream>

#include <string>

// Dependency for xml parsing
#include "xml/tinyxml2.h"

#include "xml/ns_xml_parser.h"

#include "network/ns_network.h"

#include "ns_namespace.h"

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
   
        // Create a network class object. It is needed to created routing table and arp table.
        router_network rn;
 
        // Load xml using the library.
        x.load();

        // Process the xml and create the network.
        x.process(&rn);
       
        return OK;
    }
}
