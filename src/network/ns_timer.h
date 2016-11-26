#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#ifndef __NS_TIMER_H__
#define __NS_TIMER_H__

class timer 
{
    public:
    
    timer();
        
    void start_timer();
                
    void stop_timer();
               
    void reset_timer();
                
    bool is_timer_running();
        
    bool is_timer_reset();
                
    bool is_timer_stopped();
                
    unsigned long get_time();
                
    unsigned long get_elapsed_time_in_sec();
        
    unsigned long get_elapsed_time_in_millisec();
        
    private:
    
    bool is_reset;
    bool is_running;
    bool is_stopped;
    struct timeval start_time;
    struct timeval end_time;
};

#endif //__NS_TIMER_H__

