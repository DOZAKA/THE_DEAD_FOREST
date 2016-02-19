//
//  Camera2D.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 2. 14..
//
//

#pragma once

#include "cocos2d.h"
#include "EntityBase.hpp"

namespace realtrick
{
    class GameWorld;
    class EntityBase;
    class OcculusionBuilder;
    class EffectSprite;
    class LightEffect;
    
    
    class Camera2D : public cocos2d::Node
    {
        
    public:
        
        static Camera2D* create(GameWorld* world);
        
        void setCameraPos(const cocos2d::Vec2& pos) { _cameraPosition = pos; }
        
        cocos2d::Vec2 getCameraPos() const { return _cameraPosition; }
        
        cocos2d::Node* getStaticRenderTarget() const { return _staticRenderTarget; }
        
        cocos2d::Node* getDynamicRenderTarget() const { return _dynamicRenderTarget; }
        
        cocos2d::Node* getNormalRenderTarget() const { return _normalRenderTarget; }
        
        void setZoom(float zoomFactor);
        
        void resumeGame() { _isPaused = false; }
        
        void pauseGame() { _isPaused = true;  }
        
    private:
        
        cocos2d::Size                       _worldSize;
        
        GameWorld*                          _world;
        
        cocos2d::Vec2                       _cameraPosition;
        
        float                               _zoomRatio;
        
        cocos2d::Node*                      _staticRenderTarget;
        
        cocos2d::RenderTexture*             _staticTexture;
        
        cocos2d::Node*                      _dynamicRenderTarget;
        
        cocos2d::RenderTexture*             _dynamicTexture;
        
        cocos2d::Node*                      _normalRenderTarget;
        
        cocos2d::RenderTexture*             _normalTexture;
        
        OcculusionBuilder*                  _ocBuilder;
        
        EffectSprite*                       _deferredRenderTarget;
        
        LightEffect*                        _effect;
        
        cocos2d::Sprite*                    _normalBg;
        
        bool                                _isPaused;
        
    private:
        
        explicit Camera2D(GameWorld* world);
        
        virtual ~Camera2D();
        
        virtual bool init() override;
        
        virtual void visit(cocos2d::Renderer *renderer,
                           const cocos2d::Mat4& parentTransform,
                           uint32_t parentFlags) override;
        
    };
    
} // realtrick








