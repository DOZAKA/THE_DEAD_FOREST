//
//  Inventory.hpp
//  TheDeadForest-v2
//
//  Created by mac on 2016. 2. 20..
//
//

#pragma once

#include "cocos2d.h"
#include "CocosGUI.h"

namespace realtrick
{
    namespace userinterface
    {
        class ItemSlot;
        
        class Inventory : public cocos2d::Node
        {
            
        public:
            
            static Inventory* create();
            
        private:
            
            cocos2d::ui::ImageView*         _backgroundView;
            cocos2d::ui::ScrollView*        _slotScrollView;
            std::vector<ItemSlot*>          _slots;
            
            cocos2d::Size                   _slotSize;
            int                             _numOfSlotX;
            int                             _numOfSlotY;
            
        private:
            
            Inventory();
            
            virtual ~Inventory();
            
            bool init() override;
            
        };
        
    }
}









