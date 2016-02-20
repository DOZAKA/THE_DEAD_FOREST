//
//  SingleGameFlow.cpp
//  TheDeadForest
//
//  Created by LSH on 2016. 2. 20..
//
//

#include "SingleGameFlow.hpp"
#include "GameWorld.hpp"
#include "GameManager.hpp"
#include "JoystickEx.hpp"
#include "CircularBezel.hpp"
#include "WeaponStatusEx.hpp"


namespace realtrick
{
    using namespace cocos2d;
    using namespace cocos2d::ui;
    
    void SingleGameFlow::loadGameData()
    {
        GameManager* gameMgr = _gameWorld->getGameManager();
        gameMgr->loadGameMapWithSingle("jsonData.txt");
        EntityHuman* player = gameMgr->getPlayerPtr();
        _gameWorld->setPlayerPtr(player);
        _player = player;
        
        // 화면 출력
        _gameWorld->displayGame();
    }
    
    
    std::function<void(cocos2d::Ref*, const cocos2d::Vec2&, const JoystickEx::ClickEventType&)> SingleGameFlow::getMoveJoystickCallback()
    {
        auto ret = [&, this](cocos2d::Ref* ref, cocos2d::Vec2 dir, JoystickEx::ClickEventType type){
     
            
            _player->setMoving(dir);
            
            switch ( type )
            {
                case JoystickEx::ClickEventType::BEGAN:
                {
                    _player->addInputMask(JoystickMessageTypes::MOVE);
                    
                    break;
                }
                case JoystickEx::ClickEventType::ENDED:
                {
                    _player->removeInputMask(JoystickMessageTypes::MOVE);
                    
                    break;
                }
                case JoystickEx::ClickEventType::DOUBLE_CLICK_BEGAN:
                {
                    _player->addInputMask(JoystickMessageTypes::RUN);
                    
                    break;
                }
                case JoystickEx::ClickEventType::DOUBLE_CLICK_ENDED:
                {
                    _player->removeInputMask(JoystickMessageTypes::RUN);
                    
                    break;
                }
                    
                default: break;
            }
        };

        return ret;
    }
    
    
    std::function<void(cocos2d::Ref*, const cocos2d::Vec2&)> SingleGameFlow::getBelzelCallback()
    {
        auto ret = [&, this](Ref* ref, const Vec2& dir){
            
            _player->setTargetHeading(dir);
            
        };
        
        return ret;
    }
    
    
    std::function<void(cocos2d::Ref*, const cocos2d::ui::Widget::TouchEventType)> SingleGameFlow::getAttackJoystickCallback()
    {
        auto ret = [&, this](Ref* ref, ui::Widget::TouchEventType type){
            
            switch (type)
            {
                case ui::Widget::TouchEventType::BEGAN:
                {
                    _player->addInputMask((int)JoystickMessageTypes::ATTACK_BEGAN);
                    break;
                }
                case ui::Widget::TouchEventType::ENDED:
                {
                    _player->removeInputMask((int)JoystickMessageTypes::ATTACK_BEGAN);
                    _player->addInputMask((int)JoystickMessageTypes::ATTACK_ENDED);
                    break;
                }
                case ui::Widget::TouchEventType::CANCELED:
                {
                    _player->removeInputMask((int)JoystickMessageTypes::ATTACK_BEGAN);
                    _player->addInputMask((int)JoystickMessageTypes::ATTACK_ENDED);
                    break;
                }
                    
                default: break;
            }
            
        };
        
        return ret;
    }
    
}









