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

    static void empty_callback(const ErrorCode&, std::size_t) {}

    rtac::asio::Stream::Ptr stream_;
    ProtocolVersion protocolVersion_;

    MessageHeader incomingHeader_;
    Message       incomingMessage_;

    PingClient(rtac::asio::Stream::Ptr stream, bool enableDump = true);

    void initiate_callback(const ErrorCode& err, std::size_t byteCount);
    void get_header();
    void header_callback(const ErrorCode& err, std::size_t byteCount);
    void payload_callback(const ErrorCode& err, std::size_t byteCount);

    public:

    static Ptr CreateUDP(const std::string& remoteIP, uint16_t remotePort,
                         bool enableDump = false);
    static Ptr CreateSerial(const std::string& device, unsigned int baudrate,
                            bool enableDump = false);

    rtac::asio::Stream::Ptr      stream()       { return stream_; }
    rtac::asio::Stream::ConstPtr stream() const { return stream_; }

    std::size_t send(const Message& msg);
    void async_send(const Message& msg);

    void initiate_connection();
    virtual void message_callback(const Message& msg);
};

} //namespace ping_protocol

#endif //_DEF_PING_PROTOCOL_PING_CLIENT_H_
