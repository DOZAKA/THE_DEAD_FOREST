//
//  ButtonHolder.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 2. 19..
//
//

#pragma once

#include "cocos2d.h"
#include "CocosGUI.h"

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
            
        private:
            
            GameManager*                _gameMgr;
            cocos2d::ui::CheckBox*      _status;
            cocos2d::ui::CheckBox*      _inventory;
            cocos2d::ui::CheckBox*      _setting;
            
        private:
            
            cocos2d::Size               _buttonSize;
            
            
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