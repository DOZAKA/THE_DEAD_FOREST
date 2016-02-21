//
//  ButtonHolder.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 2. 19..
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace realtrick
{
    
    class GameManager;
    
    namespace userinterface
    {
        
        class ButtonHolder : public cocos2d::Node
        {
            
        public:
            
            static ButtonHolder* create(GameManager* mgr);
            
            void setButtonSize(cocos2d::Size size);
            
            void addStausButtonEvent(int key, const cocos2d::ui::CheckBox::ccCheckBoxCallback& callback);
            
            void addInventoryButtonEvent(int key, const cocos2d::ui::CheckBox::ccCheckBoxCallback& callback);
            
            void addSettingButtonEvent(int key, const cocos2d::ui::CheckBox::ccCheckBoxCallback& callback);
            
            void detachStatusButtonEvent(int key)       { _statusButtonCallbacks.erase(key); }
            
            void detachInventoryButtonEvent(int key)    { _inventoryButtonCallbacks.erase(key); }

            void detachSettingButtonEvent(int key)      { _settingButtonCallbacks.erase(key); }
            
        private:
            
            GameManager*                _gameMgr;
            
            cocos2d::ui::CheckBox*      _status;
            
            cocos2d::ui::CheckBox*      _inventory;
            
            cocos2d::ui::CheckBox*      _setting;
            
        private:
            
            cocos2d::Size                                                   _buttonSize;
            
            std::map<int, cocos2d::ui::CheckBox::ccCheckBoxCallback>        _statusButtonCallbacks;
            
            std::map<int,cocos2d::ui::CheckBox::ccCheckBoxCallback>         _inventoryButtonCallbacks;
            
            std::map<int,cocos2d::ui::CheckBox::ccCheckBoxCallback>         _settingButtonCallbacks;
            
        private:
            
            explicit ButtonHolder(GameManager* mgr);
            
            virtual ~ButtonHolder();
            
            virtual bool init() override;
            
            void _disableButtons();
            
            void _enableStatusButton()      { _status->setSelected(true); }
            
            void _enableInventoryButton()   { _inventory->setSelected(true); }
            
            void _enableSettingButton()     { _setting->setSelected(true); }
            
        };
    }
    
}









