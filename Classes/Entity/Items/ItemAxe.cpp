//
//  ItemAxe.cpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 13..
//
//

#include "ItemAxe.hpp"
#include "EntityHuman.hpp"
#include "GameManager.hpp"
#include "GameWorld.hpp"

using namespace cocos2d;

namespace realtrick
{
    
    ItemAxe::ItemAxe(GameManager* mgr) : WeaponBase(mgr)
    {
        setEntityType(ITEM_AXE);
        setInformation("Axe informaion.");
        
        _numOfLeftRounds = 999;
        _maxRounds = 999;
        _damage = 100;
        setRange(64.0f);
    }
    
    
    ItemAxe::~ItemAxe()
    {}
    
    
    ItemAxe* ItemAxe::create(GameManager* mgr, const char* inGameImage_n, const char* inGameImage_s, const char* inSlotImage, cocos2d::ui::Widget::TextureResType texResType)
    {
        ItemAxe* ret = new (std::nothrow)ItemAxe(mgr);
        if( ret && ret->init(inGameImage_n, inGameImage_s, inSlotImage, texResType))
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    
    ItemBase* ItemAxe::clone() const
    {
        return new ItemAxe(*this);
    }
    
    
    void ItemAxe::inWeapon()
    {
        _owner->getFSM()->changeState(&HumanAxeIn::getInstance());
    }
    
    
    void ItemAxe::outWeapon()
    {
        _owner->getFSM()->changeState(&HumanAxeOut::getInstance());
    }
    
    void ItemAxe::attack()
    {
        log("<ItemAxe::attack> attack!");
    }
    
    void ItemAxe::discard()
    {
        ItemAxe* item = ItemAxe::create(_gameMgr, getInGameFrameName_n().c_str(), getInGameFrameName_s().c_str(), getInSlotFrameName().c_str(), ui::Widget::TextureResType::PLIST);
        item->setAmount( getAmount() );
        item->setNumOfLeftRounds(getNumOfLeftRounds());
        item->setPosition(Vec2(_owner->getPosition().x + 50.0f, _owner->getPosition().y));
        _gameMgr->registEntity(item, _gameMgr->getNextValidID(), Z_ORDER_ITEMS);
    }
}





