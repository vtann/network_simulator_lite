#include <iostream>
#include <sys/time.h>
#include <stdlib.h>
#include <vector>

#include "../util/ns_sim_utils.h"

#ifndef __NS_DELAY_CALCULATOR_H__
#define __NS_DELAY_CALCULATOR_H__

typedef struct delay
{
    int src_node_id;
    int dst_node_id;
    int src_if_id;
    int dst_if_id;
    int delay;
    struct delay *next;
}delay;

typedef struct src_dst
{
    std::string src_ip;
    std::string dst_ip;
    delay *delay_inst;
    struct src_dst *next; 
}src_dst;

unsigned long calculate_delay(struct timeval *start_time, struct timeval *end_time);

src_dst* add_delay(std::string& src_ip, std::string& dst_ip, int src_r, int dst_r, int src_if, int dst_if, unsigned long delay);

delay* add_int_delay(delay *d, int src_r, int dst_r, int src_if, int dst_if, unsigned long int_delay);

void dump_delay_measurement_results();

void accumulate_delay(std::string src_ip, std::string dst_ip, double delay);

#endif // __NS_DELAY_CALCULATOR_H__
