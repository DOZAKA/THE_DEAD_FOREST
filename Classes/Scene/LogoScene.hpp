//
//  LogoScene.hpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 29..
//
//

#pragma once

#include "cocos2d.h"

namespace realtrick
{
    
    class LogoScene : public cocos2d::Layer
    {
        
    public:
        
        virtual ~LogoScene();
        
        static cocos2d::Scene* createScene();
        virtual bool init() override;
        CREATE_FUNC(LogoScene);
        virtual void update(float dt) override;
        
    private:
        
        char *dummy;
        
    };
    
}