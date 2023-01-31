#ifndef CLIENTSERVERAPP_LIBS_ICMPPACKET_H_
#define CLIENTSERVERAPP_LIBS_ICMPPACKET_H_

#include <vector>
#include <unistd.h>
#include <iostream>
#include <memory>

/*
    ####################ICMP PACKET STRUCTURE######################
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Type      |     Code      |          Checksum             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |           Identifier          |        Sequence Number        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Data ...
   +-+-+-+-+-
*/

class IcmpPacket{
public:
    IcmpPacket();

    //Constructor
    IcmpPacket(uint8_t p_Type, uint8_t p_Code, uint16_t p_Checksum, uint16_t p_Identifier,
               uint16_t p_Sequence_Number, std::string p_Payload);

    //Encode and Decode Functions
    std::vector<uint8_t> encode();
    std::shared_ptr<IcmpPacket> decode(const std::shared_ptr<std::vector<uint8_t>>& input_packet);
    std::shared_ptr<IcmpPacket> pkt();

    // display info function
    void display_info(std::shared_ptr<IcmpPacket> packet, std::string extra_msg);

    //GETTERS AND SETTERS
    uint8_t get_type() const;
    uint8_t get_code() const;
    uint16_t get_checksum() const;
    uint16_t get_identifier() const;
    uint16_t get_sequence_number() const;
    std::string get_payload() const;

    void set_type(const uint8_t &new_type);
    void set_code(const uint8_t &new_code);
    void set_checksum(const uint16_t &new_checksum);
    void set_identifier(const uint16_t &new_identifier);
    void set_sequence_number(const uint16_t &new_sequence_number);
    void set_payload(const std::string &new_payload);

    static uint16_t compute_checksum(std::shared_ptr<IcmpPacket> packet);

private:
    uint8_t type_; //8 for echo message; 0 for echo reply message.
    uint8_t code_; // 0
    uint16_t checksum_; //The checksum is the 16-bit ones's complement of the one's
                        // complement sum of the ICMP message starting with the ICMP Type.
                        // For computing the checksum , the checksum field should be zero.
                        // If the total length is odd, the received data is padded with one
                        // octet of zeros for computing the checksum.  This checksum may be
                        // replaced in the future.
    uint16_t identifier_; //If code = 0, an identifier to aid in matching echos and replies, may be zero.
    uint16_t sequence_number_; //
    std::string payload_; //If code = 0, a sequence number to aid in matching echos and replies, may be zero.
};

#endif // CLIENTSERVERAPP_LIBS_ICMPPACKET_H_