//
//  AnimatedButton.cpp
//  TheDeadForest-v2
//
//  Created by mac on 2016. 2. 21..
//
//

#include "AnimatedButton.hpp"

namespace realtrick
{
    namespace userinterface
    {
    
        using namespace cocos2d;
        
        AnimatedButton::AnimatedButton() :
        _currFrame(nullptr),
        _animInterval(0.0f),
        _isActive(false)
        {}
        
        
        AnimatedButton::~AnimatedButton()
        {
        }
        
        
        AnimatedButton* AnimatedButton::create(const char* normal, const char* selected, cocos2d::ui::Widget::TextureResType type)
        {
            AnimatedButton* ret = new (std::nothrow) AnimatedButton();
            if ( ret && ret->init(normal, selected, type) )
            {
                ret->autorelease();
                return ret;
            }
            CC_SAFE_DELETE(ret);
            return nullptr;
        }
        
        
        bool AnimatedButton::init(const char* normal, const char* selected, cocos2d::ui::Widget::TextureResType type)
        {
            if ( !Widget::init() )
                return false;
            
            loadTextures(normal, selected, "", type);
            
            _currFrame = Sprite::create();
            _currFrame->setPosition(Vec2(getContentSize() / 2.0f));
            addChild(_currFrame);
            
            return true;
        }
        
    }
}









