#include "ns_packet_ethr.h"

using namespace std;

static int get_offset(ns_ns::packet_param_type param);

std::string ethr_pkt::get_src_mac_address() const
{
    return src_mac_address;
}

std::string ethr_pkt::get_dst_mac_address() const
{
    return dst_mac_address;
}

std::string ethr_pkt::get_src_ipv4_address() const
{
    return src_ipv4_address;
}

std::string ethr_pkt::get_dst_ipv4_address() const
{
    return dst_ipv4_address;
}

int ethr_pkt::get_l2_ethertype() const
{
    return l2_ethertype;
}
   
int ethr_pkt::get_ip_version_type() const
{
    return ip_version_type; 
}

int ethr_pkt::get_ip_header_length() const
{
    return ip_header_length; 
}

int ethr_pkt::get_dscp_priority() const
{
    return dscp_priority;
}

int ethr_pkt::get_ip_total_length() const
{
    return ip_total_length; 
}

int ethr_pkt::get_packet_identifier() const
{
    return packet_identifier; 
}

int ethr_pkt::get_more_frag_flag() const
{
    return more_frag_flag; 
}

int ethr_pkt::get_dont_frag_flag() const
{
    return dont_frag_flag; 
}

int ethr_pkt::get_packet_offset() const
{
    return frag_offset_identifier; 
}

int ethr_pkt::get_ttl() const
{
    return ttl;
}

int ethr_pkt::get_protocol() const
{
    return l3_protocol_type;
}

int ethr_pkt::get_ip_header_checksum() const
{
    return ip_header_checksum;
}

void ethr_pkt::set_src_mac_address(unsigned char* pkt, std::string src_mac_addr)
{
    src_mac_address = src_mac_addr;
    string_to_substring(pkt, src_mac_address, ":", SRC_MAC_ADDRESS); 
}

void ethr_pkt::set_dst_mac_address(unsigned char* pkt, std::string dst_mac_addr)
{
    dst_mac_address = dst_mac_addr;
    string_to_substring(pkt, dst_mac_address, ":", DST_MAC_ADDRESS); 
}

void ethr_pkt::set_src_ipv4_address(unsigned char* pkt, std::string src_ip_addr)
{
    src_ipv4_address = src_ip_addr;
    string_to_substring(pkt, src_ip_addr, ".", SRC_IP_ADDRESS); 
}

void ethr_pkt::set_dst_ipv4_address(unsigned char* pkt, std::string dst_ip_addr)
{
    dst_ipv4_address = dst_ip_addr;
    string_to_substring(pkt, dst_ip_addr, ".", DST_IP_ADDRESS); 
}

void ethr_pkt::set_l2_ethertype(unsigned char* pkt, int ethrtype)
{
    l2_ethertype = ethrtype;
    pkt[l2_ethertype_offset] = (ethrtype >> 8);
    pkt[l2_ethertype_offset + 1] = (0x00FF & ethrtype);   
}

void ethr_pkt::set_ip_version_type(unsigned char* pkt, int type)
{
    ip_version_type = type; 
    pkt[ip_header_offset] = (type << 4);
}

void ethr_pkt::set_ip_header_length(unsigned char* pkt, int length)
{
    ip_header_length = length / 4; 
    pkt[ip_header_offset] = (((length / 4) & 0xF) | pkt[ip_header_offset]);
}

void ethr_pkt::set_dscp_priority(unsigned char* pkt, int priority)
{
    dscp_priority = priority;
    pkt[ip_dscp_offset] = priority;
}

void ethr_pkt::set_ip_total_length(unsigned char* pkt, int length)
{
    ip_total_length = length;
    pkt[ip_total_length_offset] = ((length & 0xFF00) >> 8);
    pkt[ip_total_length_offset + 1] = (length & 0x00FF);
}

void ethr_pkt::set_packet_identifier(unsigned char* pkt, int id)
{
    packet_identifier = id;
    pkt[ip_identifier_offset] = ((id & 0xFF00) >> 8);
    pkt[ip_identifier_offset + 1] = (id & 0x00FF);
}

void ethr_pkt::set_fragment_flags(unsigned char* pkt, bool dont_frag, bool more_frag, int frag_offset)
{
    more_frag_flag = more_frag;
    dont_frag_flag = dont_frag;
    frag_offset_identifier = frag_offset;
    pkt[ip_fragment_offset] = (((frag_offset & 0xFF00) >> 8) | (dont_frag << 6) | (more_frag << 5));
    pkt[ip_fragment_offset + 1] = (frag_offset & 0x00FF);
}

void ethr_pkt::set_ttl(unsigned char* pkt, int value)
{
    ttl = value;
    pkt[ip_ttl_offset] = value;
}

void ethr_pkt::set_protocol(unsigned char* pkt, int value)
{
    l3_protocol_type = value;
    pkt[ip_protocol_offset] = value;
}

