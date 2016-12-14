#include <list>
#include <sstream>
#include <stdint.h>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <memory>

#include "../node/ns_node_router.h"

#include "../network/ns_network.h"

#include "../network/ns_routing_table.h"

#include "../network/ns_arp_table.h"

#include "../packet/ns_packet_ethr.h"

#include "../util/ns_sim_utils.h"

#include "../ns_namespace.h"

#ifndef __NS_PACKET_SENDER_H__
#define __NS_PACKET_SENDER_H__

void packet_sender(std::shared_ptr<router_network> rn, std::shared_ptr<router> r);

#endif //__NS_PACKET_SENDER_H__
