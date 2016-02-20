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
        
        class ItemSlot : public cocos2d::ui::Button
        {
            
        public:
            
            static ItemSlot* create(const char* normal, const char* selected, cocos2d::ui::Widget::TextureResType texType = cocos2d::ui::Widget::TextureResType::LOCAL);
            
            void addTouchCallback(const cocos2d::ui::Widget::ccWidgetTouchCallback& callback) { _touchCallbacks.push_back(callback); }
            
            void setSelected(bool enable) { _isSelected = enable; _selectedImage->setVisible(enable); }
            
            bool isSelected() const { return _isSelected; }
            
            void toggleSelected() { _isSelected ? setSelected(false) : setSelected(true); }
            
        private:
            
            cocos2d::Sprite*                                                _selectedImage;
            
            std::vector<cocos2d::ui::Widget::ccWidgetTouchCallback>         _touchCallbacks;
            
            bool                                                            _isSelected;
            
        private:
            
            bool init(const char* normal, const char* selected, cocos2d::ui::Widget::TextureResType texType);
            
            ItemSlot();
            
            virtual ~ItemSlot();
            
        };
        
    }
}









