//
//  LightTest.cpp
//  TheDeadForest
//
//  Created by 남준현 on 2016. 2. 9..
//
//

#include "LightTest.hpp"

using namespace cocos2d;

namespace realtrick
{
    
    cocos2d::Scene* LightTest::createScene()
    {
        auto scene = Scene::create();
        auto layer = LightTest::create();
        scene->addChild(layer);
        return scene;
    }
    
    
    LightTest::~LightTest()
    {
    }
    
    
    bool LightTest::init()
    {
        if ( !LayerColor::initWithColor(Color4B::BLUE) )
        {
            return false;
        }
        
        this->scheduleUpdate();
        _winSize = Director::getInstance()->getVisibleSize();
        

        
        return true;
    }
    
    
    void LightTest::update(float dt)
    {
        
    }
    
}





