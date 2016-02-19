//
//  ItemM16A2.cpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 13..
//
//

#include "ItemM16A2.hpp"
#include "EntityHuman.hpp"
#include "GameManager.hpp"

using namespace cocos2d;

namespace realtrick
{
    
    ItemM16A2::ItemM16A2(GameManager* mgr) : WeaponBase(mgr)
    {
        setEntityType(ITEM_M16A2);
        setInformation("M16A2 informaion.");
        setRange(128.0f);
        setDamage(24);
        setMaxRounds(30);
        setNumOfLeftRounds(0);
    }
    
    
    ItemM16A2::~ItemM16A2()
    {}
    
    
    ItemM16A2* ItemM16A2::create(GameManager* mgr,
                                 const char* inGameImage_n, const char* inGameImage_s, const char* inSlotImage,
                                 cocos2d::ui::Widget::TextureResType texResType)
    {
        ItemM16A2* ret = new (std::nothrow)ItemM16A2(mgr);
        if( ret && ret->init(inGameImage_n, inGameImage_s, inSlotImage, texResType))
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    
    ItemBase* ItemM16A2::clone() const
    {
        return new ItemM16A2(*this);
    }
    
    
    void ItemM16A2::inWeapon()
    {
        _owner->getFSM()->changeState(&HumanM16A2In::getInstance());
    }
    
    
    void ItemM16A2::outWeapon()
    {
        _owner->getFSM()->changeState(&HumanM16A2Out::getInstance());
    }
    
    void ItemM16A2::attack()
    {
//        if ( _numOfLeftRounds > 0 )
//        {
//            log("<ItemM16A2::attack> attack!");
//            _numOfLeftRounds--;
//            const std::list<EntityBase*>& members = _gameMgr->getCameraNeighbor();
//            for (const auto &d : members)
//            {
//                if ( d == this ) continue;
//                
//                if ( d->getEntityType() == ENTITY_HUMAN )
//                {
//                    if( physics::intersect(Segment(_owner->getWorldPosition(), _owner->getWorldPosition() + _owner->getHeading() * 1000.0f),
//                                           Circle(d->getWorldPosition(), 20.0f)) )
//                    {
//                        log("<ItemM16A2::attack> hit!!");
//                        Dispatch.pushMessage(0.0, d, _owner, MessageType::RUN_BACK_DEAD, nullptr);
//                        break;
//                    }
//                }
//            }
//        }
//        else
//        {
//            log("<ItemM16A2::attack> Number Of Left Rounds is 0.");
//        }
    }
    
    void ItemM16A2::discard()
    {
        ItemM16A2* item = ItemM16A2::create(_gameMgr, getInGameFrameName_n().c_str(), getInGameFrameName_s().c_str(), getInSlotFrameName().c_str(), ui::Widget::TextureResType::PLIST);
        item->setAmount( getAmount() );
        item->setNumOfLeftRounds(getNumOfLeftRounds());
        item->setPosition(Vec2(_owner->getPosition().x + 50.0f, _owner->getPosition().y));
        _gameMgr->registEntity(item, _gameMgr->getNextValidID(), Z_ORDER_ITEMS);
    }
    
    
}





