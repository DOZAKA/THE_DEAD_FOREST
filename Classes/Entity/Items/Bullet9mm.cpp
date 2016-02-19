//
//  Bullet9mm.cpp
//  TheDeadForest
//
//  Created by mac on 2016. 2. 3..
//
//

#include "Bullet9mm.hpp"
#include "EntityHuman.hpp"
#include "GameManager.hpp"

namespace realtrick
{
    
    Bullet9mm::Bullet9mm(GameManager* mgr) : BulletBase(mgr)
    {
        setEntityType(BULLET_9MM);
        setInformation("9mm round informaion.");
        setMaxBandedNumber(30);
    }
    
    
    Bullet9mm::~Bullet9mm()
    {}
    
    
    Bullet9mm* Bullet9mm::create(GameManager* mgr,
                                 const char* inGameImage_n, const char* inGameImage_s, const char* inSlotImage,
                                 cocos2d::ui::Widget::TextureResType texResType)
    {
        Bullet9mm* ret = new (std::nothrow)Bullet9mm(mgr);
        if( ret && ret->init(inGameImage_n, inGameImage_s, inSlotImage, texResType))
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    
    Bullet9mm* Bullet9mm::clone() const
    {
        return new Bullet9mm(*this);
    }
    
    
    void Bullet9mm::discard()
    {
        Bullet9mm* item = Bullet9mm::create(_gameMgr, getInGameFrameName_n().c_str(), getInGameFrameName_s().c_str(), getInSlotFrameName().c_str(), ui::Widget::TextureResType::PLIST);
        item->setAmount( getAmount() );
        item->setPosition(Vec2(_owner->getPosition().x + 50.0f, _owner->getPosition().y));
        _gameMgr->registEntity(item, _gameMgr->getNextValidID(), Z_ORDER_ITEMS);
    }
    
}







