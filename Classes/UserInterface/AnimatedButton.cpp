//
//  AnimatedButton.cpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 24..
//
//

#include "AnimatedButton.hpp"

using namespace cocos2d;

namespace realtrick
{
    
    AnimatedButton::AnimatedButton() :
    _isShow(false),
    _spriteForAnimate(nullptr),
    _delayPerUnit(0.0f),
    _currFrame(0)
    {}
    
    
    AnimatedButton::~AnimatedButton()
    {}
    
    AnimatedButton* AnimatedButton::create(const std::string& normal, const std::string& selected, const std::vector<std::string>& frames, float delayPerUnit,
                                           cocos2d::ui::Widget::TextureResType texResType, cocos2d::ui::Widget::ccWidgetTouchCallback callback)
    {
        AnimatedButton* ret = new (std::nothrow)AnimatedButton();
        if ( ret && ret->init(normal, selected, frames, delayPerUnit, texResType, callback) )
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    bool AnimatedButton::init(const std::string& normal, const std::string& selected, const std::vector<std::string>& frames, float delayPerUnit,
                              cocos2d::ui::Widget::TextureResType texResType, cocos2d::ui::Widget::ccWidgetTouchCallback callback)
    {
        if ( !Widget::init() )
        {
            return false;
        }
        
        this->loadTextures(normal, selected, "", texResType);
        
        _spriteForAnimate = Sprite::create();
        _spriteForAnimate->setPosition(getContentSize() / 2.0f);
        _spriteForAnimate->setVisible(false);
        addChild(_spriteForAnimate);
        
        _frames = frames;
        _delayPerUnit = delayPerUnit;
        
        setOpacity(0);
        _isShow = false;
        this->setTouchEnabled(false);
        
        this->addTouchEventListener(callback);
        
        return true;
    }
    
    
    void AnimatedButton::setAnimationFrames(const std::vector<std::string>& framePaths, float delayPerUnit)
    {
        _frames.clear();
        _frames = framePaths;
        _delayPerUnit = delayPerUnit;
    }
    
    
    void AnimatedButton::show()
    {
        if ( _isShow )
            return;
        
        if( getActionManager()->getNumberOfRunningActionsInTarget(this) == 0 )
        {
            runAction(Sequence::create(CallFunc::create([&,this]()
                                                        {
                                                            _spriteForAnimate->setVisible(true);
                                                            setOpacity(0);
                                                        }),
                                       Repeat::create(Sequence::create(CallFunc::create([&, this]()
                                                                                        {
                                                                                            _spriteForAnimate->setSpriteFrame(_frames.at(_currFrame));
                                                                                            _currFrame++;
                                                                                        }),
                                                                       DelayTime::create(_delayPerUnit),
                                                                       nullptr),
                                                      (unsigned int)_frames.size()),
                                       CallFunc::create([&, this]()
                                                        {
                                                            _spriteForAnimate->setVisible(false);
                                                            setOpacity(255);
                                                            this->setTouchEnabled(true);
                                                            _isShow = true;
                                                            _currFrame = (int)_frames.size() - 1;
                                                        }),
                                       nullptr));
        }
    }
    
    
    void AnimatedButton::hide()
    {
        if ( !_isShow )
            return;
        
        if( getActionManager()->getNumberOfRunningActionsInTarget(this) == 0 )
        {
            runAction(Sequence::create(CallFunc::create([&,this]()
                                                        {
                                                            this->setTouchEnabled(false);
                                                            _spriteForAnimate->setVisible(true);
                                                            setOpacity(0);
                                                        }),
                                       Repeat::create(Sequence::create(CallFunc::create([&, this]()
                                                                                        {
                                                                                            _spriteForAnimate->setSpriteFrame(_frames.at(_currFrame));
                                                                                            _currFrame--;
                                                                                        }),
                                                                       DelayTime::create(_delayPerUnit),
                                                                       nullptr),
                                                      (unsigned int)_frames.size()),
                                       CallFunc::create([&, this]()
                                                        {
                                                            _spriteForAnimate->setVisible(false);
                                                            setOpacity(0);
                                                            _isShow = false;
                                                            _currFrame = 0;
                                                        }),
                                       nullptr));
        }
    }
    
    void AnimatedButton::forceShow()
    {
        stopAllActions();
        _currFrame = 0;
        runAction(Sequence::create(CallFunc::create([&,this]()
                                                    {
                                                        _spriteForAnimate->setVisible(true);
                                                        setOpacity(0);
                                                    }),
                                   Repeat::create(Sequence::create(CallFunc::create([&, this]()
                                                                                    {
                                                                                        _spriteForAnimate->setSpriteFrame(_frames.at(_currFrame));
                                                                                        _currFrame++;
                                                                                    }),
                                                                   DelayTime::create(_delayPerUnit),
                                                                   nullptr),
                                                  (unsigned int)_frames.size()),
                                   CallFunc::create([&, this]()
                                                    {
                                                        _spriteForAnimate->setVisible(false);
                                                        setOpacity(255);
                                                        this->setTouchEnabled(true);
                                                        _isShow = true;
                                                        _currFrame = (int)_frames.size() - 1;
                                                    }),
                                   nullptr));
    }
    
    void AnimatedButton::forceHide()
    {
        stopAllActions();
        _currFrame = (int)_frames.size() - 1;
        runAction(Sequence::create(CallFunc::create([&,this]()
                                                    {
                                                        this->setTouchEnabled(false);
                                                        _spriteForAnimate->setVisible(true);
                                                        setOpacity(0);
                                                    }),
                                   Repeat::create(Sequence::create(CallFunc::create([&, this]()
                                                                                    {
                                                                                        _spriteForAnimate->setSpriteFrame(_frames.at(_currFrame));
                                                                                        _currFrame--;
                                                                                    }),
                                                                   DelayTime::create(_delayPerUnit),
                                                                   nullptr),
                                                  (unsigned int)_frames.size()),
                                   CallFunc::create([&, this]()
                                                    {
                                                        _spriteForAnimate->setVisible(false);
                                                        setOpacity(0);
                                                        _isShow = false;
                                                        _currFrame = 0;
                                                    }),
                                   nullptr));
    }
    
}







