//
//  MainMenu2.cpp
//  TheDeadForest
//
//  Created by mac on 2015. 12. 23..
//
//

#include "MainMenu2.hpp"

using namespace cocos2d;
using namespace cocos2d::ui;
// 
namespace realtrick
{
    
    MainMenu2* MainMenu2::create()
    {
        static MainMenu2* ret = new (std::nothrow) MainMenu2();
        if(ret && ret->init())
        {
            ret->autorelease();
            return ret;
        }
        else
        {
            CC_SAFE_DELETE(ret);
            return nullptr;
        }
    }
    
    Scene* MainMenu2::createScene()
    {
        Scene* scene = Scene::create();
        Layer* layer = MainMenu2::create();
        scene->addChild(layer);
        return scene;
    }
    
    void MainMenu2::initCallbacks()
    {
        _callbacks[PLAY_BUTTON] = [&, this](Ref* ref, Widget::TouchEventType type)
        {
            if(type == Widget::TouchEventType::ENDED && _isButtonClicked == false)
            {
                _sceneState = SCENE_PLAY;
                BUTTON_ON(0.3f);
                
                _buttons[PLAY_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.0f, 0, -350.0f, 0.0f));
                _buttons[OPTION_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.1f, 0, -350.0f, 0.0f));
                _buttons[EXIT_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.13f, 0, -350.0f, 0.0f));
                
