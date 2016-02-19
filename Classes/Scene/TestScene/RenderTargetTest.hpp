//
//  RenderTargetTest.hpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 12. 6..
//
//


#pragma once

#include "cocos2d.h"
#include "CocosGUI.h"

#include "EffectSprite.hpp"

namespace realtrick
{
    
    class RenderTargetTest : public cocos2d::Layer
    {
        
    public:
        
        virtual ~RenderTargetTest();
        static cocos2d::Scene* createScene();
        virtual bool init() override;
        CREATE_FUNC(RenderTargetTest);
        virtual void update(float dt) override;
        virtual void onEnter() override;
        
    private:
        
        cocos2d::RenderTexture*             _rt;
        cocos2d::Sprite*                    _obj;
        cocos2d::Size                       _winSize;
        
    };
    
}