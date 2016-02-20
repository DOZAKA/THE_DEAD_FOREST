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
    
    class ItemBase;
    
    namespace userinterface
    {
        
        class ItemSlot : public cocos2d::ui::Button
        {
            
        public:
            
            static ItemSlot* create(const char* normal, const char* selected, cocos2d::ui::Widget::TextureResType texType = cocos2d::ui::Widget::TextureResType::LOCAL);
            
            void addTouchCallback(const cocos2d::ui::Widget::ccWidgetTouchCallback& callback) { _touchCallbacks.push_back(callback); }
            
            bool isSelected() const { return _isSelected; }
            
            bool tryDisableSelected() { if (_isSelected) { toggleSelected(); return true; } return false; }
            
            void toggleSelected() { _isSelected ? _setSelected(false) : _setSelected(true); }
            
            void setItem(ItemBase* item);
            
            void removeItem();
            
            ItemBase* getItemPtr() { return _item; }
            
        private:
            
            cocos2d::Sprite*                                                _selectedImage;
            
            std::vector<cocos2d::ui::Widget::ccWidgetTouchCallback>         _touchCallbacks;
            
            bool                                                            _isSelected;
            
            ItemBase*                                                       _item;
            
        private:
            
            bool init(const char* normal, const char* selected, cocos2d::ui::Widget::TextureResType texType);
            
            ItemSlot();
            
            virtual ~ItemSlot();
            
            void _setSelected(bool enable) { _isSelected = enable; _selectedImage->setVisible(enable); }
            
            void _useItem();
            
        };
        
    }
}









