#include "../headers/server.h"
#include <cstring>
#include <iostream>

Server::Server()
{
    std::string st = "127.0.0.1";
    socket_handler_.open_socket();
    socket_handler_.bind(SERVER_PORT);
    socket_handler_.connect(CLIENT_PORT, st);
}

void Server::listen()
{
    std::shared_ptr<std::vector<uint8_t>> request_buffer = std::make_shared<std::vector<uint8_t>>(26,0);
    socket_handler_.recv(request_buffer);
    pkt = echo_message_->decode(request_buffer);
    echo_message_->display_info(pkt, "ON SERVER ECHO_REQUEST");
    Server::reply();
}

void Server::reply()
{
    pkt->set_type(RPLY_MSG);
    pkt->set_payload("Hello from server!");
    socket_handler_.send(pkt->encode());
}