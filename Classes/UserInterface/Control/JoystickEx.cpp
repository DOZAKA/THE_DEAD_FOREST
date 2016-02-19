//
//  JoystickEx.cpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 20..
//
//

#include "JoystickEx.hpp"

using namespace cocos2d;
using namespace cocos2d::ui;

namespace realtrick
{
    
    JoystickEx::JoystickEx() :
    _direction(Vec2::ZERO),
    _maxMovableRadius(50.0f),
    _joystick(nullptr),
    _isTouched(false),
    _isDoubleClicked(false),
    _isEnableDoubleClick(true),
    _firstTouchedTime(std::chrono::system_clock::now().time_since_epoch()),
    _rotationType(RotationType::ROTATION_ALL),
    _oldDegree(0),
    _pad(nullptr),
    _enablePad(false),
    _doubleClickCallback(nullptr),
    _changedDirectionCallback(nullptr),
    _clickCallback(nullptr)
    {
    }
    
    JoystickEx::~JoystickEx()
    {
    }
    
    
    JoystickEx* JoystickEx::create(const char* joystickNormalImagePath,
                                   const char* joystickSelectedImagePath,
                                   cocos2d::ui::Widget::TextureResType type)
    {
        JoystickEx* ret = new (std::nothrow)JoystickEx();
        if( ret && ret->init(joystickNormalImagePath, joystickSelectedImagePath, type) )
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    
    bool JoystickEx::init(const char* joystickNormalImagePath,
                          const char* joystickSelectedImagePath,
                          cocos2d::ui::Widget::TextureResType type)
    {
        _joystick = Button::create(joystickNormalImagePath, joystickSelectedImagePath, "", type);
        _joystick->setSwallowTouches(false);
        _joystick->setOpacity(128);
        _joystick->addTouchEventListener([&, this](Ref* ref, Widget::TouchEventType type){
            
            Button* self = (Button*)ref;
            Vec2 world = _getJoystickExNodeWorldPosition();
            
            switch (type)
            {
                case Widget::TouchEventType::BEGAN:
                {
                    _isTouched = true;
                    if( _clickCallback )
                    {
                        _clickCallback(this, Widget::TouchEventType::BEGAN);
                    }
                    
                    Vec2 touch = self->getTouchBeganPosition();
                    Vec2 local = touch - world;
                    
                    float degree = _calculateDegree(local.getNormalized());
                    switch ( _rotationType )
                    {
                        case RotationType::ROTATION_4:
                        {
                            int d = (int)((degree + 45.0f) / 90.0f) * 90.0f;
                            Vec2 dir = Vec2(cosf(MATH_DEG_TO_RAD(d)), sinf(MATH_DEG_TO_RAD(d)));
                            self->stopAllActions();
                            self->runAction(EaseElasticOut::create(MoveTo::create(0.5f, _maxMovableRadius * dir)));
                            _calculateDirection(dir);
                            
                            break;
                        }
                        case RotationType::ROTATION_8:
                        {
                            int d = (int)((degree + 22.5f) / 45.0f) * 45.0f;
                            Vec2 dir = Vec2(cosf(MATH_DEG_TO_RAD(d)), sinf(MATH_DEG_TO_RAD(d)));
                            self->stopAllActions();
                            self->runAction(EaseElasticOut::create(MoveTo::create(0.5f, _maxMovableRadius * dir)));
                            _calculateDirection(dir);
                            
                            break;
                        }
                        case RotationType::ROTATION_ALL:
                        {
                            if( world.distanceSquared(touch) > _maxMovableRadius * _maxMovableRadius )
                            {
                                Vec2 dir = touch - world;
                                dir.normalize();
                                local = dir * _maxMovableRadius;
                            }
                            self->stopAllActions();
                            self->runAction(EaseElasticOut::create(MoveTo::create(0.5f, local)));
                            _calculateDirection(local);
                            
                            break;
                        }
                            
                        default: break;
                    }
                    
                    std::chrono::duration<double> offset = std::chrono::system_clock::now().time_since_epoch() - _firstTouchedTime;
                    if( offset.count() < MAX_DOUBLE_CLICK_TOLERANCE_TIME )
                    {
                        _runDoubleClickBeginEvent();
                        if ( _changedDirectionAndStatusCallback ) _changedDirectionAndStatusCallback(this, _direction, ClickEventType::DOUBLE_CLICK_BEGAN);
                    }
                    
                    if( !_isDoubleClicked )
                    {
                        _firstTouchedTime =  std::chrono::system_clock::now().time_since_epoch();
                        if ( _changedDirectionAndStatusCallback ) _changedDirectionAndStatusCallback(this, _direction, ClickEventType::BEGAN);
                    }
                    
                    
                    break;
                }
                case Widget::TouchEventType::MOVED:
                {
                    if( _clickCallback )
                    {
                        _clickCallback(this, Widget::TouchEventType::MOVED);
                    }
                    
                    Vec2 touch = self->getTouchMovePosition();
                    Vec2 local = touch - world;
                    
                    float degree = _calculateDegree(local.getNormalized());
                    switch ( _rotationType )
                    {
                        case RotationType::ROTATION_4:
                        {
                            int d = (int)((degree + 45.0f) / 90.0f) * 90.0f;
                            if( _oldDegree != d)
                            {
                                Vec2 dir = Vec2(cosf(MATH_DEG_TO_RAD(d)), sinf(MATH_DEG_TO_RAD(d)));
                                self->stopAllActions();
                                self->runAction(EaseElasticOut::create(MoveTo::create(0.5f, _maxMovableRadius * dir)));
                                _calculateDirection(dir);
                                
                                if ( _changedDirectionAndStatusCallback ) _changedDirectionAndStatusCallback(this, _direction, ClickEventType::MOVED);
                                
                            }
                            _oldDegree = d;
                            break;
                        }
                        case RotationType::ROTATION_8:
                        {
                            int d = (int)((degree + 22.5f) / 45.0f) * 45.0f;
                            if( _oldDegree != d)
                            {
                                Vec2 dir = Vec2(cosf(MATH_DEG_TO_RAD(d)), sinf(MATH_DEG_TO_RAD(d)));
                                self->stopAllActions();
                                self->runAction(EaseElasticOut::create(MoveTo::create(0.5f, _maxMovableRadius * dir)));
                                _calculateDirection(dir);
                                
                                if ( _changedDirectionAndStatusCallback ) _changedDirectionAndStatusCallback(this, _direction, ClickEventType::MOVED);
                            }
                            _oldDegree = d;
                            break;
                        }
                        case RotationType::ROTATION_ALL:
                        {
                            if( world.distanceSquared(touch) > _maxMovableRadius * _maxMovableRadius )
                            {
                                Vec2 dir = touch - world;
                                dir.normalize();
                                local = dir * _maxMovableRadius;
                            }
                            self->setPosition(local);
                            _calculateDirection(local);
                            
                            if ( _changedDirectionAndStatusCallback ) _changedDirectionAndStatusCallback(this, _direction, ClickEventType::MOVED);
                            
                            break;
                        }
                    }
                    break;
                }
                case Widget::TouchEventType::ENDED:
                {
                    if( _clickCallback )
                    {
                        _clickCallback(this, Widget::TouchEventType::ENDED);
                    }
                    
                    _isTouched = false;
                    if ( _isDoubleClicked )
                    {
                        _runDoubleClickEndEvent();
                        if ( _changedDirectionAndStatusCallback ) _changedDirectionAndStatusCallback(this, _direction, ClickEventType::DOUBLE_CLICK_ENDED);
                    }
                    else
                    {
                        if ( _changedDirectionAndStatusCallback ) _changedDirectionAndStatusCallback(this, _direction, ClickEventType::ENDED);
                    }
                    
                    self->stopAllActions();
                    self->runAction(EaseElasticOut::create(MoveTo::create(0.2f, Vec2::ZERO)));
                    _calculateDirection(Vec2::ZERO);
                    break;
                }
                case Widget::TouchEventType::CANCELED:
                {
                    if ( _clickCallback )
                    {
                        _clickCallback(this, Widget::TouchEventType::CANCELED);
                    }
                    
                    _isTouched = false;
                    if ( _isDoubleClicked )
                    {
                        _runDoubleClickEndEvent();
                        if ( _changedDirectionAndStatusCallback ) _changedDirectionAndStatusCallback(this, _direction, ClickEventType::DOUBLE_CLICK_ENDED);
                    }
                    else
                    {
                        if ( _changedDirectionAndStatusCallback ) _changedDirectionAndStatusCallback(this, _direction, ClickEventType::ENDED);
                    }

                    self->stopAllActions();
                    self->runAction(EaseElasticOut::create(MoveTo::create(0.2f, Vec2::ZERO)));
                    _calculateDirection(Vec2::ZERO);
                    break;
                }
                    
                default: break;
            }
            
        });
        
        addChild(_joystick);
        
        return true;
    }
    
    
    void JoystickEx::_runDoubleClickBeginEvent()
    {
        if ( _doubleClickCallback )
        {
            _doubleClickCallback(this, ClickEventType::BEGAN);
        }
        _isDoubleClicked = true;
        
        if( _enablePad )
        {
            _pad->stopAllActions();
            _pad->runAction(Spawn::create(TintTo::create(0.2f, 255, 255, 0),
                                          EaseElasticOut::create(ScaleTo::create(0.5f, 1.2f)),
                                          nullptr));
        }
    }
    
    
    void JoystickEx::_runDoubleClickEndEvent()
    {
        if( _doubleClickCallback )
        {
            _doubleClickCallback(this, ClickEventType::ENDED);
        }
        _isDoubleClicked = false;
        
        if( _enablePad )
        {
            _pad->stopAllActions();
            _pad->runAction(Spawn::create(TintTo::create(0.2f, 255, 255, 255),
                                          EaseElasticOut::create(ScaleTo::create(0.5f, 1.0f)),
                                          nullptr));
        }
    }
    
    
    void JoystickEx::setJoystickPad(const char* filePath, cocos2d::ui::Widget::TextureResType texResType)
    {
        _enablePad = true;
        
        if ( _pad )
        {
            _pad->removeFromParent();
        }
        
        if( texResType == ui::Widget::TextureResType::LOCAL )
        {
            _pad = Sprite::create(filePath);
        }
        else
        {
            _pad = Sprite::createWithSpriteFrameName(filePath);
        }
        
        _pad->setOpacity(64);
        addChild(_pad);
    }
    
}








