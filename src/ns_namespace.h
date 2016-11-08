#include <iostream>
#include <vector>

//class router;
class router_interface;
class router_link;
class ethr_pkt;

namespace ns_ns
{
   const int ip_header_size = 20;  
   const int raw_eth_header_size = 14;  
   const int l2_ethertype = 0x0800;  
   typedef std::vector<router_interface*> interfaces;
   typedef std::vector<router_link*> links;
   typedef std::vector<ethr_pkt*> packets; 
}
