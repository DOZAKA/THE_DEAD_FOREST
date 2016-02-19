//
//  EntityHuman.cpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 15..
//
//

#include "EntityHuman.hpp"
#include "HumanOwnedAnimations.hpp"
#include "HumanOwnedStates.hpp"
#include "ParamLoader.hpp"
#include "GameManager.hpp"
#include "ItemGlock17.hpp"
#include "GameWorld.hpp"
#include "Items.hpp"

using namespace cocos2d;

namespace realtrick
{

    EntityHuman::EntityHuman(GameManager* mgr) : DynamicEntity(mgr),
    _FSM(nullptr),
    _bodyAnimationPlayer(nullptr),
    _footAnimationPlayer(nullptr),
    _footHeading(Vec2::UNIT_X),
    _footTargetHeading(Vec2::UNIT_X),
    _footTurnSpeed(270.0f),
    _crossHair(nullptr),
    _isWeaponEquipCompletly(false),
    _equipedWeapon(nullptr),
    _inputMask(0),
    _blood(0),
    _maxBlood(0),
    _isAlive(false),
    _isFovOn(false),
    _bodyRot(0.0f),
    _walkSpeed(75.0f),
    _runSpeed(200.0f),
    _noEventTime(0.0f),
    _enduranceTime(0.0f)
    {
        setEntityType(ENTITY_HUMAN);
        setBoundingRadius(20.0f);
    }
    
    
    EntityHuman::~EntityHuman()
    {
        CC_SAFE_DELETE(_bodyAnimationPlayer);
        CC_SAFE_DELETE(_FSM);
    }
    
    bool EntityHuman::init()
    {
        _bodyAnimationPlayer = new AnimationPlayer(this, &AnimHumanFistIdleLoop::getInstance(), 4);
        
        _FSM = new StateMachine<EntityHuman>(this);
        _FSM->setCurrState(&HumanFistIdleLoop::getInstance());
        _FSM->changeState(&HumanFistIdleLoop::getInstance());
        
        _crossHair = Sprite::create("cross_hair.png");
        _crossHair->setCameraMask((unsigned short)CameraFlag::USER1);
        _crossHair->setOpacity(0);
        _crossHair->setVisible(false);
        addChild(_crossHair);
                                    
        _maxBlood = Prm.getValueAsInt("maxBlood");
        _blood = _maxBlood;
        
        setAlive();
        
        _enduranceTime  = 5.0f;
        
        return true;
    }
    
    
    EntityHuman* EntityHuman::create(GameManager* mgr)
    {
        EntityHuman* ret = new (std::nothrow)EntityHuman(mgr);
        if (ret && ret->init())
        {
            ret->autorelease();
            return ret;
        }
        else
        {
            delete ret;
            ret = nullptr;
            return nullptr;
        }
    }
    
    void EntityHuman::update(float dt)
    {
        moveEntity();
        rotateEntity();
        
        if ( _FSM ) _FSM->update(dt);
        if ( _bodyAnimationPlayer) _bodyAnimationPlayer->processAnimation(dt);
        if ( _equipedWeapon && _isWeaponEquipCompletly )
        {
            _crossHair->setPosition(getHeading() * _equipedWeapon->getRange());
        }
    }

    
    void EntityHuman::setDead()
    {
        _isAlive = false;
    }
    
    
    
    void EntityHuman::setAlive()
    {
        _isAlive = true;
        _blood = _maxBlood;
    }
    
    
    
    bool EntityHuman::handleMessage(const Telegram& msg)
    {
        return _FSM->handleMessage(msg);
    }
    
    
    bool EntityHuman::isIntersectOther(const cocos2d::Vec2& futurePosition, EntityBase* other)
    {
        
        // TODO
        //_gameMgr->getGameMap()->getModerateTileIndex(futurePosition);
        
        if ( other->getEntityType() == ENTITY_HUMAN )
        {
            if( physics::intersect(Circle(futurePosition, 20.0f), Circle(other->getWorldPosition(), 20.0f)) )
            {
                return true;
            }
        }
        else if ( isMasked(other->getFamilyMask(), ITEM_BASE) )
        {
            //                if( physics::intersect(Circle(getPosition(), 15.0f), Circle(d->getPosition(), 15.0f)) )
            //                {
            //                    InventoryEx* inventory = _gameMgr->getGameWorld()->getInventory();
            //                    ItemBase* item = (ItemBase*)d;
            //                    item->setOwner(this);
            //                    int oldAmount = item->getAmount();
            //                    int remainAmount = inventory->pushItemAndReturnRemainAmount(item); // 아이템을 먹고 남은 갯수를 반환받는다.
            //                    if ( remainAmount != oldAmount )
            //                    {
            //                        // 아이템의 갯수에 변동이 있으면 (1개 이상 먹혔으면)
            //                        item->setAmount(remainAmount);
            //                        if( remainAmount == 0 )
            //                        {
            //                            // 남은 갯수가 0개면 (모두 먹었으면) 아이템은 없앤다.
            //                            _gameMgr->removeEntity(item->getTag());
            //                        }
            //                    }
            //                    else
            //                    {
            //                        // 못 먹는 경우면,
            //                        log("<EntityHuman::moveEntoty> Can not get item. (no slot)");
            //                    }
            //                    break;
            //                }
        }
        
        return false;
    }
    
    
    bool EntityHuman::isIntersectWall(const cocos2d::Vec2& futurePosition, const Polygon& wall)
    {
        for( int i = 0 ; i < wall.vertices.size() - 1 ; ++ i)
        {
            if ( physics::intersect(Circle(futurePosition, getBoundingRadius()), Segment(wall.vertices[i], wall.vertices[i + 1])) )
            {
//                TODO: sliding
//                Vec2 wallNormal = (wall.vertices[i + 1] - wall.vertices[i]).getRPerp().getNormalized();
//                Vec2 sliding = getMoving() + (-getMoving().dot(wallNormal) * wallNormal);
//                setMoving(sliding);
                return true;
            }
        }
        if ( physics::intersect(Circle(futurePosition, getBoundingRadius()), Segment(wall.vertices.back(), wall.vertices.front())) )
        {
            return true;
        }
        
        return false;
    }
    
    
    void EntityHuman::rotateEntity()
    {
        if ( _heading.dot(_targetHeading) < 0.995f )
        {
            float dt = Director::getInstance()->getDeltaTime();
            
            float d = _heading.cross(_targetHeading);
            if( d > 0 )
            {
                Mat3 rotMat;
                rotMat.rotate(MATH_DEG_TO_RAD(_turnSpeed * dt));
                _heading = rotMat.getTransformedVector(_heading);
            }
            else
            {
                Mat3 rotMat;
                rotMat.rotate(-MATH_DEG_TO_RAD(_turnSpeed * dt));
                _heading = rotMat.getTransformedVector(_heading);
            }
        }
        
        setBodyRot(-physics::getAngleFromZero(_heading));
    }
    
}





