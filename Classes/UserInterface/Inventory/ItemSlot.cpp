//
//  ItemSlot.cpp
//  TheDeadForest-v2
//
//  Created by mac on 2016. 2. 20..
//
//

#include "ItemSlot.hpp"
#include "ItemBase.hpp"

namespace realtrick
{
    namespace userinterface
    {
        
        using namespace cocos2d;
        
        ItemSlot::ItemSlot() :
        _selectedImage(nullptr),
        _isSelected(false),
        _item(nullptr)
        {}
        
        
        ItemSlot::~ItemSlot()
        {
        }
        
        
        ItemSlot* ItemSlot::create(const char* normal, const char* selected, cocos2d::ui::Widget::TextureResType texType)
        {
            ItemSlot* ret = new (std::nothrow) ItemSlot();
            if ( ret && ret->init(normal, selected, texType) )
            {
                ret->autorelease();
                return ret;
            }
            CC_SAFE_DELETE(ret);
            return nullptr;
        }
        
        
        bool ItemSlot::init(const char* normal, const char* selected, cocos2d::ui::Widget::TextureResType texType)
        {
            if ( !Widget::init() )
            {
                return false;
            }
            
            loadTextures(normal, normal, "", texType);
            setZoomScale(1.0f);
            
            if ( texType == ui::Widget::TextureResType::LOCAL )
                _selectedImage = Sprite::create(selected);
            else
                _selectedImage = Sprite::createWithSpriteFrameName(selected);
            
            _selectedImage->setPosition(getContentSize() / 2);
            addChild(_selectedImage);
            
            _setSelected(false);
            
            addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType type){
                
                for ( const auto& callback : _touchCallbacks )
                    callback(ref, type);
                
            });
            
            return true;
        }
        
        
        void ItemSlot::setItem(ItemBase *item)
        {
            _item = item;
        }
        
        
        void ItemSlot::removeItem()
        {
            
        }
        
        
        void ItemSlot::_useItem()
        {
            
        }
        
    }
}









