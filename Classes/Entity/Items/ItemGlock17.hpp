//
//  ItemGlock17.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 13..
//
//

#pragma once

#include "WeaponBase.hpp"
#include "ui/CocosGUI.h"

namespace realtrick
{
    
    class ItemGlock17 : public WeaponBase
    {
        
    public:
        
        static ItemGlock17* create(GameManager* mgr,
                                   const char* inGameImage_n, const char* inGameImage_s, const char* inSlotImage,
                                   cocos2d::ui::Widget::TextureResType texResType = cocos2d::ui::Widget::TextureResType::LOCAL);
        
        virtual ItemBase* clone() const override;
        
        virtual void inWeapon() override;
        
        virtual void outWeapon() override;
        
        virtual void attack() override;
        
        virtual void discard() override;
        
    private:
        
        ItemGlock17(GameManager* mgr);
        ItemGlock17(const ItemGlock17& rhs);
        virtual ~ItemGlock17();
        
    };
    
}





