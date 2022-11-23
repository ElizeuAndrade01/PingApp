#include <thread>


#include "./libs/server.h"

void start_server()
{
    try
    {
        Server servidor;
        servidor.listen();
    }
    catch (const std::exception& e)
    {
        std::string error_msg = "ON SERVER: ";
        error_msg.append(e.what());
        throw std::runtime_error(error_msg);
    }
}



int main()
{
    try
    {
        std::thread serv_thread (start_server);

        serv_thread.join();

        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}