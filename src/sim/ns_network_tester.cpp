#include "ns_network_tester.h"

network_test::network_test(std::shared_ptr<router_network> r)
{
    this->r = r;
}

void network_test::create_features()
{
    std::list<std::thread> sender_threads, receiver_threads;
    std::vector<router*> routers = r->get_all_routers();

    // Start threads on nodes   
    for (int index = 0; index < r->number_of_routers(); index++)
    {
        int *i = (int*) malloc(sizeof(int));    
        *i = index;
        sender_threads.push_back(create_sender_thread(i));
        receiver_threads.push_back(create_receiver_thread(i));
    }
    for(auto& index2 : sender_threads)
    {
        index2.join();
    }

    for(auto& index2 : receiver_threads)
    {
        index2.join();
    }
}

std::thread network_test::create_sender_thread(void* router_index){
    return std::thread([=] {create_sender_features(router_index);});
}

std::thread network_test::create_receiver_thread(void* router_index){
    return std::thread([=] {create_receiver_features(router_index);});
}

void* network_test::create_sender_features(void* router_index)
{
    void *return_value = nullptr; 
    int* index = (int*) router_index;
    router* rou = r->get_router(*index);
    
    packet_sender(this->r, rou);

    return return_value; 
}

void* network_test::create_receiver_features(void* router_index)
{
    void *return_value = nullptr; 
    int* index = (int*) router_index;
    router* rou = r->get_router(*index);
    packet_receiver pkt_rec;
    
    pkt_rec.packet_poller(this->r, rou);  
    
    return return_value; 
}


