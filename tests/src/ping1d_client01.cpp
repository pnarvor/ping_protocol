#include <iostream>
using namespace std;

#include <ping_protocol/PingClient.h>
#include <ping_protocol/messages/Ping1DMessages.h>
using namespace ping_protocol;

int main()
{
    //auto client = PingClient::CreateUDP("192.168.2.2", 9090);
    auto client = PingClient::CreateSerial("/dev/narval_ping1d", 115200u, true);
    //client->stream()->enable_io_dump();

    //getchar();
    //client->send(ping1d::ContinuousStart(1211));
    //getchar();
    //client->send(ping1d::ContinuousStop(1211));
    //getchar();

    //getchar();
    //client->send(ping1d::ContinuousStart(1300));
    //getchar();
    //client->send(ping1d::ContinuousStop(1300));
    //getchar();

    //getchar();
    while(1) {
        client->send(GeneralRequest(1300));
        getchar();
    }

    return 0;
}
