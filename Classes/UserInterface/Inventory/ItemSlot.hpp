//
//  ItemSlot.hpp
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
        
        class ItemSlot : public cocos2d::ui::CheckBox
        {
            
        public:
            
            static ItemSlot* create(const char* normal, const char* selected, cocos2d::ui::Widget::TextureResType texType = cocos2d::ui::Widget::TextureResType::LOCAL);
            
        private:
            
            bool init(const char* normal, const char* selected, cocos2d::ui::Widget::TextureResType texType);
            ItemSlot();
            virtual ~ItemSlot();
            
        };
        
    }
}









