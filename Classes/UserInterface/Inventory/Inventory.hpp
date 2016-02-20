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
            
            cocos2d::ui::ScrollView*        _slotScrollView;
            std::vector<ItemSlot*>          _slots;
            
        private:
            
            Inventory();
            
            virtual ~Inventory();
            
            bool init() override;
            
        };
        
    }
}









