#include "./libs/socket.h"


void Socket::openSocket()
{
    if((socketFd_ = ::socket(AF_INET, SOCK_DGRAM, 0)) <= 0)
    {
        throw std::runtime_error("Socket Error");
    }
}

void Socket::bind(const uint16_t &port)
{
    srcAddress_.sin_family = AF_INET;
    srcAddress_.sin_addr.s_addr = INADDR_ANY;
    srcAddress_.sin_port = htons(port);

    if (::bind(socketFd_, (struct sockaddr *) &srcAddress_, sizeof(srcAddress_)) < 0)
    {
        throw std::runtime_error("Bind Error");
    }
}

void Socket::connect(const uint16_t &port, const std::string &ip)
{
    destAddress_.sin_family = AF_INET;
    destAddress_.sin_addr.s_addr = inet_addr(ip.data());
    destAddress_.sin_port = htons(port);

    if (::connect(socketFd_,
                  (struct sockaddr *) &destAddress_,
                  sizeof (destAddress_)) < 0)
    {
        throw std::runtime_error("Connect Error");
    }
}

void Socket::send(std::shared_ptr<std::vector<uint8_t>> buf)
{
    if (::send(socketFd_, buf->data(), buf->size(),0) < 0)
    {
        throw std::runtime_error("Send Error");
    }
}

void Socket::recv(std::shared_ptr<std::vector<uint8_t>> buf)
{
    if (::recv(socketFd_, buf->data(), buf->size(),0) < 0)
    {
        throw std::runtime_error("Receive Error");
    }
}