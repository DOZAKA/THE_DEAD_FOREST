//
//  BulletBase.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 2. 3..
//
//

#pragma once

#include "ItemBase.hpp"

namespace realtrick
{
    
    class BulletBase : public ItemBase
    {
        
    public:
        
        BulletBase(GameManager* mgr);
        
        BulletBase(const BulletBase& rhs);
        
        virtual ~BulletBase();

        virtual ItemBase* clone() const override = 0;
        
        virtual void use() override {}
        
        virtual void discard() override = 0;
        
    protected:
        
        
        
    };
    
}