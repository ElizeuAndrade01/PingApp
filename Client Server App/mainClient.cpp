#include <thread>

#include "./libs/client.h"
#include <gtest/gtest.h>

void start_client()
{
    try
    {
        Client client;
        client.send();

    }
    catch (const std::exception& e)
    {
        std::string error_msg = "ON CLIENT: ";
        error_msg.append(e.what());
        throw std::runtime_error(error_msg);
    }
}

TEST(ICMPACKETS, ICMPPACKETSSTARTNULL){
    Client cTest;

    std::string ip = cTest.getIp();

    ASSERT_EQ(ip, NULL);
}


int main(int argc, char ** argv)
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

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}