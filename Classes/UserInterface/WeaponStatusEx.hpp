//
//  WeaponStatusEx.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 2. 2..
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace realtrick
{
    
    class GameManager;
    class EntityHuman;
    class WeaponBase;
    
    class WeaponStatusEx : public cocos2d::Node
    {
        
    public:
        
        static WeaponStatusEx* create(const char* normal, const char* selected,
                                      cocos2d::ui::Widget::TextureResType texResType = cocos2d::ui::Widget::TextureResType::LOCAL);
    
        void setReloadButtonCallback(const cocos2d::ui::Widget::ccWidgetTouchCallback& callback) { _reloadCallback = callback; }
        
    private:
        
        WeaponBase*                                             _currWeapon;
        cocos2d::ui::Button*                                    _reloadButton;
        cocos2d::ui::Widget::ccWidgetTouchCallback              _reloadCallback;
        
    private:
        
        WeaponStatusEx();
        virtual ~WeaponStatusEx();
        bool init(const char* normal, const char* selected, cocos2d::ui::Widget::TextureResType texResType);
        
    };
    
}
