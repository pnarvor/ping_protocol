#ifndef _DEF_PING_PROTOCOL_MESSAGES_PING360_MESSAGES_H_
#define _DEF_PING_PROTOCOL_MESSAGES_PING360_MESSAGES_H_

#include <ping_protocol/messages/MessageBase.h>
#include <ping_protocol/messages/common.h>

namespace ping_protocol { namespace ping1d {

// one byte packing
#pragma pack(push, 1)

struct SetPing1DId : public Message
{
    static constexpr uint16_t MessageId = 1000;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2 + sizeof(uint8_t);

    SetPing1DId(uint8_t deviceId) :
        Message(MessageId, sizeof(uint8_t))
    {
        this->device_id() = deviceId;
        this->update_checksum();
    }
    
    uint8_t device_id() const {
        return *reinterpret_cast<const uint8_t*>(this->payload());
    }
    uint8_t& device_id() {
        return *reinterpret_cast<uint8_t*>(this->payload());
    }
};

struct SetRange : public Message
{
    static constexpr uint16_t MessageId = 1001;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2 + 2*sizeof(uint32_t);

    SetRange(uint32_t minRange, uint32_t maxRange) :
        Message(MessageId, 2*sizeof(uint32_t))
    {
        this->min_range() = minRange;
        this->max_range() = maxRange;
        this->update_checksum();
    }
    
    uint32_t min_range() const {
        return *reinterpret_cast<const uint32_t*>(this->payload());
    }
    uint32_t& min_range() {
        return *reinterpret_cast<uint32_t*>(this->payload());
    }
    uint32_t max_range() const {
        return *(reinterpret_cast<const uint32_t*>(this->payload()) + 1);
    }
    uint32_t& max_range() {
        return *(reinterpret_cast<uint32_t*>(this->payload()) + 1);
    }
};

struct SetSpeedOfSound : public Message
{
    static constexpr uint16_t MessageId = 1002;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2 + sizeof(uint32_t);

    SetSpeedOfSound(uint32_t speedOfSound) :
        Message(MessageId, sizeof(uint32_t))
    {
        this->speed_of_sound() = speedOfSound;
        this->update_checksum();
    }
    
    uint32_t speed_of_sound() const {
        return *reinterpret_cast<const uint32_t*>(this->payload());
    }
    uint32_t& speed_of_sound() {
        return *reinterpret_cast<uint32_t*>(this->payload());
    }
};

struct SetModeAuto : public Message
{
    static constexpr uint16_t MessageId = 1003;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2 + sizeof(uint8_t);

    SetModeAuto(uint8_t autoMode) :
        Message(MessageId, sizeof(uint8_t))
    {
        if(autoMode != 0 && autoMode != 1) {
            std::ostringstream oss;
            oss << "ping1d::SetAutoMode : invalid auto mode (" 
                << (unsigned int)autoMode
                << "). Shoud be 0 (manual) or 1 (auto)";
            throw std::runtime_error(oss.str());
        }
        this->mode_auto() = autoMode;
        this->update_checksum();
    }
    
    uint8_t mode_auto() const {
        return *reinterpret_cast<const uint8_t*>(this->payload());
    }
    uint8_t& mode_auto() {
        return *reinterpret_cast<uint8_t*>(this->payload());
    }
};

struct SetPingInterval : public Message
{
    static constexpr uint16_t MessageId = 1004;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2 + sizeof(uint16_t);

    SetPingInterval(uint16_t interval) :
        Message(MessageId, sizeof(uint16_t))
    {
        this->ping_interval() = interval;
        this->update_checksum();
    }
    
    uint16_t ping_interval() const {
        return *reinterpret_cast<const uint16_t*>(this->payload());
    }
    uint16_t& ping_interval() {
        return *reinterpret_cast<uint16_t*>(this->payload());
    }
};

struct SetGainSetting : public Message
{
    static constexpr uint16_t MessageId = 1005;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2 + sizeof(uint8_t);

