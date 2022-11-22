#ifndef SERVER_H
#define SERVER_H

#include "icmpPacket.h"
#include "socket.h"
#include "utils.h"

class Server {
public:
    Server();
    void listen();
    void reply();
private:
    Socket socketHandler_;
    std::shared_ptr<IcmpPacket> echoMessage_;
};
#endif