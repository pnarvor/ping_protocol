#ifndef _DEF_PING_PROTOCOL_DRIVER_MESSAGES_PRINT_UTILS_H_
#define _DEF_PING_PROTOCOL_DRIVER_MESSAGES_PRINT_UTILS_H_

#include <iostream>

#include <ping_protocol/messages/MessageBase.h>
#include <ping_protocol/messages/common.h>
#include <ping_protocol/messages/Ping360Messages.h>

namespace ping_protocol {

inline std::ostream& print(std::ostream& os, const Message& msg)
{
    switch(msg.header().message_id) {
        default: os << msg; break;

        case Acknowledged::MessageId:      os << reinterpret_cast<const Acknowledged&>(msg);      break;
        case NotAcknowledged::MessageId:   os << reinterpret_cast<const NotAcknowledged&>(msg);   break;
        case AsciiMessage::MessageId:      os << reinterpret_cast<const AsciiMessage&>(msg);      break;
        case GeneralRequest::MessageId:    os << reinterpret_cast<const GeneralRequest&>(msg);    break;
        case DeviceInformation::MessageId: os << reinterpret_cast<const DeviceInformation&>(msg); break;
        case ProtocolVersion::MessageId:   os << reinterpret_cast<const ProtocolVersion&>(msg);   break;
        case SetDeviceId::MessageId:       os << reinterpret_cast<const SetDeviceId&>(msg);       break;
        case SetPing360Id::MessageId:      os << reinterpret_cast<const SetPing360Id&>(msg);      break;
        case DeviceData::MessageId:        os << reinterpret_cast<const DeviceData&>(msg);        break;
        case Transducer::MessageId:        os << reinterpret_cast<const Transducer&>(msg);        break;
        case Reset::MessageId:             os << reinterpret_cast<const Reset&>(msg);             break;
        case MotorOff::MessageId:          os << reinterpret_cast<const MotorOff&>(msg);          break;
    }
    return os;
}

} //namespace ping_protocol

#endif //_DEF_PING_PROTOCOL_DRIVER_MESSAGES_PRINT_UTILS_H_
