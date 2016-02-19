//
//  ItemM16A2.hpp
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
    
    class ItemM16A2 : public WeaponBase
    {
        
    public:
        
        static ItemM16A2* create(GameManager* mgr,
                                 const char* inGameImage_n, const char* inGameImage_s, const char* inSlotImage,
                                 cocos2d::ui::Widget::TextureResType texResType = cocos2d::ui::Widget::TextureResType::LOCAL);
        
        virtual ItemBase* clone() const override;
        
        virtual void inWeapon() override;
        
        virtual void outWeapon() override;
        
        virtual void attack() override;
        
        virtual void discard() override;
        
    private:
        
        ItemM16A2(GameManager* mgr);
        
        virtual ~ItemM16A2();
        
    };
    
}