    SetGainSetting(uint8_t gainSetting) :
        Message(MessageId, sizeof(uint8_t))
    {
        if(gainSetting > 6) {
            std::ostringstream oss;
            oss << "ping1d::SetGainSetting : invalid gain setting ("
                << (unsigned int)gainSetting
                << "). Shoud be [0-6].";
            throw std::runtime_error(oss.str());
        }
        this->gain_setting() = gainSetting;
        this->update_checksum();
    }
    
    uint8_t gain_setting() const {
        return *reinterpret_cast<const uint8_t*>(this->payload());
    }
    uint8_t& gain_setting() {
        return *reinterpret_cast<uint8_t*>(this->payload());
    }
};

struct SetPingEnable : public Message
{
    static constexpr uint16_t MessageId = 1006;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2 + sizeof(uint8_t);

    SetPingEnable(uint8_t pingEnable) :
        Message(MessageId, sizeof(uint8_t))
    {
        if(pingEnable > 1)
            pingEnable = 1;
        this->ping_enable() = pingEnable;
        this->update_checksum();
    }
    
    uint8_t ping_enable() const {
        return *reinterpret_cast<const uint8_t*>(this->payload());
    }
    uint8_t& ping_enable() {
        return *reinterpret_cast<uint8_t*>(this->payload());
    }
};


struct FirmwareVersion : public Message
{
    struct Version {
        uint8_t  device_type;
        uint8_t  device_model;
        uint16_t firmware_version_major;
        uint16_t firmware_version_minor;
    };

    static constexpr uint16_t MessageId = 1200;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2
                                        + sizeof(Version);

    FirmwareVersion() :
        Message(MessageId, sizeof(Version))
    {
        this->update_checksum();
    }
    
    const Version& version() const {
        return *reinterpret_cast<const Version*>(this->payload());
    }
    Version& version() {
        return *reinterpret_cast<Version*>(this->payload());
    }
};

struct DeviceId : public Message
{
    static constexpr uint16_t MessageId = 1201;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2 + sizeof(uint8_t);

    DeviceId() :
        Message(MessageId, sizeof(uint8_t))
    {
        this->update_checksum();
    }
    
    uint8_t device_id() const {
        return *reinterpret_cast<const uint8_t*>(this->payload());
    }
    uint8_t& device_id() {
        return *reinterpret_cast<uint8_t*>(this->payload());
    }
};


struct Voltage5 : public Message
{
    static constexpr uint16_t MessageId = 1202;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2 + sizeof(uint16_t);

    Voltage5() :
        Message(MessageId, sizeof(uint16_t))
    {
        this->update_checksum();
    }
    
    uint16_t voltage() const {
        return *reinterpret_cast<const uint16_t*>(this->payload());
    }
    uint16_t& voltage() {
        return *reinterpret_cast<uint16_t*>(this->payload());
    }
};

struct SpeedOfSound : public Message
{
    static constexpr uint16_t MessageId = 1203;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2 + sizeof(uint32_t);

    SpeedOfSound() :
        Message(MessageId, sizeof(uint32_t))
    {
        this->update_checksum();
    }
    
    uint32_t speed_of_sound() const {
        return *reinterpret_cast<const uint32_t*>(this->payload());
    }
    uint32_t& speed_of_sound() {
        return *reinterpret_cast<uint32_t*>(this->payload());
    }
};

struct Range : public Message
{
    static constexpr uint16_t MessageId = 1204;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2 + 2*sizeof(uint32_t);

    Range() :
        Message(MessageId, 2*sizeof(uint32_t))
    {
        this->update_checksum();
    }
    
    uint32_t min_range() const {
        return *reinterpret_cast<const uint32_t*>(this->payload());
    }
    uint32_t& min_range() {
        return *reinterpret_cast<uint32_t*>(this->payload());
    }
    uint32_t range_length() const {
        return *(reinterpret_cast<const uint32_t*>(this->payload()) + 1);
    }
    uint32_t& range_length() {
        return *(reinterpret_cast<uint32_t*>(this->payload()) + 1);
    }
};

struct ModeAuto : public Message
{
    static constexpr uint16_t MessageId = 1205;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2 + sizeof(uint8_t);

    ModeAuto() :
        Message(MessageId, sizeof(uint8_t))
    {
        this->update_checksum();
    }
    
