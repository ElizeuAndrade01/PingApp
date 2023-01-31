#ifndef CLIENTSERVERAPP_LIBS_SOCKET_H_
#define CLIENTSERVERAPP_LIBS_SOCKET_H_

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <memory>
#include <stdexcept>
#include <vector>

#define SERVER_PORT 6666
#define CLIENT_PORT 6667

class Socket{
public:
    // function that opens the socket
    void open_socket();
    // Bind the server to an specific port to wait a connection from any client
    void bind(const uint16_t &port);
    // Connect to client connect to server
    void connect(const uint16_t &port,
                        std::string ip);
    // Send and Receive packets
    void send(std::vector<uint8_t> buf);
    void recv(std::shared_ptr<std::vector<uint8_t>> buf);
private:
    std::string s;
    int socket_fd_;
    sockaddr_in src_address_, dest_address_;
};

#endif //CLIENTSERVERAPP_LIBS_SOCKET_H_