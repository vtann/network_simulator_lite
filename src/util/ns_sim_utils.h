#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>

#include "../ns_namespace.h"

#ifndef __NS_SIM_UTILS_H__
#define __NS_SIM_UTILS_H__

#define LOG_MESSAGE(text)                                                    \
{                                                                            \
    if (true == g_enable_logs)                                               \
    {                                                                        \
        std::ofstream log_file(                                              \
       "logs/ns_packet_logs.txt", std::ios_base::out | std::ios_base::app ); \
        log_file << text << std::endl;                                       \
    }                                                                        \
}

int create_mutex(pthread_mutex_t *m_name); 

void lock_mutex(pthread_mutex_t* m_name);

void unlock_mutex(pthread_mutex_t* m_name);

#endif // __NS_SIM_UTILS_H__

