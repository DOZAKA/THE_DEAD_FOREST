#include "PacketProcess.h"
#include "PacketClass.h"
#include "Network.h"
#include "GameManager.hpp"
#include "EntityHuman.hpp"
#include "GameWorld.hpp"
#include "Camera2D.hpp"
#include <memory>

using namespace cocos2d;

namespace realtrick
{
    namespace network
    {
        bool  PacketProcess::_isNetworkReady  = false;
        GameManager* PacketProcess::_gameMgr = nullptr;
        
        void PacketProcess::registSubPacketFunc()
        {
            
#define INSERT_PACKET_PROCESS(type)		_runFuncTable.insert(std::make_pair(PacketType::E_##type, &PacketProcess::type))
            
            INSERT_PACKET_PROCESS(S_REQ_HEARTBEAT);
            
            INSERT_PACKET_PROCESS(S_NOTIFY_FIXED_UPDATE_BUNCH);
            
            INSERT_PACKET_PROCESS(S_NOTIFY_STARTPOINT);
            INSERT_PACKET_PROCESS(S_BROADCAST_STARTPOINT);
            
            INSERT_PACKET_PROCESS(S_BROADCAST_JOYSTICK_MOVE_KEYDOWN);
            INSERT_PACKET_PROCESS(S_BROADCAST_JOYSTICK_MOVE_KEYUP);
            
            INSERT_PACKET_PROCESS(S_BROADCAST_JOYSTICK_DOUBLE_MOVE_KEYDOWN);
            INSERT_PACKET_PROCESS(S_BROADCAST_JOYSTICK_DOUBLE_MOVE_KEYUP);
            
            INSERT_PACKET_PROCESS(S_BROADCAST_JOYSTICK_MOVING_CHANGE);
            
            INSERT_PACKET_PROCESS(S_BROADCAST_BEZEL_MOVE_KEYDOWN);

            INSERT_PACKET_PROCESS(S_NOTIFY_GAMESTART);
            
            
            
        }
        
        PacketProcess::PacketProcess(GameManager* gameMgr)
        {
            _gameMgr = gameMgr;
            registSubPacketFunc();
        }
        
        void PacketProcess::packetExecute(Packet* packet)
        {
            RunFunc runFunction = _runFuncTable.at(packet->type());
            runFunction(packet);
        }
        
        void PacketProcess::S_REQ_HEARTBEAT(Packet* rowPacket)
        {
            PK_C_ANS_HEARTBEAT packet;
            
            Network::getInstance().sendPacket(&packet);
            
            
        }
       
        void PacketProcess::S_NOTIFY_FIXED_UPDATE_BUNCH(Packet* rowPacket)
        {
            PK_S_NOTIFY_FIXED_UPDATE_BUNCH* packet = (PK_S_NOTIFY_FIXED_UPDATE_BUNCH*)rowPacket;
            
            
            log("PK_S_NOTIFY_FIXED_UPDATE :  %lu", sizeof(PK_S_NOTIFY_FIXED_UPDATE));
            
        
            auto a = packet->bunch;
            for(int i = 0 ; i < a.size() ; ++i)
            {
                S_NOTIFY_FIXED_UPDATE(a[i]);
            }

            delete packet;
        }
        