void ethr_pkt::set_ip_header_checksum(unsigned char* pkt, int checksum)
{
    ip_header_checksum = checksum;
    pkt[ip_header_checksum_offset] = ((checksum & 0xFF00) >> 8);
    pkt[ip_header_checksum_offset + 1] = (checksum & 0x00FF);
}

int ethr_pkt::int_string_to_int(std::string ip_addr_seg)
{
    int value;
    std::istringstream buffer(ip_addr_seg);
     
    buffer >> value;
    return value;
}

int ethr_pkt::hex_string_to_int(std::string mac_addr_seg)
{
    unsigned long hex_value = std::strtoul(mac_addr_seg.c_str(), 0, 16);
    return hex_value;
}

void ethr_pkt::string_to_substring(unsigned char* pkt, std::string str, std::string delim, ns_ns::packet_param_type param)
{
    size_t pos = 0;
    int offset = get_offset(param);
    std::string token;
    std::vector<std::string> sub_strings; 
    
    while ((pos = str.find(delim)) != std::string::npos) 
    {
        token = str.substr(0, pos);
        sub_strings.push_back(token);        
        str.erase(0, pos + delim.length());
    }
    sub_strings.push_back(str);        

    if ((DST_MAC_ADDRESS == param) || (SRC_MAC_ADDRESS == param))
    {
        for (unsigned int index = 0; index < sub_strings.size(); index++)
        {
            unsigned char temp;
            temp = hex_string_to_int(sub_strings[index]);         
            pkt[offset + index] = temp;     
        } 
    }
    if ((DST_IP_ADDRESS == param) || (SRC_IP_ADDRESS == param))
    {
        for (unsigned int index = 0; index < sub_strings.size(); index++)
        {
            unsigned char temp;
            temp = int_string_to_int(sub_strings[index]);         
            pkt[offset + index] = temp;     
        } 
    }
}  

void ethr_pkt::parse_src_mac_address(unsigned char* pkt)
{
    std::stringstream mac_nib1;
    mac_nib1 << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<int>(pkt[src_mac_address_offset]);
    std::stringstream mac_nib2;
    mac_nib2 << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<int>(pkt[src_mac_address_offset + 1]);
    std::stringstream mac_nib3;
    mac_nib3 << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<int>(pkt[src_mac_address_offset + 2]);
    std::stringstream mac_nib4;
    mac_nib4 << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<int>(pkt[src_mac_address_offset + 3]);
    std::stringstream mac_nib5;
    mac_nib5 << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<int>(pkt[src_mac_address_offset + 4]);
    std::stringstream mac_nib6;
    mac_nib6 << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<int>(pkt[src_mac_address_offset + 5]);
    src_mac_address = mac_nib1.str() + ":" + mac_nib2.str() + ":" + mac_nib3.str() + ":" 
                      + mac_nib4.str() + ":" + mac_nib5.str() + ":" + mac_nib6.str(); 
}

void ethr_pkt::parse_dst_mac_address(unsigned char* pkt)
{
    std::stringstream mac_nib1;
    mac_nib1 << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<int>(pkt[dst_mac_address_offset]);
    std::stringstream mac_nib2;
    mac_nib2 << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<int>(pkt[dst_mac_address_offset + 1]);
    std::stringstream mac_nib3;
    mac_nib3 << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<int>(pkt[dst_mac_address_offset + 2]);
    std::stringstream mac_nib4;
    mac_nib4 << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<int>(pkt[dst_mac_address_offset + 3]);
    std::stringstream mac_nib5;
    mac_nib5 << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<int>(pkt[dst_mac_address_offset + 4]);
    std::stringstream mac_nib6;
    mac_nib6 << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<int>(pkt[dst_mac_address_offset + 5]);
    dst_mac_address = mac_nib1.str() + ":" + mac_nib2.str() + ":" + mac_nib3.str() + ":" 
                      + mac_nib4.str() + ":" + mac_nib5.str() + ":" + mac_nib6.str(); 
}

void ethr_pkt::parse_src_ipv4_address(unsigned char* pkt)
{
    std::stringstream ip_nib1;
    ip_nib1 << static_cast<int>(pkt[src_network_address_offset]); 
    std::stringstream ip_nib2;
    ip_nib2 << static_cast<int>(pkt[src_network_address_offset + 1]); 
    std::stringstream ip_nib3;
    ip_nib3 << static_cast<int>(pkt[src_network_address_offset + 2]); 
    std::stringstream ip_nib4;
    ip_nib4 << static_cast<int>(pkt[src_network_address_offset + 3]); 
    src_ipv4_address = ip_nib1.str() + "." + ip_nib2.str() + "." + ip_nib3.str() + "." + ip_nib4.str(); 
}

void ethr_pkt::parse_dst_ipv4_address(unsigned char* pkt)
{
    std::stringstream ip_nib1;
    ip_nib1 << static_cast<int>(pkt[dst_network_address_offset]); 
    std::stringstream ip_nib2;
    ip_nib2 << static_cast<int>(pkt[dst_network_address_offset + 1]); 
    std::stringstream ip_nib3;
    ip_nib3 << static_cast<int>(pkt[dst_network_address_offset + 2]); 
    std::stringstream ip_nib4;
    ip_nib4 << static_cast<int>(pkt[dst_network_address_offset + 3]); 
    dst_ipv4_address = ip_nib1.str() + "." + ip_nib2.str() + "." + ip_nib3.str() + "." + ip_nib4.str(); 
}

