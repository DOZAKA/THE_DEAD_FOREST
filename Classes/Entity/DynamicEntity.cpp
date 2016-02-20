//
//  DynamicEntity.cpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 2..
//
//

#include "DynamicEntity.hpp"
#include "GameManager.hpp"

using namespace cocos2d;

namespace realtrick
{
    DynamicEntity::DynamicEntity(GameManager* gameMgr) :
    EntityBase(gameMgr),
    _heading(Vec2::UNIT_X),
    _targetHeading(Vec2::UNIT_X),
    _moving(Vec2::UNIT_X),
    _left(Vec2::ZERO),
    _right(Vec2::ZERO),
    _velocity(Vec2::ZERO),
    _force(Vec2::ZERO),
    _acceleration(Vec2::ZERO),
    _mass(1.0f),
    _maxSpeed(0.0f),
    _turnSpeed(0.0f),
    _boundingRadius(0.0f)
    {
        ADD_FAMILY_MASK(_familyMask, DYNAMIC_ENTITY);
    }
    
    DynamicEntity::~DynamicEntity()
    {
        
    }
    
    void DynamicEntity::moveEntity()
    {
        if ( getVelocity() == Vec2::ZERO ) return ;
        
        float dt = Director::getInstance()->getDeltaTime();
        cocos2d::Vec2 oldPos = getWorldPosition();
        cocos2d::Vec2 futurePosition = getWorldPosition() + getVelocity() * dt;
        float speed = getVelocity().getLength();
        bool intersectResult = false;
        
        // only player debug
        if ( this == _gameMgr->getPlayerPtr() && _gameMgr->getDebugNode()->isVisible() )
        {
            _gameMgr->getDebugNode()->drawRect(_gameMgr->worldToLocal(Vec2(getWorldPosition().x - speed / 2, getWorldPosition().y - speed / 2) ),
                                               _gameMgr->worldToLocal(Vec2(getWorldPosition().x + speed / 2, getWorldPosition().y + speed / 2) ), Color4F::YELLOW);
        }
        
        // 엔티티들과의 충돌처리
        const std::list<EntityBase*> members = _gameMgr->getNeighborsOnMove(oldPos, speed);
        for ( const auto &entity : members )
        {
            // debug node
            if ( _gameMgr->getDebugNode()->isVisible() )
            {
                _gameMgr->getDebugNode()->drawCircle(_gameMgr->worldToLocal(entity->getWorldPosition()), 20.0f, 360, 30, false, Color4F::YELLOW);
            }
            
            if ( entity == this ) continue;
            
            if ( isIntersectOther(futurePosition, entity) )
            {
                intersectResult = true;
            }
            
        }
        
        // 벽과의 충돌처리
        const std::vector<Polygon> walls = _gameMgr->getNeighborWalls(futurePosition, speed);
        for( const auto& wall : walls )
        {
            if ( isIntersectWall(futurePosition, wall) )
            {
                intersectResult = true;
            }
        }
        
        // debug node
        if ( _gameMgr->getDebugNode()->isVisible() )
        {
            for( auto& wall : walls )
            {
                for(int i = 0 ; i < wall.vertices.size() - 1; ++ i)
                {
                    _gameMgr->getDebugNode()->drawSegment(_gameMgr->worldToLocal(wall.vertices[i]), _gameMgr->worldToLocal(wall.vertices[i + 1]), 1.0f, Color4F::MAGENTA);
                }
                _gameMgr->getDebugNode()->drawSegment(_gameMgr->worldToLocal(wall.vertices.back()), _gameMgr->worldToLocal(wall.vertices.front()), 1.0f, Color4F::MAGENTA);
            }
        }
        
        if ( !intersectResult )
        {
            setWorldPosition(futurePosition);
            _gameMgr->getCellSpace()->updateEntity(this, oldPos);
        }
    }
    
}





