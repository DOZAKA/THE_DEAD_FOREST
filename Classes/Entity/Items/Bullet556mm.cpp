//
//  Bullet556mm.cpp
//  TheDeadForest
//
//  Created by mac on 2016. 2. 3..
//
//

#include "Bullet556mm.hpp"
#include "EntityHuman.hpp"
#include "GameManager.hpp"

namespace realtrick
{
    
    Bullet556mm::Bullet556mm(GameManager* mgr) : BulletBase(mgr)
    {
        setEntityType(BULLET_556MM);
        setInformation("5.56mm round informaion.");
        setMaxBandedNumber(30);
    }
    
    
    Bullet556mm::~Bullet556mm()
    {}
    
    
    Bullet556mm* Bullet556mm::create(GameManager* mgr,
                                     const char* inGameImage_n, const char* inGameImage_s, const char* inSlotImage,
                                     cocos2d::ui::Widget::TextureResType texResType)
    {
        Bullet556mm* ret = new (std::nothrow)Bullet556mm(mgr);
        if( ret && ret->init(inGameImage_n, inGameImage_s, inSlotImage, texResType))
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    
    Bullet556mm* Bullet556mm::clone() const
    {
        return new Bullet556mm(*this);
    }
    
    
    void Bullet556mm::discard()
    {
        Bullet556mm* item = Bullet556mm::create(_gameMgr, getInGameFrameName_n().c_str(), getInGameFrameName_s().c_str(), getInSlotFrameName().c_str(), ui::Widget::TextureResType::PLIST);
        item->setAmount( getAmount() );
        item->setPosition(Vec2(_owner->getPosition().x + 50.0f, _owner->getPosition().y));
        _gameMgr->registEntity(item, _gameMgr->getNextValidID(), Z_ORDER_ITEMS);
    }
    
}