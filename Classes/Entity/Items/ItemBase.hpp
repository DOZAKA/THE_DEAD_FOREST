//
//  ItemBase.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 13..
//
//

#pragma once

#include "EntityBase.hpp"
#include "CocosGUI.h"

namespace realtrick
{
    
    class EntityHuman;
    class GameManager;
    
    class ItemBase : public EntityBase
    {
        
    public:
        
        ItemBase(GameManager* mgr);
        ItemBase(const ItemBase& rhs);
        virtual ~ItemBase();
        
        void setOwner(EntityHuman* owner) { _owner=  owner; }
        
        void setAmount(int amount) { _amount = amount; }
        
        void setInSlotFrameName(const std::string& name) { _inSlotFrameName = name; }
        
        void setInSlotSpriteSize(const cocos2d::Size& size) { _inSlotSpriteSize = size; }
        
        EntityHuman* getOwner() const { return _owner; }
        
        int getAmount() const { return _amount; }
        
        std::string getInSlotFrameName() const { return _inSlotFrameName; }
        
        cocos2d::Size getInSlotSpriteSize() const { return _inSlotSpriteSize; }
        
        std::string getInfomation() const { return _information; }
        
        void setInformation(const std::string& info) { _information = info; }
        
        void setInGameFrameName_n(const std::string& name) { _inGameImageName_n = name; }
        
        void setInGameFrameName_s(const std::string& name) { _inGameImageName_s = name; }
        
        std::string getInGameFrameName_n() const { return _inGameImageName_n; }
        
        std::string getInGameFrameName_s() const { return _inGameImageName_s; }
        
        void setMaxBandedNumber(int num) { _maxBandedNumber = num; }
        
        int getMaxBandedNumber() const { return _maxBandedNumber; }
        
        virtual ItemBase* clone() const = 0;
        
        virtual void use() = 0;
        
        virtual void discard() = 0;
        
        virtual void releaseWeapon() {}
        
    protected:
        
        EntityHuman*                    _owner;
        
        int                             _amount;
        
        int                             _maxBandedNumber;
        
        std::string                     _inSlotFrameName;
        
        cocos2d::Size                   _inSlotSpriteSize;
        
        std::string                     _inGameImageName_n;
        
        std::string                     _inGameImageName_s;
        
        std::string                     _information;
        
        cocos2d::Sprite*                _inGameImage_n;
        
        cocos2d::Sprite*                _inGameImage_s;
        
        cocos2d::Sprite*                _inSlotImage;
        
    protected:
        
        bool init(const char* inGameImage_n, const char* inGameImage_s, const char* inSlotImage, cocos2d::ui::Widget::TextureResType texResType);

    };
    
}