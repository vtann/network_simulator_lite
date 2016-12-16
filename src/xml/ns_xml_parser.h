#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <mutex>

// dependency/library for xml parsing
#include "tinyxml2.h"

#include "../ns_namespace.h"

#include "../network/ns_network.h"

using namespace tinyxml2;
using namespace ns_ns;

/**
 * Macro for checking xml parsing error results
 */
#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

/**
 * Handles the parsing of an xml to retrieve the network topology
 */
class XMLparser{
public:
	/**
	 * Constructor takes the filepath of the xml to parse
	 */
    XMLparser(const char* filepath);

    ~XMLparser();

	/**
     * Loads the xml into memory
     */
    int load();

	/**
     * Parses the loaded xml into the network simulator
     */
    int process(std::shared_ptr<router_network> rn);

	/**
     * extracts node and interface id from link element's source and destination string attribute
     * @param String - Containg links source/destination attributes
     */
    std::vector<std::string> get_nodeAndinterfaceID(std::string param);

	/**
     * Get path of the XML file entered as command line argument
     * Returns the filepath of the loaded xml
     */
    std::string get_XMLfilepath() const {return this->filepath;}

private:
    tinyxml2::XMLDocument xmlDoc;
    tinyxml2::XMLError eResult;
    const char* filepath;

};
