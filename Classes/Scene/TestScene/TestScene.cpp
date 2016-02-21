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
        
        return true;
    }
    
    
    void TestScene::update(float dt)
    {
       
        
    }
    
}





