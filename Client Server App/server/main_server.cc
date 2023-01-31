#include <thread>
#include "../headers/server.h"

void start_server()
{
        Server server;
        server.listen();
}

int main()
{
    try
    {
        start_server();
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return -1;
}