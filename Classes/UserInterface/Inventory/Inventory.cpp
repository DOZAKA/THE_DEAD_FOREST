//
//  Inventory.cpp
//  TheDeadForest-v2
//
//  Created by mac on 2016. 2. 20..
//
//

#include "Inventory.hpp"
#include "ParamLoader.hpp"

namespace realtrick
{
    namespace userinterface
    {
        
        using namespace cocos2d;
        
        Inventory::Inventory()
        {}
        
        
        Inventory::~Inventory()
        {
            
        }
        
        
        Inventory* Inventory::create()
        {
            Inventory* ret = new (std::nothrow) Inventory();
            if ( ret && ret->init() )
            {
                ret->autorelease();
                return ret;
            }
            CC_SAFE_DELETE(ret);
            return nullptr;
        }
        
        
        bool Inventory::init()
        {
            if ( !Node::init() )
                return false;
            
            _slotScrollView = ui::ScrollView::create();
            _slotScrollView->setAnchorPoint(Vec2(0.5f, 0.5f));
            _slotScrollView->setContentSize(Size(Prm.getValueAsFloat("inventoryScrollViewWidth"), Prm.getValueAsFloat("inventoryScrollViewHeight")));
            addChild(_slotScrollView);
            
            _slotScrollView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
            _slotScrollView->setBackGroundColor(Color3B::WHITE);
            _slotScrollView->setScrollBarEnabled(true);
            
            return true;
        }
        
    }
}









