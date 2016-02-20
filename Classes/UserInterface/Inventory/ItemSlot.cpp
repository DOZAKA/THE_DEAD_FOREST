//
//  ItemSlot.cpp
//  TheDeadForest-v2
//
//  Created by mac on 2016. 2. 20..
//
//

#include "ItemSlot.hpp"

namespace realtrick
{
    namespace userinterface
    {
        
        using namespace cocos2d;
        
        ItemSlot::ItemSlot()
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
            
            setSelected(false);
            loadTextures(normal, "", selected, "", "", texType);
            
            return true;
        }
        
    }
}