void ethr_pkt::parse_l2_ethertype(unsigned char* pkt)
{
    l2_ethertype = 0;
    l2_ethertype = (pkt[l2_ethertype_offset] << 8); 
    l2_ethertype = (pkt[l2_ethertype_offset + 1] | l2_ethertype); 
}

void ethr_pkt::parse_ip_version_type(unsigned char* pkt)
{
    ip_version_type = (pkt[ip_header_offset] >> 4);
}

void ethr_pkt::parse_ip_header_length(unsigned char* pkt)
{
    ip_header_length = (pkt[ip_header_offset] & 0x0F);
}

void ethr_pkt::parse_dscp_priority(unsigned char* pkt)
{
    dscp_priority = pkt[ip_dscp_offset];
}

void ethr_pkt::parse_ip_total_length(unsigned char* pkt)
{
    ip_total_length = 0;
    ip_total_length = (pkt[ip_total_length_offset] << 8); 
    ip_total_length = (pkt[ip_total_length_offset + 1] | ip_total_length); 
}

void ethr_pkt::parse_packet_identifier(unsigned char* pkt)
{
    packet_identifier = 0;
    packet_identifier = (pkt[ip_identifier_offset] << 8); 
    packet_identifier = (pkt[ip_identifier_offset + 1] | packet_identifier); 
}

void ethr_pkt::parse_fragment_flags(unsigned char* pkt)
{
    dont_frag_flag = ((pkt[ip_fragment_offset] & 0x40) >> 6);  
    more_frag_flag = ((pkt[ip_fragment_offset] & 0x20) >> 5); 
    frag_offset_identifier = 0;
    frag_offset_identifier = ((pkt[ip_fragment_offset] & 0x1F) << 8); 
    frag_offset_identifier = (pkt[ip_fragment_offset + 1] | frag_offset_identifier); 
}

void ethr_pkt::parse_ttl(unsigned char* pkt)
{
    ttl = pkt[ip_ttl_offset];
}

void ethr_pkt::parse_protocol(unsigned char* pkt)
{
    l3_protocol_type = pkt[ip_protocol_offset];
}

void ethr_pkt::parse_ip_header_checksum(unsigned char* pkt)
{
    ip_header_checksum = 0;
    ip_header_checksum = (pkt[ip_header_checksum_offset] << 8);
    ip_header_checksum = (pkt[ip_header_checksum_offset + 1] | ip_header_checksum);
}

static int get_offset(ns_ns::packet_param_type param)
{
    if (DST_MAC_ADDRESS == param)
    {
        return dst_mac_address_offset;
    }
    else if (SRC_MAC_ADDRESS == param)
    {
        return src_mac_address_offset;
    }
    else if (SRC_IP_ADDRESS == param)
    {
        return src_network_address_offset;
    }
    else if (DST_IP_ADDRESS == param)
    {
        return dst_network_address_offset;
    }
    return 0;
}

void ethr_pkt::construct_pkt(unsigned char* packet, std::string src_mac_addr, std::string dst_mac_addr,
                             std::string src_ip_addr, std::string dst_ip_addr)
{
    set_src_mac_address(packet, src_mac_addr);     
    set_dst_mac_address(packet, dst_mac_addr);     
    set_dst_ipv4_address(packet, dst_ip_addr);     
    set_src_ipv4_address(packet, src_ip_addr);     
    set_l2_ethertype(packet, RAW_ETHR_L2_ETHERTYPE);    
    set_ip_version_type(packet, 4); 
    set_ip_header_length(packet, DEFAULT_IPV4_HEADER_SIZE); 
    set_dscp_priority(packet, 56); 
    set_ip_total_length(packet, DEFAULT_IPV4_PACKET_SIZE); 
    set_packet_identifier(packet, 1); 
    set_fragment_flags(packet, 0, 0, 0); 
    set_ttl(packet, DEFAULT_TTL_VALUE); 
    set_protocol(packet, RAW_ETHR_L3_ETHERTYPE); 
    set_ip_header_checksum(packet, 65535);
}  

void ethr_pkt::parse_pkt(unsigned char* packet)
{
    parse_src_mac_address(packet);     
    parse_dst_mac_address(packet);     
    parse_dst_ipv4_address(packet);     
    parse_src_ipv4_address(packet);     
    parse_l2_ethertype(packet);    
    parse_ip_version_type(packet); 
    parse_ip_header_length(packet); 
    parse_dscp_priority(packet); 
    parse_ip_total_length(packet); 
    parse_packet_identifier(packet); 
    parse_fragment_flags(packet); 
    parse_ttl(packet); 
    parse_protocol(packet); 
    parse_ip_header_checksum(packet);
}  
