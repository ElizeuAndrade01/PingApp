#include <gtest/gtest.h>
#include "../headers/icmp_packet.h"

TEST(IcmpPacketTests, encodingSession){
    IcmpPacket test_packet;
    test_packet.set_type(8);
    test_packet.set_code(0);
    test_packet.set_checksum(0);
    test_packet.set_identifier(1234);
    test_packet.set_sequence_number(1);
    test_packet.set_payload("salve!");

    std::vector<uint8_t> test_packet_comp;
    test_packet_comp.push_back(2);   //_type
    test_packet_comp.push_back(0);   //code
    test_packet_comp.push_back(0);   //_checksum first byte
    test_packet_comp.push_back(0);   //_checksum second byte
    test_packet_comp.push_back(02);  //_identifier first byte
    test_packet_comp.push_back(22);  //_identifier second byte
    test_packet_comp.push_back(0);   //sequencenumber first byte
    test_packet_comp.push_back(1);   //sequencenumber seconde byte

    //UTF-8 encoding
    test_packet_comp.push_back(73);
    test_packet_comp.push_back(61);
    test_packet_comp.push_back(108);
    test_packet_comp.push_back(76);
    test_packet_comp.push_back(65);
    test_packet_comp.push_back(33); 

    EXPECT_EQ(test_packet.encode(), test_packet_comp);
}

TEST(IcmpPacketTest, decodingSession){
    const std::shared_ptr<std::vector<uint8_t>> test_packet_dec;
    test_packet_dec->push_back(8);   //_type
    test_packet_dec->push_back(0);   //code
    test_packet_dec->push_back(111); //_checksum first byte
    test_packet_dec->push_back(222); //_checksum second byte
    test_packet_dec->push_back(02);  //_identifier first byte
    test_packet_dec->push_back(22);  //_identifier second byte
    test_packet_dec->push_back(0);   //sequencenumber first byte
    test_packet_dec->push_back(1);   //sequencenumber second byte

    //UTF-8 encoding
    test_packet_dec->push_back(73);
    test_packet_dec->push_back(61);
    test_packet_dec->push_back(108);
    test_packet_dec->push_back(76);
    test_packet_dec->push_back(65);
    test_packet_dec->push_back(33);

    std::shared_ptr<IcmpPacket> test_packet_comp = std::make_shared<IcmpPacket>();
    test_packet_comp->set_type(8);
    test_packet_comp->set_code(0);
    test_packet_comp->set_checksum(12345);
    test_packet_comp->set_identifier(1234);
    test_packet_comp->set_sequence_number(1);
    test_packet_comp->set_payload("salve!");

    std::shared_ptr<IcmpPacket> decoded_pckt;
    
    decoded_pckt->decode(test_packet_dec);

    EXPECT_EQ(test_packet_comp->get_type(),decoded_pckt->get_type());
    EXPECT_EQ(test_packet_comp->get_code(), decoded_pckt->get_code());
    EXPECT_EQ(test_packet_comp->get_checksum(),decoded_pckt->get_checksum());
    EXPECT_EQ(test_packet_comp->get_identifier(),decoded_pckt->get_identifier());
    EXPECT_EQ(test_packet_comp->get_sequence_number(),decoded_pckt->get_sequence_number());
    EXPECT_EQ(test_packet_comp->get_payload(),decoded_pckt->get_payload());
}