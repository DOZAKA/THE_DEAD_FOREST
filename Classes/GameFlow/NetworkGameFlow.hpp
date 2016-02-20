//
//  NetworkGameFlow.hpp
//  TheDeadForest
//
//  Created by LSH on 2016. 2. 20..
//
//

#pragma once

#include "GameFlow.hpp"

namespace realtrick
{
    
    class NetworkGameFlow : public GameFlow
    {
        
    public:
        
        NetworkGameFlow(GameWorld* world) : GameFlow(world)
        {}
        
        virtual ~NetworkGameFlow() = default;
        
        virtual void loadGameData() override;
        
        virtual std::function<void(cocos2d::Ref*, const cocos2d::Vec2&, const JoystickEx::ClickEventType&)> getMoveJoystickCallback() override;
        
        virtual std::function<void(cocos2d::Ref*, const cocos2d::Vec2&)> getBelzelCallback() override;
        
        virtual std::function<void(cocos2d::Ref*, const cocos2d::ui::Widget::TouchEventType)> getAttackJoystickCallback() override;

        virtual void packetExecute() override;
    
    };
    
}









