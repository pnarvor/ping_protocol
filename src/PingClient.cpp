#include <ping_protocol/PingClient.h>
#include <ping_protocol/messages/print_utils.h>

#include <iostream>

namespace ping_protocol {

// allows to use _1, _2 ...
using namespace std::placeholders;

PingClient::PingClient(rtac::asio::Stream::Ptr stream, bool enableDump) :
    stream_(stream),
    incomingMessage_(0,0)
{
    if(enableDump) {
        stream_->enable_io_dump();
    }
    stream_->flush();
    stream_->start();
    this->initiate_connection();
}

PingClient::Ptr PingClient::CreateUDP(const std::string& remoteIP, uint16_t remotePort,
                                      bool enableDump)
{
    return Ptr(new PingClient(
        rtac::asio::Stream::CreateUDPClient(remoteIP, remotePort), enableDump));
}

PingClient::Ptr PingClient::CreateSerial(const std::string& device, unsigned int baudrate,
                                         bool enableDump)
{
    return Ptr(new PingClient(rtac::asio::Stream::CreateSerial(device, baudrate),
                              enableDump));
}

std::size_t PingClient::send(const Message& msg)
{
    // synchronous write
    auto sent = stream_->write(msg.size(), msg.data());
    if(sent != msg.size()) {
        //std::ostringstream oss;
        //oss << "PingClient : could not send full message ("
        //    << sent << '/' << msg.size() << " bytes)";
        //throw std::runtime_error(oss.str());
        std::cerr << "PingClient : could not send full message ("
            << sent << '/' << msg.size() << " bytes)" << std::endl;
    }
    return sent;
}

void PingClient::async_send(const Message& msg)
{
    // synchronous write
    if(!stream_->async_write(msg.size(), msg.data(), empty_callback)) {
        std::ostringstream oss;
        oss << "PingClient : could not send message";
        throw std::runtime_error(oss.str());
    }
}

void PingClient::initiate_connection()
{
    std::cout << "Initiating connection " << std::endl;
    stream_->async_read(protocolVersion_.size(), protocolVersion_.data(),
        std::bind(&PingClient::initiate_callback, this, _1, _2));
    this->async_send(GeneralRequest(5));
    //this->send(GeneralRequest(5));
}

void PingClient::initiate_callback(const ErrorCode& err, std::size_t byteCount)
{
    if(err) {
        std::ostringstream oss;
        oss << "PingClient::initiate_callback : got stream error ("
            << err << ')';
        throw std::runtime_error(oss.str());
    }
    else if(byteCount != ProtocolVersion::FixedSize || !protocolVersion_.is_valid()) {
        std::cerr << "PingClient::initiate_callback : invalid ProtocolVersion message"
                  << std::endl;
        this->initiate_connection();
    }
    else {
        // valid connection
        std::cout << protocolVersion_ << std::endl;
        this->get_header();
    }
}

void PingClient::get_header()
{
    stream_->async_read(sizeof(incomingHeader_), (uint8_t*)&incomingHeader_,
        std::bind(&PingClient::header_callback, this, _1, _2));
}

void PingClient::header_callback(const ErrorCode& err, std::size_t byteCount)
{
    if(err) {
        std::ostringstream oss;
        oss << "PingClient::header_callback : got stream error ("
            << err << ')';
        throw std::runtime_error(oss.str());
    }
    else if(byteCount != sizeof(incomingHeader_) || !incomingHeader_.is_valid()) {
        std::cerr << "Invalid Header" << std::endl << std::flush;
        this->get_header();
    }
    else {
        incomingMessage_.accomodate_for_message(incomingHeader_);
        stream_->async_read(incomingHeader_.payload_length + 2,
                            incomingMessage_.payload(),
                            std::bind(&PingClient::payload_callback, this, _1, _2));
    }
}

void PingClient::payload_callback(const ErrorCode& err, std::size_t byteCount)
{
    if(err) {
        std::ostringstream oss;
        oss << "PingClient::payload_callback : got stream error ("
            << err << ')';
        throw std::runtime_error(oss.str());
    }
    this->message_callback(incomingMessage_);
    this->get_header();
}

void PingClient::message_callback(const Message& msg) const
{
    print(std::cout, msg) << std::endl;
}

} //namespace ping_protocol
