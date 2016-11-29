#include <limits.h>
#include "gtest/gtest.h"
#include "../../../packet/ns_packet_ethr.h"

TEST(test_ethr_packet, packet_creation)
{
    std::string src_mac_address = "01:02:03:04:05:06";
    std::string dst_mac_address = "00:0A:FF:00:00:02";
    std::string src_ip_address = "1.1.1.1";
    std::string dst_ip_address = "3.3.3.3";
    int l2_ip_ether = 2048;
    int ip_version = 4;
    int header_length = 20;
    int total_packet_length = 64;
    int dscp_priority = 56;
    int ttl = 253;
    int ip_protocol = 254;
    int header_checksum = 65535;
    int identifier = 1;
    bool dont = 0;
    bool more = 0;
    unsigned char packet[64] = { 0 };

    ethr_pkt pkt;
    pkt.set_src_mac_address(packet, src_mac_address);     
    pkt.set_dst_mac_address(packet, dst_mac_address);     
    pkt.set_dst_ipv4_address(packet, dst_ip_address);     
    pkt.set_src_ipv4_address(packet, src_ip_address);     
    pkt.set_l2_ethertype(packet, l2_ip_ether);    
    pkt.set_ip_version_type(packet, ip_version); 
    pkt.set_ip_header_length(packet, header_length); 
    pkt.set_dscp_priority(packet, dscp_priority); 
    pkt.set_ip_total_length(packet, total_packet_length); 
    pkt.set_packet_identifier(packet, identifier); 
    pkt.set_fragment_flags(packet, dont, more, 0); 
    pkt.set_ttl(packet, ttl); 
    pkt.set_protocol(packet, ip_protocol); 
    pkt.set_ip_header_checksum(packet, header_checksum);
    
    EXPECT_EQ(src_mac_address, pkt.get_src_mac_address()); 
    EXPECT_EQ(dst_mac_address, pkt.get_dst_mac_address()); 
    EXPECT_EQ(src_ip_address, pkt.get_src_ipv4_address()); 
    EXPECT_EQ(dst_ip_address, pkt.get_dst_ipv4_address()); 
    EXPECT_EQ(l2_ip_ether, pkt.get_l2_ethertype()); 
    EXPECT_EQ(ip_version, pkt.get_ip_version_type()); 
    EXPECT_EQ((header_length / 4), pkt.get_ip_header_length()); 
    EXPECT_EQ(dscp_priority, pkt.get_dscp_priority()); 
    EXPECT_EQ(total_packet_length, pkt.get_ip_total_length()); 
    EXPECT_EQ(identifier, pkt.get_packet_identifier()); 
    EXPECT_EQ(dont, pkt.get_dont_frag_flag()); 
    EXPECT_EQ(more, pkt.get_more_frag_flag()); 
    EXPECT_EQ(0, pkt.get_packet_offset()); 
    EXPECT_EQ(ttl, pkt.get_ttl()); 
    EXPECT_EQ(ip_protocol, pkt.get_protocol()); 
    EXPECT_EQ(header_checksum, pkt.get_ip_header_checksum());
    for (int index = 0; index < 64; index++)
    {
        std::cout << static_cast<int>(packet[index]) << " ";    
    } 
    std::cout << std::endl; 
   
}

TEST(test_ethr_packet, int_string_to_int_conversion)
{
    ethr_pkt pkt; 
    unsigned char value;
    
    value = pkt.int_string_to_int("05");
    EXPECT_EQ(5, value);
    value = pkt.int_string_to_int("0");
    EXPECT_EQ(0, value);
    value = pkt.int_string_to_int("255");
    EXPECT_EQ(255, value);
}

TEST(test_ethr_packet, hex_string_to_int_conversion)
{
    ethr_pkt pkt; 
    unsigned char value;
    
    value = pkt.hex_string_to_int("05");
    EXPECT_EQ(5, value);
    value = pkt.hex_string_to_int("00");
    EXPECT_EQ(0, value);
    value = pkt.hex_string_to_int("0A");
    EXPECT_EQ(10, value);
    value = pkt.hex_string_to_int("FF");
    EXPECT_EQ(255, value);
    value = pkt.hex_string_to_int("DE");
    EXPECT_EQ(222, value);
}