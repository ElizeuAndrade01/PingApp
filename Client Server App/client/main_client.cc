#include <cstring>
#include "../headers/client.h"

void start_client(int arg, char *ip)
{
    try
    {
        Client client(ip);
        client.send();
    }
    catch (const std::exception& e)
    {
        std::string error_msg = "ON CLIENT: ";
        error_msg.append(e.what());
        throw std::runtime_error(error_msg);
    }
}

int main(int argc, char *argv[])
{
    try
    {
        start_client(argc, argv[1]);
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}