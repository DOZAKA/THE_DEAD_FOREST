//
//  MainMenu2.hpp
//  TheDeadForest
//
//  Created by mac on 2015. 12. 23..
//
//

#pragma once

#include <vector>
#include <functional>

#include "cocos2d.h"
#include "CocosGUI.h"


#define BUTTON_ON(delay) \
do { _isButtonClicked = true; \
_buttonTimer->runAction(Sequence::create(DelayTime::create(delay), \
                                         CallFunc::create([&, this]{ _isButtonClicked = false; }), \
                                         nullptr));} while(0)

#define ACTION_DELAY_FADETO_MOVEBY(delay,opacity,x,y) \
Sequence::create(DelayTime::create(delay), \
                 Spawn::create(FadeTo::create(0.3f, opacity), \
                               EaseIn::create(MoveBy::create(0.3f, Vec2(x, y)), 3.0f), \
                               nullptr), \
                 nullptr)

#define ACTION_PLACE_DELAY_FADETO_MOVEBY(px, py, delay, opacity, mx, my) \
Sequence::create(Place::create(Vec2(px, py)), \
                 DelayTime::create(delay), \
                 Spawn::create(FadeTo::create(0.3f, opacity), \
                               EaseIn::create(MoveBy::create(0.3f, Vec2(mx, my)), 3.0f), \
                               nullptr), \
                 nullptr)

#define ACTION_LABEL_DELAY_PLACE_CHANGE(delay, x, y, string) \
Sequence::create(FadeTo::create(0.1f, 0), \
                 CallFunc::create([&, this]{ _infoLabel->setPosition(Vec2(x, y)); _infoLabel->setString(string); }),\
                 DelayTime::create(delay), \
                 FadeTo::create(0.3f, 255),\
                 nullptr)

#define POS_Y_1 450.0f
#define POS_Y_2 405.0f
#define POS_Y_3 360.0f
#define POS_Y_4 315.0f

#define INFO_PAD 40.0f

namespace realtrick
{
    
    class MainMenu2 : public cocos2d::Layer
    {
        
    public:
        
        static MainMenu2* create();
        static cocos2d::Scene* createScene();
        virtual bool init() override;
        
        void initCallbacks();
        
    private:
        
        typedef std::function<void(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType)> ButtonCallBack;
        
        enum Buttons
        {
            PLAY_BUTTON = 0,
            OPTION_BUTTON,
            EXIT_BUTTON,
            BACK_BUTTON,
            CAMPAIGN_BUTTON,
            MULTIPLAYER_BUTTON,
            CUSTOM_BUTTON,
            
            
            BUTTON_NUM
        };
        
        enum SceneState
        {
            SCENE_INIT = 0,
            SCENE_PLAY,
            SCENE_OPTION,
            SCENE_CAMPAIGN,
            SCENE_MULTIPLAYER,
            SCENE_CUSTOM,
            
            SCENE_NUM
        };
        
        cocos2d::Size                       _winSize;
        
        cocos2d::Sprite*                    _title;
        cocos2d::ui::Button*                _buttons[BUTTON_NUM];
        ButtonCallBack                      _callbacks[BUTTON_NUM];
        bool                                _isButtonClicked;
        cocos2d::Node*                      _buttonTimer;
        cocos2d::Label*                     _infoLabel;
        int                                 _sceneState = SCENE_INIT;
        
    };
    
}





