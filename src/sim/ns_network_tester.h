#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <thread>

#include "ns_delay_calculator.h"

#include "../network/ns_network.h"

#include "../util/ns_sim_utils.h"

#include "../feature/ns_packet_sender.h"

#include "../feature/ns_packet_receiver.h"

#ifndef __NS_NETWORK_TESTER_H__
#define __NS_NETWORK_TESTER_H__

class network_test
{
    public:
    network_test(std::shared_ptr<router_network> r);    

    ~network_test();    

    void create_features();
    
    std::thread create_sender_thread(void* router_index);
    
    std::thread create_receiver_thread(void* router_index);
    
    void* create_receiver_features(void* router_index);
    
    void* create_sender_features(void* router_index);
    
    private:
    std::shared_ptr<router_network> r;    
};

#endif // __NS_NETWORK_TESTER_H__
