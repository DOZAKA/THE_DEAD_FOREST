#pragma once

#include "PacketClass.h"
#include "cocos2d.h"
#include <unordered_map>

namespace std
{
    template<>
    struct hash< realtrick::network::PacketType>
    {
        typedef realtrick::network::PacketType argument_type;
        typedef std::underlying_type< argument_type >::type underlying_type;
        typedef std::hash< underlying_type >::result_type result_type;
        result_type operator()( const argument_type& arg ) const
        {
            std::hash< underlying_type > hasher;
            return hasher( static_cast< underlying_type >( arg ) );
        }
    };
}

namespace realtrick
{
    
    class GameManager;
    
    namespace network
    {
        
        class PacketProcess
        {
            
            using RunFunc = void(*)(Packet* rowPacket);
            std::unordered_map<PacketType, RunFunc> _runFuncTable;
            
        public:
            
            PacketProcess(GameManager* gameMgr);
            static void setNode(cocos2d::Node* n) {_node = n;}
            void registSubPacketFunc();
            void packetExecute(Packet* packet);
            
            static void S_REQ_HEARTBEAT(Packet* rowPacket);
            static void S_NOTIFY_FIXED_UPDATE_BUNCH(Packet* rowPacket);
            static void S_NOTIFY_FIXED_UPDATE(PK_S_NOTIFY_FIXED_UPDATE rowPacket);
            
            static void S_NOTIFY_STARTPOINT(Packet* rowPacket);
            static void S_BROADCAST_STARTPOINT(Packet* rowPacket);
            
            static void S_BROADCAST_JOYSTICK_MOVE_KEYDOWN(Packet* rowPacket);
            static void S_BROADCAST_JOYSTICK_MOVE_KEYUP(Packet* rowPacket);
            
            static void S_BROADCAST_JOYSTICK_DOUBLE_MOVE_KEYDOWN(Packet* rowPacket);
            static void S_BROADCAST_JOYSTICK_DOUBLE_MOVE_KEYUP(Packet* rowPacket);
            static void S_BROADCAST_JOYSTICK_MOVING_CHANGE(Packet* rowPacket);
            static void S_BROADCAST_BEZEL_MOVE_KEYDOWN(Packet* rowPacket);
            
        private:
            
            static GameManager* _gameMgr;
            static cocos2d::Node* _node;
            
        };
    }
}
