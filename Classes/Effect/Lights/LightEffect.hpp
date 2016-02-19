//
//  LightEffect.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 2. 8..
//
//

#pragma once

#include "EffectBase.hpp"
#include "Lights.hpp"

namespace realtrick
{
    
    class LightEffect : public EffectBase
    {
        
    public:
        
        LightEffect();
        
        virtual ~LightEffect();
        
        static LightEffect* create(const std::string& fragment);
        
        void setNormalMap(cocos2d::Texture2D* map);
        
        void setDynamicMap(cocos2d::Texture2D* map);
        
        void setStaticMap(cocos2d::Texture2D* map);
        
        void setOcculusionMap(cocos2d::Texture2D* map);
        
        void addLight(LightBase* light);
        
        void removeLight(LightBase* light);
        
        void removeAllLights();
        
        void prepareForRender(cocos2d::Sprite *sprite) override;
        
    private:
    
        cocos2d::Vector<LightBase*>     _lights;
        
        cocos2d::Texture2D*             _normalMap;
        
        cocos2d::Texture2D*             _dynamicMap;
        
        cocos2d::Texture2D*             _staticMap;
        
        cocos2d::Texture2D*             _occulusionMap;
        
        
    private:
        
        std::string _to_string(int number)
        {
            std::ostringstream convStream;
            convStream << number;
            return convStream.str();
        }
        
    };
    
};









