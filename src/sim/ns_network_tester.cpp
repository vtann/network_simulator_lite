#include "ns_network_tester.h"

extern pthread_mutex_t send_mutex;

static void* create_router_features(void* router_index);

network_test::network_test(router_network *r)
{
    this->r = r;
}

void network_test::create_features()
{
    std::list<pthread_t> node_threads;
    std::vector<router*> routers = r->get_all_routers();
    //int *i = (int) malloc(sizeof(int)); 
    int *i = (int*) malloc(sizeof(int));    

    // Start threads on nodes   
    for (int index = 0; index < r->number_of_routers(); index++)
    {
        pthread_t thread; 
        *i = index;
        std::cout << "Index: " << *i << std::endl;
        if (0 != pthread_create(&thread, NULL, create_router_features, i))
        {
            std::cout << "Run.........." << std::endl;   
        }
        node_threads.push_back(thread);
    }
    for (std::list<pthread_t>::iterator index2 = node_threads.begin(); index2 != node_threads.end(); index2++)
    {
        pthread_join(*index2, NULL);
    }
}

static void* create_router_features(void* router_index)
{
    lock_mutex(&send_mutex); 
    int* index = (int*) router_index;
    std::cout << "Node index" << *index << std::endl;
    unlock_mutex(&send_mutex); 
}
