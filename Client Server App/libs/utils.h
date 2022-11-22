#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <memory>
#include "icmpPacket.h"

class Utils{
public:
    static void displayInfo(std::shared_ptr<IcmpPacket> packet, std::string extra_msg);
};

#endif