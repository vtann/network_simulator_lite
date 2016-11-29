#include <iostream>

#ifndef __NS_PACKET_H__
#define __NS_PACKET_H__

class packet
{
    public:
    int get_packet_size()
    {
        return packet_size;
    }  
 
    private:
    int packet_size; 
};

#endif //__NS_PACKET_H__
