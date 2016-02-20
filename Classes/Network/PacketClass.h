#pragma once

#include "packetHeader.h"
#include "Stream.h"

namespace realtrick
{
    namespace network
    
    {
        class Packet
        {
        public:
            virtual PacketType type() = 0;
            virtual void encode(Stream& stream) { stream << (Int64)this->type(); }
            virtual void decode(Stream& stream) {}
        };
        
        class PK_C_REQ_EXIT : public Packet
        {
        public:
            PacketType type() { return PacketType::E_C_REQ_EXIT; }
        };
        
        class PK_S_ANS_EXIT : public Packet
        {
        public:
            PacketType type() { return PacketType::E_S_ANS_EXIT; }
        };
        
        class PK_I_NOTIFY_TERMINAL : public Packet
        {
        public:
            PacketType type() { return PacketType::E_I_NOTIFY_TERMINAL; }
        };
        
        class PK_S_REQ_HEARTBEAT : public Packet
        {
        public:
            PacketType type() { return PacketType::E_S_REQ_HEARTBEAT; }
        };
        
        class PK_C_ANS_HEARTBEAT : public Packet
        {
        public:
            PacketType type() { return PacketType::E_C_ANS_HEARTBEAT; }
        };
        
        class PK_S_NOTIFY_FIXED_UPDATE //: public Packet
        {
        public:
           // PacketType type() { return PacketType::E_S_NOTIFY_FIXED_UPDATE; }
            UInt32     validID;
            cocos2d::Vec2     position;
            /*
            void encode(Stream& stream) {
                stream << (Int64) this->type();
                stream << validID;
                stream << position;
            }
            
            void decode(Stream& stream){
                stream >> &validID;
                stream >> &position;
            }
             */
        };
        
        class PK_S_NOTIFY_FIXED_UPDATE_BUNCH : public Packet
        {
        public:
            PacketType type() { return PacketType::E_S_NOTIFY_FIXED_UPDATE_BUNCH; }
            std::vector<PK_S_NOTIFY_FIXED_UPDATE>     bunch;
            
            void encode(Stream& stream) {
                stream << (Int64) this->type();
                stream << bunch;
            }
            
            void decode(Stream& stream){
                stream >> &bunch;
            }
        };
        
        class PK_C_REQ_REGIST : public Packet
        {
        public:
            PacketType type() { return PacketType::E_C_REQ_REGIST; }
            UInt64     pid;
            UInt32     roomID;
            
            void encode(Stream& stream) {
                stream << (Int64) this->type();
                stream << pid;
                stream << roomID;
            }
            
            void decode(Stream& stream){
                stream >> &pid;
                stream >> &roomID;
            }
        };
        
        class PK_S_NOTIFY_STARTPOINT : public Packet
        {
        public:
            PacketType type() { return PacketType::E_S_NOTIFY_STARTPOINT; }
            UInt32     validID;
            cocos2d::Vec2     position;
            
            void encode(Stream& stream) {
                stream << (Int64) this->type();
                stream << validID;
                stream << position;
            }
            
            void decode(Stream& stream){
                stream >> &validID;
                stream >> &position;
            }
        };
        
        class PK_S_BROADCAST_STARTPOINT : public Packet
        {
        public:
            PacketType type() { return PacketType::E_S_BROADCAST_STARTPOINT; }
            UInt32     validID;
            cocos2d::Vec2     position;
            
            void encode(Stream& stream) {
                stream << (Int64) this->type();
                stream << validID;
                stream << position;
            }
            
            void decode(Stream& stream){
                stream >> &validID;
                stream >> &position;
            }
        };
        
        class PK_S_NOTIFY_GAMESTART : public Packet
        {
        public:
            PacketType type() { return PacketType::E_S_NOTIFY_GAMESTART; }
        };
        
        class PK_C_REQ_JOYSTICK_MOVE_KEYDOWN : public Packet
        {
        public:
            PacketType type() { return PacketType::E_C_REQ_JOYSTICK_MOVE_KEYDOWN; }
            UInt32     validID;
            cocos2d::Vec2     moving;
            
            void encode(Stream& stream) {
                stream << (Int64) this->type();
                stream << validID;
                stream << moving;
            }
            
            void decode(Stream& stream){
                stream >> &validID;
                stream >> &moving;
            }
        };
        
        class PK_S_BROADCAST_JOYSTICK_MOVE_KEYDOWN : public Packet
        {
        public:
            PacketType type() { return PacketType::E_S_BROADCAST_JOYSTICK_MOVE_KEYDOWN; }
            UInt32     validID;
            cocos2d::Vec2     moving;
            
            void encode(Stream& stream) {
                stream << (Int64) this->type();
                stream << validID;
                stream << moving;
            }
            
            void decode(Stream& stream){
                stream >> &validID;
                stream >> &moving;
            }
        };
        
        class PK_C_REQ_JOYSTICK_MOVE_KEYUP : public Packet
        {
        public:
            PacketType type() { return PacketType::E_C_REQ_JOYSTICK_MOVE_KEYUP; }
            UInt32     validID;
            cocos2d::Vec2     position;
            
