//
//  Lights.cpp
//  TheDeadForest
//
//  Created by mac on 2016. 2. 9..
//
//

#include "Lights.hpp"

using namespace cocos2d;

namespace realtrick
{
    
    //
    // DirectionalLight
    //
    DirectionalLight::DirectionalLight() : _direction(Vec3::ZERO)
    {
        setLightType(LightType::DIRECTIONAL);
    }
    
    DirectionalLight::~DirectionalLight()
    {}
    
    DirectionalLight* DirectionalLight::create(const cocos2d::Vec3& direction)
    {
        DirectionalLight* ret = new (std::nothrow) DirectionalLight();
        if ( ret && ret->init(direction))
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    bool DirectionalLight::init(const cocos2d::Vec3& direction)
    {
        if ( direction.length() < MATH_EPSILON )
            return false;
        
        _direction = direction.getNormalized();
        
        return true;
    }
    
    
    //
    // PointLight
    //
    PointLight::PointLight() :
    _lightPos(Vec3::ZERO),
    _range(0.0f)
    {
        setLightType(LightType::POINT);
    }
    
    PointLight::~PointLight()
    {}
    
    PointLight* PointLight::create(const cocos2d::Vec3& lightPos,
                                   float range)
    {
        PointLight* ret = new (std::nothrow) PointLight();
        if ( ret && ret->init(lightPos, range))
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    bool PointLight::init(const cocos2d::Vec3& lightPos,
                          float range)
    {
        if ( range < 0.0f )
            return false;
        
        _lightPos = lightPos;
        _range = range;
        
        return true;
    }
    
}









