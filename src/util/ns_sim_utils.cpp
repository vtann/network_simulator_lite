#include "ns_sim_utils.h"

using namespace ns_ns;

int create_mutex(pthread_mutex_t* m_name)
{
    if (0 != (pthread_mutex_init(m_name, NULL)))
    {
        return NOT_OK;
    }
    return OK;
}

void lock_mutex(pthread_mutex_t* m_name)
{
    pthread_mutex_lock(m_name);
}

void unlock_mutex(pthread_mutex_t* m_name)
{
    pthread_mutex_unlock(m_name);
}
