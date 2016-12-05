#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#include "../ns_namespace.h"

#ifndef __NS_SIM_UTILS_H__
#define __NS_SIM_UTILS_H__

int create_mutex(pthread_mutex_t *m_name); 

void lock_mutex(pthread_mutex_t* m_name);

void unlock_mutex(pthread_mutex_t* m_name);

#endif // __NS_SIM_UTILS_H__