        void PacketProcess::S_NOTIFY_FIXED_UPDATE(PK_S_NOTIFY_FIXED_UPDATE rowPacket)
        {
            
            EntityBase* ret = _gameMgr->getEntityFromID((int)rowPacket.validID);
            if (ret ==nullptr || ret->getEntityType() != EntityType::ENTITY_HUMAN ) return;
            
            
            EntityHuman* player = (EntityHuman*)ret;
            
            log("S_NOTIFY_FIXED_UPDATE %f %f", rowPacket.position.x, rowPacket.position.y);
            player->setWorldPosition(rowPacket.position);
            
            //_gameMgr->getGameWorld()->getGameCamera()->setCameraPos(rowPacket.position);
        }
        
        
        void PacketProcess::S_NOTIFY_STARTPOINT(Packet* rowPacket)
        {
            PK_S_NOTIFY_STARTPOINT* notifyPacket = (PK_S_NOTIFY_STARTPOINT*)rowPacket;
            
            EntityHuman* human = EntityHuman::create(_gameMgr);
            
            human->setWorldPosition(notifyPacket->position);
            
            
            _gameMgr->registEntity(human, notifyPacket->validID, Z_ORDER_HUMAN);
            _gameMgr->getGameWorld()->setPlayerPtr(human);
            _gameMgr->setPlayer(human);
           
            human->setVisibleCrossHair(true);
            _gameMgr->getGameWorld()->displayGame();
            
            
            log("player position: %f %f", human->getPosition().x, human->getPosition().y);
            
            delete notifyPacket;
            
        }
        void PacketProcess::S_BROADCAST_STARTPOINT(Packet* rowPacket)
        {
            PK_S_BROADCAST_STARTPOINT* broadcastPacket = (PK_S_BROADCAST_STARTPOINT*)rowPacket;
            
            EntityHuman* myPlayer = _gameMgr->getPlayerPtr();
            
            
            
            if (myPlayer->getTag() == broadcastPacket->validID) return;
            
            EntityHuman* human = EntityHuman::create(_gameMgr);
            
            
            human->setWorldPosition(broadcastPacket->position);

            _gameMgr->registEntity(human, broadcastPacket->validID, Z_ORDER_HUMAN);
            
            
           
            delete broadcastPacket;
            
        }
        void PacketProcess::S_BROADCAST_JOYSTICK_MOVE_KEYDOWN(Packet* rowPacket)
        {
            PK_S_BROADCAST_JOYSTICK_MOVE_KEYDOWN* broadcastPacket = (PK_S_BROADCAST_JOYSTICK_MOVE_KEYDOWN*)rowPacket;
            
            EntityBase* ret = _gameMgr->getEntityFromID((int)broadcastPacket->validID);
           if (ret ==nullptr || ret->getEntityType() != EntityType::ENTITY_HUMAN ) return;
            
            
            EntityHuman* player = (EntityHuman*)ret;
            
            player->setMoving(broadcastPacket->moving);
            
            player->setInputMask(JoystickMessageTypes::MOVE);
            
            
            delete broadcastPacket;
        }
        void PacketProcess::S_BROADCAST_JOYSTICK_MOVE_KEYUP(Packet* rowPacket)
        {
            PK_S_BROADCAST_JOYSTICK_MOVE_KEYUP* broadcastPacket = (PK_S_BROADCAST_JOYSTICK_MOVE_KEYUP*)rowPacket;
            
            EntityBase* ret = _gameMgr->getEntityFromID((int)broadcastPacket->validID);
            if (ret ==nullptr || ret->getEntityType() != EntityType::ENTITY_HUMAN ) return;
            
            EntityHuman* player = (EntityHuman*)ret;
            
            //player->setPosition(broadcastPacket->position);
            
             player->removeInputMask(JoystickMessageTypes::MOVE);
            delete broadcastPacket;
        }
        
        
        void PacketProcess::S_BROADCAST_JOYSTICK_DOUBLE_MOVE_KEYDOWN(Packet* rowPacket)
        {
            PK_S_BROADCAST_JOYSTICK_DOUBLE_MOVE_KEYDOWN* broadcastPacket = (PK_S_BROADCAST_JOYSTICK_DOUBLE_MOVE_KEYDOWN*)rowPacket;
            
            EntityBase* ret = _gameMgr->getEntityFromID((int)broadcastPacket->validID);
            if (ret ==nullptr || ret->getEntityType() != EntityType::ENTITY_HUMAN ) return;
            
            
            EntityHuman* player = (EntityHuman*)ret;
            
            player->setMoving(broadcastPacket->moving);
            player->setTargetHeading(broadcastPacket->moving);
            
            player->setInputMask(JoystickMessageTypes::RUN);
            
            
            delete broadcastPacket;
        }
        void PacketProcess::S_BROADCAST_JOYSTICK_DOUBLE_MOVE_KEYUP(Packet* rowPacket)
        {
            PK_S_BROADCAST_JOYSTICK_DOUBLE_MOVE_KEYUP* broadcastPacket = (PK_S_BROADCAST_JOYSTICK_DOUBLE_MOVE_KEYUP*)rowPacket;
            
            EntityBase* ret = _gameMgr->getEntityFromID((int)broadcastPacket->validID);
            if (ret ==nullptr || ret->getEntityType() != EntityType::ENTITY_HUMAN ) return;
            
            EntityHuman* player = (EntityHuman*)ret;
            
            //player->setPosition(broadcastPacket->position);
            
            player->removeInputMask(JoystickMessageTypes::RUN);
            
            
            delete broadcastPacket;
        }
        
        
        void PacketProcess::S_BROADCAST_JOYSTICK_MOVING_CHANGE(Packet* rowPacket)
        {
            PK_S_BROADCAST_JOYSTICK_MOVING_CHANGE* broadcastPacket = (PK_S_BROADCAST_JOYSTICK_MOVING_CHANGE*)rowPacket;
            
            EntityBase* ret = _gameMgr->getEntityFromID((int)broadcastPacket->validID);
            if (ret ==nullptr || ret->getEntityType() != EntityType::ENTITY_HUMAN ) return;
            
            EntityHuman* player = (EntityHuman*)ret;
            
            player->setMoving(broadcastPacket->moving);
            player->setTargetHeading(broadcastPacket->heading);
            
            delete broadcastPacket;
        }
        
        void PacketProcess::S_BROADCAST_BEZEL_MOVE_KEYDOWN(Packet* rowPacket)
        {
            PK_S_BROADCAST_BEZEL_MOVE_KEYDOWN* broadcastPacket = (PK_S_BROADCAST_BEZEL_MOVE_KEYDOWN*)rowPacket;
            
            EntityBase* ret = _gameMgr->getEntityFromID((int)broadcastPacket->validID);
            
            if (ret ==nullptr || ret->getEntityType() != EntityType::ENTITY_HUMAN ) return;
            
            EntityHuman* player = (EntityHuman*)ret;
            
            player->setTargetHeading(broadcastPacket->heading);
            
        }
        
        void PacketProcess::S_NOTIFY_GAMESTART(Packet* rowPacket)
        {
             _isNetworkReady = true;
            
        }
        
        
        
    }
}
