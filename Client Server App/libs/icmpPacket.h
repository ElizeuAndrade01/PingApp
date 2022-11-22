#ifndef ICMPPACKET_H
#define ICMPPACKET_H

#include <vector>
#include <unistd.h>
#include <iostream>
#include <memory>


class IcmpPacket{
private:
    uint8_t type_{};
    uint8_t code_{};
    uint16_t checksum_{};
    uint16_t identifier_{};
    uint16_t sequenceNumber_{};
    std::string payload_;

public:  
    IcmpPacket();
    IcmpPacket(uint8_t p_Type, uint8_t p_Code, uint16_t p_Checksum, uint16_t p_Identifier,
               uint16_t p_SequenceNumber, std::string p_Payload);

    std::shared_ptr<std::vector<uint8_t>> encode();
    static std::shared_ptr<IcmpPacket> decode(const std::shared_ptr<std::vector<uint8_t>>& inputPacket)
{
    std::shared_ptr<IcmpPacket> pkt = std::make_shared<IcmpPacket>();
    pkt->setType(inputPacket->at(0));
    pkt->setCode(inputPacket->at(1));
    pkt->setChecksum((inputPacket->at(2) << 8) + inputPacket->at(3));
    pkt->setIdentifier((inputPacket->at(4) << 8) + inputPacket->at(5));
    pkt->setSequenceNumber((inputPacket->at(6) << 8) + inputPacket->at(7));

    std::string payload_msg;
    for (auto i = inputPacket->begin()+8; i != inputPacket->end(); ++i){
        payload_msg.push_back(*i);
    }
    pkt->setPayload(payload_msg);
    return pkt;
}

    uint8_t getType() const;
    uint8_t getCode() const;
    uint16_t getChecksum() const;
    uint16_t getIdentifier() const;
    uint16_t getSequenceNumber() const;
    std::string getPayload() const;

    void setType(const uint8_t &newType);
    void setCode(const uint8_t &newCode);
    void setChecksum(const uint16_t &newChecksum);
    void setIdentifier(const uint16_t &newIdentifier);
    void setSequenceNumber(const uint16_t &newSequenceNumber);
    void setPayload(const std::string &newPayload);

    static uint16_t computeChecksum(std::shared_ptr<IcmpPacket> packet);
};

#endif