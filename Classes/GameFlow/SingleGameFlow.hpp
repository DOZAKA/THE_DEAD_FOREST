//
//  SingleGameFlow.hpp
//  TheDeadForest
//
//  Created by LSH on 2016. 2. 20..
//
//

#pragma once

#include "GameFlow.hpp"

namespace realtrick
{
    
    class SingleGameFlow : public GameFlow
    {
        
    public:
        
        SingleGameFlow(GameWorld* world) : GameFlow(world)
        {}
        
        virtual ~SingleGameFlow() = default;
        
        virtual void loadGameData() override;
        
        virtual std::function<void(cocos2d::Ref*, const cocos2d::Vec2&, const JoystickEx::ClickEventType&)> getMoveJoystickCallback() override;
        
        virtual std::function<void(cocos2d::Ref*, const cocos2d::Vec2&)> getBelzelCallback() override;
        
        virtual std::function<void(cocos2d::Ref*, const cocos2d::ui::Widget::TouchEventType)> getAttackJoystickCallback() override;
        
    };
    
}











