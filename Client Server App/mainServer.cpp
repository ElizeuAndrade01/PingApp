#include <thread>


#include "./libs/server.h"
#include <gtest/gtest.h>

void start_server()
{
    try
    {
        Server server;
        server.listen();
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

    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}