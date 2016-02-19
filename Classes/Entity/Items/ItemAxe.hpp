//
//  ItemAxe.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 13..
//
//

#pragma once

#include "WeaponBase.hpp"
#include "CocosGUI.h"

namespace realtrick
{
    
    class ItemAxe : public WeaponBase
    {
        
    public:
        
        static ItemAxe* create(GameManager* mgr,
                               const char* inGameImage_n, const char* inGameImage_s, const char* inSlotImage,
                               cocos2d::ui::Widget::TextureResType texResType = cocos2d::ui::Widget::TextureResType::LOCAL);
        
        virtual ItemBase* clone() const override;
        
        virtual void inWeapon() override;
        
        virtual void outWeapon() override;
        
        virtual void attack() override;
        
        virtual void discard() override;
        
    private:
        
        ItemAxe(GameManager* mgr);
        
        virtual ~ItemAxe();
        
    };
    
}




