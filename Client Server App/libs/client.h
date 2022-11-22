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
private:
    Socket socketHandler_;
    std::shared_ptr<IcmpPacket> echoMessage_;
};

#endif