            void encode(Stream& stream) {
                stream << (Int64) this->type();
                stream << validID;
                stream << position;
            }
            
            void decode(Stream& stream){
                stream >> &validID;
                stream >> &position;
            }
        };
        
        class PK_S_BROADCAST_JOYSTICK_MOVE_KEYUP : public Packet
        {
        public:
            PacketType type() { return PacketType::E_S_BROADCAST_JOYSTICK_MOVE_KEYUP; }
            UInt32     validID;
            cocos2d::Vec2     position;
            
            void encode(Stream& stream) {
                stream << (Int64) this->type();
                stream << validID;
                stream << position;
            }
            
            void decode(Stream& stream){
                stream >> &validID;
                stream >> &position;
            }
        };
        
        class PK_C_REQ_JOYSTICK_DOUBLE_MOVE_KEYDOWN : public Packet
        {
        public:
            PacketType type() { return PacketType::E_C_REQ_JOYSTICK_DOUBLE_MOVE_KEYDOWN; }
            UInt32     validID;
            cocos2d::Vec2     moving;
            
            void encode(Stream& stream) {
                stream << (Int64) this->type();
                stream << validID;
                stream << moving;
            }
            
            void decode(Stream& stream){
                stream >> &validID;
                stream >> &moving;
            }
        };
        
        class PK_S_BROADCAST_JOYSTICK_DOUBLE_MOVE_KEYDOWN : public Packet
        {
        public:
            PacketType type() { return PacketType::E_S_BROADCAST_JOYSTICK_DOUBLE_MOVE_KEYDOWN; }
            UInt32     validID;
            cocos2d::Vec2     moving;
            
            void encode(Stream& stream) {
                stream << (Int64) this->type();
                stream << validID;
                stream << moving;
            }
            
            void decode(Stream& stream){
                stream >> &validID;
                stream >> &moving;
            }
        };
        
        class PK_C_REQ_JOYSTICK_DOUBLE_MOVE_KEYUP : public Packet
        {
        public:
            PacketType type() { return PacketType::E_C_REQ_JOYSTICK_DOUBLE_MOVE_KEYUP; }
            UInt32     validID;
            cocos2d::Vec2     position;
            
            void encode(Stream& stream) {
                stream << (Int64) this->type();
                stream << validID;
                stream << position;
            }
            
            void decode(Stream& stream){
                stream >> &validID;
                stream >> &position;
            }
        };
        
        class PK_S_BROADCAST_JOYSTICK_DOUBLE_MOVE_KEYUP : public Packet
        {
        public:
            PacketType type() { return PacketType::E_S_BROADCAST_JOYSTICK_DOUBLE_MOVE_KEYUP; }
            UInt32     validID;
            cocos2d::Vec2     position;
            
            void encode(Stream& stream) {
                stream << (Int64) this->type();
                stream << validID;
                stream << position;
            }
            
            void decode(Stream& stream){
                stream >> &validID;
                stream >> &position;
            }
        };
        
        class PK_C_REQ_JOYSTICK_MOVING_CHANGE : public Packet
        {
        public:
            PacketType type() { return PacketType::E_C_REQ_JOYSTICK_MOVING_CHANGE; }
            UInt32     validID;
            cocos2d::Vec2     heading;
            cocos2d::Vec2     moving;
            
            void encode(Stream& stream) {
                stream << (Int64) this->type();
                stream << validID;
                stream << heading;
                stream << moving;
            }
            
            void decode(Stream& stream){
                stream >> &validID;
                stream >> &heading;
                stream >> &moving;
            }
        };
        
        class PK_S_BROADCAST_JOYSTICK_MOVING_CHANGE : public Packet
        {
        public:
            PacketType type() { return PacketType::E_S_BROADCAST_JOYSTICK_MOVING_CHANGE; }
            UInt32     validID;
            cocos2d::Vec2     heading;
            cocos2d::Vec2     moving;
            
            void encode(Stream& stream) {
                stream << (Int64) this->type();
                stream << validID;
                stream << heading;
                stream << moving;
            }
            
            void decode(Stream& stream){
                stream >> &validID;
                stream >> &heading;
                stream >> &moving;
            }
        };
        
        class PK_C_REQ_BEZEL_MOVE_KEYDOWN : public Packet
        {
        public:
            PacketType type() { return PacketType::E_C_REQ_BEZEL_MOVE_KEYDOWN; }
            UInt32     validID;
            cocos2d::Vec2     heading;
            
            void encode(Stream& stream) {
                stream << (Int64) this->type();
                stream << validID;
                stream << heading;
            }
            
            void decode(Stream& stream){
                stream >> &validID;
                stream >> &heading;
            }
        };
        
        class PK_S_BROADCAST_BEZEL_MOVE_KEYDOWN : public Packet
        {
        public:
            PacketType type() { return PacketType::E_S_BROADCAST_BEZEL_MOVE_KEYDOWN; }
            UInt32     validID;
            cocos2d::Vec2     heading;
            
            void encode(Stream& stream) {
                stream << (Int64) this->type();
                stream << validID;
                stream << heading;
            }
            
            void decode(Stream& stream){
                stream >> &validID;
                stream >> &heading;
            }
        };
        
        
    }
}