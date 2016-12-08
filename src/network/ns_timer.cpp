#include "ns_timer.h"

timer::timer()
{
    is_reset = false;
    is_running = false;
    is_stopped = false;
    memset(&start_time, 0, sizeof(struct timeval));
    memset(&end_time, 0, sizeof(struct timeval));
}

void timer::start_timer() 
{
    if (false == is_running) 
    {
        gettimeofday(&start_time, NULL);
        if (false != is_stopped)
        {
            memset(&end_time, 0, sizeof(struct timeval));
            is_stopped = false; 
        }
        is_running = true;
        is_reset = false;
    }
}

void timer::stop_timer() 
{
    if (true == is_running) 
    {
        gettimeofday(&end_time, NULL);
        is_running = false;
    }
}

void timer::reset_timer()
{
    gettimeofday(&start_time, NULL);
    memset(&end_time, 0, sizeof(struct timeval));
    is_reset = true; 
}

bool timer::is_timer_running()
{
    return is_running;  
}

bool timer::is_timer_reset()
{
    return is_reset;  
}

bool timer::is_timer_stopped()
{
    return is_stopped;  
}

unsigned long timer::get_elapsed_time_in_sec()
{
    unsigned long secs;
    unsigned long usecs;
    unsigned long msecs;

    if (true == is_stopped)
    {
        secs = (end_time.tv_sec - start_time.tv_sec); 
        usecs = (end_time.tv_usec - start_time.tv_usec);
        msecs = ((secs * 1000) + usecs/1000.0) + 0.5; 
    }
    else
    {
        struct timeval temp_end_time;
        gettimeofday(&temp_end_time, NULL);
        secs = (temp_end_time.tv_sec - start_time.tv_sec); 
        usecs = (temp_end_time.tv_usec - start_time.tv_usec);
        msecs = ((secs * 1000) + usecs/1000.0) + 0.5; 
    }
    return (msecs / 1000);
}

unsigned long timer::get_elapsed_time_in_millisec()
{
    unsigned long secs;
    unsigned long usecs;
    unsigned long msecs;

    if (true == is_stopped)
    {
        secs = (end_time.tv_sec - start_time.tv_sec); 
        usecs = (end_time.tv_usec - start_time.tv_usec);
        msecs = ((secs * 1000) + usecs/1000.0) + 0.5; 
    }
    else
    {
        struct timeval temp_end_time;
        gettimeofday(&temp_end_time, NULL);
        secs = (temp_end_time.tv_sec - start_time.tv_sec); 
        usecs = (temp_end_time.tv_usec - start_time.tv_usec);
        msecs = ((secs * 1000) + usecs/1000.0) + 0.5; 
    }
    return msecs;
}

unsigned long timer::get_elapsed_time_in_microsec()
{
    unsigned long secs;
    unsigned long usecs;
    unsigned long f_secs;

    if (true == is_stopped)
    {
        secs = (end_time.tv_sec - start_time.tv_sec); 
        usecs = (end_time.tv_usec - start_time.tv_usec);
        f_secs = ((secs * 1000 * 1000) + usecs) + 0.5; 
    }
    else
    {
        struct timeval temp_end_time;
        gettimeofday(&temp_end_time, NULL);
        secs = (temp_end_time.tv_sec - start_time.tv_sec); 
        usecs = (temp_end_time.tv_usec - start_time.tv_usec);
        f_secs = ((secs * 1000 * 1000) + usecs) + 0.5; 
    }
    return f_secs;
}
