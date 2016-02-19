//
//  EntityBase.cpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 3..
//
//

#include "EntityBase.hpp"
#include "GameWorld.hpp"
#include "GameManager.hpp"
#include "Camera2D.hpp"

namespace realtrick
{
    EntityBase::EntityBase(GameManager* gameMgr) :
    _gameMgr(gameMgr),
    _familyMask(0),
    _entityType(0)
    {
        ADD_FAMILY_MASK(_familyMask, ENTITY_BASE);
    }
    
    EntityBase::EntityBase(const EntityBase& rhs)
    {
        _gameMgr = rhs._gameMgr;
        _familyMask = rhs._familyMask;
        _entityType = rhs._entityType;
    }
    
    void EntityBase::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
    {
        setPosition( getWorldPosition() - _gameMgr->getGameWorld()->getGameCamera()->getCameraPos() );
        Node::visit(renderer, transform, flags);
    }
    
}