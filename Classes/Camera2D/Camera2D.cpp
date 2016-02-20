//
//  Camera2D.cpp
//  TheDeadForest
//
//  Created by mac on 2016. 2. 14..
//
//

#include "Camera2D.hpp"
#include "OcculusionBuilder.hpp"
#include "GameWorld.hpp"
#include "GameManager.hpp"
#include "EffectSprite.hpp"
#include "LightEffect.hpp"
#include "EntityHuman.hpp"
#include "AnimationPlayer.hpp"

namespace realtrick
{
    using namespace cocos2d;
    
    Camera2D::Camera2D(GameWorld* world) :
    _worldSize(Size::ZERO),
    _world(world),
    _cameraPosition(Vec2::ZERO),
    _zoomRatio(1.0f),
    _staticRenderTarget(nullptr),
    _staticTexture(nullptr),
    _dynamicRenderTarget(nullptr),
    _dynamicTexture(nullptr),
    _normalRenderTarget(nullptr),
    _normalTexture(nullptr),
    _ocBuilder(nullptr),
    _deferredRenderTarget(nullptr),
    _effect(nullptr),
    _normalBg(nullptr),
    _isPaused(true)
    {}
    

    Camera2D::~Camera2D()
    {
    }
    
    
    Camera2D* Camera2D::create(GameWorld* world)
    {
        Camera2D* ret = new (std::nothrow)Camera2D(world);
        if ( ret && ret->init() )
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    
    bool Camera2D::init()
    {
        if ( !Node::init() )
            return false;
        
        _worldSize = _world->getWorldSize();
        
        _staticRenderTarget = Node::create();
        _staticRenderTarget->setPosition(_worldSize / 2);

        _dynamicRenderTarget = Node::create();
        _dynamicRenderTarget->setPosition(_worldSize / 2);
        
        _normalRenderTarget = Node::create();
        _normalRenderTarget->setPosition(_worldSize / 2);
        
        _staticRenderTarget->retain();
        _dynamicRenderTarget->retain();
        _normalRenderTarget->retain();
        
        _staticTexture = RenderTexture::create(_worldSize.width, _worldSize.height);
        _dynamicTexture = RenderTexture::create(_worldSize.width, _worldSize.height);
        _normalTexture = RenderTexture::create(_worldSize.width, _worldSize.height);
        
        _staticTexture->retain();
        _dynamicTexture->retain();
        _normalTexture->retain();
        
        _ocBuilder = OcculusionBuilder::create(this, _worldSize);
        _ocBuilder->getRenderTexture()->setPosition(_worldSize / 2);
        _ocBuilder->setDebugNode(_world->getDebugNode());
        _ocBuilder->retain();
        
        _normalBg = Sprite::create("normal_bg.png");
        _normalBg->setPosition(_worldSize / 2);
        _normalBg->retain();
        
        _effect = LightEffect::create("lights.fsh");
        _effect->retain();
        
        
        DirectionalLight* dl = DirectionalLight::create(Vec3(0, -0.7f, -0.7f));
        dl->setColor(Vec3(0.7f, 0.7f, 0.7f));
        dl->setIntensity(1.0f);
        _effect->addLight(dl);
        
        
//        PointLight* pl = PointLight::create(Vec3(568,320 ,100), 300);
//        pl->setIntensity(0.2);
//        _effect->addLight(pl);
    
        
        _deferredRenderTarget = EffectSprite::create("normal_bg.png");
        _deferredRenderTarget->setPosition(_worldSize / 2);
        _deferredRenderTarget->setEffect(_effect);
        _deferredRenderTarget->setFlippedY(true);
        addChild(_deferredRenderTarget);
        
        
        return true;
    }
  
    
    void Camera2D::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags)
    {
        if ( _isPaused ) return ;
        
        _staticTexture->beginWithClear(0,0,0,0);
        _staticRenderTarget->visit();
        _staticTexture->end();
    

        _dynamicTexture->beginWithClear(0,0,0,0);
        _dynamicRenderTarget->visit();
        _dynamicTexture->end();
        
        
        for ( auto &child : _dynamicRenderTarget->getChildren() )
        {
            EntityHuman* human = (EntityHuman*)child;
            human->getBodyAnimator()->enableShadow(false);
            human->getBodyAnimator()->enableNormal(true);
        }
        
        GameMap* map = (GameMap*)_staticRenderTarget->getChildByTag(999);
        map->enableNormal(true);
        
        _normalTexture->beginWithClear(0,0,0,0);
        _normalBg->visit();
        _staticRenderTarget->visit();
        _dynamicRenderTarget->visit();
        _normalTexture->end();
        
        
        map->enableNormal(false);
        for ( auto &child : _dynamicRenderTarget->getChildren() )
        {
            EntityHuman* human = (EntityHuman*)child;
            human->getBodyAnimator()->enableShadow(true);
            human->getBodyAnimator()->enableNormal(false);
        }
        
        OcculusionBuilder::FieldOfView fov;
        fov.aroundCircleRadius = 40.0f;
        fov.aroundCircleSlice = 30;
        fov.entryDegree = 110.0f;
        fov.heading = _world->getGameManager()->getPlayerPtr()->getHeading();
        fov.isEnable = Prm.getValueAsBool("isFovMode");
        
        EntityHuman* player = _world->getGameManager()->getPlayerPtr();
        _ocBuilder->invalidateTexture(player->getWorldPosition(),
                                      _world->getGameManager()->getNeighborWalls(player->getWorldPosition(), _worldSize),
                                      _worldSize,
                                      fov);
        
        _effect->setStaticMap(_staticTexture->getSprite()->getTexture());
        _effect->setDynamicMap(_dynamicTexture->getSprite()->getTexture());
        _effect->setOcculusionMap(_ocBuilder->getOcculusionTexture());
        _effect->setNormalMap(_normalTexture->getSprite()->getTexture());
        
        Node::visit(renderer, parentTransform, parentFlags);
    }
    
    
    void Camera2D::setZoom(float zoomFactor)
    {
        _world->getDebugNode()->setScale(zoomFactor);
        _deferredRenderTarget->setScale(zoomFactor);
        _ocBuilder->getRenderTexture()->setScale(zoomFactor);
    }
 
}








