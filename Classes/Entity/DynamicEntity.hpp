//
//  DynamicEntity.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 2..
//
//

#pragma once

#include "cocos2d.h"
#include "EntityBase.hpp"
#include "Physics.hpp"

namespace realtrick
{
    
    class GameManager;
    
    class DynamicEntity : public EntityBase
    {
        
    public:
        
        DynamicEntity(GameManager* gameMgr);
        
        virtual ~DynamicEntity();
        
        cocos2d::Vec2 getHeading() const                            { return _heading; }
        
        inline void setHeading(const cocos2d::Vec2 heading);
        
        cocos2d::Vec2 getTargetHeading() const                      { return _targetHeading; }
        
        void setTargetHeading(const cocos2d::Vec2& target)          { _targetHeading = target; }
        
        cocos2d::Vec2 getLeft() const                               { return _left; }
        
        cocos2d::Vec2 getRight() const                              { return _right; }
        
        cocos2d::Vec2 getMoving() const                             { return _moving; }
        
        void setMoving(const cocos2d::Vec2& moving)                 { _moving = moving; }
        
        cocos2d::Vec2 getVelocity() const                           { return _velocity; }
        
        void setVelocity(const cocos2d::Vec2 velocity)              { _velocity = velocity; }
        
        cocos2d::Vec2 getForce() const                              { return _force; }
        
        void setForce(const cocos2d::Vec2 force)                    { _force = force; }
        
        cocos2d::Vec2 getAcceleration() const                       { return _acceleration; }
        
        void setAcceleration(const cocos2d::Vec2 ac)                { _acceleration = ac; }
        
        float getMass() const                                       { return _mass; }
        
        void setMass(float mass)                                    { _mass = mass; }
        
        float getMaxSpeed() const                                   { return _maxSpeed; }
        
        void setMaxSpeed(float maxSpeed)                            { _maxSpeed = maxSpeed; }
        
        float getTurnSpeed() const                                  { return _turnSpeed; }
        
        void setTurnSpeed(float speed)                              { _turnSpeed = speed; }
        
        float getBoundingRadius() const                             { return _boundingRadius; }
        
        void setBoundingRadius(float r)                             { _boundingRadius = r; }
        
        virtual bool handleMessage(const Telegram& msg) override    { return false; }
        
        virtual void update(float dt) override {}
        
        virtual void moveEntity() final;
        
        virtual bool isIntersectOther(const cocos2d::Vec2& futurePosition, EntityBase* other) { return true; }
        
        virtual bool isIntersectWall(const cocos2d::Vec2& futurePosition, const Polygon& wall) { return true; }
        
        virtual void rotateEntity() {}
        
    protected:
        
        cocos2d::Vec2               _heading;
        
        cocos2d::Vec2               _targetHeading;
        
        cocos2d::Vec2               _moving;
        
        cocos2d::Vec2               _left;
        
        cocos2d::Vec2               _right;
        
        cocos2d::Vec2               _velocity;
        
        cocos2d::Vec2               _force;
        
        cocos2d::Vec2               _acceleration;
        
        float                       _mass;
        
        float                       _maxSpeed;
        
        float                       _turnSpeed;
        
        float                       _boundingRadius;
        
    };
    
    inline void DynamicEntity::setHeading(const cocos2d::Vec2 heading)
    {
        _heading = heading;
        _heading.normalize();
        _left = _heading.getPerp();
        _right = _heading.getRPerp();
    }

}






