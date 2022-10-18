#ifndef _DEF_PING_PROTOCOL_PING_CLIENT_H_
#define _DEF_PING_PROTOCOL_PING_CLIENT_H_

#include <memory>

#include <rtac_asio/Stream.h>

#include <ping_protocol/messages/common.h>

namespace ping_protocol {

class PingClient
{
    public:

    using Ptr      = std::shared_ptr<PingClient>;
    using ConstPtr = std::shared_ptr<const PingClient>;

    using ErrorCode = rtac::asio::Stream::ErrorCode;

    protected:

    rtac::asio::Stream::Ptr stream_;
    ProtocolVersion protocolVersion_;

    MessageHeader incomingHeader_;
    Message       incomingMessage_;

    PingClient(rtac::asio::Stream::Ptr stream);

    void initiate_callback(const ErrorCode& err, std::size_t byteCount);
    void get_header();
    void header_callback(const ErrorCode& err, std::size_t byteCount);
    void payload_callback(const ErrorCode& err, std::size_t byteCount);

    public:

    static Ptr CreateUDP(const std::string& remoteIP, uint16_t remotePort);

    void send(const Message& msg);

    void initiate_connection();
    virtual void message_callback(const Message& msg) const;
};

} //namespace ping_protocol

#endif //_DEF_PING_PROTOCOL_PING_CLIENT_H_
