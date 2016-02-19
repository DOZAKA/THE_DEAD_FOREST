//
//  ParseStructures.hpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 28..
//
//

#pragma once

#include "cocos2d.h"
#include "EntityType.hpp"

using namespace cocos2d;

namespace realtrick
{
    
    struct NameCoord
    {
        std::string name;
        Vec2 pos;
        
        NameCoord()
        {
            pos = Vec2::ZERO;
        }
        
        NameCoord(std::string name, Vec2 pos) : name(name), pos(pos)
        {}
        
        NameCoord(const NameCoord& rhs) : name(rhs.name), pos(rhs.pos)
        {}
        
        NameCoord operator=(const NameCoord& rhs)
        {
            if(&rhs == this)
                return *this;
            name = rhs.name;
            pos = rhs.pos;
            return *this;
        }
        
    };
    
    struct NameCoordAmount
    {
        std::string name;
        Vec2 pos;
        int amount;
        
        NameCoordAmount()
        {
            pos = Vec2::ZERO;
        }
        
        NameCoordAmount(std::string name, Vec2 pos, int amount) : name(name), pos(pos), amount(amount)
        {}
        
        NameCoordAmount(const NameCoordAmount& rhs) : name(rhs.name), pos(rhs.pos), amount(rhs.amount)
        {}
        
        NameCoordAmount operator=(const NameCoordAmount& rhs)
        {
            if(&rhs == this)
                return *this;
            name = rhs.name;
            pos = rhs.pos;
            amount = rhs.amount;
            return *this;
        }
    };

}



















