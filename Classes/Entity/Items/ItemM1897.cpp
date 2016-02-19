//
//  ItemM1897.cpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 13..
//
//

#include "ItemM1897.hpp"
#include "EntityHuman.hpp"
#include "GameManager.hpp"

using namespace cocos2d;

namespace realtrick
{
    
    ItemM1897::ItemM1897(GameManager* mgr) : WeaponBase(mgr)
    {
        setEntityType(ITEM_M1897);
        setInformation("M1897 informaion.");
    }
    
    
    ItemM1897::~ItemM1897()
    {}
    
    
    ItemM1897* ItemM1897::create(GameManager* mgr,
                                 const char* inGameImage_n, const char* inGameImage_s, const char* inSlotImage,
                                 cocos2d::ui::Widget::TextureResType texResType)
    {
        ItemM1897* ret = new (std::nothrow)ItemM1897(mgr);
        if( ret && ret->init(inGameImage_n, inGameImage_s, inSlotImage, texResType))
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    ItemBase* ItemM1897::clone() const
    {
        return new ItemM1897(*this);
    }
    
    
    void ItemM1897::inWeapon()
    {
       // _owner->getFSM()->changeState(&HumanM1897In::getInstance());
    }
    
    
    void ItemM1897::outWeapon()
    {
       // _owner->getFSM()->changeState(&HumanM1897Out::getInstance());
    }
    
    void ItemM1897::discard()
    {
        ItemM1897* item = ItemM1897::create(_gameMgr, getInGameFrameName_n().c_str(), getInGameFrameName_s().c_str(), getInSlotFrameName().c_str(), ui::Widget::TextureResType::PLIST);
        item->setAmount( getAmount() );
        item->setNumOfLeftRounds(getNumOfLeftRounds());
        item->setPosition(Vec2(_owner->getPosition().x + 50.0f, _owner->getPosition().y));
        _gameMgr->registEntity(item, _gameMgr->getNextValidID(), Z_ORDER_ITEMS);
    }
    
}





