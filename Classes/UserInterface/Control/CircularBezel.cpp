//
//  CircularBezel.cpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 21..
//
//

#include "CircularBezel.hpp"
#include "Physics.hpp"

using namespace cocos2d;
using namespace cocos2d::ui;

namespace realtrick
{
    
    CircularBezel::CircularBezel() :
    _bezel(nullptr),
    _image(nullptr),
    _isTouched(false),
    _oldDirection(Vec2::ZERO),
    _debugNode(nullptr),
    _debugNodeInit(nullptr),
    _minTriggerDeg(2.0f),
    _maxTriggerDeg(10.0f),
    _interpolatedTriggerDeg(10.0f),
    _isDebug(false),
    _triggerCallback(nullptr),
    _minimumTriggerRadius(80.0f),
    _maximumTriggerRadius(200.0f),
    _precision(2)
    {
    }
    
    
    CircularBezel::~CircularBezel()
    {}
    
    
    CircularBezel* CircularBezel::create(const char* bezelImagePath, cocos2d::ui::Widget::TextureResType type)
    {
        CircularBezel* ret = new (std::nothrow)CircularBezel();
        if ( ret && ret->init(bezelImagePath, type) )
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    
    bool CircularBezel::init(const char* bezelImagePath, cocos2d::ui::Widget::TextureResType type)
    {
        _debugNode = DrawNode::create();
        _debugNode->setVisible(false);
        addChild(_debugNode);
        
        _debugNodeInit = DrawNode::create();
        _debugNodeInit->setVisible(false);
        addChild(_debugNodeInit);
        
        _bezel = Button::create(bezelImagePath, bezelImagePath, "", type);
        _bezel->setSwallowTouches(false);
        _bezel->setOpacity(0);
        _bezel->setSwallowTouches(false);
        addChild(_bezel);
        
        if( type == ui::Widget::TextureResType::PLIST)
            _image = Sprite::createWithSpriteFrameName(bezelImagePath);
        else
            _image = Sprite::create(bezelImagePath);
        addChild(_image);
        
        
        _bezel->addTouchEventListener([&, this](Ref* ref, Widget::TouchEventType type) {
        
            _debugNode->clear();
            const float kDebugRad  = 120.0f;
            
            Button* self = (Button*)ref;
            Vec2 world = _getWorldPosition();
            
            switch ( type )
            {
                case Widget::TouchEventType::BEGAN:
                {
                    Vec2 touch = self->getTouchBeganPosition();
                    if( _minimumTriggerRadius * _minimumTriggerRadius > touch.distanceSquared(world) )
                    {
                        _isTouched = false;
                        break;
                    }
                    
                    _isTouched = true;
                    _oldDirection = (touch - world).getNormalized();
                    
                    _debugNode->drawDot(_oldDirection * kDebugRad, 5.0f, Color4F::RED);
                    
                    break;
                }
                case Widget::TouchEventType::MOVED:
                {
                    Vec2 touch = self->getTouchMovePosition();
                    Vec2 currDirection = (touch - world).getNormalized();
                    
                    if( _minimumTriggerRadius * _minimumTriggerRadius > touch.distanceSquared(world) )
                    {
                        _isTouched = false;
                        break;
                    }
                    
                    if( _isTouched == false )
                    {
                        _oldDirection = (touch - world).getNormalized();
                        _isTouched = true;
                    }
                    
                    _debugNode->drawDot(_oldDirection * kDebugRad, 5.0f, Color4F::RED);
                    _debugNode->drawDot(currDirection * kDebugRad, 5.0f, Color4F::GREEN);
                    _debugNode->drawSegment(_oldDirection * kDebugRad, currDirection * kDebugRad, 2.0f, Color4F::WHITE);
                    
                    float dot = _oldDirection.dot(currDirection);
                    float offsetDeg = MATH_RAD_TO_DEG(acosf(dot));
                    
                    float distanceFromOrigin = touch.distance(world);
                    distanceFromOrigin = clampf(distanceFromOrigin,
                                                _minimumTriggerRadius + 1,
                                                _maximumTriggerRadius - 1);
                    
                    distanceFromOrigin -= _minimumTriggerRadius;
                    
                    float slice = (_maximumTriggerRadius - _minimumTriggerRadius) / _precision;
                    int multiplier = ((int)distanceFromOrigin / slice);
                    
                    float multiplier2 = (float)multiplier / (_precision - 1);
                    if ( _precision == 1) multiplier2 = 0;
                    
                    _interpolatedTriggerDeg = _maxTriggerDeg - (_maxTriggerDeg - _minTriggerDeg) * multiplier2;
                    
                    if ( _interpolatedTriggerDeg < offsetDeg )
                    {
                        int multiplier = -1;
                        if ( _oldDirection.cross(currDirection) > 0 )
                            multiplier = 1;
                        
                        Mat3 rotMat;
                        rotMat.rotate(multiplier * MATH_DEG_TO_RAD(_interpolatedTriggerDeg));
                        _oldDirection = rotMat.getTransformedVector(_oldDirection);
                        _image->setRotation( _image->getRotation() + _interpolatedTriggerDeg * -multiplier );
                        
                        if (_triggerCallback )
                        {
                            float rot = -( _image->getRotation() );
                            _triggerCallback(this, Vec2(cosf(MATH_DEG_TO_RAD(rot)), sinf(MATH_DEG_TO_RAD(rot))));
                        }
                    }
                    
                    break;
                }
                
                default: break;
            }
            
        });
        
        return true;
    }
    
    void CircularBezel::setTriggerRadius(const std::pair<float ,float>& min_max)
    {
         _minimumTriggerRadius = min_max.first;
        _maximumTriggerRadius = min_max.second;
        
        _debugNodeInit->clear();
        _debugNodeInit->drawRect(Vec2(-_bezel->getContentSize().width / 2, -_bezel->getContentSize().height / 2),
                                 Vec2(_bezel->getContentSize().width / 2, _bezel->getContentSize().height / 2),
                                 Color4F::RED);
        _debugNodeInit->drawCircle(Vec2::ZERO, _minimumTriggerRadius, 360.0f, 50, false, Color4F::GRAY);
        _debugNodeInit->drawCircle(Vec2::ZERO, _maximumTriggerRadius, 360.0f, 50, false, Color4F::GRAY);
    }
    
    void CircularBezel::setBezelDirection(const cocos2d::Vec2& dir, float turnSpeed)
    {
//        float A = -( _image->getRotation() );
//        Vec2 imageDir = Vec2(cosf(MATH_DEG_TO_RAD(A)), sinf(MATH_DEG_TO_RAD(A)));
//        float offset = acosf(dir.dot(imageDir));
//        
//        float d = imageDir.cross(dir);
//        if ( d > 0 )    offset = -MATH_RAD_TO_DEG(offset);
//        else            offset = MATH_RAD_TO_DEG(offset);
//        
//        _image->stopAllActions();
//        _image->runAction(RotateBy::create(fabsf(offset) / turnSpeed, offset));
    }
    
    
}









