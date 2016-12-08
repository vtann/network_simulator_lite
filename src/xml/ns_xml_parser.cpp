#include <iostream>
#include <string>
#include "ns_xml_parser.h"

XMLparser::XMLparser(const char* filepath) {
    this->filepath=filepath;
}
XMLparser::~XMLparser() { }

int XMLparser::load() {
    eResult = xmlDoc.LoadFile(this->filepath);
    XMLCheckResult(eResult);
    
    return OK;
}

int XMLparser::process(router_network* rn) {
    
    // Node
    XMLHandle docHandle(xmlDoc);
    XMLElement* nodeElement = docHandle.FirstChild().FirstChildElement("node").ToElement();
    
    int nodeID, numbInterfaces; 
    double xAxis, yAxis;
    while (nodeElement) {
        
        eResult = nodeElement->QueryIntAttribute("id", &nodeID);
        XMLCheckResult(eResult);

        eResult = nodeElement->QueryIntAttribute("interfaces", &numbInterfaces);
        XMLCheckResult(eResult);

        eResult = nodeElement->QueryDoubleAttribute("x", &xAxis);
        XMLCheckResult(eResult);

        eResult = nodeElement->QueryDoubleAttribute("y", &yAxis);
        XMLCheckResult(eResult);
    
        router* newRouter = new router(nodeID, numbInterfaces, xAxis, yAxis);
        rn->add_router(newRouter);
        
        // Interface
        XMLHandle ieHandle(nodeElement);
        XMLElement* interfaceElement = ieHandle.FirstChildElement("interface").ToElement();
    
        int interfaceID, mask, interfaceQueue;
        double interfaceSpeed;
        std::string mac, ip;
        const char* szAttributeText = 0;

        while (interfaceElement != 0){
            eResult = interfaceElement->QueryIntAttribute("id", &interfaceID);
            XMLCheckResult(eResult);

            szAttributeText = interfaceElement->Attribute("mac");
            if (szAttributeText == 0) return XML_ERROR_PARSING_ATTRIBUTE;
            mac = szAttributeText;

            szAttributeText = interfaceElement->Attribute("ip");
            if (szAttributeText == 0) return XML_ERROR_PARSING_ATTRIBUTE;
            ip = szAttributeText;

            eResult = interfaceElement->QueryIntAttribute("mask", &mask);
            XMLCheckResult(eResult);

            eResult = interfaceElement->QueryIntAttribute("queue", &interfaceQueue);
            XMLCheckResult(eResult);

            eResult = interfaceElement->QueryDoubleAttribute("speed", &interfaceSpeed);
            XMLCheckResult(eResult);

            router_interface* newInterface= new router_interface(nodeID,interfaceID,mac,ip,mask,interfaceQueue,interfaceSpeed);
            newRouter->add_interface(newInterface);

            interfaceElement = interfaceElement->NextSiblingElement("interface");
        }
        nodeElement = nodeElement->NextSiblingElement("node");
    }
    
    // Link
    XMLElement* linkElement = docHandle.FirstChild().FirstChildElement("link").ToElement();
    int linkID,sourceNodeID,sourceInterfaceID,destNodeID,destInterfaceID;
    std::string source, destination;
    double linkCost,linkDelay;
    std::string source_nodeID, source_interfaceID, dest_nodeID, dest_interfaceID;
    std::vector<std::string> source_params,dest_params;
    const char* szAttributeText = 0;

    while (linkElement) {
        eResult = linkElement->QueryIntAttribute("id", &linkID);
        XMLCheckResult(eResult);
        
        szAttributeText = linkElement->Attribute("source");
        if (szAttributeText == 0) return XML_ERROR_PARSING_ATTRIBUTE;
        source = szAttributeText;
        source_params=get_nodeAndinterfaceID(source);
        sourceNodeID=atoi((source_params.at(0)).c_str());
        sourceInterfaceID=atoi((source_params.at(1)).c_str());
        router* sourceNode(rn->get_router(sourceNodeID));
        router_interface* sourceInterface(sourceNode->get_interface(sourceInterfaceID));

        szAttributeText = linkElement->Attribute("destination");
        if (szAttributeText == 0) return XML_ERROR_PARSING_ATTRIBUTE;
        destination = szAttributeText;
        dest_params=get_nodeAndinterfaceID(destination);
        destNodeID=atoi((dest_params.at(0)).c_str());
        destInterfaceID=atoi((dest_params.at(1)).c_str());
        router* destNode(rn->get_router(destNodeID));
        router_interface* destInterface(destNode->get_interface(destInterfaceID));

        eResult = linkElement->QueryDoubleAttribute("delay", &linkDelay);
        XMLCheckResult(eResult);

        eResult = linkElement->QueryDoubleAttribute("cost", &linkCost);
        XMLCheckResult(eResult);

        router_link* newLink = new router_link(linkID);
        newLink->create_link(sourceNode,sourceInterface,destNode,destInterface,linkDelay,linkCost);
        rn->add_link(newLink);
        
        linkElement = linkElement->NextSiblingElement("link");
    }
    
    return OK;
}

std::vector<std::string> XMLparser::get_nodeAndinterfaceID(std::string param){
    size_t pos = 0;
    std::string nodeID;
    std::string interfaceID;
    std::vector<std::string> sub_strings;
    std::string delimiter = ".";

    pos = param.find(delimiter);
    nodeID = param.substr(0, pos);
    sub_strings.push_back(nodeID);
    param.erase(0, pos + delimiter.length());
    interfaceID=param;
    sub_strings.push_back(interfaceID);
    return sub_strings;
}
