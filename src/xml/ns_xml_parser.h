#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <mutex>

#include "tinyxml2.h"

#include "../ns_namespace.h"

#include "../network/ns_network.h"

using namespace tinyxml2;
using namespace ns_ns;

#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

class XMLparser{
public:
    XMLparser(const char* filepath);
    
    ~XMLparser();
    
    int load();

    int process(std::shared_ptr<router_network> rn);
    
    std::vector<std::string> get_nodeAndinterfaceID(std::string param);
    
    std::string get_XMLfilepath() const {return this->filepath;}
    
private:
    tinyxml2::XMLDocument xmlDoc;
    tinyxml2::XMLError eResult;
    const char* filepath;
    
};

