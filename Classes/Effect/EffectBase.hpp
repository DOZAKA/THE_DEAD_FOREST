//
//  EffectBase.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 2. 8..
//
//

#pragma once

#include "cocos2d.h"

namespace realtrick
{
    
    class EffectBase : public cocos2d::Ref
    {
        
    public:
        
        cocos2d::GLProgramState* getGLProgramState() const { return _glProgramState; }
        virtual void prepareForRender(cocos2d::Sprite *sprite);

    protected:
        
        bool initGLProgramState(const std::string &fragmentFilename);
        
        EffectBase();
        
        virtual ~EffectBase();
        
        cocos2d::GLProgramState* _glProgramState;
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
        std::string _fragSource;
        cocos2d::EventListenerCustom* _backgroundListener;
#endif
        
    };
    
};