                _buttons[CAMPAIGN_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.16f, 255, 350.0f, 0.0f));
                _buttons[MULTIPLAYER_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.19f, 255, 350.0f, 0.0f));
                _buttons[CUSTOM_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.22f, 255, 350.0f, 0.0f));
                _buttons[BACK_BUTTON]->runAction(ACTION_PLACE_DELAY_FADETO_MOVEBY(0.0f, POS_Y_4, 0.25f, 255, 350.0f, 0.0f));
                
                _infoLabel->runAction(ACTION_LABEL_DELAY_PLACE_CHANGE(0.25f, 340.0f, POS_Y_4 - INFO_PAD, "Select Mode"));
            }
        };
        
        _callbacks[OPTION_BUTTON] = [&, this](Ref* ref, Widget::TouchEventType type)
        {
            if(type == Widget::TouchEventType::ENDED && _isButtonClicked == false)
            {
                _sceneState = SCENE_OPTION;
                BUTTON_ON(0.3f);
                
                _buttons[PLAY_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.0f, 0, -350.0f, 0.0f));
                _buttons[OPTION_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.1f, 0, -350.0f, 0.0f));
                _buttons[EXIT_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.13f, 0, -350.0f, 0.0f));
                _buttons[BACK_BUTTON]->runAction(ACTION_PLACE_DELAY_FADETO_MOVEBY(0.0f, POS_Y_2, 0.16f, 255, 350.0f, 0.0f));
                
                _infoLabel->runAction(ACTION_LABEL_DELAY_PLACE_CHANGE(0.19f, 340.0f, POS_Y_2 - INFO_PAD, "Set Environment"));
            }
        };

        _callbacks[EXIT_BUTTON] = [&, this](Ref* ref, Widget::TouchEventType type)
        {
            if(type == Widget::TouchEventType::ENDED && _isButtonClicked == false)
            {
                Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                exit(0);
#endif
            }
        };
        
        _callbacks[CAMPAIGN_BUTTON] = [&, this](Ref* ref, Widget::TouchEventType type)
        {
            if(type == Widget::TouchEventType::ENDED && _isButtonClicked == false)
            {
                _sceneState = SCENE_CAMPAIGN;
                BUTTON_ON(0.3f);
                
                _buttons[CAMPAIGN_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.0f, 0, -350.0f, 0.0f));
                _buttons[MULTIPLAYER_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.1f, 0, -350.0f, 0.0f));
                _buttons[CUSTOM_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.13f, 0, -350.0f, 0.0f));
                _buttons[BACK_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.16f, 255, 0.0f, 135.0f));
                
                _infoLabel->runAction(ACTION_LABEL_DELAY_PLACE_CHANGE(0.25f, 340.0f, POS_Y_1 - INFO_PAD, "Select Campaign"));
            }
        };
        
        _callbacks[MULTIPLAYER_BUTTON] = [&, this](Ref* ref, Widget::TouchEventType type)
        {
            if(type == Widget::TouchEventType::ENDED && _isButtonClicked == false)
            {
                _sceneState = SCENE_MULTIPLAYER;
                BUTTON_ON(0.3f);
                
                _buttons[CAMPAIGN_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.0f, 0, -350.0f, 0.0f));
                _buttons[MULTIPLAYER_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.1f, 0, -350.0f, 0.0f));
                _buttons[CUSTOM_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.13f, 0, -350.0f, 0.0f));
                _buttons[BACK_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.16f, 255, 0.0f, 135.0f));
                
                _infoLabel->runAction(ACTION_LABEL_DELAY_PLACE_CHANGE(0.25f, 340.0f, POS_Y_1 - INFO_PAD, "Select Campaign"));
            }
        };
        
        _callbacks[CUSTOM_BUTTON] = [&, this](Ref* ref, Widget::TouchEventType type)
        {
            if(type == Widget::TouchEventType::ENDED && _isButtonClicked == false)
            {
                _sceneState = SCENE_CUSTOM;
                BUTTON_ON(0.3f);
                
                _buttons[CAMPAIGN_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.0f, 0, -350.0f, 0.0f));
                _buttons[MULTIPLAYER_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.1f, 0, -350.0f, 0.0f));
                _buttons[CUSTOM_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.13f, 0, -350.0f, 0.0f));
                _buttons[BACK_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.16f, 255, 0.0f, 135.0f));
                
                _infoLabel->runAction(ACTION_LABEL_DELAY_PLACE_CHANGE(0.25f, 340.0f, POS_Y_1 - INFO_PAD, "Select Custom Game"));
            }
        };

        
        _callbacks[BACK_BUTTON] = [&, this](Ref* ref, Widget::TouchEventType type)
        {
            if(type == Widget::TouchEventType::ENDED && _isButtonClicked == false)
            {
                BUTTON_ON(0.3f);
                
                if( _sceneState == SCENE_PLAY )
                {
                    _sceneState = SCENE_INIT;
                    
                    _buttons[CAMPAIGN_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.0f, 0, -350.0f, 0.0f));
                    _buttons[MULTIPLAYER_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.1f, 0, -350.0f, 0.0f));
                    _buttons[CUSTOM_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.13f, 0, -350.0f, 0.0f));
                    _buttons[BACK_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.16f, 0, -350.0f, 0.0f));
                    
                    _buttons[PLAY_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.19f, 255, 350.0f, 0.0f));
                    _buttons[OPTION_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.22f, 255, 350.0f, 0.0f));
                    _buttons[EXIT_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.25f, 255, 350.0f, 0.0f));
                    
                    _infoLabel->runAction(ACTION_LABEL_DELAY_PLACE_CHANGE(0.25f, 340.0f, POS_Y_3 - INFO_PAD, "Select Menu"));
                }
                
                else if( _sceneState == SCENE_OPTION )
                {
                    _sceneState = SCENE_INIT;
                    
                    _buttons[BACK_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.0f, 0, -350.0f, 0.0f));
                    _buttons[PLAY_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.1f, 255, 350.0f, 0.0f));
                    _buttons[OPTION_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.13f, 255, 350.0f, 0.0f));
                    _buttons[EXIT_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.16f, 255, 350.0f, 0.0f));
                    
                    _infoLabel->runAction(ACTION_LABEL_DELAY_PLACE_CHANGE(0.16f, 340.0f, POS_Y_3 - INFO_PAD, "Select Menu"));
                }
                
                else if( _sceneState == SCENE_CAMPAIGN )
                {
                    _sceneState = SCENE_PLAY;
                    _buttons[BACK_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.0f, 255, 0.0f, -135.0f));
                    _buttons[CAMPAIGN_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.1f, 255, 350.0f, 0.0f));
                    _buttons[MULTIPLAYER_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.13f, 255, 350.0f, 0.0f));
                    _buttons[CUSTOM_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.16f, 255, 350.0f, 0.0f));
                    
                    _infoLabel->runAction(ACTION_LABEL_DELAY_PLACE_CHANGE(0.16f, 340.0f, POS_Y_4 - INFO_PAD, "Select Mode"));
                }
                
                else if( _sceneState == SCENE_MULTIPLAYER )
                {
                    _sceneState = SCENE_PLAY;
                    _buttons[BACK_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.0f, 255, 0.0f, -135.0f));
                    _buttons[CAMPAIGN_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.1f, 255, 350.0f, 0.0f));
                    _buttons[MULTIPLAYER_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.13f, 255, 350.0f, 0.0f));
                    _buttons[CUSTOM_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.16f, 255, 350.0f, 0.0f));
                    
                    _infoLabel->runAction(ACTION_LABEL_DELAY_PLACE_CHANGE(0.16f, 340.0f, POS_Y_4 - INFO_PAD, "Select Mode"));
                }
                
                else if( _sceneState == SCENE_CUSTOM )
                {
                    _sceneState = SCENE_PLAY;
                    _buttons[BACK_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.0f, 255, 0.0f, -135.0f));
                    _buttons[CAMPAIGN_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.1f, 255, 350.0f, 0.0f));
                    _buttons[MULTIPLAYER_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.13f, 255, 350.0f, 0.0f));
                    _buttons[CUSTOM_BUTTON]->runAction(ACTION_DELAY_FADETO_MOVEBY(0.16f, 255, 350.0f, 0.0f));
                    
                    _infoLabel->runAction(ACTION_LABEL_DELAY_PLACE_CHANGE(0.16f, 340.0f, POS_Y_4 - INFO_PAD, "Select Mode"));
                }
            }
        };
        
    }
    
    bool MainMenu2::init()
    {
        if( !Layer::init() )
        {
            return false;
        }
        
        _winSize = Director::getInstance()->getVisibleSize();
        
        
        // _isButtonClicked의 true / false 시간지연 액션을 위한 객체
        _buttonTimer = Node::create();
        _buttonTimer->setVisible(false);
        addChild(_buttonTimer);
        
        initCallbacks();
        
        _title = Sprite::create("game_title.png");
        _title->setPosition(Vec2(180.0f, 550.0f));
        addChild(_title);
        
        _buttons[PLAY_BUTTON] = Button::create("play_btn.png", "play_btn_s.png");
        _buttons[PLAY_BUTTON]->setAnchorPoint(Vec2(1.0f, 0.5f));
        _buttons[PLAY_BUTTON]->setPosition(Vec2(350.0f, POS_Y_1));
        _buttons[PLAY_BUTTON]->addTouchEventListener(_callbacks[PLAY_BUTTON]);
        addChild(_buttons[PLAY_BUTTON]);
        
        _buttons[OPTION_BUTTON] = Button::create("option_btn.png", "option_btn_s.png");
        _buttons[OPTION_BUTTON]->setAnchorPoint(Vec2(1.0f, 0.5f));
        _buttons[OPTION_BUTTON]->setPosition(Vec2(350.0f, POS_Y_2));
        _buttons[OPTION_BUTTON]->addTouchEventListener(_callbacks[OPTION_BUTTON]);
        addChild(_buttons[OPTION_BUTTON]);
        
        _buttons[EXIT_BUTTON] = Button::create("exit_btn.png", "exit_btn_s.png");
        _buttons[EXIT_BUTTON]->setAnchorPoint(Vec2(1.0f, 0.5f));
        _buttons[EXIT_BUTTON]->setPosition(Vec2(350.0f, POS_Y_3));
        _buttons[EXIT_BUTTON]->addTouchEventListener(_callbacks[EXIT_BUTTON]);
        addChild(_buttons[EXIT_BUTTON]);
        
        _buttons[CAMPAIGN_BUTTON] = Button::create("campaign_btn.png", "campaign_btn_s.png");
        _buttons[CAMPAIGN_BUTTON]->setAnchorPoint(Vec2(1.0f, 0.5f));
        _buttons[CAMPAIGN_BUTTON]->setOpacity(0);
        _buttons[CAMPAIGN_BUTTON]->setPosition(Vec2(0.0f, POS_Y_1));
        _buttons[CAMPAIGN_BUTTON]->addTouchEventListener(_callbacks[CAMPAIGN_BUTTON]);
        addChild(_buttons[CAMPAIGN_BUTTON]);
        
        _buttons[MULTIPLAYER_BUTTON] = Button::create("multiplayer_btn.png", "multiplayer_btn_s.png");
        _buttons[MULTIPLAYER_BUTTON]->setAnchorPoint(Vec2(1.0f, 0.5f));
        _buttons[MULTIPLAYER_BUTTON]->setOpacity(0);
        _buttons[MULTIPLAYER_BUTTON]->setPosition(Vec2(0.0f, POS_Y_2));
        _buttons[MULTIPLAYER_BUTTON]->addTouchEventListener(_callbacks[MULTIPLAYER_BUTTON]);
        addChild(_buttons[MULTIPLAYER_BUTTON]);
        
        _buttons[CUSTOM_BUTTON] = Button::create("custom_btn.png", "custom_btn_s.png");
        _buttons[CUSTOM_BUTTON]->setAnchorPoint(Vec2(1.0f, 0.5f));
        _buttons[CUSTOM_BUTTON]->setOpacity(0);
        _buttons[CUSTOM_BUTTON]->setPosition(Vec2(0.0f, POS_Y_3));
        _buttons[CUSTOM_BUTTON]->addTouchEventListener(_callbacks[CUSTOM_BUTTON]);
        addChild(_buttons[CUSTOM_BUTTON]);
        
        _buttons[BACK_BUTTON] = Button::create("back_btn.png", "back_btn_s.png");
        _buttons[BACK_BUTTON]->setAnchorPoint(Vec2(1.0f, 0.5f));
        _buttons[BACK_BUTTON]->setOpacity(0);
        _buttons[BACK_BUTTON]->setPosition(Vec2(0.0f, POS_Y_4));
        _buttons[BACK_BUTTON]->addTouchEventListener(_callbacks[BACK_BUTTON]);
        addChild(_buttons[BACK_BUTTON]);
        
        _infoLabel = Label::createWithSystemFont("Select Menu", "", 20);
        _infoLabel->setAnchorPoint(Vec2(1.0f, 0.5f));
        _infoLabel->setPosition(Vec2(340.0f, POS_Y_3 - INFO_PAD));
        addChild(_infoLabel);
        
        return true;
    }
}







