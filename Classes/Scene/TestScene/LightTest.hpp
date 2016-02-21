//
//  LightTest.hpp
//  TheDeadForest
//
//  Created by 남준현 on 2016. 2. 9..
//
//


#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"

namespace realtrick
{
    
    
    class LightTest : public cocos2d::LayerColor
    {
        
    public:
        
        virtual ~LightTest();
        
        static cocos2d::Scene* createScene();
        virtual bool init() override;
        CREATE_FUNC(LightTest);
        virtual void update(float dt) override;
        
    private:
        
        cocos2d::Size                           _winSize;
        
    };
    
}