    uint8_t mode_auto() const {
        return *reinterpret_cast<const uint8_t*>(this->payload());
    }
    uint8_t& mode_auto() {
        return *reinterpret_cast<uint8_t*>(this->payload());
    }
};

struct PingInterval : public Message
{
    static constexpr uint16_t MessageId = 1206;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2 + sizeof(uint16_t);

    PingInterval() :
        Message(MessageId, sizeof(uint16_t))
    {
        this->update_checksum();
    }
    
    uint16_t ping_interval() const {
        return *reinterpret_cast<const uint16_t*>(this->payload());
    }
    uint16_t& ping_interval() {
        return *reinterpret_cast<uint16_t*>(this->payload());
    }
};

struct GainSetting : public Message
{
    static constexpr uint16_t MessageId = 1207;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2 + sizeof(uint8_t);

    GainSetting() :
        Message(MessageId, sizeof(uint8_t))
    {
        this->update_checksum();
    }
    
    uint8_t gain_setting() const {
        return *reinterpret_cast<const uint8_t*>(this->payload());
    }
    uint8_t& gain_setting() {
        return *reinterpret_cast<uint8_t*>(this->payload());
    }
};

struct TransmitDuration : public Message
{
    static constexpr uint16_t MessageId = 1208;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2 + sizeof(uint16_t);

    TransmitDuration() :
        Message(MessageId, sizeof(uint16_t))
    {
        this->update_checksum();
    }
    
    uint16_t transmit_duration() const {
        return *reinterpret_cast<const uint16_t*>(this->payload());
    }
    uint16_t& transmit_duration() {
        return *reinterpret_cast<uint16_t*>(this->payload());
    }
};

struct GeneralInfo : public Message
{
    struct Info {
        uint16_t firmware_version_major;
        uint16_t firmware_version_minor;
        uint16_t voltage_5;
        uint16_t ping_interval;
        uint8_t  gain_setting;
        uint8_t  mode_auto;
    };

    static constexpr uint16_t MessageId = 1210;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2
                                        + sizeof(Info);

    GeneralInfo() :
        Message(MessageId, sizeof(Info))
    {
        this->update_checksum();
    }
    
    const Info& info() const {
        return *reinterpret_cast<const Info*>(this->payload());
    }
    Info& info() {
        return *reinterpret_cast<Info*>(this->payload());
    }
};

struct DistanceSimple : public Message
{
    static constexpr uint16_t MessageId = 1211;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2
                                        + sizeof(uint32_t) + sizeof(uint8_t);

    DistanceSimple() :
        Message(MessageId, sizeof(uint32_t) + sizeof(uint8_t))
    {
        this->update_checksum();
    }
    
    const uint32_t& distance() const {
        return *reinterpret_cast<const uint32_t*>(this->payload());
    }
    uint32_t& distance() {
        return *reinterpret_cast<uint32_t*>(this->payload());
    }
    
    const uint8_t& confidence() const {
        return *reinterpret_cast<const uint8_t*>((&this->distance()) + 1);
    }
    uint8_t& confidence() {
        return *reinterpret_cast<uint8_t*>((&this->distance()) + 1);
    }
};

struct PingInfo {
    uint32_t distance;
    uint16_t confidence;
    uint16_t transmit_duration;
    uint32_t ping_number;
    uint32_t min_range;
    uint32_t range_length;
    uint32_t gain_setting;
};


struct Distance : public Message
{
    static constexpr uint16_t MessageId = 1212;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2
                                        + sizeof(PingInfo);

    Distance() :
        Message(MessageId, sizeof(PingInfo))
    {
        this->update_checksum();
    }
    
    const PingInfo& info() const {
        return *reinterpret_cast<const PingInfo*>(this->payload());
    }
    PingInfo& info() {
        return *reinterpret_cast<PingInfo*>(this->payload());
    }

