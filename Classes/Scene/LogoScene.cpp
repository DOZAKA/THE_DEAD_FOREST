//
//  LogoScene.cpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 29..
//
//

#include "LogoScene.hpp"
#include "MainMenu2.hpp"

using namespace cocos2d;

namespace  realtrick
{
    
    cocos2d::Scene* LogoScene::createScene()
    {
        auto scene = Scene::create();
        auto layer = LogoScene::create();
        scene->addChild(layer);
        return scene;
    }
    
    
    
    LogoScene::~LogoScene()
    {
    }
    
    
    
    bool LogoScene::init()
    {
        if ( !Layer::init() )
        {
            return false;
        }
        
        this->scheduleUpdate();
        
        auto winSize = Director::getInstance()->getVisibleSize();
        
        const float kLoadingTime = 2.0f;
        
        auto logoSprite = Sprite::create("realtrick.png");
        logoSprite->setOpacity(0);
        logoSprite->setPosition(winSize / 2);
        logoSprite->runAction(Spawn::create(ScaleTo::create(kLoadingTime, 1.05f),
                                            FadeTo::create(kLoadingTime / 4.0f, 255),
                                            Sequence::create(DelayTime::create(kLoadingTime / 2.0f),
                                                             FadeTo::create(kLoadingTime / 4.0f, 0),
                                                             nullptr),
                                            nullptr));
        addChild(logoSprite);
        
        runAction(Sequence::create(DelayTime::create(kLoadingTime),
                                   CallFunc::create([this]{ Director::getInstance()->replaceScene(MainMenu2::createScene()); }),
                                   nullptr));
                                
        
        return true;
    }
    
    
    
    void LogoScene::update(float dt)
    {
        
    }
    
}













