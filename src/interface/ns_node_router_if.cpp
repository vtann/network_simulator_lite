#include "ns_node_router_if.h"

using namespace ns_ns;

router_interface::router_interface(int nodeID, int interfaceID, std::string mac, std::string ip, int mask, int interfaceQueue, double interfaceSpeed) : node_interface(interfaceID)
{
    router_id = nodeID;
    set_interface_address(mac);
    set_network_address(ip);
    set_mask(mask);
    set_queue_size(interfaceQueue);
    set_interface_speed(interfaceSpeed);
    is_connected_flag = false;
    start_recv_buf_idx = 0;
    end_recv_buf_idx = 0;
    start_send_buf_idx = 0;
    end_send_buf_idx = 0;
    pkts_in_send_buf = 0;
    pkts_in_recv_buf = 0;

    int index;

    if_recv_buf = new packet_buf *[interfaceQueue];

    for (index = 0; index < interfaceQueue; index++)
    {
        if_recv_buf[index] = new packet_buf;  
        if_recv_buf[index]->pkt_buf = new unsigned char [DEFAULT_PACKET_SIZE_WITH_FCS]();     
        if_recv_buf[index]->timestamp = new struct timeval();     
    }
    
    if_send_buf = new packet_buf *[interfaceQueue];

    for (index = 0; index < interfaceQueue; index++)
    {
        if_send_buf[index] = new packet_buf;  
        if_send_buf[index]->pkt_buf = new unsigned char [DEFAULT_PACKET_SIZE_WITH_FCS]();     
        if_send_buf[index]->timestamp = new struct timeval();     
    }
}

router_interface::~router_interface()
{
}

int router_interface::get_router_id() const
{
    return router_id;
}

void router_interface::set_router_id(int id)
{
    router_id = id;
}
  
std::string router_interface::get_interface_address() const
{
    return mac_address;
}

void router_interface::set_interface_address(std::string& mac_addr)
{
    mac_address = mac_addr;
}

std::string router_interface::get_network_address() const
{
    return ip_address;
}

void router_interface::set_network_address(std::string& ip_addr)
{
    ip_address = ip_addr;
}

int router_interface::get_queue_size() const
{
    return queue_size;
}

void router_interface::set_queue_size(int q_size)
{
    queue_size = q_size;
}

bool router_interface::get_is_connected_flag() const
{
    return is_connected_flag;
}

void router_interface::set_is_connected_flag(bool flag)
{
    is_connected_flag = flag;
}

void router_interface::set_mask(int ip_mask) 
{
    mask = ip_mask;
}

int router_interface::get_interface_speed() const
{
    return interface_speed;
}

int router_interface::get_mask() const
{
    return mask;
}

void router_interface::set_interface_speed(int if_speed)
{
    interface_speed = if_speed;
}

router_interface::router_interface(const router_interface &r_i):node_interface(r_i.get_interface_id())
{
    this->router_id=r_i.router_id;
    this->mac_address=r_i.mac_address;
    this->queue_size=r_i.queue_size;
    this->interface_speed=r_i.interface_speed;
    this->ip_address=r_i.ip_address;
    this->mask=r_i.mask;
    this->ethr_packets=r_i.ethr_packets;
    this->is_connected_flag=r_i.is_connected_flag; 
    this->start_recv_buf_idx = 0;
    this->end_recv_buf_idx = 0;
    this->start_send_buf_idx = 0;
    this->end_send_buf_idx = 0;
    this->pkts_in_send_buf = 0;
    this->pkts_in_recv_buf = 0;
}

void router_interface::copy_packet_to_send_ring_buffer(unsigned char *pkt)
{
    // Check for buffer overflow
    if (queue_size >= (pkts_in_send_buf + 1))
    {
        pkts_in_send_buf++;
        if (queue_size <= (end_send_buf_idx + 1))
        {
            end_send_buf_idx = 0;
        }
        else 
        { 
            end_send_buf_idx += 1;  
        }
        gettimeofday(if_send_buf[end_send_buf_idx]->timestamp, NULL);
        std::memcpy(if_send_buf[end_send_buf_idx]->pkt_buf, pkt, DEFAULT_PACKET_SIZE_WITH_FCS);   
    }  
    else 
    {
        // Drop the packet and update link parameters
        std::cout << "Drop the packet" << std::endl;
    }  
}

void router_interface::copy_packet_to_recv_ring_buffer(unsigned char *pkt)
{
    // Check for buffer overflow
    if (queue_size >= (pkts_in_recv_buf + 1))
    {
        pkts_in_recv_buf++;
        if (queue_size <= (end_recv_buf_idx + 1))
        {
            end_recv_buf_idx = 0;
        }
        else 
        { 
            end_recv_buf_idx += 1;  
        }
        gettimeofday(if_recv_buf[end_recv_buf_idx]->timestamp, NULL);
        std::memcpy(if_recv_buf[end_recv_buf_idx]->pkt_buf, pkt, DEFAULT_PACKET_SIZE_WITH_FCS);   
    }  
    else 
    {
        // Drop the packet and update link parameters
        std::cout << "Drop the packet" << std::endl;
    }  
}

void router_interface::remove_packet_from_send_ring_buffer(packet_buf *pkt)
{
    // Return if there are no packets to read 
    if (0 == pkts_in_send_buf)
    {
        return;
    } 
    else
    {
        pkts_in_recv_buf--;
        std::memcpy(pkt->pkt_buf, if_send_buf[start_send_buf_idx]->pkt_buf, DEFAULT_PACKET_SIZE_WITH_FCS);
        std::memcpy(pkt->timestamp, if_send_buf[start_send_buf_idx]->timestamp, sizeof(struct timeval));
        if (queue_size == (start_send_buf_idx + 1))
        {
            start_send_buf_idx = 0;
        }
        else
        {
            start_send_buf_idx += 1;
        } 
    } 
}

void router_interface::remove_packet_from_recv_ring_buffer(packet_buf *pkt)
{
    // Return if there are no packets to read 
    if (0 == pkts_in_recv_buf)
    {
        return;
    } 
    else
    {
        pkts_in_recv_buf--;
        std::memcpy(pkt->pkt_buf, if_recv_buf[start_recv_buf_idx]->pkt_buf, DEFAULT_PACKET_SIZE_WITH_FCS);
        std::memcpy(pkt->timestamp, if_recv_buf[start_recv_buf_idx]->timestamp, sizeof(struct timeval));
        if (queue_size == (start_recv_buf_idx + 1))
        {
            start_recv_buf_idx = 0;
        }
        else
        {
            start_recv_buf_idx += 1;
        } 
    } 
}

int router_interface::get_num_pkts_in_recv_buffer()
{
    return pkts_in_recv_buf;
}

int router_interface::get_num_pkts_in_send_buffer()
{
    return pkts_in_send_buf;
}

