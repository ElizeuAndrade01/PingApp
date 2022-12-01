#include "../libs/client.h"
#include <gtest/gtest.h>

Client::Client()
{
    Client::initSocket();
}


std::string Client::setIp()
{
    std::cout << "Digite o ip que deseja pingar: ";
    std::cin >> ip;
    return ip;
}

uint16_t Client::setPort()
{
    std::cout << "Digite a port do ip que deseja pingar: ";
    std::cin >> port;
    return port;
}

void Client::initSocket(){
    const uint16_t finalPort = Client::setPort();
    const std::string finalIp = Client::setIp();
    socketHandler_.openSocket();
    socketHandler_.bind(CLIENT_PORT);
    socketHandler_.connect(finalPort, finalIp);
}

std::string Client::getIp()
{
    return ip;
}

void Client::send()
{
    echoMessage_ = std::make_shared<IcmpPacket> (8,0,0,getpid(),1,"Hello from Client");
    echoMessage_->setChecksum(IcmpPacket::computeChecksum(echoMessage_));
    sleep(1);
    socketHandler_.send(echoMessage_->encode());
    Client::receive();
}

void Client::receive()
{
    std::shared_ptr<std::vector<uint8_t>> reply_buffer = std::make_shared<std::vector<uint8_t>>(26,0);
    socketHandler_.recv(reply_buffer);
    echoMessage_ = IcmpPacket::decode(reply_buffer);
    Utils::displayInfo(echoMessage_, "ON CLIENT ECHO_REPLY  ");
}

