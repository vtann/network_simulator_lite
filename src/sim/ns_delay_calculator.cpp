#include "ns_delay_calculator.h"

src_dst *delay_result;

extern pthread_mutex_t result_mutex;

std::vector<std::pair<std::pair<std::string, std::string>, double> > delay_res;

unsigned long calculate_delay(struct timeval *start_time, struct timeval *end_time)
{
    unsigned long secs;
    unsigned long usecs;
    unsigned long f_secs;

    secs = (end_time->tv_sec - start_time->tv_sec); 
    usecs = (end_time->tv_usec - start_time->tv_usec);
    f_secs = ((secs * 1000 * 1000) + usecs); 

    return (f_secs);
}

src_dst* add_delay(std::string& src_ip, std::string& dst_ip, int src_r, int dst_r, int src_if, int dst_if, unsigned long delay)
{
    if (NULL == delay_result)
    {
        delay_result = new src_dst();
        delay_result->src_ip = src_ip; 
        delay_result->dst_ip = dst_ip;
        delay_result->next = NULL;
        delay_result->delay_inst = NULL;
        delay_result->delay_inst = add_int_delay(delay_result->delay_inst, src_r, dst_r, src_if, dst_if, delay);    
        return delay_result; 
    }
    else
    {
        src_dst *temp = delay_result;
        while (NULL != temp)
        {
            if (0 == src_ip.compare(temp->src_ip)) 
            {
                if (0 == dst_ip.compare(temp->dst_ip)) 
                {
                    delay_result->delay_inst = add_int_delay(temp->delay_inst, src_r, dst_r, src_if, dst_if, delay);
                    return delay_result; 
                }
            }
            temp = temp->next;    
        } 
        temp = new src_dst();
        temp->src_ip = src_ip; 
        temp->dst_ip = dst_ip;
        temp->next = NULL;
        temp->delay_inst = NULL;
        delay_result->delay_inst = add_int_delay(temp->delay_inst, src_r, dst_r, src_if, dst_if, delay);     
        return delay_result; 
    } 
}

delay* add_int_delay(delay *d, int src_r, int dst_r, int src_if, int dst_if, unsigned long int_delay)
{
    delay *new_node = (delay*)malloc(sizeof(delay)); 
        
    new_node->src_node_id = src_r;
    new_node->dst_node_id = dst_r;
    new_node->src_if_id = src_if;
    new_node->dst_if_id = dst_if;
    new_node->delay = int_delay; 
    new_node->next = NULL;
    static int index = 0;
    if (NULL == d)
    {
        d = new_node;
        index++;
    }
    else
    {
        delay *temp = d;
        while (NULL != temp->next)
        {
           temp = temp->next;
           index++; 
        }
        temp->next = new_node;
    }
    return d; 
}

void dump_delay_measurement_results()
{
    for (unsigned int index = 0; index < delay_res.size(); index++)
    {
        std::pair<std::string, std::string> src_dst = delay_res[index].first;
        std::cout << "Source IP address: " << src_dst.first
                  << " Dest IP address: " << src_dst.second
                  << " Delay: " << delay_res[index].second
                  << std::endl;  
    }
}

void accumulate_delay(std::string src_ip, std::string dst_ip, double delay)
{
    double int_delay = 0;
    std::vector<std::pair<std::pair<std::string, std::string>, double> >::iterator index;
   
    lock_mutex(&result_mutex);  
    for (index = delay_res.begin(); index != delay_res.end(); index++)
    {
        std::pair<std::string, std::string> src_dst = (*index).first;
        if (0 == src_ip.compare(src_dst.first))
        {
            if (0 == dst_ip.compare(src_dst.second))
            {
                int_delay = (*index).second;
                delay_res.erase(index);
                break;
            }
        }
    }
    int_delay = delay + int_delay; 
    std::pair<std::string, std::string> src_dst_pair;
    src_dst_pair.first = src_ip;
    src_dst_pair.second = dst_ip;
    std::pair<std::pair<std::string, std::string>, double> delay_pair;
    delay_pair.first = src_dst_pair;
    delay_pair.second = int_delay;
    delay_res.push_back(delay_pair);  
    unlock_mutex(&result_mutex);  
}

