//
//  Lights.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 2. 9..
//
//

#pragma once

#include "cocos2d.h"


namespace realtrick
{
    
    //
    // LightBase
    //
    class LightBase : public cocos2d::Ref
    {
        
    public:
        
        enum LightType { INVALID = -1, DIRECTIONAL = 1, POINT = 2, SPOT = 3 };
        
    public:
        
        void setColor(const cocos2d::Vec3& color) { _color = color; }
        
        cocos2d::Vec3 getColor() const { return _color; }
        
        void setIntensity(float intensity)
        {
            _intensity = std::max(intensity, 0.0f);
        }
        
        void setEnable(bool enable) { _isEnable = enable; }
        
        float getIntensity() const { return _intensity; }
        
        bool isEnable() const { return _isEnable; }
        
        int getLightType() const { return _lightType; }
        
        void setLightType(int type) { _lightType = type; }
        
    protected:
        
        cocos2d::Vec3       _color = cocos2d::Vec3::ONE;
        
        float               _intensity = 1.0f;
        
        bool                _isEnable = true;
        
        int                 _lightType = INVALID;
        
    };

    
    //
    // DirectionalLight
    //
    class DirectionalLight : public LightBase
    {
        
    public:
        
        static DirectionalLight* create(const cocos2d::Vec3& direction);
        
        cocos2d::Vec3 getDirection() const { return _direction; }
        void setDirection(const cocos2d::Vec3& dir) { _direction = dir; }
        
    private:
        
        cocos2d::Vec3 _direction;
        
    private:
        
        DirectionalLight();
        
        virtual ~DirectionalLight();
        
        bool init(const cocos2d::Vec3& direction);
        
    };
    
    
    //
    // PointLight
    //
    class PointLight : public LightBase
    {
        
    public:
        
        static PointLight* create(const cocos2d::Vec3& lightPos,
                                  float range);
        
        cocos2d::Vec3 getLightPos() const { return _lightPos; }
        
        void setLightPos(const cocos2d::Vec3& lightPos) { _lightPos = lightPos; }
        
        float getRange() const { return _range; }
        
        void setRange(float r) { _range = r; }
        
    private:
        
        cocos2d::Vec3       _lightPos;
        float               _range;
        
    private:
        
        PointLight();
        
        virtual ~PointLight();
        
        bool init(const cocos2d::Vec3& lightPos, float range);
        
    };
    
    
    //
    // SpotLight
    //
    class SpotLight : public LightBase
    {
        
    public:
        
        static SpotLight* create(const cocos2d::Vec3& lightPos, const cocos2d::Vec3& spotDirection, float cutOff);
        
        cocos2d::Vec3 getLightPos() const { return _lightPos; }
        
        void setLightPos(const cocos2d::Vec3& lightPos) { _lightPos = lightPos; }
        
        cocos2d::Vec3 getSpotDirection() const { return _spotDirection; }
        
        void setSpotDirection(const cocos2d::Vec3& dir) { _spotDirection = dir; }
        
        float getCutOffAngle() const { return _cutOff; }
        
        void setCutOffAngle(float degree) { _cutOff = degree; }
        
    private:
    
        cocos2d::Vec3       _lightPos;
        
        cocos2d::Vec3       _spotDirection;
        
        float               _cutOff;
        
    private:
        
        SpotLight();
        
        virtual ~SpotLight();
        
        bool init(const cocos2d::Vec3& lightPos, const cocos2d::Vec3& spotDirection, float cutOff);
        
    };
    
    
}


