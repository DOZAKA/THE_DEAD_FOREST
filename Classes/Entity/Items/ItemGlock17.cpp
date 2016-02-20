//
//  ItemGlock17.cpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 13..
//
//

#include "ItemGlock17.hpp"
#include "EntityHuman.hpp"
#include "GameManager.hpp"

using namespace cocos2d;

namespace realtrick
{
    
    ItemGlock17::ItemGlock17(GameManager* mgr) : WeaponBase(mgr)
    {
        setEntityType(ITEM_GLOCK17);
        setInformation("Glock17 informaion.");
        setRange(128.0f);
        setDamage(51);
        setMaxRounds(17);
        setNumOfLeftRounds(0);
    }
    
    
    ItemGlock17::~ItemGlock17()
    {}
    
    
    ItemGlock17* ItemGlock17::create(GameManager* mgr,
                                     const char* inGameImage_n, const char* inGameImage_s, const char* inSlotImage,
                                     cocos2d::ui::Widget::TextureResType texResType)
    {
        ItemGlock17* ret = new (std::nothrow)ItemGlock17(mgr);
        if( ret && ret->init(inGameImage_n, inGameImage_s, inSlotImage, texResType))
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    
    ItemBase* ItemGlock17::clone() const
    {
        return new ItemGlock17(*this);
    }
    
    
    ItemGlock17::ItemGlock17(const ItemGlock17& rhs) : WeaponBase(rhs)
    {}
    
    
    void ItemGlock17::inWeapon()
    {
        _owner->getFSM()->changeState(&HumanGlock17In::getInstance());
    }
    
    
    void ItemGlock17::outWeapon()
    {
        _owner->getFSM()->changeState(&HumanGlock17Out::getInstance());
    }
    
    void ItemGlock17::attack()
    {
        if ( _numOfLeftRounds > 0 )
        {
            log("<ItemGlock17::attack> attack!");
            _numOfLeftRounds--;
            
//            const std::list<EntityBase*>& members = _gameMgr->getCameraNeighbor();
//            for (const auto &d : members)
//            {
//                if ( d == this ) continue;
//                
//                if ( d->getEntityType() == ENTITY_HUMAN )
//                {
//                    if( physics::intersect(Segment(_owner->getPosition(), _owner->getPosition() + _owner->getHeading() * 1000.0f),
//                                           Circle(d->getPosition(), 20.0f)) )
//                    {
//                        log("<ItemGlock17::attack> hit!!");
//                        Dispatch.pushMessage(0.0, d, _owner, MessageType::RUN_BACK_DEAD, nullptr);
//                        break;
//                    }
//                }
//            }
            
            
        }
        else
        {
            log("<ItemGlock17::attack> Number Of Left Rounds is 0.");
        }
    }

    
    void ItemGlock17::discard()
    {
        ItemGlock17* item = ItemGlock17::create(_gameMgr, getInGameFrameName_n().c_str(), getInGameFrameName_s().c_str(), getInSlotFrameName().c_str(), ui::Widget::TextureResType::PLIST);
        item->setAmount( getAmount() );
        item->setNumOfLeftRounds( getNumOfLeftRounds() );
        item->setPosition(Vec2(_owner->getPosition().x + 50.0f, _owner->getPosition().y));
        _gameMgr->registEntity(item, _gameMgr->getNextValidID(), Z_ORDER_ITEMS);
    }
    
}





