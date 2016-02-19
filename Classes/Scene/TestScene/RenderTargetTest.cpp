//
//  RenderTargetTest.cpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 12. 6..
//
//

#include "RenderTargetTest.hpp"

using namespace cocos2d;

namespace realtrick
{
    
    cocos2d::Scene* RenderTargetTest::createScene()
    {
        auto scene = Scene::create();
        auto layer = RenderTargetTest::create();
        scene->addChild(layer);
        return scene;
    }
    
    
    RenderTargetTest::~RenderTargetTest()
    {
    }
    
    
    bool RenderTargetTest::init()
    {
        if ( !Layer::init() )
        {
            return false;
        }
        
        this->scheduleUpdate();
        _winSize = Director::getInstance()->getVisibleSize();

        Sprite* renderTarget = Sprite::create();
        renderTarget->setPosition(_winSize/2);
        renderTarget->setScale(3.0);
        addChild(renderTarget);
        
        Sprite* m = Sprite::createWithSpriteFrameName("1_1_1234.png");
        renderTarget->addChild(m);
        
        Sprite* player = Sprite::create("grossini.png");
        renderTarget->addChild(player);
        
        player->setFlippedY(true);
        
        return true;
    }
    
    void RenderTargetTest::onEnter()
    {
        Node::onEnter();
    }
    
    void RenderTargetTest::update(float dt)
    {
        
    }
    
}