    uint32_t distance()          const { return this->info().distance;          }
    uint16_t confidence()        const { return this->info().confidence;        }
    uint16_t transmit_duration() const { return this->info().transmit_duration; }
    uint32_t ping_number()       const { return this->info().ping_number;       }
    uint32_t min_range()         const { return this->info().min_range;         }
    uint32_t range_length()      const { return this->info().range_length;      }
    uint32_t gain_setting()      const { return this->info().gain_setting;      }
};

struct ProcessorTemperature : public Message
{
    static constexpr uint16_t MessageId = 1213;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2 + sizeof(uint16_t);

    ProcessorTemperature() :
        Message(MessageId, sizeof(uint16_t))
    {
        this->update_checksum();
    }
    
    uint16_t processor_temperature() const {
        return *reinterpret_cast<const uint16_t*>(this->payload());
    }
    uint16_t& processor_temperature() {
        return *reinterpret_cast<uint16_t*>(this->payload());
    }
};

struct PCBTemperature : public Message
{
    static constexpr uint16_t MessageId = 1214;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2 + sizeof(uint16_t);

    PCBTemperature() :
        Message(MessageId, sizeof(uint16_t))
    {
        this->update_checksum();
    }
    
    uint16_t pcb_temperature() const {
        return *reinterpret_cast<const uint16_t*>(this->payload());
    }
    uint16_t& pcb_temperature() {
        return *reinterpret_cast<uint16_t*>(this->payload());
    }
};

struct PingEnable : public Message
{
    static constexpr uint16_t MessageId = 1006;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2 + sizeof(uint8_t);

    PingEnable() :
        Message(MessageId, sizeof(uint8_t))
    {
        this->update_checksum();
    }
    
    uint8_t ping_enable() const {
        return *reinterpret_cast<const uint8_t*>(this->payload());
    }
    uint8_t& ping_enable() {
        return *reinterpret_cast<uint8_t*>(this->payload());
    }
};

struct Profile : public Message
{
    struct Metadata : PingInfo {
        uint16_t profile_data_length;
    };

    static constexpr uint16_t MessageId = 1300;
    static constexpr int      FixedSize =   -1;

    Profile() :
        Message(MessageId, sizeof(Metadata))
    {
        this->update_checksum();
    }

    const PingInfo& ping_Info() const {
        return *reinterpret_cast<const PingInfo*>(this->payload());
    }
    PingInfo& ping_Info() {
        return *reinterpret_cast<PingInfo*>(this->payload());
    }
    const Metadata& metadata() const {
        return *reinterpret_cast<const Metadata*>(this->payload());
    }
    Metadata& metadata() {
        return *reinterpret_cast<Metadata*>(this->payload());
    }
    const uint8_t* data() const {
        return this->payload() + sizeof(Metadata);
    }
    uint8_t* data() {
        return this->payload() + sizeof(Metadata);
    }
};


struct GotoBootloader : public Message
{
    static constexpr uint16_t MessageId = 1100;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2;

    GotoBootloader() :
        Message(MessageId, 0)
    {
        this->update_checksum();
    }
};

struct ContinuousStart : public Message
{
    static constexpr uint16_t MessageId = 1400;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2
                                        + sizeof(uint16_t);

    ContinuousStart(uint16_t msgId) :
        Message(MessageId, sizeof(uint16_t))
    {
        this->message_id() = msgId;
        this->update_checksum();
    }
    
    uint16_t message_id() const {
        return *reinterpret_cast<const uint16_t*>(this->payload());
    }
    uint16_t& message_id() {
        return *reinterpret_cast<uint16_t*>(this->payload());
    }
};

struct ContinuousStop : public Message
{
    static constexpr uint16_t MessageId = 1401;
    static constexpr int      FixedSize = sizeof(MessageHeader) + 2
                                        + sizeof(uint16_t);

    ContinuousStop(uint16_t msgId) :
        Message(MessageId, sizeof(uint16_t))
    {
        this->message_id() = msgId;
        this->update_checksum();
    }
    
    uint16_t message_id() const {
        return *reinterpret_cast<const uint16_t*>(this->payload());
    }
    uint16_t& message_id() {
        return *reinterpret_cast<uint16_t*>(this->payload());
    }
};

#pragma pack(pop)

} //namespace ping360
} //namespace ping_protocol

#endif //_DEF_PING_PROTOCOL_MESSAGES_PING360_MESSAGES_H_
