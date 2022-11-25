#ifndef CLIENT_H
#define CLIENT_H

#include "icmpPacket.h"
#include "socket.h"
#include "utils.h"

class Client {
public:
    Client();
    void send();
    void receive();
    std::string setIp();
    uint16_t setPort();
    void initSocket();
    void getIp();
private:
    std::string ip;
    uint16_t port;
    Socket socketHandler_;
    std::shared_ptr<IcmpPacket> echoMessage_;
};

#endif