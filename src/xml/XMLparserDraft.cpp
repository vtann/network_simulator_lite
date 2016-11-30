#include "XMLparser.h"
#include <iostream>
#include <string>

int main(){
    XMLDocument xmlDoc;
    XMLError eResult = xmlDoc.LoadFile("/home/navii/Desktop/C++/nwsimulator1/resources/example.xml");
    XMLCheckResult(eResult);
    
    std::cout<< "XML document loaded!!! "<<std::endl;
    
    //node
    XMLHandle docHandle(xmlDoc);
    XMLElement* nodeElement = docHandle.FirstChild().FirstChildElement("node").ToElement();
    
    int nodeID, numbInterfaces, xAxis, yAxis;

    eResult = nodeElement->QueryIntAttribute("id", &nodeID);
    XMLCheckResult(eResult);

    eResult = nodeElement->QueryIntAttribute("interfaces", &numbInterfaces);
    XMLCheckResult(eResult);
    
    eResult = nodeElement->QueryIntAttribute("x", &xAxis);
    XMLCheckResult(eResult);
    
    eResult = nodeElement->QueryIntAttribute("y", &yAxis);
    XMLCheckResult(eResult);
    
    std::cout<<"nodeID:"<<nodeID<<" "<<"numbInterfaces:"<<numbInterfaces<<" "<<"XAxis:"<<xAxis<<" "<<"yAxis:"<<yAxis<<std::endl;
    
    //interface
    XMLElement* interfaceElement = docHandle.FirstChild().FirstChildElement("node").FirstChildElement("interface").ToElement();
    
    int interfaceID,mask,interfaceQueue,interfaceSpeed;
    std::string mac,ip;
    const char * szAttributeText = 0;
    
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

        eResult = interfaceElement->QueryIntAttribute("speed", &interfaceSpeed);
        XMLCheckResult(eResult);

        std::cout<<"interfaceID:"<<interfaceID<<" "<<"mac:"<<mac<<" "<<"ip:"<<ip<<" "<<"mask:"<<mask<<" "<<"queue:"<<interfaceQueue<<" "<<"speed:"<<interfaceSpeed<<std::endl;

        interfaceElement = interfaceElement->NextSiblingElement("interface");
    }
    
    XMLHandle neHandle(docHandle.FirstChild().FirstChildElement("node"));
    // Load consequtive nodes
    nodeElement = neHandle.NextSiblingElement("node").ToElement();
    while (nodeElement) {
        
        eResult = nodeElement->QueryIntAttribute("id", &nodeID);
        XMLCheckResult(eResult);

        eResult = nodeElement->QueryIntAttribute("interfaces", &numbInterfaces);
        XMLCheckResult(eResult);

        eResult = nodeElement->QueryIntAttribute("x", &xAxis);
        XMLCheckResult(eResult);

        eResult = nodeElement->QueryIntAttribute("y", &yAxis);
        XMLCheckResult(eResult);
    
        std::cout<<"nodeID:"<<nodeID<<" "<<"numbInterfaces:"<<numbInterfaces<<" "<<"XAxis:"<<xAxis<<" "<<"yAxis"<<yAxis<<std::endl;
        
	//interface
        XMLHandle ieHandle(nodeElement);
        XMLElement* interfaceElement = ieHandle.FirstChildElement("interface").ToElement();

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

            eResult = interfaceElement->QueryIntAttribute("speed", &interfaceSpeed);
            XMLCheckResult(eResult);

            std::cout<<"interfaceID:"<<interfaceID<<" "<<"mac:"<<mac<<" "<<"ip:"<<ip<<" "<<"mask:"<<mask<<" "<<"queue:"<<interfaceQueue<<" "<<"speed:"<<interfaceSpeed<<std::endl;

            interfaceElement = interfaceElement->NextSiblingElement("interface");
        }
        
        XMLHandle neHandle(nodeElement);
        nodeElement = neHandle.NextSiblingElement("node").ToElement();
    }
    
    //link
    XMLElement* linkElement = docHandle.FirstChild().FirstChildElement("link").ToElement();
    double source, destination, linkSpeed, linkWeight;

    while (linkElement) {
        eResult = linkElement->QueryDoubleAttribute("source", &source);
        XMLCheckResult(eResult);

        eResult = linkElement->QueryDoubleAttribute("destination", &destination);
        XMLCheckResult(eResult);

        eResult = linkElement->QueryDoubleAttribute("speed", &linkSpeed);
        XMLCheckResult(eResult);

        eResult = linkElement->QueryDoubleAttribute("weight", &linkWeight);
        XMLCheckResult(eResult);

        std::cout<<"source:"<<source<<" "<<"destination:"<<destination<<" "<<"speed:"<<linkSpeed<<" "<<"weight:"<<linkWeight<<std::endl;
        
        linkElement = linkElement->NextSiblingElement("link");
    }
}
