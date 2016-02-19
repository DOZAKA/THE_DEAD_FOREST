//
//  ItemBase.cpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 13..
//
//

#include "ItemBase.hpp"

using namespace cocos2d;

namespace realtrick
{
    
    ItemBase::ItemBase(GameManager* mgr) :
    EntityBase(mgr),
    _owner(nullptr),
    _amount(0),
    _maxBandedNumber(0),
    _inSlotFrameName("#NO NAME"),
    _inSlotSpriteSize(Size::ZERO),
    _inGameImageName_n("#NO NAME"),
    _inGameImageName_s("#NO NAME"),
    _information("#NO NAME"),
    _inGameImage_n(nullptr),
    _inGameImage_s(nullptr),
    _inSlotImage(nullptr)
    {
        ADD_FAMILY_MASK(_familyMask, ITEM_BASE);
    }
    
    
    ItemBase::~ItemBase()
    {
        _owner = nullptr;
        _inGameImage_n = nullptr;
        _inGameImage_s = nullptr;
        _inSlotImage = nullptr;
    }
    
    ItemBase::ItemBase(const ItemBase& rhs) : EntityBase(rhs)
    {
        _owner = rhs._owner;
        _amount = rhs._amount;
        _maxBandedNumber = rhs._maxBandedNumber;
        _inSlotFrameName = rhs._inSlotFrameName;
        _inSlotSpriteSize = rhs._inSlotSpriteSize;
        _inGameImageName_n = rhs._inGameImageName_n;
        _inGameImageName_s = rhs._inGameImageName_s;
        _information = rhs._information;
        _inGameImage_n = nullptr;
        _inGameImage_s = nullptr;
        _inSlotImage = nullptr;
    }
    
    
    bool ItemBase::init(const char* inGameImage_n, const char* inGameImage_s, const char* inSlotImage, cocos2d::ui::Widget::TextureResType texResType)
    {
        if( texResType == ui::Widget::TextureResType::LOCAL )
        {
            _inGameImage_n = Sprite::create(inGameImage_n);
            _inGameImage_s = Sprite::create(inGameImage_s);
            _inSlotImage = Sprite::create(inSlotImage);
        }
        else if ( texResType == ui::Widget::TextureResType::PLIST )
        {
            _inGameImage_n = Sprite::createWithSpriteFrameName(inGameImage_n);
            _inGameImage_s = Sprite::createWithSpriteFrameName(inGameImage_s);
            _inSlotImage = Sprite::createWithSpriteFrameName(inSlotImage);
        }
        
        _inGameImage_n->setCameraMask((unsigned short)CameraFlag::USER1);
        _inGameImage_s->setCameraMask((unsigned short)CameraFlag::USER1);
        _inGameImage_s->setVisible(false);
        _inSlotImage->setVisible(false);
        
        addChild(_inGameImage_n);
        
        setInSlotFrameName(inSlotImage);
        setInSlotSpriteSize(_inSlotImage->getContentSize());
        setInGameFrameName_n(inGameImage_n);
        setInGameFrameName_s(inGameImage_s);
        
        return true;
    }

}







