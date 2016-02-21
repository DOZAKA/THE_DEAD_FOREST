//
//  CircularBezel.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 21..
//
//

#pragma once

#include <functional>

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace realtrick
{
    
    class CircularBezel : public cocos2d::Node
    {
    
    public:
        
        typedef std::function<void(cocos2d::Ref*, const cocos2d::Vec2&)>    ccTriggerCallback;
    
    public:
        
        static CircularBezel* create(const char* bezelImagePath, cocos2d::ui::Widget::TextureResType type = cocos2d::ui::Widget::TextureResType::LOCAL);
        
        void addTriggerCallback(const ccTriggerCallback& callback) { _triggerCallback = callback; }
            
        void setTriggerDegree(const std::pair<float, float>& min_max ) { _minTriggerDeg = min_max.first; _maxTriggerDeg = min_max.second; }
            
        std::pair<float,float> getTriggerDegree() const { return std::make_pair(_minTriggerDeg, _maxTriggerDeg); }
        
        void enableDebugNode(bool enable) { _isDebug = enable; _debugNode->setVisible(enable); _debugNodeInit->setVisible(enable); }
        
        bool isDebugMode() const { return _isDebug; }
        
        void setTriggerRadius(const std::pair<float ,float>& min_max);
        
        std::pair<float, float> getTriggerRadius() const { return std::make_pair(_minimumTriggerRadius, _maximumTriggerRadius); }
        
        void setPrecision(int pre)  { _precision = pre; }
        
        int getPrecision() const { return _precision; }
        
        void setBezelDirection(const cocos2d::Vec2& dir, float turnSpeed);
        
    private:
        
        cocos2d::ui::Button*                    _bezel;
        cocos2d::Sprite*                        _image;
        bool                                    _isTouched;
        cocos2d::Vec2                           _oldDirection;
        cocos2d::DrawNode*                      _debugNode;
        cocos2d::DrawNode*                      _debugNodeInit;
        float                                   _minTriggerDeg;
        float                                   _maxTriggerDeg;
        float                                   _interpolatedTriggerDeg;
        bool                                    _isDebug;
        float                                   _minimumTriggerRadius;
        float                                   _maximumTriggerRadius;
                
        ccTriggerCallback                       _triggerCallback;
        int                                     _precision;
        
    private:
        
        CircularBezel();
        virtual ~CircularBezel();
        bool init(const char* bezelImagePath, cocos2d::ui::Widget::TextureResType type = cocos2d::ui::Widget::TextureResType::LOCAL);
            
        inline cocos2d::Vec2 _getWorldPosition()
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
        
        inline float _calculateRadian(const cocos2d::Vec2& dir)
        {
            if( dir.y >= 0.0f )
            {
                return acosf(dir.dot(cocos2d::Vec2::UNIT_X));
            }
            return acosf(dir.dot(-cocos2d::Vec2::UNIT_X) + 3.141592f);
        }
        
        inline float _calculateDegree(const cocos2d::Vec2& dir)
        {
            return MATH_RAD_TO_DEG(_calculateRadian(dir));
        }
        
    };
    
}
