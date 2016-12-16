#include "ns_node_router_if.h"

using namespace ns_ns;

extern bool g_enable_logs;

/*! \fn router_interface(int node_id, int interface_id, std::string mac, std::string ip, int mask, int if_queue, double if_speed) : node_interface(interface_id)
 *  \brief A constructor function which creates a router object.
 *  \param interface_id, unique identifier for router interface.
 *  \param mac, MAC address of the interface.
 *  \param ip, IP address of the interface.
 *  \param mask, Mask for the IP address of the interface.
 *  \param if_queue, Number of buffers in the interface.
 *  \param if_speed, Speed of the interface.
 *  \return None.
 */
router_interface::router_interface(int node_id, int interface_id, std::string mac, std::string ip, int mask, int if_queue, double if_speed) : node_interface(interface_id)
{
    router_id = node_id;
    set_interface_address(mac);
    set_network_address(ip);
    set_mask(mask);
    set_queue_size(if_queue);
    set_interface_speed(if_speed);
    is_connected_flag = false;
    start_recv_buf_idx = 0;
    end_recv_buf_idx = 0;
    start_send_buf_idx = 0;
    end_send_buf_idx = 0;
    pkts_in_send_buf = 0;
    pkts_in_recv_buf = 0;

    int index;

    // Create mentioned number of RX buffers for the interface
    if_recv_buf = new packet_buf *[if_queue];

    for (index = 0; index < if_queue; index++)
    {
        if_recv_buf[index] = new packet_buf;  
        if_recv_buf[index]->pkt_buf = new unsigned char [DEFAULT_PACKET_SIZE_WITH_FCS]();     
        if_recv_buf[index]->timestamp = new struct timeval();     
    }
    
    // Create mentioned number of TX buffers for the interface
    if_send_buf = new packet_buf *[if_queue];

    for (index = 0; index < if_queue; index++)
    {
        if_send_buf[index] = new packet_buf;  
        if_send_buf[index]->pkt_buf = new unsigned char [DEFAULT_PACKET_SIZE_WITH_FCS]();     
        if_send_buf[index]->timestamp = new struct timeval();     
    }
}

router_interface::~router_interface()
{
}

/*! \fn get_router_id() 
 *  \brief Function to get the router id in which interface is present.
 *  \return router id.
 */
int router_interface::get_router_id() const
{
    return router_id;
}

/*! \fn set_router_id() 
 *  \brief Function to set the router id to identify in which interface is present.
 *  \param id, Router id to relate interface.
 *  \return None.
 */
void router_interface::set_router_id(int id)
{
    router_id = id;
}
  
/*! \fn get_interface_address() 
 *  \brief Function to get interface MAC address.
 *  \return MAC address string.
 */
std::string router_interface::get_interface_address() const
{
    return mac_address;
}

/*! \fn set_interface_address() 
 *  \brief Function to set interface MAC address.
 *  \param mac_addr, MAC address string.
 *  \return None.   
 */
void router_interface::set_interface_address(std::string& mac_addr)
{
    mac_address = mac_addr;
}

/*! \fn get_network_address() 
 *  \brief Function to get IP address.
 *  \return IP address string.
 */
std::string router_interface::get_network_address() const
{
    return ip_address;
}

/*! \fn set_network_address() 
 *  \brief Function to set IP address.
 *  \param ip_addr, IP address string.
 *  \return None.
 */
void router_interface::set_network_address(std::string& ip_addr)
{
    ip_address = ip_addr;
}

/*! \fn get_queue_size() 
 *  \brief Function to get queue size of TX, RX buffers.
 *  \return q_size, Queue size of TX & RX buffers.
 */
int router_interface::get_queue_size() const
{
    return queue_size;
}

/*! \fn set_queue_size() 
 *  \brief Function to set queue size for TX, RX buffers.
 *  \param q_size, Queue size of TX & RX buffers.
 *  \return None.
 */
void router_interface::set_queue_size(int q_size)
{
    queue_size = q_size;
}

/*! \fn get_is_connected_flag() 
 *  \brief Function to know whether a link is present over this interface.
 *  \return is_connected_flag.
 */
bool router_interface::get_is_connected_flag() const
{
    return is_connected_flag;
}

/*! \fn set_is_connected_flag() 
 *  \brief Function to set a flag when link is created over this interface.
 *  \param flag, Flag to denote whether a link is present.
 *  \return None.
 */
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

void router_interface::copy_packet_to_send_ring_buffer(packet_buf *pkt)
{
    // Check for buffer overflow
    if (queue_size >= (pkts_in_send_buf + 1))
    {
        pkts_in_send_buf++;
        std::memcpy(if_send_buf[end_send_buf_idx]->pkt_buf, pkt->pkt_buf, DEFAULT_PACKET_SIZE_WITH_FCS);   
        std::memcpy(if_send_buf[end_send_buf_idx]->timestamp, pkt->timestamp, sizeof(struct timeval));   
        if (queue_size == (end_send_buf_idx + 1))
        {
            end_send_buf_idx = 0;
        }
        else 
        { 
            end_send_buf_idx += 1;  
        }
    }  
    else 
    {
        // Drop the packet and update link parameters
        LOG_MESSAGE("Packet not sent due to buffer overflow."); 
    }  
}

void router_interface::copy_packet_to_recv_ring_buffer(packet_buf *pkt)
{
    // Check for buffer overflow
    if (queue_size >= (pkts_in_recv_buf + 1))
    {
        pkts_in_recv_buf++;
        std::memcpy(if_recv_buf[end_recv_buf_idx]->pkt_buf, pkt->pkt_buf, DEFAULT_PACKET_SIZE_WITH_FCS);   
        std::memcpy(if_recv_buf[end_recv_buf_idx]->timestamp, pkt->timestamp, sizeof(struct timeval));   
        if (queue_size == (end_recv_buf_idx + 1))
        {
            end_recv_buf_idx = 0;
        }
        else 
        { 
            end_recv_buf_idx += 1;  
        }
    }  
    else 
    {
        // Drop the packet and update link parameters
        LOG_MESSAGE("Packet not sent due to buffer overflow."); 
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

