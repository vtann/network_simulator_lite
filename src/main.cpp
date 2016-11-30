#include <iostream>
#include <string>
// Dependency for xml parsing
#include "xml/tinyxml2.h"
#include "xml/ns_xml_parser.h"

#include "network/ns_network.h"

#include "ns_namespace.h"


int main(int argc, char* argv[]) {
    // Check the number of parameters
    if (argc < 2) {
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << " <FILEPATH/XMLFILENAME.xml>" << std::endl;
        return 1;
    }
    else{
        XMLparser x(argv[1]);
        std::cout<<"XMLfilepath: "<<x.get_XMLfilepath()<<std::endl;
        router_network rn;
        x.load();
        x.process(&rn);
        return 0;
    }
}
