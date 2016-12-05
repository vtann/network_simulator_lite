#include "ns_network_tester.h"

extern pthread_mutex_t send_mutex;

network_test::network_test(router_network *r)
{
    this->r = r;
}

void network_test::create_features()
{
    std::list<std::thread> node_threads;
    std::vector<router*> routers = r->get_all_routers();
    int *i = (int*) malloc(sizeof(int));    
    // Start threads on nodes   
    for (int index = 0; index < r->number_of_routers(); index++)
    {
        *i = index;
        std::cout << "Index: " << *i << std::endl;
        node_threads.push_back(create_thread(i));
    }
    for(auto& index2 : node_threads)
    {
        index2.join();
    }
}

std::thread network_test::create_thread(void* router_index){
    return std::thread([=] {create_router_features(router_index);});
}

void* network_test::create_router_features(void* router_index)
{
    lock_mutex(&send_mutex); 
    int* index = (int*) router_index;
    std::cout << "Node index " << *index << std::endl;
    unlock_mutex(&send_mutex); 
}
