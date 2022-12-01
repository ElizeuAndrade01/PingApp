#include <gtest/gtest.h>
#include "libs/icmpPacket.h"


TEST(IcmpPacketTests, encodingSession){
    IcmpPacket test_packet;
    test_packet.setType(2);
    test_packet.setCode(0);
    test_packet.setChecksum(12345);
    test_packet.setIdentifier(1234);
    test_packet.setSequenceNumber(1);
    test_packet.setPayload("salve!");

    std::vector<uint8_t> test_packet_comp;
    test_packet_comp.push_back(2);   //type
    test_packet_comp.push_back(0);   //code
    test_packet_comp.push_back(111); //checksum first byte
    test_packet_comp.push_back(222); //checksum second byte
    test_packet_comp.push_back(08);  //identifier first byte
    test_packet_comp.push_back(22);  //identifier second byte
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
    std::vector<uint8_t> test_packet_dec;
    test_packet_dec.push_back(2);   //type
    test_packet_dec.push_back(0);   //code
    test_packet_dec.push_back(111); //checksum first byte
    test_packet_dec.push_back(222); //checksum second byte
    test_packet_dec.push_back(08);  //identifier first byte
    test_packet_dec.push_back(22);  //identifier second byte
    test_packet_dec.push_back(0);   //sequencenumber first byte
    test_packet_dec.push_back(1);   //sequencenumber second byte

    //UTF-8 encoding
    test_packet_dec.push_back(73); 
    test_packet_dec.push_back(61);
    test_packet_dec.push_back(108);
    test_packet_dec.push_back(76);
    test_packet_dec.push_back(65); 
    test_packet_dec.push_back(33);

    std::shared_ptr<IcmpPacket> test_packet_comp = std::make_shared<IcmpPacket>();
    test_packet_comp->setType(2);
    test_packet_comp->setCode(0);
    test_packet_comp->setChecksum(12345);
    test_packet_comp->setIdentifier(1234);
    test_packet_comp->setSequenceNumber(1);
    test_packet_comp->setPayload("salve!");

    std::shared_ptr<IcmpPacket> decoded_pckt = IcmpPacket::decode(entry);

    EXPECT_EQ(test_packet_comp->getType(),decoded_pckt->getType());
    EXPECT_EQ(test_packet_comp->getCode(), decoded_pckt->getCode());
    EXPECT_EQ(test_packet_comp->getChecksum(),decoded_pckt->getChecksum());
    EXPECT_EQ(test_packet_comp->getIdentifier(),decoded_pckt->getIdentifier());
    EXPECT_EQ(test_packet_comp->getSequenceNumber(),decoded_pckt->getSequenceNumber());
    EXPECT_EQ(test_packet_comp->getPayload(),decoded_pckt->getPayload());
}