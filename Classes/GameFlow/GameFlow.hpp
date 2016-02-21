//
//  GameFlow.hpp
//  TheDeadForest
//
//  Created by LSH on 2016. 2. 20..
//
//

#pragma once


#include <memory>

#include "PacketProcess.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "JoystickEx.hpp"

namespace realtrick
{
    class GameWorld;
    class JoystickEx;
    class CircularBezel;
    class WeaponStatusEx;
    class EntityHuman;
    
    class GameFlow
    {
        
    public:
        
        GameFlow(GameWorld* world) : _gameWorld(world)
        {}
        
        virtual ~GameFlow() = default;
    
        virtual void loadGameData() = 0;
        
        virtual std::function<void(cocos2d::Ref*, const cocos2d::Vec2&, const JoystickEx::ClickEventType&)> getMoveJoystickCallback() = 0;
        
        virtual std::function<void(cocos2d::Ref*, const cocos2d::Vec2&)> getBelzelCallback() = 0;
        
        virtual std::function<void(cocos2d::Ref*, const cocos2d::ui::Widget::TouchEventType)> getAttackJoystickCallback() = 0;

        virtual void packetExecute() {};
        
    protected:
        
        GameWorld*                                  _gameWorld;
        
        EntityHuman*                                _player;
        
        std::shared_ptr<network::PacketProcess>     _packetProcess;
        
    };
}









