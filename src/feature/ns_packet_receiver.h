#include <list>
#include <sstream>
#include <stdint.h>
#include <algorithm>
#include <stdexcept>
#include <string>

#include "../ns_namespace.h"

#include "../packet/ns_packet_ethr.h"

#include "../node/ns_node_router.h"

#ifndef __NS_PACKET_RECEIVER_H__
#define __NS_PACKET_RECEIVER_H__

class packet_receiver
{
    public:
    
    void receive_packet(unsigned char *pkt); 
    
    private:
    router* rec_router;
    int rec_interface_id;
};

#endif //__NS_PACKET_RECEIVER_H__
