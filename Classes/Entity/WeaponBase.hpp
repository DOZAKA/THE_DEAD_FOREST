//
//  WeaponBase.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 13..
//
//

#pragma once

#include "ItemBase.hpp"

namespace realtrick
{
    
    class EntityHuman;
    class PureWeaponBase;
    
    class WeaponBase : public ItemBase
    {
     
    public:
        
        WeaponBase(GameManager* mgr);
        
        WeaponBase(const WeaponBase& rhs);
        
        virtual ~WeaponBase();
        
        int getMaxRounds() const { return _maxRounds; }
        
        void setMaxRounds(int rounds) { _maxRounds = rounds; }
        
        int getNumOfLeftRounds() const { return _numOfLeftRounds; }
        
        void setNumOfLeftRounds(int rounds) { _numOfLeftRounds = rounds; }
        
        int getDamage() const { return _damage; }
        
        void setDamage(int dam) { _damage = dam; }
        
        float getRange() const { return _range; }
        
        void setRange(float range) { _range = range; }
        
        virtual void use() override final;
        
        virtual void releaseWeapon() override final;
        
        virtual void inWeapon() = 0;
        
        virtual void outWeapon() = 0;
        
        virtual void attack() = 0;
        
        virtual ItemBase* clone() const override = 0;
        
        virtual void discard() override = 0;
        
    protected:
        
        int                         _numOfLeftRounds;
        
        int                         _maxRounds;
        
        int                         _damage;
        
        float                       _range;
        
    };
    
}







