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
            
            
            _status = ui::CheckBox::create("status.png", "status_s.png");
            _status->setPosition(Vec2(-100, -50));
            _status->addEventListener([this](Ref* ref, const ui::CheckBox::EventType& type){
                
                for( const auto& callback : _statusButtonCallbacks )
                {
                    callback.second(ref, type);
                }
                
            });
            addChild(_status);
            
            
            _inventory = ui::CheckBox::create("inventory.png", "inventory_s.png");
            _inventory->setPosition(Vec2(0, 0));
            _inventory->addEventListener([this](Ref* ref, const ui::CheckBox::EventType& type){
                
                for( const auto& callback : _inventoryButtonCallbacks )
                {
                    callback.second(ref, type);
                }
                
            });
            addChild(_inventory);
            
            
            _setting = ui::CheckBox::create("setting.png", "setting_s.png");
            _setting->setPosition(Vec2(100, -50));
            _setting->addEventListener([this](Ref* ref, const ui::CheckBox::EventType& type){
                
                for( const auto& callback : _settingButtonCallbacks )
                {
                    callback.second(ref, type);
                }
                
            });
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
        
        
        void ButtonHolder::addStausButtonEvent(int key, const cocos2d::ui::CheckBox::ccCheckBoxCallback& callback)
        {
            _statusButtonCallbacks.insert(std::make_pair(key, callback));
        }
        
        
        void ButtonHolder::addInventoryButtonEvent(int key, const cocos2d::ui::CheckBox::ccCheckBoxCallback& callback)
        {
            _inventoryButtonCallbacks.insert(std::make_pair(key, callback));
        }
        
        
        void ButtonHolder::addSettingButtonEvent(int key, const cocos2d::ui::CheckBox::ccCheckBoxCallback& callback)
        {
            _settingButtonCallbacks.insert(std::make_pair(key, callback));
        }
        
        
    }
}









