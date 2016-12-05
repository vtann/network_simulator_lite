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
 
    private:
    router_network *r;     
};

#endif // __NS_NETWORK_TESTER_H__
