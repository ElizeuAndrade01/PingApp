#include "../headers/icmp_packet.h"
#include <gtest/gtest.h>

IcmpPacket::IcmpPacket(){}
 
IcmpPacket::IcmpPacket(uint8_t p_type,
                       uint8_t p_code,
                       uint16_t p_checksum,
                       uint16_t p_identifier,
                       uint16_t p_sequence_number,
                       std::string p_payload) :
        type_{p_type},
        code_{p_code},
        checksum_{p_checksum},
        identifier_{p_identifier},
        sequence_number_{p_sequence_number},
        payload_{std::move(p_payload)}
{
}

std::vector<uint8_t> IcmpPacket::encode()
{
    std::vector<uint8_t> pkt;
    pkt.push_back(type_); //type
    pkt.push_back(code_); //code
    pkt.push_back(static_cast<uint8_t> (checksum_ >> 8)); //checksum first byte
    pkt.push_back(static_cast<uint8_t> (checksum_ & 0xFF)); //checksum second byte
    pkt.push_back(static_cast<uint8_t> (identifier_ >> 8)); //identifier first byte
    pkt.push_back(static_cast<uint8_t> (identifier_ & 0xFF)); //identifier second byte
    pkt.push_back(static_cast<uint8_t> (sequence_number_ >> 8)); //sequencenumber first byte
    pkt.push_back(static_cast<uint8_t> (sequence_number_ & 0xFF)); //sequencenumber second byte

    for (const auto& c : payload_)
    {
        pkt.push_back(static_cast<uint8_t> (c));
    }
    return pkt;
}
std::shared_ptr<IcmpPacket> IcmpPacket::decode(const std::shared_ptr<std::vector<uint8_t>>& input_packet)
{
    std::shared_ptr<IcmpPacket> pkt = std::make_shared<IcmpPacket>();
    pkt->set_type(input_packet->at(0));
    pkt->set_code(input_packet->at(1));
    pkt->set_checksum((input_packet->at(2) << 8) + input_packet->at(3));
    pkt->set_identifier((input_packet->at(4) << 8) + input_packet->at(5));
    pkt->set_sequence_number((input_packet->at(6) << 8) + input_packet->at(7));

    std::string payload_msg;
    for (auto i = input_packet->begin()+8; i != input_packet->end(); ++i){
        payload_msg.push_back(*i);
    }
    pkt->set_payload(payload_msg);
    return pkt;
}

void IcmpPacket::display_info(std::shared_ptr<IcmpPacket> packet, std::string extra_msg)
{
    std::cout   << extra_msg
                << " type="         << unsigned(packet->get_type())
                << " code="         << unsigned(packet->get_code())
                << " checksum="     << packet->get_checksum()
                << " identifier="   << packet->get_identifier()
                << " sequence="     << packet->get_sequence_number()
                << " payload=\""    << packet->get_payload()  << "\""
                << std::endl;
}

uint8_t IcmpPacket::get_type() const                 {return type_;}
uint8_t IcmpPacket::get_code() const                 {return code_;}
uint16_t IcmpPacket::get_checksum() const            {return checksum_;}
uint16_t IcmpPacket::get_identifier() const          {return identifier_;}
uint16_t IcmpPacket::get_sequence_number() const      {return sequence_number_;}
std::string IcmpPacket::get_payload() const          {return payload_;}

void IcmpPacket::set_type(const uint8_t &new_type)                      { type_ = new_type; }
void IcmpPacket::set_code(const uint8_t &new_code)                      { code_ = new_code; }
void IcmpPacket::set_checksum(const uint16_t &new_checksum)             { checksum_ = new_checksum; }
void IcmpPacket::set_identifier(const uint16_t &new_identifier)         { identifier_ = new_identifier; }
void IcmpPacket::set_sequence_number(const uint16_t &new_sequence_number) { sequence_number_ = new_sequence_number; }
void IcmpPacket::set_payload(const std::string &new_payload)            { payload_ = new_payload; }

uint16_t IcmpPacket::compute_checksum(std::shared_ptr<IcmpPacket> packet)
{
    uint32_t sum = (packet->get_type() << 8) + packet->get_code()
                   + packet->get_identifier() + packet->get_sequence_number();

    for (const auto& c : packet->get_payload())
    {
        sum += static_cast<uint8_t> (c << 8);
        sum += static_cast<uint8_t> (c);
    }

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return static_cast<uint16_t>(~sum);
}