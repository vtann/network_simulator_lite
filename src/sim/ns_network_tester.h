#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <thread>

#include "../network/ns_network.h"

#include "../util/ns_sim_utils.h"

#ifndef __NS_NETWORK_TESTER_H__
#define __NS_NETWORK_TESTER_H__

class network_test
{
    public:
    network_test(router_network *r);    

    ~network_test();    

    void create_features();
    
    //std::thread create_thread(void* rounter_index);
    std::thread create_sender_thread(void* router_index);
    std::thread create_receiver_thread(void* router_index);
    //void* create_router_features(void* router_index);
    void* create_receiver_features(void* router_index);
    void* create_sender_features(void* router_index);
    private:
    router_network *r;     
};

#endif // __NS_NETWORK_TESTER_H__
