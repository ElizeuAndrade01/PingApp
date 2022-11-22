#include "libs/icmpPacket.h"
#include <utility>

IcmpPacket::IcmpPacket(){}

IcmpPacket::IcmpPacket(uint8_t p_type,
                       uint8_t p_code,
                       uint16_t p_checksum,
                       uint16_t p_identifier,
                       uint16_t p_sequenceNumber,
                       std::string p_payload) :
        type_{p_type},
        code_{p_code},
        checksum_{p_checksum},
        identifier_{p_identifier},
        sequenceNumber_{p_sequenceNumber},
        payload_{std::move(p_payload)}
{
}

std::shared_ptr<std::vector<uint8_t>> IcmpPacket::encode()
{
    std::shared_ptr<std::vector<uint8_t>> pkt = std::make_shared<std::vector<uint8_t>>();
    pkt->push_back(type_); //type
    pkt->push_back(code_); //code
    pkt->push_back(static_cast<uint8_t> (checksum_ >> 8)); //checksum first byte
    pkt->push_back(static_cast<uint8_t> (checksum_ & 0xFF)); //checksum second byte
    pkt->push_back(static_cast<uint8_t> (identifier_ >> 8)); //identifier first byte
    pkt->push_back(static_cast<uint8_t> (identifier_ & 0xFF)); //identifier second byte
    pkt->push_back(static_cast<uint8_t> (sequenceNumber_ >> 8)); //sequencenumber first byte
    pkt->push_back(static_cast<uint8_t> (sequenceNumber_ & 0xFF)); //sequencenumber second byte

    for (const auto& c : payload_)
    {
        pkt->push_back(static_cast<uint8_t> (c));
    }
    return pkt;
}


uint8_t IcmpPacket::getType() const                 {return type_;}
uint8_t IcmpPacket::getCode() const                 {return code_;}
uint16_t IcmpPacket::getChecksum() const            {return checksum_;}
uint16_t IcmpPacket::getIdentifier() const          {return identifier_;}
uint16_t IcmpPacket::getSequenceNumber() const      {return sequenceNumber_;}
std::string IcmpPacket::getPayload() const          {return payload_;}

void IcmpPacket::setType(const uint8_t &newType)                      { type_ = newType; }
void IcmpPacket::setCode(const uint8_t &newCode)                      { code_ = newCode; }
void IcmpPacket::setChecksum(const uint16_t &newChecksum)             { checksum_ = newChecksum; }
void IcmpPacket::setIdentifier(const uint16_t &newIdentifier)         { identifier_ = newIdentifier; }
void IcmpPacket::setSequenceNumber(const uint16_t &newSequenceNumber) { sequenceNumber_ = newSequenceNumber; }
void IcmpPacket::setPayload(const std::string &newPayload)            { payload_ = newPayload; }

uint16_t IcmpPacket::computeChecksum(std::shared_ptr<IcmpPacket> packet)
{
    uint32_t sum = (packet->getType() << 8) + packet->getCode()
                   + packet->getIdentifier() + packet->getSequenceNumber();

    for (const auto& c : packet->getPayload())
    {
        sum += static_cast<uint8_t> (c << 8);
        sum += static_cast<uint8_t> (c);
    }

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return static_cast<uint16_t>(~sum);
}