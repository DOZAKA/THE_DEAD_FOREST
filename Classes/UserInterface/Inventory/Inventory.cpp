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
        
        Inventory::Inventory() :
        _backgroundView(nullptr),
        _slotScrollView(nullptr),
        _slotSize(Size(Prm.getValueAsFloat("slotWidth"), Prm.getValueAsFloat("slotHeight"))),
        _numOfSlotX(Prm.getValueAsInt("numOfSlotX")),
        _numOfSlotY(Prm.getValueAsInt("numOfSlotY"))
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
            
            _backgroundView = ui::ImageView::create("inventory_background_view.png", ui::Widget::TextureResType::LOCAL);
            addChild(_backgroundView);
            
            _slotScrollView = ui::ScrollView::create();
            _slotScrollView->setPosition(Vec2(20.0f, 20.0f));
            _slotScrollView->setContentSize(Size(Prm.getValueAsFloat("inventoryScrollViewWidth"), Prm.getValueAsFloat("inventoryScrollViewHeight")));
            _slotScrollView->setInnerContainerSize(Size(Prm.getValueAsFloat("inventoryScrollViewWidth"), _slotSize.height * _numOfSlotY + (_numOfSlotY + 1 * 20.0f)));
            _backgroundView->addChild(_slotScrollView);
            
            _slotScrollView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
            _slotScrollView->setBackGroundColor(Color3B::YELLOW);
            _slotScrollView->setScrollBarEnabled(true);
            
            return true;
        }
        
    }
}









