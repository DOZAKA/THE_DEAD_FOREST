#pragma once
#include "packetHeader.h"
#include "packetClass.h"


namespace realtrick
{
    namespace network
    
    {
        class PacketFactory : public Singleton<PacketFactory>
        {
            friend class Singleton<PacketFactory>;
        public:
            Packet* getPacket(PacketType packetType)
            {
                switch(packetType){
                    case PacketType::E_C_REQ_EXIT:    return new PK_C_REQ_EXIT();
                    case PacketType::E_S_ANS_EXIT:    return new PK_S_ANS_EXIT();
                    case PacketType::E_I_NOTIFY_TERMINAL:    return new PK_I_NOTIFY_TERMINAL();
                    case PacketType::E_S_REQ_HEARTBEAT:    return new PK_S_REQ_HEARTBEAT();
                    case PacketType::E_C_ANS_HEARTBEAT:    return new PK_C_ANS_HEARTBEAT();
                    case PacketType::E_S_NOTIFY_FIXED_UPDATE:    return new PK_S_NOTIFY_FIXED_UPDATE();
                    case PacketType::E_S_NOTIFY_FIXED_UPDATE_BUNCH:    return new PK_S_NOTIFY_FIXED_UPDATE_BUNCH();
                    case PacketType::E_C_REQ_REGIST:    return new PK_C_REQ_REGIST();
                    case PacketType::E_S_NOTIFY_STARTPOINT:    return new PK_S_NOTIFY_STARTPOINT();
                    case PacketType::E_S_BROADCAST_STARTPOINT:    return new PK_S_BROADCAST_STARTPOINT();
                    case PacketType::E_S_NOTIFY_GAMESTART:    return new PK_S_NOTIFY_GAMESTART();
                    case PacketType::E_C_REQ_JOYSTICK_MOVE_KEYDOWN:    return new PK_C_REQ_JOYSTICK_MOVE_KEYDOWN();
                    case PacketType::E_S_BROADCAST_JOYSTICK_MOVE_KEYDOWN:    return new PK_S_BROADCAST_JOYSTICK_MOVE_KEYDOWN();
                    case PacketType::E_C_REQ_JOYSTICK_MOVE_KEYUP:    return new PK_C_REQ_JOYSTICK_MOVE_KEYUP();
                    case PacketType::E_S_BROADCAST_JOYSTICK_MOVE_KEYUP:    return new PK_S_BROADCAST_JOYSTICK_MOVE_KEYUP();
                    case PacketType::E_C_REQ_JOYSTICK_DOUBLE_MOVE_KEYDOWN:    return new PK_C_REQ_JOYSTICK_DOUBLE_MOVE_KEYDOWN();
                    case PacketType::E_S_BROADCAST_JOYSTICK_DOUBLE_MOVE_KEYDOWN:    return new PK_S_BROADCAST_JOYSTICK_DOUBLE_MOVE_KEYDOWN();
                    case PacketType::E_C_REQ_JOYSTICK_DOUBLE_MOVE_KEYUP:    return new PK_C_REQ_JOYSTICK_DOUBLE_MOVE_KEYUP();
                    case PacketType::E_S_BROADCAST_JOYSTICK_DOUBLE_MOVE_KEYUP:    return new PK_S_BROADCAST_JOYSTICK_DOUBLE_MOVE_KEYUP();
                    case PacketType::E_C_REQ_JOYSTICK_MOVING_CHANGE:    return new PK_C_REQ_JOYSTICK_MOVING_CHANGE();
                    case PacketType::E_S_BROADCAST_JOYSTICK_MOVING_CHANGE:    return new PK_S_BROADCAST_JOYSTICK_MOVING_CHANGE();
                    case PacketType::E_C_REQ_BEZEL_MOVE_KEYDOWN:    return new PK_C_REQ_BEZEL_MOVE_KEYDOWN();
                    case PacketType::E_S_BROADCAST_BEZEL_MOVE_KEYDOWN:    return new PK_S_BROADCAST_BEZEL_MOVE_KEYDOWN();
                }
                return nullptr;
            }
        };
    }
}