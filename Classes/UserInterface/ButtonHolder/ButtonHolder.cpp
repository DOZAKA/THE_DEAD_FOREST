//
//  ButtonHolder.cpp
//  TheDeadForest
//
//  Created by mac on 2016. 2. 19..
//
//

#include "ButtonHolder.hpp"
#include "GameManager.hpp"

namespace realtrick
{
    namespace userinterface
    {
        
        using namespace cocos2d;
        
        ButtonHolder::ButtonHolder(GameManager* mgr) :
        _gameMgr(mgr),
        _status(nullptr),
        _inventory(nullptr),
        _setting(nullptr)
        {}
        
        
        ButtonHolder::~ButtonHolder()
        {
            
        }
        
        
        ButtonHolder* ButtonHolder::create(GameManager* mgr)
        {
            ButtonHolder* ret = new (std::nothrow) ButtonHolder(mgr);
            if ( ret && ret->init() )
            {
                ret->autorelease();
                return ret;
            }
            CC_SAFE_DELETE(ret);
            return nullptr;
        }
        
        
        bool ButtonHolder::init()
        {
            if ( !Node::init() )
            {
                return false;
            }
            
            _status = ui::CheckBox::create("status.png", "status.png");
            _status->setPosition(Vec2(-100, -50));
            _status->addEventListener([](Ref* ref, const ui::CheckBox::EventType& type){
                
                switch ( type )
                {
                    case ui::CheckBox::EventType::SELECTED:
                    {
                        break;
                    }
                    case ui::CheckBox::EventType::UNSELECTED:
                    {
                        break;
                    }
                    default: break;
                }
                
            });
            addChild(_status);
            
            _inventory = ui::CheckBox::create("inventory.png", "inventory.png");
            _inventory->setPosition(Vec2(0, 0));
            addChild(_inventory);
            
            _setting = ui::CheckBox::create("setting.png", "setting.png");
            _setting->setPosition(Vec2(100, -50));
            addChild(_setting);
            
            return true;
        }
        
        
        void ButtonHolder::setButtonSize(cocos2d::Size size)
        {
            _status->setScale(size.width / _status->getContentSize().width, size.height / _status->getContentSize().height);
            _inventory->setScale(size.width / _inventory->getContentSize().width, size.height / _inventory->getContentSize().height);
            _setting->setScale(size.width / _setting->getContentSize().width, size.height / _setting->getContentSize().height);
        }
      
        void ButtonHolder::_disableButtons()
        {
            _status->setSelected(false);
            _inventory->setSelected(false);
            _setting->setSelected(false);
        }
        
    }
}









