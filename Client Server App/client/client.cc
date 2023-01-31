#include "../headers/client.h"
#include <gtest/gtest.h>

Client::Client(char *ip)
{
    Client::initSocket(ip);
}

void Client::initSocket(char *ip){
    std::string ip_server(ip);
    socket_handler_.open_socket();
    socket_handler_.bind(CLIENT_PORT);
    socket_handler_.connect(SERVER_PORT, ip_server);
}

void Client::send()
{
    p = getpid();
    echo_message_ = std::make_shared<IcmpPacket> (REQ_MSG,CODE,0,p,1,"Hello from Client");
    echo_message_->set_checksum(IcmpPacket::compute_checksum(echo_message_));
    socket_handler_.send(echo_message_->encode());
    Client::receive();
}

void Client::receive()
{
    std::shared_ptr<std::vector<uint8_t>> reply_buffer = std::make_shared<std::vector<uint8_t>>(SIZEBUF, 0);
    socket_handler_.recv(reply_buffer);
    echo_message_->display_info(echo_message_->decode(reply_buffer), "ON CLIENT ECHO_REPLY  ");
}