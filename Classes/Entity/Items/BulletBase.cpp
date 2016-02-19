//
//  BulletBase.cpp
//  TheDeadForest
//
//  Created by mac on 2016. 2. 3..
//
//

#include "BulletBase.hpp"

namespace realtrick
{
    
    BulletBase::BulletBase(GameManager* mgr) : ItemBase(mgr)
    {
        ADD_FAMILY_MASK(_familyMask, BULLET_BASE);
    }
    
    BulletBase::BulletBase(const BulletBase& rhs) : ItemBase(rhs)
    {
        
    }
    
    BulletBase::~BulletBase()
    {
        
    }
}