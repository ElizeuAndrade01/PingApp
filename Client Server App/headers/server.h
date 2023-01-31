#ifndef CLIENTSERVERAPP_LIBS_SERVER_H_
#define CLIENTSERVERAPP_LIBS_SERVER_H_

#include "icmp_packet.h"
#include "socket.h"

#define RPLY_MSG 8
class Server {
public:
    Server();
    // function that sets the server to listen and reply after receive a icmp packet
    void listen();
    void reply();
private:
    Socket socket_handler_;
    std::shared_ptr<IcmpPacket> echo_message_;
    std::shared_ptr<IcmpPacket> pkt;
};
#endif //CLIENTSERVERAPP_LIBS_SERVER_H_ 