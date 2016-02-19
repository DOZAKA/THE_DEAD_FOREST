//
//  JoystickEx.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 20..
//
//

#pragma once

#include <chrono>
#include <functional>

#include "cocos2d.h"
#include "CocosGUI.h"

#define MAX_DOUBLE_CLICK_TOLERANCE_TIME                 0.25f

namespace realtrick
{
    
    class JoystickEx : public cocos2d::Node
    {
        
    public:
        
        enum class RotationType { ROTATION_8, ROTATION_4, ROTATION_ALL };
        
        enum class ClickEventType { BEGAN, ENDED, DOUBLE_CLICK_BEGAN, DOUBLE_CLICK_ENDED, MOVED };
        
    public:
        
        typedef std::function<void(cocos2d::Ref*, const ClickEventType&)>                               ccDoubleClickCallback;
        typedef std::function<void(cocos2d::Ref*, const cocos2d::Vec2&)>                                ccChangedDirectionCallback;
        typedef std::function<void(cocos2d::Ref*, const cocos2d::Vec2&, const ClickEventType&)>         ccChangedDirectionAndStatusCallback;
        typedef std::function<void(cocos2d::Ref*, const cocos2d::ui::Widget::TouchEventType)>           ccClickCallback;
        
    public:
        
        static JoystickEx* create(const char* joystickNormalImagePath,
                                  const char* joystickSelectedImagePath,
                                  cocos2d::ui::Widget::TextureResType type = cocos2d::ui::Widget::TextureResType::LOCAL);
    
        void enableDoubleClick(bool enable)         { _isEnableDoubleClick = enable; }
        
        cocos2d::Vec2 getDirection() const          { return _direction; }
        
        float getMaxMovableRadius() const           { return _maxMovableRadius; }
        
        bool isDoubleClicked() const                { return _isDoubleClicked; }
        
        bool isEnableDoubleClicked() const          { return _isEnableDoubleClick; }
        
        bool isTouched() const                      { return _isTouched; }
        
        void setMaxMovableRadius(float rad)         { _maxMovableRadius = rad; }
        
        void setRotationType(RotationType type)     { _rotationType = type; }

        void setJoystickPad(const char* filePath, cocos2d::ui::Widget::TextureResType texResType = cocos2d::ui::Widget::TextureResType::LOCAL);
        
        void enableJoystickPad(bool enable)         { _enablePad = enable; }
        
        void setDoubleClickCallback(const ccDoubleClickCallback& callback)                                  { _doubleClickCallback = callback; }
        
        void setChangedDirectionCallback(const ccChangedDirectionCallback& callback)                        { _changedDirectionCallback = callback; }
        
        void setChangedDirectionAndStatusCallback(const ccChangedDirectionAndStatusCallback& callback)      { _changedDirectionAndStatusCallback = callback; }
        
        void setClickCallback(const ccClickCallback& callback)                                              { _clickCallback = callback; }
        
    private:
        
        cocos2d::Vec2                                           _direction;
        
        float                                                   _maxMovableRadius;
        
        cocos2d::ui::Button*                                    _joystick;
        
        bool                                                    _isTouched;
        
        bool                                                    _isDoubleClicked;
        
        bool                                                    _isEnableDoubleClick;
        
        std::chrono::duration<double>                           _firstTouchedTime;
        
        RotationType                                            _rotationType;
        
        int                                                     _oldDegree;
        
        cocos2d::Sprite*                                        _pad;
        
        bool                                                    _enablePad;
        
        ccDoubleClickCallback                                   _doubleClickCallback;
        
        ccChangedDirectionCallback                              _changedDirectionCallback;
        
        ccChangedDirectionAndStatusCallback                     _changedDirectionAndStatusCallback;
        
        ccClickCallback                                         _clickCallback;
        
    private:
        
        JoystickEx();
        virtual ~JoystickEx();
        
        void _runDoubleClickBeginEvent();
        
        void _runDoubleClickEndEvent();
        
        bool init(const char* joystickNormalImagePath,
                  const char* joystickSelectedImagePath,
                  cocos2d::ui::Widget::TextureResType type);
        
        inline cocos2d::Vec2 _getJoystickExNodeWorldPosition()
        {
            cocos2d::Vec2 ret = getPosition();
            cocos2d::Node* p = getParent();
            while( !p )
            {
                ret += p->getPosition();
                p = p->getParent();
            }
            return ret;
        }
        
        inline void _calculateDirection(const cocos2d::Vec2& v)
        {
            if ( v == cocos2d::Vec2::ZERO )
                _direction = cocos2d::Vec2::ZERO;
            else
                _direction = v.getNormalized();
            
            if ( _changedDirectionCallback ) _changedDirectionCallback(this, _direction);
        }
        
        inline float _calculateDegree(const cocos2d::Vec2& dir)
        {
            if( dir.y >= 0.0f )
            {
                return MATH_RAD_TO_DEG(acosf(dir.dot(cocos2d::Vec2::UNIT_X)));
            }
            return MATH_RAD_TO_DEG(acosf(dir.dot(-cocos2d::Vec2::UNIT_X)) + 3.141592f);
        }
        
    };
    
}




