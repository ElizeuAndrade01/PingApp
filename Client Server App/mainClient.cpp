#include <thread>

#include "./libs/client.h"

void start_client()
{
    try
    {
        Client cliente;
        cliente.send();
    }
    catch (const std::exception& e)
    {
        std::string error_msg = "ON CLIENT: ";
        error_msg.append(e.what());
        throw std::runtime_error(error_msg);
    }
}

int main()
{
    try
    {
        std::thread client_thread (start_client);

        client_thread.join();

        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}