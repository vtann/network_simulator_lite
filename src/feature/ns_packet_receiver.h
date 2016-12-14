#include <list>
#include <sstream>
#include <stdint.h>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>

#include "../ns_namespace.h"

#include "../sim/ns_delay_calculator.h"

#include "../packet/ns_packet_ethr.h"

#include "../node/ns_node_router.h"

#include "../interface/ns_node_router_if.h"

#include "../network/ns_routing_table.h"

#include "../network/ns_timer.h"

#include "../network/ns_network.h"

#include "../util/ns_sim_utils.h"

#ifndef __NS_PACKET_RECEIVER_H__
#define __NS_PACKET_RECEIVER_H__

class packet_receiver : timer
{
    public:
    void packet_poller(std::shared_ptr<router_network> r_n, std::shared_ptr<router> r);
    
    void received_packet(std::shared_ptr<router_network> r_n, std::shared_ptr<router> r, int rec_if_id, packet_buf *pkt); 
};

#endif //__NS_PACKET_RECEIVER_H__
