//
//  NetworkGameFlow.cpp
//  TheDeadForest
//
//  Created by LSH on 2016. 2. 20..
//
//

#include "NetworkGameFlow.hpp"
#include "GameWorld.hpp"
#include "GameManager.hpp"
#include "JoystickEx.hpp"
#include "CircularBezel.hpp"
#include "WeaponStatusEx.hpp"

#include "Network.h"
#include "PacketQueue.h"
#include "PacketClass.h"
#include "PacketProcess.h"

namespace realtrick
{
    
    using namespace network;
    
    void NetworkGameFlow::loadGameData()
    {
        GameManager* gameMgr = _gameWorld->getGameManager();
        gameMgr->loadGameMapWithNetwork("jsonData.txt");
        
        _packetProcess = std::make_shared<PacketProcess>(gameMgr);
        
        while(!(Network::getInstance().isConnection()));
        
        PK_C_REQ_REGIST reqPacket;
        reqPacket.pid = ClientGenerator::getInstance().id();
        reqPacket.roomID = 1;
        
        Network::getInstance().sendPacket(&reqPacket);
        
        while( !_packetProcess->isNetworkReady() )
        {
            network::Packet* packet;
            if(PacketQueue::getInstance().pop(packet))
            {
                _packetProcess->packetExecute(packet);
            }
        }
        
        // 네트워크 로딩이 끝난 시점
        _player = _gameWorld->getPlayerPtr();
        _gameWorld->displayGame();
    }
    
    
    std::function<void(cocos2d::Ref*, const cocos2d::Vec2&, const JoystickEx::ClickEventType&)> NetworkGameFlow::getMoveJoystickCallback()
    {
        auto ret = [&, this](cocos2d::Ref* ref, cocos2d::Vec2 dir, JoystickEx::ClickEventType type){
            
            switch ( type )
            {
                case JoystickEx::ClickEventType::BEGAN:
                {
                    PK_C_REQ_JOYSTICK_MOVE_KEYDOWN packet;
                    packet.validID = _player->getTag();
                    packet.moving = dir;
                    Network::getInstance().sendPacket(&packet);
                    log("normal click begin to (x, y) %f %f", dir.x, dir.y );
                    break;
                }
                case JoystickEx::ClickEventType::ENDED:
                {
                    PK_C_REQ_JOYSTICK_MOVE_KEYUP packet;
                    packet.validID = _player->getTag();
                    packet.position = _player->getPosition();
                    Network::getInstance().sendPacket(&packet);
                    log("normal click ended to (x, y) %f %f", dir.x, dir.y );
                    break;
                }
                case JoystickEx::ClickEventType::DOUBLE_CLICK_BEGAN:
                {
                    PK_C_REQ_JOYSTICK_DOUBLE_MOVE_KEYDOWN packet;
                    packet.validID = _player->getTag();
                    packet.moving = dir;
                    Network::getInstance().sendPacket(&packet);
                    log("double click began to (x, y) %f %f", dir.x, dir.y );
                    break;
                }
                case JoystickEx::ClickEventType::DOUBLE_CLICK_ENDED:
                {
                    PK_C_REQ_JOYSTICK_DOUBLE_MOVE_KEYUP packet;
                    packet.validID = _player->getTag();
                    packet.position = _player->getPosition();
                    Network::getInstance().sendPacket(&packet);
                    log("double click ended to (x, y) %f %f", dir.x, dir.y );
                    break;
                }
                case JoystickEx::ClickEventType::MOVED:
                {
                    JoystickEx* self = (JoystickEx*)ref;
                    PK_C_REQ_JOYSTICK_MOVING_CHANGE packet;
                    
                    if( self->isDoubleClicked())
                    {
                        
                        log("double Run");
                        packet.validID = _player->getTag();
                        packet.heading = dir;
                        packet.moving = dir;
                    }
                    else
                    {
                        log("Run");
                        packet.validID = _player->getTag();
                        packet.heading = _player->getHeading();
                        packet.moving = dir;
                        
                        
                        // .. walk
                    }
                    
                    Network::getInstance().sendPacket(&packet);
                    log("moveed to (x, y) %f %f", dir.x, dir.y );
                    break;
                }
                    
                default: break;
            }
        };
        
        return ret;
    }
    
    
    std::function<void(cocos2d::Ref*, const cocos2d::Vec2&)> NetworkGameFlow::getBelzelCallback()
    {
        auto ret = [&, this](Ref* ref, const Vec2& dir){
            
            PK_C_REQ_BEZEL_MOVE_KEYDOWN packet;
            packet.validID = _player->getTag();
            packet.heading = dir;
            Network::getInstance().sendPacket(&packet);
            
        };
        
        return ret;
    }
    
    
    std::function<void(cocos2d::Ref*, const cocos2d::ui::Widget::TouchEventType)> NetworkGameFlow::getAttackJoystickCallback()
    {
        auto ret = [&, this](Ref* ref, ui::Widget::TouchEventType type){
            
            switch (type)
            {
                case ui::Widget::TouchEventType::BEGAN:
                {
                    _player->addInputMask((int)JoystickMessageTypes::ATTACK_BEGAN);
                    break;
                }
                case ui::Widget::TouchEventType::ENDED:
                {
                    _player->removeInputMask((int)JoystickMessageTypes::ATTACK_BEGAN);
                    _player->addInputMask((int)JoystickMessageTypes::ATTACK_ENDED);
                    break;
                }
                case ui::Widget::TouchEventType::CANCELED:
                {
                    _player->removeInputMask((int)JoystickMessageTypes::ATTACK_BEGAN);
                    _player->addInputMask((int)JoystickMessageTypes::ATTACK_ENDED);
                    break;
                }
                    
                default: break;
            }
            
        };
        
        return ret;
    }
    
    
    void NetworkGameFlow::packetExecute()
    {
        network::Packet* packet;
        if(network::PacketQueue::getInstance().pop(packet))
        {
            _packetProcess->packetExecute(packet);
        }
    }
    
}









