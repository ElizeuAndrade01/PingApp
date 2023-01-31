#ifndef CLIENTSERVERAPP_LIBS_CLIENT_H_
#define CLIENTSERVERAPP_LIBS_CLIENT_H_

#include "icmp_packet.h"
#include "socket.h"

#define REQ_MSG 0
#define CODE 0
#define SIZEBUF 26

class Client {
public:
    Client();
    Client(char *ip);
    // Send and Receive ICMP Packets functions
    void send();
    void receive();
    // function that gets the ip and port from user to init socket
    void initSocket(char *ip);
private:
    int p;
    Socket socket_handler_;
    std::shared_ptr<IcmpPacket> echo_message_;
};

#endif // CLIENTSERVERAPP_LIBS_CLIENT_H_