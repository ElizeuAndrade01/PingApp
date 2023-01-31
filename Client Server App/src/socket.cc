#include "../headers/socket.h"
#include <iostream>

void Socket::open_socket()
{
    if((socket_fd_ = ::socket(AF_INET, SOCK_DGRAM, 0)) <= 0)
    {
        throw std::runtime_error("Socket Error");
    }
}

void Socket::bind(const uint16_t &port)
{
    src_address_.sin_family = AF_INET;
    src_address_.sin_addr.s_addr = INADDR_ANY;
    src_address_.sin_port = htons(port);

    if (::bind(socket_fd_, (struct sockaddr *) &src_address_, sizeof(src_address_)) < 0)
    {
        throw std::runtime_error("Bind Error");
    }
}

void Socket::connect(const uint16_t &port, std::string ip)
{
    dest_address_.sin_family = AF_INET;
    dest_address_.sin_addr.s_addr = inet_addr(ip.data());
    dest_address_.sin_port = htons(port);

    if (::connect(socket_fd_,
                  (struct sockaddr *) &dest_address_,
                  sizeof (dest_address_)) < 0)
    {
        throw std::runtime_error("Connect Error" + ip);
    }
}

void Socket::send(std::vector<uint8_t> buf)
{
    if (::send(socket_fd_, buf.data(), buf.size(),0) < 0)
    {
        throw std::runtime_error("Send Error");
    }
}

void Socket::recv(std::shared_ptr<std::vector<uint8_t>> buf)
{
    if (::recv(socket_fd_, buf->data(), buf->size(),0) < 0)
    {
        throw std::runtime_error("Receive Error");
    }
}