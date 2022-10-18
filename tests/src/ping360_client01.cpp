#include <iostream>
using namespace std;

#include <ping_protocol/PingClient.h>
#include <ping_protocol/messages/Ping360Messages.h>
using namespace ping_protocol;

int main()
{
    auto client = PingClient::CreateUDP("192.168.2.2", 9092);

    getchar();

    for(int i = 0; i < 10; i++) {
        //client->send(GeneralRequest(5));
        //client->send(GeneralRequest(4));
        client->send(ping360::Transducer());
        getchar();
        client->send(ping360::MotorOff());
        getchar();
    }

    return 0;
}
