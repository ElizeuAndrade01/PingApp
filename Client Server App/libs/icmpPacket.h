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
               uint16_t p_SequenceNumber, std::string p_Payload
    );
    std::shared_ptr<std::vector<uint8_t>> encode();
    static std::shared_ptr<IcmpPacket> decode(const std::shared_ptr<std::vector<uint8_t>>& inputPacket);

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