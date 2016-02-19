//
//  WeaponStatusEx.cpp
//  TheDeadForest
//
//  Created by mac on 2016. 2. 2..
//
//

#include "WeaponStatusEx.hpp"

using namespace cocos2d;

namespace realtrick
{
    
    WeaponStatusEx::WeaponStatusEx()
    {
    }
    
    WeaponStatusEx::~WeaponStatusEx()
    {
    }
    
    WeaponStatusEx* WeaponStatusEx::create(const char* normal, const char* selected, cocos2d::ui::Widget::TextureResType texResType)
    {
        WeaponStatusEx* ret = new (std::nothrow) WeaponStatusEx();
        if( ret && ret->init(normal, selected, texResType) )
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    
    bool WeaponStatusEx::init(const char* normal, const char* selected, cocos2d::ui::Widget::TextureResType texResType)
    {
        _reloadButton = ui::Button::create(normal, selected, "", texResType);
        addChild(_reloadButton);
        
        _reloadButton->addTouchEventListener([&, this](Ref* ref, ui::Widget::TouchEventType type) {
            
            _reloadCallback(this, type);
            
            switch (type)
            {
                case ui::Widget::TouchEventType::BEGAN:
                {
                    break;
                }
                case ui::Widget::TouchEventType::MOVED:
                {
                    break;
                }
                case ui::Widget::TouchEventType::ENDED:
                {
                    break;
                }
                case ui::Widget::TouchEventType::CANCELED:
                {
                    break;
                }
                default: break;
            }
            
        });
        
        return true;
    }
    
}





