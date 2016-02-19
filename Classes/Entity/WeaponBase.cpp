//
//  WeaponBase.cpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 13..
//
//

#include "WeaponBase.hpp"
#include "EntityHuman.hpp"

using namespace cocos2d;

namespace realtrick
{
    
    WeaponBase::WeaponBase(GameManager* mgr) : ItemBase(mgr),
    _numOfLeftRounds(0),
    _maxRounds(0),
    _damage(0),
    _range(0)
    {
        ADD_FAMILY_MASK(_familyMask, WEAPON_BASE);
        setMaxBandedNumber(1);
    }
    
    
    WeaponBase::~WeaponBase()
    {
    }
    
    
    WeaponBase::WeaponBase(const WeaponBase& rhs) : ItemBase(rhs)
    {
        _numOfLeftRounds = rhs._numOfLeftRounds;
        _maxRounds = rhs._maxRounds;
        _damage = rhs._damage;
        _range = rhs._range;
    }
    
    
    void WeaponBase::use()
    {
        log("<WeaponBase::use> Weapon(%d) Equiped.", _entityType);
        if( _owner->getEquipedWeapon() == nullptr )
        {
            // 주먹일 때, 주먹을 집어넣고 무기를 세팅한다.
            _owner->getFSM()->changeState(&HumanFistIn::getInstance());
            _owner->setEquipedWeapon(this);
        }
        else
        {
            // 장착 중인 무기를 집어넣고, 장착 무기를 바꾼다.
            _owner->getEquipedWeapon()->inWeapon();
            _owner->setEquipedWeapon(this);
        }
    }
    
    
    void WeaponBase::releaseWeapon()
    {
        log("<WeaponBase::releaseWeapon> Weapon(%d) Released.", _entityType);
        
        // 장착 무기를 nullptr(맨손)으로 만든다.
        _owner->setEquipedWeapon(nullptr);
        // 무기를 집어넣는다.
        inWeapon();
    }
    
}







