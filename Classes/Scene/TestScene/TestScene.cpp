//
//  TestScene.cpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 12. 6..
//
//

#include "TestScene.hpp"
#include "Items.hpp"
#include "GameManager.hpp"
#include "LightEffect.hpp"
#include "EffectSprite.hpp"
#include "Lights.hpp"

using namespace cocos2d;

namespace realtrick
{
    
    cocos2d::Scene* TestScene::createScene()
    {
        auto scene = Scene::create();
        auto layer = TestScene::create();
        scene->addChild(layer);
        return scene;
    }
    
    
    TestScene::~TestScene()
    {
    }
    
    
    bool TestScene::init()
    {
        if ( !LayerColor::initWithColor(Color4B::BLACK) )
        {
            return false;
        }
        
        this->scheduleUpdate();
        _winSize = Director::getInstance()->getVisibleSize();
        
        
        auto lrt = RenderTexture::create(1136, 640);
        
        Sprite* bg = Sprite::create("normal_bg.png");
        Sprite* hn = Sprite::createWithSpriteFrameName("HumanGlock17Attack2_n.png");
        hn->setPosition(_winSize / 2);
        bg->addChild(hn);
        bg->setPosition(_winSize /2);
        
        lrt->beginWithClear(1, 0, 1, 1);
        bg->visit();
        lrt->end();
        
//        lrt->setPosition(_winSize/2);
//        addChild(lrt);
        
        
        auto rt = RenderTexture::create(1136, 640);
        
        Sprite* h = Sprite::createWithSpriteFrameName("HumanGlock17Attack2.png");
        h->setPosition(_winSize/2);
        
        rt->beginWithClear(0, 0, 1, 1);
        h->visit();
        rt->end();
        
//        rt->setPosition(_winSize/2);
//        addChild(rt);
        
        
        _lightEffect = LightEffect::create("lights.fsh");
        _lightEffect->setNormalMap(lrt->getSprite()->getTexture());
        _lightEffect->retain();
        
//        DirectionalLight* pl = DirectionalLight::create(Vec3(0, 0, 1));
//        pl->setColor(Vec3(1.0f, 1.0f, 1.0f));
//        pl->setIntensity(1.0f);
//        _lightEffect->addLight(pl);
        
        PointLight* pl2 = PointLight::create(Vec3(568, 320, 20), 100);
        pl2->setIntensity(1.0f);
        _lightEffect->addLight(pl2);
        
        EffectSprite* spr = EffectSprite::createWithTexture(rt->getSprite()->getTexture());
        spr->setPosition(_winSize / 2);
        spr->setEffect(_lightEffect);
        addChild(spr);

        
        return true;
    }
    
    
    void TestScene::update(float dt)
    {
       
        
    }
    
}





